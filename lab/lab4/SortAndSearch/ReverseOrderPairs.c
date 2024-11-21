#include <stdio.h>

#define MAXSIZE 100000
long long ans = 0;

void merge(int* a, int lo, int mid, int hi) {
    int aux[MAXSIZE];
    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            a[k] = aux[j++];
        } else if (j > hi) {
            a[k] = aux[i++];
        } else if (aux[j] < aux[i]) {
            a[k] = aux[j++];
            ans += (mid - i + 1);
        } else {
            a[k] = aux[i++];
        }
    }
}

void mergeTD(int* a, int lo, int hi) {
    if (hi <= lo) {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    mergeTD(a, lo, mid);
    mergeTD(a, mid + 1, hi);
    merge(a, lo, mid, hi);
}


void reversePairs(int *arr, int begin, int end) {
    mergeTD(arr, begin, end);
}

int main() {
    int n;
    int arr[MAXSIZE];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    reversePairs(arr, 0, n - 1);
    printf("%lld\n", ans);
    return 0;
}