#include <iostream>

template <typename T>
struct Comparator {
    virtual bool operator()(T const&, T const&) const = 0;
};

struct IntComparator final : Comparator<int> {
    bool operator()(int const& lha, int const& rha) const override {
        return lha < rha;
    }
};

template <typename T>
int part(T* A, int lo, int hi, Comparator<T>& comparator) {
    T pivot = A[(hi + lo) / 2];
    int i = lo;
    int j = hi;
    while (true) {
        while (comparator(A[i], pivot)) {
            i++;
        }
        while (comparator(pivot, A[j])) {
            j--;
        }
        if (i >= j) {
            return j;
        }
        T t = A[i];
        A[i] = A[j];
        A[j] = t;
        i++;
        j--;
    }
}

template <typename T>
void quicksort(T* A, int lo, int hi, Comparator<T>& comparator)
{
    if (lo < hi) {
        T p = part(A, lo, hi, comparator);
        quicksort(A, lo, p, comparator);
        quicksort(A, p + 1, hi, comparator);
    }
}

int main() {
    IntComparator compare;
    int n = 0;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    quicksort(arr, 0, n - 1, compare);
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}