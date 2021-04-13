#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::nothrow;

int main()
{
    int **arr;
    int num_of_rows;
    int row_len;

    cin >> num_of_rows;

    if (num_of_rows == 0)
    {
        cout << 0 << endl;
        return EXIT_SUCCESS;
    }

    arr = new (nothrow) int*[num_of_rows];

    for (int i = 0; i < num_of_rows; i++)
    {
        cin >> row_len;

        arr[i] = new (nothrow) int[row_len + 1];
        arr[i][0] = row_len;

        for (int j = 0; j < row_len; j++)
        {
            cin >> arr[i][j + 1];
        }
    }

    int sum = 0;

    for (int i = 0; i < num_of_rows; i++)
    {
        for (int j = 0; j < arr[i][0]; j++)
        {
            sum += arr[i][j+1];
        }
    }

    cout << sum;

    for (int i = 0; i < num_of_rows; i++) {
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;

}