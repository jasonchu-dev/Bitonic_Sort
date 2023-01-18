#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

void bitonicSort(int arr[], int n) {
    int stages = 0;
    int cd = 1, cBS = 2;
    for (int i = cd; i <= n; i <<= 1)
        stages++;
    stages--;

    for (int i = 0; i < stages; i++) {
        int direction = 0, cnt = 0;
        for (int j = cd; j > 0; j >>= 1) {
            direction = 0;
            for (int k = 0; k < n; k++) {
                if (cnt == j) {
                    cnt = 0;
                    k += j;
                    if (k % cBS == 0)
                        direction = direction == 0 ? 1 : 0;
                    k--;
                }
                else {
                    cnt++;
                    if ((direction == 0 && arr[k] > arr[k + j]) || (direction == 1 && arr[k] < arr[k + j]))
                        swap(arr[k], arr[k + j]);
                }
            }
        }
        cBS <<= 1, cd <<= 1;
    }
}

int main() {
    const int n = 32;
    int arr[n];
    for (int i = 0; i < n; i++)
        arr[i] = i;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(arr, arr + n, default_random_engine(seed));
    cout << is_sorted(arr, arr + n);
    return 0;
}