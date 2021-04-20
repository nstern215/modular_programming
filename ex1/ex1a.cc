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
using std::cerr;
using std::endl;
using std::cin;
using std::setw;
using std::nothrow;

//------------------functions section------------------
void read_data(int **arr, int num_of_rows);
int** allocate_matrix(int size);
void print_sum(const int **arr, int num_of_rows);
void free_memory(int **arr, int num_of_rows);

//-----------------------------------------------------------------------------
int main()
{
    //variables section
    int **arr;
    int num_of_rows;

    cin >> num_of_rows;

    arr = allocate_matrix(num_of_rows);

    read_data(arr, num_of_rows);

    print_sum((const int**)arr, num_of_rows);

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
*/
void read_data(int **arr, int num_of_rows)
{
    int row_len;

    //read data for the matrix
    for (int i = 0; i < num_of_rows; i++)
    {
        cin >> row_len;

        //allocate memory for the row
        arr[i] = new (nothrow) int[row_len + 1];
        if (arr[i] == nullptr)
        {
            cerr << "Failed to allocate memory" << endl;
            exit(EXIT_FAILURE);
        }
            
        //first cell in the row store the length of the row
        arr[i][0] = row_len;

        for (int j = 1; j < row_len + 1; j++)
            cin >> arr[i][j];
    }
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
           sum += arr[i][j+1];

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

    if (matrix == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

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