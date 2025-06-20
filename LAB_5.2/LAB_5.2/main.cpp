#include <iostream>

using namespace std;

// Функция для проверки локального максимума
bool isLocalMax(int32_t** matrix, int32_t i, int32_t j, int32_t size) {
    int32_t current = matrix[i][j];
    for (int32_t di = -1; di <= 1; di++) {
        for (int32_t dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;
            int32_t ni = i + di;
            int32_t nj = j + dj;
            if (ni >= 0 && ni < size && nj >= 0 && nj < size) {
                if (matrix[ni][nj] >= current) {
                    return false;
                }
            }
        }
    }
    return true;
}

void findMaxLocalMax(int32_t** matrix, int32_t size, int32_t& maxValue, int32_t& maxRow, int32_t& maxCol) {
    maxValue = matrix[0][0];
    maxRow = maxCol = -1;
    bool found = false;

    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            if (isLocalMax(matrix, i, j, size) && (!found || matrix[i][j] > maxValue)) {
                maxValue = matrix[i][j];
                maxRow = i;
                maxCol = j;
                found = true;
            }
        }
    }
}

int64_t productBelowSecondaryDiagonal(int32_t** matrix, int32_t size) {
    int64_t product = 1;
    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            if (i + j > size - 1) {
                product *= matrix[i][j];
            }
        }
    }
    return product;
}

int main() {
    int32_t size;
    cout << "Enter the size of the square matrix: ";
    cin >> size;

    if (size <= 0) {
        cout << "Incorrect matrix size!\n";
        return 1;
    }

    // Выделение памяти
    int32_t** matrix = new int32_t * [size];
    for (int32_t i = 0; i < size; i++) {
        matrix[i] = new int32_t[size];
    }

    // Ввод матрицы
    cout << "Enter the elements of the matrix:\n";
    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }

    // Поиск локальных максимумов
    int32_t maxVal, maxR, maxC;
    findMaxLocalMax(matrix, size, maxVal, maxR, maxC);

    if (maxR == -1) {
        cout << "No local maxima were found\n";
    }
    else {
        cout << "Maximum local maximum: " << maxVal
            << " on the position (" << maxR << "," << maxC << ")\n";
    }

    // Вычисление произведения
    int64_t prod = productBelowSecondaryDiagonal(matrix, size);
    cout << "The product of the elements below the side diagonal: " << prod << "\n";

    // Освобождение памяти
    for (int32_t i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}