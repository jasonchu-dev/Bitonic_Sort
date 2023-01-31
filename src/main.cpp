#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

void bitonicSort(int arr[], int n, int cd, int cBS, int stages) {
    if (stages == n) return;
    for (int i = cd; i > 0; i >>= 1) {
        int direction = 0, cnt = 0;
        for (int j = 0; j < n; j++) {
            if (cnt == i) {
                cnt = 0;
                j += i;
                if (j % cBS == 0)
                    direction = direction == 0 ? 1 : 0;
                j--;
            }
            else {
                cnt++;
                if ((direction == 0 && arr[j] > arr[j + i]) || (direction == 1 && arr[j] < arr[j + i]))
                    swap(arr[j], arr[j + i]);
            }
        }
    }
    bitonicSort(arr, n, cd << 1, cBS << 1, stages << 1);
}

int main() {
    // const int n = 1048576;
    const int n = 8;
    int arr[n];

    for (int i = 0; i < n; i++)
        arr[i] = i;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(arr, arr + n, default_random_engine(seed));
    
    // start @ stage 1
    // cd = 1
    // cBS = 2

    bitonicSort(arr, n, 1, 2, 1);
    cout << is_sorted(arr, arr + n);

    return 0;
}