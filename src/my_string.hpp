#pragma once
#include <cstdlib>
#include <iostream>
#include <cstdint>

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
            printf("Starting check for ptr %p and bit %b\n", get(), is_unique());
#endif
            if (is_unique())
            {
#ifdef DEBUG
                printf("Starting deallocation\n");
#endif
                free(get_non_const());
            }
        }

    public:
        string1();
        string1(const char *ptr);

        string1(const char *ptr_, size_t len);
        string1(string1 &&other);
        string1(const string1 &other);
        string1 &operator=(string1 &&other);
        string1 &operator=(const string1 &other);
        ~string1();

        const char *get() const
        {
            return reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(ptr) & (~1));
        }

        bool is_unique() const
        {
            return !(reinterpret_cast<uintptr_t>(ptr) & 1);
        }
        friend std::ostream &operator<<(std::ostream &os, const string1 &p);
    };

    std::ostream &operator<<(std::ostream &os, const my::string1 &str);
}
