#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

const int ROWS = 2; // Количество строк в матрице
const int COLS = 2; // Количество столбцов в матрице

// Функция для умножения части матрицы и записи результата в указанную область памяти
void multiplyMatrix(int matrixA[ROWS][COLS], int matrixB[ROWS][COLS], int result[ROWS][COLS], int startRow, int endRow) {
    // Умножаем часть матрицы
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int sum = 0;
            for (int k = 0; k < ROWS; ++k) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            result[i][j] = sum;
        }
    }
}

int main() {
    int matrixA[ROWS][COLS] = {{1, 2}, {3, 4}};
    int matrixB[ROWS][COLS] = {{5, 6}, {7, 8}};
    int result[ROWS][COLS];

    // Создаем процессы для умножения матриц
    pid_t pid;
    for (int i = 0; i < ROWS; ++i) {
        pid = fork();
        if (pid == 0) { // Код, выполняемый дочерним процессом
            multiplyMatrix(matrixA, matrixB, result, i, i + 1);
            exit(0);
        } else if (pid < 0) { // Обработка ошибок при создании процесса
            cerr << "Error: Failed to create child process." << endl;
            exit(1);
        }
    }

    // Ожидаем завершения выполнения всех дочерних процессов
    for (int i = 0; i < ROWS; ++i) {
        wait(NULL);
    }

    // Выводим результат
    cout << "Результат:" << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
