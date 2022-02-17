#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

vector<int> merge(vector<int> a, vector<int> b) {
    vector<int> ans;

    for (int i = 0, j = 0; i < a.size() || j < b.size();) {
        if (i >= a.size()) {
            while (j < b.size()) {
                ans.push_back(b[j]);
                j++;
            }
            return ans;
        }
        if (j >= b.size()) {
            while (i < a.size()) {
                ans.push_back(a[i]);
                i++;
            }
            return ans;
        }
        if (a[i] < b[j] ) {
            while (i < a.size() && a[i] < b[j]) {
                ans.push_back(a[i]);
                i++;
            }
        }
        else {
            while (j < b.size() && a[i] >= b[j]) {
                ans.push_back(b[j]);
                j++;
            }
        }
    }
    return ans;
}
vector<int> mergeSort(vector<int> v) {
    if (v.size() < 2) {
        return v;
    }

    int middle = v.size() / 2;

    vector<int> left = v;
    vector<int> right = v;

    left.erase(left.begin() + middle, left.end());
    right.erase(right.begin(), right.begin() + middle);

    return merge(mergeSort(left), mergeSort(right));
}
// ---------------------------------------------------
vector<int> mergeWithPragma(vector<int> a, vector<int> b) {
    vector<int> ans;

    for (int i = 0, j = 0; i < a.size() || j < b.size();) {
        if (i >= a.size()) {
            while (j < b.size()) {
                ans.push_back(b[j]);
                j++;
            }
            return ans;
        }
        if (j >= b.size()) {
            while (i < a.size()) {
                ans.push_back(a[i]);
                i++;
            }
            return ans;
        }
        if (a[i] < b[j]) {
            while (i < a.size() && a[i] < b[j]) {
                ans.push_back(a[i]);
                i++;
            }
        }
        else {
            while (j < b.size() && a[i] >= b[j]) {
                ans.push_back(b[j]);
                j++;
            }
        }
    }
    return ans;
}
vector<int> mergeSortWithPragma(vector<int> v) {
    if (v.size() < 2) {
        return v;
    }

    int middle = v.size() / 2;

    vector<int> left = v;
    vector<int> right = v;

    left.erase(left.begin() + middle, left.end());
    right.erase(right.begin(), right.begin() + middle);

    #pragma omp parallel 
    {
        left = mergeSortWithPragma(left);
        right = mergeSortWithPragma(right);
    }
    return mergeWithPragma(left, right);
}

int main() {
    setlocale(0, "");

    random_device rd;
    mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

    long n;
    double st; // переменная для установки отсчета времени
    double end; // для фиксирования конца работы алгоритма

    cin >> n;
    vector<int> a(n);
    vector <int> c;
    for (int i = 0;i < n;i++) {
        a[i] = mersenne() % 100000;
    }

    st = omp_get_wtime(); // начало отсчета
    c = mergeSort(a);
    end = omp_get_wtime(); // конец отсчета
    for (int i = 0;i < c.size(); i++) {
        cout << c[i] << ' ';
    }
    cout << "Выполнение алгоритма без прагмы в секундах: " << end - st << endl;

    c.clear();
    cout << "\n\n\n\n\n\-------------------------------------------------------------" << endl;
// ---------------------------------Распараллеливание----------------------------
    st = omp_get_wtime(); // начало отсчета
    c = mergeSortWithPragma(a);
    end = omp_get_wtime(); // конец отсчета
    for (int i = 0;i < c.size(); i++) {
        cout << c[i] << ' ';
    }
    cout << "Выполнение алгоритма c использованием прагмы в секундах: " << end - st << endl;
}
