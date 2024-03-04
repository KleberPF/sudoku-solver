#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <array>

// For now, the array will always be 9 x 9
template <typename T>
class Array2D
{
public:
    Array2D(){};

    T& operator()(size_t row, size_t col)
    {
        return this->cells_[row * 9 + col];
    }

    const T& operator()(size_t row, size_t col) const
    {
        return this->cells_[row * 9 + col];
    }

private:
    std::array<T, 9 * 9> cells_ = {};
};

#endif  // ARRAY2D_H
