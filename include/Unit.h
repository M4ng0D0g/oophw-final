#pragma once

#include <cstddef>
#include <vector>

struct Pos2 {
    int x;
    int y;
};

struct Size2 {
    size_t width;
    size_t height;
};

template <typename T>
using Vector2 = std::vector<std::vector<T>>;

template <typename T>
using Vector1 = std::vector<T>;

enum class Direction { STOP, UP, LEFT, DOWN, RIGHT, COUNT };

