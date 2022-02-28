#include <iostream>
#include <random>
#include <omp.h>
using namespace std;

int** creatingMatrix(long size1, long size2) {
    random_device rd;
    mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
    int** matrix;
    matrix = new int* [size1];
    for (int i = 0; i < size1; i++) {
        matrix[i] = new int[size2];
        for (int j = 0; j < size2; j++)
            matrix[i][j] = mersenne() % 1000;
    }
    return matrix;
}
int** multiMatrixWithPragma(int** matrix1, int** matrix2, int first1, int second1, int second2) {
    int** res;
    res = new int* [first1];

    double start;
    double end;

#pragma omp parallel for
    for (int i = 0; i < first1; i++) {
        res[i] = new int[second2];
        for (int j = 0; j < second2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < second1; k++)
                res[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
    return res;
}
int** multiMatrix(int** matrix1, int** matrix2, int first1, int second1, int second2) {
    int** res;
    res = new int* [first1];

    double start;
    double end;

    for (int i = 0; i < first1; i++) {
        res[i] = new int[second2];
        for (int j = 0; j < second2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < second1; k++)
                res[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
    return res;
}
void coutMatrix(int** matrix, long size1, long size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}
int main() {
    setlocale(0,"");

    double st; // переменная для установки отсчета времени
    double end; // для фиксирования конца работы алгоритма

    long first1, first2, second1, second2;
    cin >> first1 >> first2 >> second1 >> second2;
    int** matrix1;
    int** matrix2;
    int** matrixResult;

    matrix1 = creatingMatrix(first1, first2);
    matrix2 = creatingMatrix(second1, second2);

    //coutMatrix(matrix1, first1, first2);
    //cout << "--------------------------------" << endl;
    //coutMatrix(matrix2, second1, second2);
    //cout << "--------------------------------" << endl;

    st = omp_get_wtime(); // начало отсчета
    matrixResult = multiMatrix(matrix1, matrix2, first1, second1, second2);
    end = omp_get_wtime(); // конец отсчета
    //coutMatrix(matrixResult, first1, second2);
    cout << endl <<"Выполнение алгоритма без прагмы в секундах: " << end - st << endl;
   
    st = omp_get_wtime(); // начало отсчета
    matrixResult = multiMatrixWithPragma(matrix1, matrix2, first1, second1, second2);
    end = omp_get_wtime(); // конец отсчета
    //coutMatrix(matrixResult, first1, second2);
    cout << endl << "Выполнение алгоритма c использованием прагмы в секундах: " << end - st << endl;
   
    return 0;
}
