#include <iostream>

using namespace std;

typedef double(*func)(const void* arr, int index);

double get_height(const void* data, int index)
{
    return (double)(*((int *)data + index));
}

double get_double(func f, void* arr, int index)
{
    return f(arr, index);
}

int main()
{
    int arr[5] = {1,2,3,4,5};

    double d = get_double(get_height, arr, 3);

    if (d > 2)
        cout << 456 << endl;

    cout << d << endl;

    return EXIT_SUCCESS;
}