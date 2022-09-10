#include <iostream>

using namespace std;

int compare_int(void* last, void* next) 
{
    int* int_last = reinterpret_cast<int*>(last);
    int* int_next = reinterpret_cast<int*>(next);
    if (*int_last < *int_next) 
    {
        return -1;
    }
    if (*int_last > *int_next) 
    {
        return 1;
    }
    return 0;
}

int min(void* arr, int arr_size, int type_size, int (*compare)(void*, void*)) 
{
    int i_min = 0;
    unsigned char* arr_c = reinterpret_cast<unsigned char*>(arr);
    for (int i = 1; i < arr_size; i++) 
    {
        if (compare(arr_c + i * type_size, arr_c + i_min * type_size) < 0) 
        {
            i_min = i;
        }
    }
    return i_min;
}


int main() 
{
    int arr[3] = {0};
    for (int i = 0; i < 3; i++) 
    {
        cin >> arr[i];
    }
    cout << "Min index = " << min(arr, 3, sizeof(int), compare_int);
    return 0;
}