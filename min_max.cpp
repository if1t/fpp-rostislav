#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main() {
    setlocale(0, "");
    random_device rd;
    mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

    int n;
    double st; // переменная для установки отсчета времени
    double end; // для фиксирования конца работы алгоритма 
    cin >> n;

    int* a = new int[n];
    int max = INT16_MIN, min = INT16_MAX;

    for (long i = 0; i < n; i++) { // заполнение массива рандомными числами
        a[i] = mersenne()%10000;
    }

    st = omp_get_wtime();

    cout << "Выполнение алгоритма без использования прагмы:" << endl;
    for (long i = 0; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
            cout << "max = " << max << ", номер ядра, в котором исполняется код: " << omp_get_thread_num() << "\n";
        }
        if (min > a[i]) {
            min = a[i];
            cout << "min = " << min << ", номер ядра, в котором исполняется код: " << omp_get_thread_num() << "\n";
        }
    }
    end = omp_get_wtime();
    cout << "Выполнение алгоритма в секундах: " << end - st << endl << "max: " << max <<" min: "<< min << endl;
//------------------------------------------------------------------
    cout << "Выполнение алгоритма с использованием прагмы:" << endl;
    max = INT16_MIN;
    min = INT16_MAX;
    st = omp_get_wtime();

    #pragma omp parallel for 
    for (int i = 0; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
            cout << "max = " << max << ", номер ядра, в котором исполняется код: " << omp_get_thread_num() << "\n";
        }
        if (min > a[i]) {
            min = a[i];
            cout << "min = " << min << ", номер ядра, в котором исполняется код: " << omp_get_thread_num() << "\n";
        }
    }
    end = omp_get_wtime();
    cout << "Выполнение алгоритма в секундах: " << end - st << endl << "max: " << max << " min: " << min << endl;
}
