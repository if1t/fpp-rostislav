#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    int max = INT16_MIN, min = INT16_MAX;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    double start;
    double end;
    start = omp_get_wtime();
        
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
            cout << "Max update!" << omp_get_thread_num() << endl;
        }
        if (min > a[i]) {
            min = a[i];
            cout << "Min update!" << omp_get_thread_num() << endl;
        }
    }
    end = omp_get_wtime();
    cout << "Work took %f seconds\n"<< end - start;
    cout << max << endl;
    cout << min << endl;
}
