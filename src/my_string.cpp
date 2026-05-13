#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <iostream>

namespace my
{
    class string1
    {
    private:
        uintptr_t ptr;

        void set_bit(bool bit)
        {
            ptr = ptr | (bit ? 1 : 0);
        }

        void free_ptr()
        {
#ifdef DEBUG
            printf("Starting check for ptr %p and bit %b\n", get(), get_bit());
#endif
            if (!get_bit() && get() != nullptr)
            {
#ifdef DEBUG
                printf("Starting deallocation\n");
#endif
                free(get());
            }
        }

    public:
        string1()
        {
#ifdef DEBUG
            printf("Creating empty string\n");
#endif
            ptr = 0;
        }

        string1(const char *ptr) : string1(ptr, strlen(ptr))
        {
        }

        string1(const char *ptr_, size_t len)
        {
#ifdef DEBUG
            printf("Creating by string and length\n");
#endif
            auto allocated = malloc(len);
            memcpy(allocated, ptr_, len);
            ptr = reinterpret_cast<uintptr_t>(allocated);
        }

        // Move constructor
        string1(string1 &&other) : ptr(other.ptr)
        {
#ifdef DEBUG
            printf("Move constructor\n");
#endif
            other.ptr = 0;
        }

        // Copy constructor
        string1(string1 &other) : ptr(other.ptr)
        {
#ifdef DEBUG
            printf("Copy constructor\n");
#endif
            set_bit(true);
            other.set_bit(true);
        }

        string1 &operator=(string1 &&other)
        {
#ifdef DEBUG
            printf("Set move\n");
#endif
            free_ptr();

            ptr = other.ptr;
            other.ptr = 0;
            return *this;
        }

        string1 &operator=(string1 &other)
        {
#ifdef DEBUG
            printf("Set copy\n");
#endif
            free_ptr();

            other.set_bit(true);
            ptr = other.ptr;
            return *this;
        }

        ~string1()
        {
            free_ptr();
        }

        char *get() const
        {
            return reinterpret_cast<char *>(ptr & (~1));
        }

        bool get_bit() const
        {
            return ptr & 1;
        }

        friend std::ostream &operator<<(std::ostream &os, const string1 &p);
    };

    std::ostream &operator<<(std::ostream &os, const my::string1 &str)
    {
        os << reinterpret_cast<void *>(str.get()) << " [" << str.get_bit() << "]";
        return os;
    }
}
