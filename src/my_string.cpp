#pragma once
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <iostream>

namespace my
{
    class string1
    {
    private:
        char *ptr;
        bool *unique_;

        void mark_not_unique() const
        {
            *unique_ = false;
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
                free(ptr);
                free(unique_);
            }
        }

    public:
        string1()
        {
#ifdef DEBUG
            printf("Creating empty string\n");
#endif
            ptr = nullptr;
            unique_ = nullptr;
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
                unique_ = nullptr;
            }
            else
            {
                auto allocated = malloc(len);
                if (allocated == nullptr) {
                    exit(EXIT_FAILURE);
                }

                memcpy(allocated, ptr_, len);
                ptr = reinterpret_cast<char *>(allocated);

                unique_ = reinterpret_cast<bool *>(malloc(sizeof(bool)));
                if (unique_ == nullptr) {
                    exit(EXIT_FAILURE);
                }
                *unique_ = true;
            }
        }

        // Move constructor
        string1(string1 &&other) : ptr(other.ptr), unique_(other.unique_)
        {
#ifdef DEBUG
            printf("Move constructor from %p [%b]\n", other.get(), other.unique());
#endif
            other.ptr = nullptr;
            other.unique_ = reinterpret_cast<bool *>(malloc(sizeof(bool)));
            *unique_ = true;
        }

        // Copy constructor
        string1(const string1 &other) : ptr(other.ptr), unique_(other.unique_)
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
            unique_ = other.unique_;
            other.ptr = nullptr;
            other.unique_ = nullptr;

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
                unique_ = other.unique_;
            }
            return *this;
        }

        ~string1()
        {
            free_ptr();
        }

        const char *get() const
        {
            return ptr;
        }

        bool unique() const
        {
            if (unique_ != nullptr)
            {
                return *unique_;
            }
            return false;
        }

        friend std::ostream &operator<<(std::ostream &os, const string1 &p);
    };

    std::ostream &operator<<(std::ostream &os, const my::string1 &str)
    {
        os << reinterpret_cast<const void *>(str.get()) << " [" << str.unique() << "]";
        return os;
    }
}
