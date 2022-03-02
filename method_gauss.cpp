#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

void sout(double** a, double* y, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
}
double* gauss(double** a, double* b, int n) {
    double* x, max;
    int k, index;
    const double eps = 0.00001;
    x = new double[n];
    k = 0;

    while (k < n) {
        max = abs(a[k][k]);
        index = k;

        for (int i = k + 1; i < n; i++) {
            if (abs(a[i][k]) > max) {
                max = abs(a[i][k]);
                index = i;
            }
        }

        if (max < eps) {
            cout << "Решение получить невозможно из-за нулевого столбца " << index << " матрицы A" << endl;
            return 0;
        }

        for (int j = 0; j < n; j++) {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        swap(b[k], b[index]);

        for (int i = k; i < n; i++) {
            double temp = a[i][k];

            if (abs(temp) < eps) continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            b[i] = b[i] / temp;
            if (i == k)  continue;

            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            b[i] = b[i] - b[k];
        }
        k++;
    }

    for (k = n - 1; k >= 0; k--) {
        x[k] = b[k];

        for (int i = 0; i < k; i++)
            b[i] = b[i] - a[i][k] * x[k];
    }
    return x;
}

double* gaussWithOMP(double** a, double* y, int n) {
    double* x, max;
    int k, index;
    const double eps = 0.00001;
    x = new double[n];
    k = 0;

    while (k < n) {
        max = abs(a[k][k]);
        index = k;

        #pragma omp parallel for
        for (int i = k + 1; i < n; i++) {
            if (abs(a[i][k]) > max) {
                max = abs(a[i][k]);
                index = i;
            }
        }

        if (max < eps) {
            cout << "Решение получить невозможно из-за нулевого столбца " << index << " матрицы A" << endl;
            return 0;
        }
        #pragma omp parallel for
        for (int j = 0; j < n; j++) {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }

        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;

        #pragma omp parallel for
        for (int i = k; i < n; i++) {
            double temp = a[i][k];

            if (abs(temp) < eps) continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue;

            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }

    for (k = n - 1; k >= 0; k--) {
        x[k] = y[k];

        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

int main() {
    setlocale(0, "");

    double** a, * b;
    int n;

    cin >> n;
    a = new double* [n];
    double** az = new double* [n];
    b = new double [n];
    double* bz = new double [n];

    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
        az[i] = new double[n];
        for (int j = 0; j < n; j++) {
            //cin >> a[i][j];
            a[i][j] = rand() % 500;
            az[i][j] = a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        //cin >> b[i];
        b[i] = rand() % 1000;
        bz[i] = b[i];
    }

    double st;
    double end;
    double* x;
    
    //sout(a, b, n);
    st = omp_get_wtime();
    x = gauss(a, b, n);
    end = omp_get_wtime();
    cout << "Выполнение алгоритма без прагмы в секундах: " << end - st << endl;
    
    //for (int i = 0; i < n; i++)
        //cout << "x[" << i << "]=" << x[i] << endl;
    cout << endl;
// ---------------With OMP----------------------------
    double* y;
    //sout(az, bz, n);
    st = omp_get_wtime();
    y = gaussWithOMP(az, bz, n);
    end = omp_get_wtime();
    cout << "Выполнение алгоритма с использованием прагмы в секундах: " << end - st << endl;

    //for (int i = 0; i < n; i++)
        //cout << "y[" << i << "]=" << y[i] << endl;
    return 0;
}
