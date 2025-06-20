#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>

using namespace std;

// Функция для ввода матрицы с клавиатуры
void inputMatrix(int32_t** matrix, int32_t size) {
    cout << "Enter the elements of the matrix:" << '\n';
    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
}

// Функция для заполнения матрицы случайными числами (без cstdlib)
void fillRandomMatrix(int32_t** matrix, int32_t size, int32_t minVal, int32_t maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            matrix[i][j] = distrib(gen);
        }
    }
}

// Функция для вывода матрицы
void printMatrix(int32_t** matrix, int32_t size) {
    cout << "The matrix: " << '\n';
    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// Функция для нахождения максимального элемента в нижнем правом треугольнике
int32_t findMaxInLowerRightTriangle(int32_t** matrix, int32_t size) {
    if (size == 0) return 0;

    int32_t maxElem = matrix[0][size - 1];

    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = size - i - 1; j < size; j++) {
            if (matrix[i][j] > maxElem) {
                maxElem = matrix[i][j];
            }
        }
    }
    return maxElem;
}

// Функция для поиска максимального положительного элемента
bool findMaxPositiveElement(int32_t** matrix, int32_t size, int32_t& maxRow, int32_t& maxCol) {
    maxRow = -1;
    maxCol = -1;
    bool foundPositive = false;
    int32_t maxPositive = 0;

    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            if (matrix[i][j] > 0) {
                if (!foundPositive || matrix[i][j] > maxPositive) {
                    maxPositive = matrix[i][j];
                    maxRow = i;
                    maxCol = j;
                    foundPositive = true;
                }
            }
        }
    }
    return foundPositive;
}

// Функция для перестановки строк
void swapRows(int32_t** matrix, int32_t size, int32_t row1, int32_t row2) {
    for (int32_t j = 0; j < size; j++) {
        swap(matrix[row1][j], matrix[row2][j]);
    }
}

// Функция для перестановки столбцов
void swapColumns(int32_t** matrix, int32_t size, int32_t col1, int32_t col2) {
    for (int32_t i = 0; i < size; i++) {
        swap(matrix[i][col1], matrix[i][col2]);
    }
}

int main() {

    int32_t size{};
    cout << "Enter the size of the square matrix: ";
    cin >> size;

    if (size <= 0) {
        cout << "Incorrect matrix size!" << endl;
        return 1;
    }

    // Создание динамического массива
    int32_t** matrix = new int32_t* [size];
    for (int32_t i = 0; i < size; i++) {
        matrix[i] = new int32_t[size];
    }

    int32_t choice{};
    cout << "Choose a way to fill in the matrix:" << endl;
    cout << "1 - keyboard input" << endl;
    cout << "2 - filling with random numbers" << endl;
    cin >> choice;

    if (choice == 1) {
        inputMatrix(matrix, size);
    }
    else if (choice == 2) {
        int32_t minVal, maxVal;
        cout << "Enter the minimum value: ";
        cin >> minVal;
        cout << "Enter the maximum value: ";
        cin >> maxVal;
        fillRandomMatrix(matrix, size, minVal, maxVal);
    }
    else {
        cout << "Incorrect choice!" << endl;
        // Освобождаем память перед выходом
        for (int32_t i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        return 1;
    }

    printMatrix(matrix, size);

    // Задание 1: Максимальный элемент нижнего правого треугольника
    int32_t maxInTriangle = findMaxInLowerRightTriangle(matrix, size);
    cout << "The maximum element of the lower right triangle: " << maxInTriangle << endl;

    // Задание 2: Перестановка строк и столбцов
    int32_t maxRow, maxCol;
    bool hasPositive = findMaxPositiveElement(matrix, size, maxRow, maxCol);

    if (!hasPositive) {
        cout << "There are no positive elements in the matrix!" << endl;
    }
    else {
        swapRows(matrix, size, 0, maxRow);
        swapColumns(matrix, size, 0, maxCol);
        cout << "The matrix after permutation:" << endl;
        printMatrix(matrix, size);
    }

    // Освобождение памяти
    for (int32_t i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}