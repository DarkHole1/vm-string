#include <iostream>
#include <algorithm>
#include <random>
#include "my_string.cpp"

const int ARRAY_SIZE = 10;

void bubble_sort(my::string1 *arr, int len)
{
    bool not_sorted = true;
    while (not_sorted)
    {
        not_sorted = false;
        for (int j = 0; j < len - 1; j++)
        {
            if (arr[j].get() > arr[j + 1].get())
            {
                std::swap(arr[j], arr[j + 1]);
                not_sorted = true;
            }
        }
    }
}

int main()
{
    my::string1 s = "123\n";
    std::cout << s << "\n";

    my::string1 s2 = s;
    std::cout << s << " " << s2 << "\n";

    my::string1 s3 = "123\n";
    my::string1 s4 = std::move(s3);
    std::cout << s3 << " " << s4 << "\n";

    my::string1 s5 = "123\n";
    std::cout << s5 << " " << s2 << "\n";
    std::swap(s5, s2);
    std::cout << s5 << " " << s2 << "\n";

    my::string1 *arr = new my::string1[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        char buffer[128];
        sprintf(buffer, "%d", i);

        arr[i] = buffer;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(arr, arr + ARRAY_SIZE, g);

    std::cout << "Arr (shuffled):\n";
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        std::cout << arr[i] << "\n";
    }

    bubble_sort(arr, ARRAY_SIZE);

    std::cout << "Arr (sorted):\n";
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        std::cout << arr[i] << "\n";
    }

    return EXIT_SUCCESS;
}