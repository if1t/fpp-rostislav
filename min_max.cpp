#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    setlocale(0, "");
    int n;
    cin >> n;
    int* a = new int[n];
    int max = INT16_MIN, min = INT16_MAX;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
            cout << "Max update!" << " поток " << omp_get_thread_num() << endl;
        }
        if (min > a[i]) {
            min = a[i];
            cout << "Min update!" << " поток " << omp_get_thread_num() << endl;
        }
    }
    
    cout << max << endl;
    cout << min << endl;
}