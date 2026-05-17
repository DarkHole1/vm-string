#include "my_string.hpp"
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <iostream>

namespace my
{
    string1::string1()
    {
#ifdef DEBUG
        printf("Creating empty string\n");
#endif
        ptr = nullptr;
    }

    string1::string1(const char *ptr) : string1(ptr, ptr == nullptr ? 0 : strlen(ptr))
    {
    }

    string1::string1(const char *ptr_, size_t len)
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
            if (allocated == nullptr)
            {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }

            memcpy(allocated, ptr_, len);
            ptr = reinterpret_cast<char *>(allocated);
        }
    }

    // Move constructor
    string1::string1(string1 &&other) : ptr(other.ptr)
    {
#ifdef DEBUG
        printf("Move constructor from %p [%b]\n", other.get(), other.is_unique());
#endif
        other.ptr = nullptr;
    }

    // Copy constructor
    string1::string1(const string1 &other) : ptr(other.ptr)
    {
#ifdef DEBUG
        printf("Copy constructor from %p [%b]\n", other.get(), other.is_unique());
#endif
        mark_not_unique();
        other.mark_not_unique();
    }

    string1 &string1::operator=(string1 &&other)
    {
#ifdef DEBUG
        printf("Set move from %p [%b]\n", other.get(), other.is_unique());
#endif
        free_ptr();

        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    string1 &string1::operator=(const string1 &other)
    {
#ifdef DEBUG
        printf("Set copy from %p [%b]\n", other.get(), other.is_unique());
#endif
        if (other.ptr != ptr)
        {
            free_ptr();

            other.mark_not_unique();
            ptr = other.ptr;
        }
        return *this;
    }

    string1::~string1()
    {
        free_ptr();
    }

    std::ostream &operator<<(std::ostream &os, const my::string1 &str)
    {
        os << reinterpret_cast<const void *>(str.get()) << " [" << str.is_unique() << "]";
        return os;
    }
}
