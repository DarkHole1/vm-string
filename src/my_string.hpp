#pragma once
#include <cstdlib>
#include <iostream>

namespace my
{
    class string1
    {
    private:
        mutable char *ptr;
        void mark_not_unique() const;
        char *get_non_const();
        void free_ptr();
    public:
        string1();
        string1(const char *ptr);

        string1(const char *ptr_, size_t len);
        string1(string1 &&other);
        string1(const string1 &other);
        string1 &operator=(string1 &&other);
        string1 &operator=(const string1 &other);
        ~string1();

        const char *get() const;
        bool is_unique() const;
        friend std::ostream &operator<<(std::ostream &os, const string1 &p);
    };

    std::ostream &operator<<(std::ostream &os, const my::string1 &str);
}
