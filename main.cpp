#include <iostream>
#include <cstdlib>
#include <ctime>
#include "include/array.hpp"

int main()
{
    rays::Array<int, 10> arr;
    for (const auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    int counter{};
    for (auto &i : arr) {
        i = counter++;
    }
    for (const auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::srand(std::time(nullptr));
    for (auto &i : arr) {
        i = std::rand();
    }
    for (const auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
