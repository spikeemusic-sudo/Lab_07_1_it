// Lab_07_1_it.cpp
// Фащевський Богдан
// Лабораторна робота № 7.1
// Варіант 28
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <Windows.h> 

using namespace std;

// Прототипи функцій
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** a, const int rowCount, const int colCount);
void Sort(int** a, const int rowCount, const int colCount);
void Change(int** a, const int row1, const int row2, const int colCount);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k);

int main() {
    // Встановлення кодування UTF-8 для коректного відображення кирилиці
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    srand((unsigned)time(NULL));

    // Параметри за варіантом 28
    int Low = 9;
    int High = 61;
    int rowCount = 7;
    int colCount = 6;

    // Створення динамічної матриці S
    int** S = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        S[i] = new int[colCount];
    }

    Create(S, rowCount, colCount, Low, High);
    cout << "Початкова матриця:" << endl;
    Print(S, rowCount, colCount);

    Sort(S, rowCount, colCount);
    cout << "Впорядкована матриця:" << endl;
    Print(S, rowCount, colCount);

    int sum = 0;
    int count = 0;
    Calc(S, rowCount, colCount, sum, count);

    cout << "Кількість елементів, що задовольняють критерій (k) = " << count << endl;
    cout << "Сума елементів, що задовольняють критерій (S) = " << sum << endl;
    cout << "Модифікована матриця (елементи замінено на 0):" << endl;
    Print(S, rowCount, colCount);

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++) {
        delete[] S[i];
    }
    delete[] S;

    return 0;
}

// Функція формування матриці
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            a[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

// Функція виведення матриці
void Print(int** a, const int rowCount, const int colCount) {
    cout << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Функція впорядкування рядків матриці методом "бульбашки"
void Sort(int** a, const int rowCount, const int colCount) {
    for (int i0 = 0; i0 < rowCount - 1; i0++) {
        for (int i1 = 0; i1 < rowCount - i0 - 1; i1++) {
            // Ключі впорядкування: ↑ ↓ ↓ (стовпці 0, 1, 2)
            if ((a[i1][0] > a[i1 + 1][0]) ||
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] < a[i1 + 1][1]) ||
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] < a[i1 + 1][2]))
            {
                Change(a, i1, i1 + 1, colCount);
            }
        }
    }
}

// Допоміжна функція обміну рядків
void Change(int** a, const int row1, const int row2, const int colCount) {
    int tmp;
    for (int j = 0; j < colCount; j++) {
        tmp = a[row1][j];
        a[row1][j] = a[row2][j];
        a[row2][j] = tmp;
    }
}

// Функція обчислення кількості, суми та модифікації за заданим критерієм
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k) {
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            // Критерій: всі, крім: непарних з сумою індексів, кратною 7
            if (!(a[i][j] % 2 != 0 && (i + j) % 7 == 0)) {
                S += a[i][j];
                k++;
                a[i][j] = 0;
            }
        }
    }
}