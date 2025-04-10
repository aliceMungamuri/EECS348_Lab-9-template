#include <iostream>
#include <fstream>
#include <iomanip>
#include "matrix.hpp"

// Constructor with size
Matrix::Matrix(std::size_t N) : size(N), data(N, std::vector<int>(N)) {}

// Constructor with pre-defined vector
Matrix::Matrix(std::vector<std::vector<int>> nums) : size(nums.size()), data(nums) {}

// Get element
int Matrix::get_value(std::size_t i, std::size_t j) const {
    return data[i][j];
}

// Set element
void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    data[i][j] = n;
}

// Get size
int Matrix::get_size() const {
    return static_cast<int>(size);
}

// Major diagonal sum
int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i)
        sum += data[i][i];
    return sum;
}

// Minor diagonal sum
int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for (std::size_t i = 0; i < size; ++i)
        sum += data[i][size - i - 1];
    return sum;
}

// Swap two rows
void Matrix::swap_rows(std::size_t r1, std::size_t r2) {
    if (r1 < size && r2 < size)
        std::swap(data[r1], data[r2]);
}

// Swap two columns
void Matrix::swap_cols(std::size_t c1, std::size_t c2) {
    if (c1 < size && c2 < size) {
        for (std::size_t i = 0; i < size; ++i)
            std::swap(data[i][c1], data[i][c2]);
    }
}

// Print matrix
void Matrix::print_matrix() const {
    for (const auto& row : data) {
        for (const auto& val : row)
            std::cout << std::setw(5) << val;
        std::cout << '\n';
    }
}

// Matrix addition
Matrix Matrix::operator+(const Matrix &rhs) const {
    Matrix result(size);
    for (std::size_t i = 0; i < size; ++i)
        for (std::size_t j = 0; j < size; ++j)
            result.data[i][j] = data[i][j] + rhs.data[i][j];
    return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix &rhs) const {
    Matrix result(size);
    for (std::size_t i = 0; i < size; ++i)
        for (std::size_t j = 0; j < size; ++j) {
            int sum = 0;
            for (std::size_t k = 0; k < size; ++k)
                sum += data[i][k] * rhs.data[k][j];
            result.data[i][j] = sum;
        }
    return result;
}
