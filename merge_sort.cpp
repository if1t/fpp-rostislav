#include <iostream>

void merge(int* AP, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int* L; int* R;
    L = new int[n1 + 1];
    R = new int[n2 + 1];
#pragma omp parallel for
    for (int i = 1;i <= n1; i++) {
        L[i - 1] = AP[p + i - 1];
    }
#pragma omp parallel for
    for (int j = 1;j <= n2; j++) {
        R[j - 1] = AP[q + j];
    }
#pragma omp parallel for
    for (int i = 0, j = 0, k = p; k <= r; k++) {
        if (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                AP[k] = L[i];
                i++;
            }
            else {
                AP[k] = R[j];
                j++;
            }
        }
        else if (i < n1) {
            AP[k] = L[i];
            i++;
        }
        else {
            AP[k] = R[j];
            j++;
        }
    }
    delete[] L; delete[] R;
}
void merge_sort(int* AP, int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) / 2;
        merge_sort(AP, p, q);
        merge_sort(AP, q + 1, r);
        merge(AP, p, q, r);
    }
}


void print(int* A, int size) {
#pragma omp parallel for
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    //int arr[] = { 4,2,7,1,23,1,23,1 };
    int arr[] = { 3,6,4,1,5,7,2,9,8,10,3,11,14,12,15,19,18,20,17,13,11 };

    print(arr, sizeof(arr) / sizeof(int));
    merge_sort(arr, 0, sizeof(arr) / sizeof(int) - 1); printf("\n");
    print(arr, sizeof(arr) / sizeof(int));

    getchar();
}