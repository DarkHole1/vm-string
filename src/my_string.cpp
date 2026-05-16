#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <iostream>

namespace my
{
    class string1
    {
    private:
        mutable char *ptr;

        void mark_not_unique() const
        {
            ptr = reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(ptr) | 1);
        }

        char *get_non_const()
        {
            return reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(ptr) & (~1));
        }

        void free_ptr()
        {
#ifdef DEBUG
            printf("Starting check for ptr %p and bit %b\n", get(), unique());
#endif
            if (unique())
            {
#ifdef DEBUG
                printf("Starting deallocation\n");
#endif
                free(get_non_const());
            }
        }

    public:
        string1()
        {
#ifdef DEBUG
            printf("Creating empty string\n");
#endif
            ptr = nullptr;
        }

        string1(const char *ptr) : string1(ptr, ptr == nullptr ? 0 : strlen(ptr))
        {
        }

        string1(const char *ptr_, size_t len)
        {
#ifdef DEBUG
            printf("Creating by string and length\n");
#endif
            if (ptr_ == nullptr)
            {
                ptr = nullptr;
            }
            else
            {
                auto allocated = malloc(len);
                memcpy(allocated, ptr_, len);
                ptr = reinterpret_cast<char *>(allocated);
            }
        }

        // Move constructor
        string1(string1 &&other) : ptr(other.ptr)
        {
#ifdef DEBUG
            printf("Move constructor from %p [%b]\n", other.get(), other.unique());
#endif
            other.ptr = nullptr;
        }

        // Copy constructor
        string1(const string1 &other) : ptr(other.ptr)
        {
#ifdef DEBUG
            printf("Copy constructor from %p [%b]\n", other.get(), other.unique());
#endif
            mark_not_unique();
            other.mark_not_unique();
        }

        string1 &operator=(string1 &&other)
        {
#ifdef DEBUG
            printf("Set move from %p [%b]\n", other.get(), other.unique());
#endif
            free_ptr();

            ptr = other.ptr;
            other.ptr = nullptr;
            return *this;
        }

        string1 &operator=(const string1 &other)
        {
#ifdef DEBUG
            printf("Set copy from %p [%b]\n", other.get(), other.unique());
#endif
            if (other.ptr != ptr)
            {
                free_ptr();

                other.mark_not_unique();
                ptr = other.ptr;
            }
            return *this;
        }

        ~string1()
        {
            free_ptr();
        }

        const char *get() const
        {
            return reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(ptr) & (~1));
        }

        bool unique() const
        {
            return !(reinterpret_cast<uintptr_t>(ptr) & 1);
        }

        friend std::ostream &operator<<(std::ostream &os, const string1 &p);
    };

    std::ostream &operator<<(std::ostream &os, const my::string1 &str)
    {
        os << reinterpret_cast<const char *>(str.get()) << " [" << str.unique() << "]";
        return os;
    }
}
