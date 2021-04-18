/*
 * Ex #0: Dynamic array allocation
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program read from the user num of rows in the matrix
 * and the data for each row than print the sum
 * the matrix size is dynamic and depend on the input from the user
 * 
 * input:
 * num of rows in the matrix and content of each row
 *
 * output:
 * sum of the matrix
 */

//------------------include section------------------
#include <iostream>
#include <iomanip>

//------------------using section------------------
using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::nothrow;

//------------------functions section------------------
int read_data(int& **arr);
int** allocate_matrix(int size);
void print_sum(const int **arr, int num_of_rows);
void free_memory(int **arr, int num_of_rows);

//-----------------------------------------------------------------------------
int main()
{
    //variables section
    int **arr;
    int num_of_rows;

    int num_of_rows = read_data(arr);

    print_sum(arr, num_of_rows);

    free_memory(arr, num_of_rows);
}

//-------------------functions section--------------------------

/**
 * this function use to read data from the client into the matrix
 * the user type num of lines in the matrix
 * than, for each line, the length of the line and the content
 * 
 * parameters: 
 * **arr: pointer for int matrix
 * output:
 * num of rows in the matrix
*/
int read_data(int& **arr)
{
    int num_of_rows;
    int row_len;

    cin >> num_of_rows;

    //allocate memory for the matrix
    arr = allocate_matrix(num_of_rows);

    //read data for the matrix
    for (int i = 0; i < num_of_rows; i++)
    {
        cin >> row_len;

        //allocate memory for the row
        arr[i] = new (nothrow) int[row_len + 1];
        //first cell in the row store the length of the row
        arr[i][0] = row_len;

        for (int j = 0; j < row_len; j++)
            cin >> arr[i][j + 1];
    }

    return num_of_rows;
}

//-----------------------------------------------------------------------------


/**
 * this function use to sum the values in the matrix and print the sum
 * 
 * parameters:
 * **arr: pointer for the matrix
 * num_of_rows: how many rows in the matrix
*/
void print_sum(const int **arr, int num_of_rows)
{
    int sum = 0;

   for (int i = 0; i < num_of_rows; i++)
       for (int j = 0; j < arr[i][0]; j++)
       {
           sum += arr[i][j+1];
       }

   cout << sum;
}


//-----------------------------------------------------------------------------

/**
 * this function use to allocate memory for int array of int pointers
 * 
 * parameters:
 * size: size of the array
*/
int** allocate_matrix(int size)
{
    int **matrix;
    matrix = new (nothrow) int*[size];

    return matrix;
}


//-----------------------------------------------------------------------------

/**
 * this function use to release the memory allocated by this program
 * 
 * parameters:
 * **arr: pointer for int array of pointers
 * num_of_rows: array size
*/
void free_memory(int **arr, int num_of_rows)
{
    //delete internal arrays
    for (int i = 0; i < num_of_rows; i++)
    {
       delete[] arr[i];
       arr[i] = nullptr;
    }

    //delete main array
    delete[] arr;
}