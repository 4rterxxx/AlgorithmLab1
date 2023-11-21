#include <iostream>
#include <chrono>

using namespace std;

int M = 8192; // Строки

int N = 8192; // Столбцы

int Num_Of_Tests = 1000; // Колличество тестов

// Функции для выделения динамической памяти и её удаления

int** Create_Array() {
    int** arr = new int* [M];
    for (int i = 0; i < M; i++) {
        arr[i] = new int[N];
    }
    return arr;
}
void Delete_Array(int** arr) {
    for (int i = 0; i < M; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}


// Функции для запонения матриц

void Fill_Arr_1(int** arr, int* target) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = (N / M * i + j) * 2;
        }
    }
    (*target) = 2 * N + 1;
}

void Fill_Arr_2(int** arr, int* target) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = (N / M * i * j) * 2;
        }
    }
    (*target) = 16 * N + 1;
}


bool binSearch(int* arr, int target, int left, int right) {
    while (left <= right) {
        int mid = (right - left) / 2 + left;
        if (arr[mid] == target) {
            return true;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}

int expSearch(int* arr, int target, int index) {
    int step = 1;
    int left = 0, right = 0;
    while (index >= 0) {
        if (arr[index] > target) {
            index -= step;
            step *= 2;
        }
        else if (arr[index] == target) {
            return index;
        }
        else {
            left = index;
            right = step / 2 + index;
            break;
        }
    }
    if (index < 0) {
        left = 0;
        right = step / 2 + index;
    }
    while (left <= right) {
        int mid = (right - left) / 2 + left;
        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left - 1;
}

// Лесенка

bool Search_1(int** arr, int target) {
    int i = 0, j = N - 1;
    while (i < M && j >= 0) {
        if (target < arr[i][j]) {
            //left
            j--;
        }
        else if (target > arr[i][j]) {
            //down
            i++;
        }
        else {
            return true;
        }
    }
    return false;
}

// Бинарный поиск

bool Search_2(int** arr, int target) {
    for (int i = 0; i < M; i++) {
        if (binSearch(arr[i], target, 0, N - 1)) {
            return true;
        }
    }
    return false;
}

// Эксп поиск

bool Search_3(int** arr, int target) {
    int i = 0, j = N - 1;
    while (i < M && j >= 0) {
        if (target < arr[i][j]) {
            //left
            j = expSearch(arr[i], target, j);
        }
        else if (target > arr[i][j]) {
            //down
            i++;
        }
        else {
            return true;
        }
    }
    return false;
}


// Функция для замера времени 

void CheckTime(int** arr, int target, bool (*Search)(int** arr, int target)) {
    long double res = 0;

    for (int i = 0; i < Num_Of_Tests; i++) {
        auto start_time = chrono::steady_clock::now();
        Search(arr, target);
        auto end_time = chrono::steady_clock::now();
        auto result = end_time - start_time;
        res += chrono::duration<double, micro>(result).count();
    }

    res /= Num_Of_Tests;
    cout << res << " ";
}


int main()
{
    setlocale(LC_ALL, "ru");
    auto arr = Create_Array();
    int target;


    cout << "1st generation" << endl;
    cout << "M Ladder Binary Exponential" << endl;
    for (int i = 1; i <= 8192; i *= 2) {
        M = i;
        cout << M << " ";
        Fill_Arr_1(arr, &target);
        CheckTime(arr, target, Search_1);
        CheckTime(arr, target, Search_2);
        CheckTime(arr, target, Search_3);
        cout << endl;
    }

    cout << "2nd generation" << endl;
    cout << "M Ladder Binary Exponential" << endl;
    for (int i = 1; i <= 8192; i *= 2) {
        M = i;
        cout << M << " ";
        Fill_Arr_2(arr, &target);
        CheckTime(arr, target, Search_1);
        CheckTime(arr, target, Search_2);
        CheckTime(arr, target, Search_3);
        cout << endl;
    }

    Delete_Array(arr);
}

