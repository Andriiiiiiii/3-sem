#include <iostream>
#include <vector>

template <typename T>
struct Comparator
{
    virtual bool operator()(T const&, T const&) = 0;
};

struct IntComparator final : Comparator<int>
{
    bool operator()(int const& lha, int const& rha) override
    {
        return (lha < rha);
    }
};

template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
class PriorityQueue
{
private:
    std::vector<T> mas;
    Comparator<T>& comp;
    int parent(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return (2 * i + 1);
    }
    int right(int i) {
        return (2 * i + 2);
    }

    void Sort_up(int i)
    {
        while (i > 0 && comp(mas[parent(i)], mas[i]))
        {
            swap(mas[parent(i)], mas[i]);
            i = parent(i);
        }
    }

    void Sort_Down(int i) {
        if (right(i) < mas.size() && comp(mas[i], mas[right(i)]) && comp(mas[left(i)], mas[right(i)])) {
            swap(mas[right(i)], mas[i]);
            Sort_Down(right(i));
        }

        else if (left(i) < mas.size() && comp(mas[i], mas[left(i)]) && comp(mas[right(i)], mas[left(i)])) {
            swap(mas[left(i)], mas[i]);
            Sort_Down(left(i));
        }
    }
public:
    PriorityQueue(Comparator<T>& comp) : comp(comp) {}

    PriorityQueue(std::vector<T> arr, Comparator<T>& comp) : PriorityQueue(comp) {
        for (int i = 0; i < arr.size(); i++) {
            push(arr[i]);
        }
    }

    void push(T value) {
        mas.push_back(value);
        Sort_up(mas.size() - 1);
    }
    T peek() {
        return mas[0];
    }
    void poll() {
        mas[0] = mas.back();
        if (is_empty() == 0) {
            mas.pop_back();
        }
        Sort_Down(0);
    }
    bool is_empty() {
        if (mas.size() == 0) {
            return true;
        }
        return false;
    }
};

int main()
{
    IntComparator comp;
    std::vector<int> arr = { 4, 6, 2, 7, 9, 72, 6, 32, 89, 23, 76, 45, 5, 7, 12 };
    PriorityQueue<int> queue(arr, comp);
    for (int i = 0; i < 14; i++)
    {
        std::cout << queue.peek() << ' ';
        queue.poll();
    }
    std::cout << '\n';

    return (0);
}