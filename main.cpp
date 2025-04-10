#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <string>

template <typename T>
class Matrix {
private:
    std::size_t size;
    std::vector<std::vector<T>> data;

public:
    Matrix(std::size_t N) : size(N), data(N, std::vector<T>(N)) {}

    void set_value(std::size_t i, std::size_t j, T value) {
        if (i >= size || j >= size) throw std::out_of_range("Index out of range");
        data[i][j] = value;
    }

    T get_value(std::size_t i, std::size_t j) const {
        if (i >= size || j >= size) throw std::out_of_range("Index out of range");
        return data[i][j];
    }

    std::size_t get_size() const {
        return size;
    }

    T sum_diagonal_major() const {
        T sum = 0;
        for (std::size_t i = 0; i < size; ++i)
            sum += data[i][i];
        return sum;
    }

    T sum_diagonal_minor() const {
        T sum = 0;
        for (std::size_t i = 0; i < size; ++i)
            sum += data[i][size - i - 1];
        return sum;
    }

    void swap_rows(std::size_t r1, std::size_t r2) {
        if (r1 < size && r2 < size)
            std::swap(data[r1], data[r2]);
    }

    void swap_cols(std::size_t c1, std::size_t c2) {
        if (c1 < size && c2 < size) {
            for (std::size_t i = 0; i < size; ++i)
                std::swap(data[i][c1], data[i][c2]);
        }
    }

    Matrix<T> operator+(const Matrix<T>& rhs) const {
        Matrix<T> result(size);
        for (std::size_t i = 0; i < size; ++i)
            for (std::size_t j = 0; j < size; ++j)
                result.data[i][j] = data[i][j] + rhs.data[i][j];
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& rhs) const {
        Matrix<T> result(size);
        for (std::size_t i = 0; i < size; ++i)
            for (std::size_t j = 0; j < size; ++j) {
                T sum = 0;
                for (std::size_t k = 0; k < size; ++k)
                    sum += data[i][k] * rhs.data[k][j];
                result.data[i][j] = sum;
            }
        return result;
    }

    void print_matrix() const {
        for (const auto& row : data) {
            for (const auto& val : row)
                std::cout << std::setw(6) << val;
            std::cout << '\n';
        }
    }

    friend std::istream& operator>>(std::istream& in, Matrix<T>& mat) {
        for (std::size_t i = 0; i < mat.size; ++i)
            for (std::size_t j = 0; j < mat.size; ++j)
                in >> mat.data[i][j];
        return in;
    }
};

int main() {
    std::string filename;
    std::cout << "Enter input filename: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Could not open file.\n";
        return 1;
    }

    std::size_t size;
    int type_flag;
    infile >> size >> type_flag;

    if (type_flag == 0) {
        Matrix<int> A(size), B(size);
        infile >> A >> B;

        std::cout << "\nMatrix A:\n"; A.print_matrix();
        std::cout << "\nMatrix B:\n"; B.print_matrix();

        std::cout << "\nA + B:\n"; (A + B).print_matrix();
        std::cout << "\nA * B:\n"; (A * B).print_matrix();

        std::cout << "\nSum of major diagonal: " << A.sum_diagonal_major() << '\n';
        std::cout << "Sum of minor diagonal: " << A.sum_diagonal_minor() << '\n';

        A.swap_rows(0, 1);
        std::cout << "\nA after swapping rows 0 and 1:\n"; A.print_matrix();

        A.swap_cols(0, 1);
        std::cout << "\nA after swapping columns 0 and 1:\n"; A.print_matrix();

        A.set_value(1, 1, 99);
        std::cout << "\nA after setting (1,1) = 99:\n"; A.print_matrix();
    } else if (type_flag == 1) {
        Matrix<double> A(size), B(size);
        infile >> A >> B;

        std::cout << "\nMatrix A:\n"; A.print_matrix();
        std::cout << "\nMatrix B:\n"; B.print_matrix();

        std::cout << "\nA + B:\n"; (A + B).print_matrix();
        std::cout << "\nA * B:\n"; (A * B).print_matrix();

        std::cout << "\nSum of major diagonal: " << A.sum_diagonal_major() << '\n';
        std::cout << "Sum of minor diagonal: " << A.sum_diagonal_minor() << '\n';

        A.swap_rows(0, 1);
        std::cout << "\nA after swapping rows 0 and 1:\n"; A.print_matrix();

        A.swap_cols(0, 1);
        std::cout << "\nA after swapping columns 0 and 1:\n"; A.print_matrix();

        A.set_value(1, 1, 9.99);
        std::cout << "\nA after setting (1,1) = 9.99:\n"; A.print_matrix();
    } else {
        std::cerr << "Invalid type flag in file. Use 0 (int) or 1 (double).\n";
        return 1;
    }

    return 0;
