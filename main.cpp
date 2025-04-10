#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include "matrix.hpp"

// Operator overloading to input values into the Matrix class
std::istream& operator>>(std::istream& in, Matrix& mat) {
    for (std::size_t i = 0; i < mat.get_size(); ++i) {
        for (std::size_t j = 0; j < mat.get_size(); ++j) {
            int val;
            in >> val;
            mat.set_value(i, j, val);
        }
    }
    return in;
}

// Template function to update std::vector<int> or std::vector<double>
template <typename T>
void update_vector_value(std::vector<std::vector<T>>& vec, std::size_t row, std::size_t col, T new_val) {
    if (row < vec.size() && col < vec[row].size()) {
        vec[row][col] = new_val;
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file.\n";
        return 1;
    }

    std::size_t N;
    int type_flag;
    infile >> N >> type_flag;

    std::cout << "\nMatrix size: " << N << "x" << N << "\n";
    std::cout << "Data type: " << (type_flag == 0 ? "int" : "double") << "\n";

    if (type_flag == 0) {
        Matrix A(N), B(N);
        infile >> A >> B;

        std::cout << "\nMatrix A:\n";
        A.print_matrix();

        std::cout << "\nMatrix B:\n";
        B.print_matrix();

        std::cout << "\nA + B:\n";
        (A + B).print_matrix();

        std::cout << "\nA * B:\n";
        (A * B).print_matrix();

        std::cout << "\nMajor diagonal sum of A: " << A.sum_diagonal_major() << "\n";
        std::cout << "Minor diagonal sum of A: " << A.sum_diagonal_minor() << "\n";

        A.swap_rows(0, 1);
        std::cout << "\nA after swapping rows 0 and 1:\n";
        A.print_matrix();

        A.swap_cols(0, 1);
        std::cout << "\nA after swapping columns 0 and 1:\n";
        A.print_matrix();

        A.set_value(2, 2, 99);
        std::cout << "\nA after updating position (2,2) to 99:\n";
        A.print_matrix();

        // Polymorphism example using std::vector<int>
        std::vector<std::vector<int>> vec = {
            {1, 2},
            {3, 4}
        };
        update_vector_value(vec, 0, 1, 99);
        std::cout << "\nUpdated std::vector<int> at (0,1) = 99: " << vec[0][1] << "\n";

    } else if (type_flag == 1) {
        std::vector<std::vector<double>> a(N, std::vector<double>(N));
        std::vector<std::vector<double>> b(N, std::vector<double>(N));

        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < N; ++j)
                infile >> a[i][j];
        for (std::size_t i = 0; i < N; ++i)
            for (std::size_t j = 0; j < N; ++j)
                infile >> b[i][j];

        std::cout << "\nMatrix A (double):\n";
        for (const auto& row : a) {
            for (double val : row)
                std::cout << std::setw(6) << val;
            std::cout << '\n';
        }

        std::cout << "\nMatrix B (double):\n";
        for (const auto& row : b) {
            for (double val : row)
                std::cout << std::setw(6) << val;
            std::cout << '\n';
        }

        update_vector_value(a, 1, 1, 42.42);
        std::cout << "\nUpdated A[1][1] to 42.42:\n";
        for (const auto& row : a) {
            for (double val : row)
                std::cout << std::setw(6) << val;
            std::cout << '\n';
        }
    } else {
        std::cerr << "Error: Invalid type flag.\n";
    }

    return 0;
}
