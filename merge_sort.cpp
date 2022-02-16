#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<int> merge(vector<int>& a, vector<int>& b) {
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

int main() {    
    
    vector<int> a = { 1,2,3,4,5,6 };
    vector<int> b = { 1,2,3,4,5,6,7};
    vector <int> c = merge(a, b);

    for (int i = 0;i < c.size(); i++) {
        cout << c[i] << ' ';
    }
}
