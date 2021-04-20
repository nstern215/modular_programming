/*
 * Ex #1: Numbers matrix
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * this program read rows of numbers from the user and save them in the struct
 * in int matrix
 * 
 * for each row, the program check:
 * if the row is already exist or there is an exist row that contains the new
 * row, the row will be ignored
 * if the new row contains an existing row (the beginning of the rows are
 * equal), the new row will replace the existing one
 * otherwise, the new row will be added to the matrix
 * 
 * the program can print the matrix
 * 
 * input:
 * 0: exit
 * 1: add new row - first input for row length, after insert the content of
 * the row
 * 2: print the matrix
 *
 * output:
 * the matrix
 */

//-------------------incluce section-------------------------------------------
#include <iostream>

//-------------------using section---------------------------------------------
using std::nothrow;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

//-------------------struct section--------------------------------------------
struct Data {
    int** _data;
    int _num_of_lines;
    int* _lines_len;
};

//-------------------functions section-----------------------------------------
void add_line(Data &the_data, const int new_line[], int
line_len);
void allocate_data(Data *data);
void free_memory(Data& data);
void read_line();
void print_data(Data& data);
void read_line(Data &data);
void allocate_new_line(Data &data);
void copy_array(int *dest, const int *src, int size);
int array_contains(const int *arr1, const int *arr2, int arr1_len, int arr2_len);
int **allocate_matrix(int size);
int *allocate_array(int size);

//-----------------------------------------------------------------------------
int main()
{
    //variables section
    Data data;
    int input;

    allocate_data(&data);

    cin >> input;

    //handling different input options
    while (input != 0)
    {
        if (input == 1)
            read_line(data);
        else if (input == 2)
            print_data(data);

        cin >> input;
    } 

    free_memory(data);

    return EXIT_SUCCESS;
}

//-------------------functions section-----------------------------------------
/**
 * this function use to allocate memory for the int matrix in the struct
 * the matrix is an int pointer for array of int pointers
 * 
 * input:
 * *data: pointer for data struct instance
*/
void allocate_data(Data *data)
{
    data->_num_of_lines = 0;
    data->_data = allocate_matrix(data->_num_of_lines);
    data->_lines_len = allocate_array(data->_num_of_lines);
}

//-----------------------------------------------------------------------------
/**
 * this function use to read line of integers from the client and send
 * to the matrix
 * 
 * intput:
 * &data: reference for data struct instance
*/
void read_line(Data &data)
{
    int line_len;
    cin >> line_len;

    int *line = allocate_array(line_len);

    for (int i = 0; i < line_len; i++)
        cin >> line[i];
    
    add_line(data, line, line_len);

    delete[] line;
}

//-----------------------------------------------------------------------------
/**
 * this function use to add a new line to the matrix
 * 
 * the function check if the row is already exist or there is an exist row 
 * that contains the new
 * row, the row will be ignored
 * if the new row contains an existing row (the beginning of the rows are
 * equal), the new row will replace the existing one
 * otherwise, the new row will be added to the matrix
 * 
 * paramters:
 * &the_data: reference for a data struct instance
 * new_line: a new line from the user
 * line_len: the length of the new line
*/
void add_line(Data &the_data, const int new_line[], int line_len)
{
    int compare_results = 0;
    int i = 0;
    //for each line, check if it contains the new line
    //or, if the new line contains an existing one
    for (; i < the_data._num_of_lines; i++)
        //an existing line contains the new line
        if (the_data._lines_len[i] >= line_len) {
            compare_results = array_contains(the_data._data[i], new_line, 
                the_data._lines_len[i], line_len);

            if (compare_results == 1)
                return;
        } else {
            compare_results = array_contains(new_line, the_data._data[i], 
                line_len, the_data._lines_len[i]);

            if (compare_results == 1)
                break;
        }

    //no existing line contains the new line -> add the new line
    if (compare_results == 0)
    {
        allocate_new_line(the_data);
        the_data._lines_len[the_data._num_of_lines] = line_len;
        the_data._data[the_data._num_of_lines] = allocate_array(line_len);
        copy_array(the_data._data[the_data._num_of_lines], new_line, line_len);
        the_data._num_of_lines++;
    } else { //the new line contains an existing line -> replace with new line
        delete[] the_data._data[i];
        the_data._data[i] = allocate_array(line_len);
        copy_array(the_data._data[i], new_line, line_len);
        the_data._lines_len[i] = line_len;
    }    
}

//-----------------------------------------------------------------------------
/**
 * this function use to allocate memory in the struct for a new line
 * the functin creating new memory space (for the matrix and the array)
 * and copying the existing data to the new memory
 * 
 * parameters:
 * &data: reference for a data struct instance
*/
void allocate_new_line(Data &data)
{
    int new_size = data._num_of_lines + 1;
    
    int **matrix = allocate_matrix(new_size);
    int *line_len = allocate_array(new_size);

    for (int i = 0; i < data._num_of_lines; i++)
    {
        matrix[i] = data._data[i];
        data._data[i] = nullptr;

        line_len[i] = data._lines_len[i];
    }

    delete[] data._data;
    data._data = matrix;

    delete[] data._lines_len;
    data._lines_len = line_len;
}

//-----------------------------------------------------------------------------
/**
 * this function use to allocate memory for an integer matrix
 * the metrix is a pointer for pointers array
 * 
 * parameters:
 * size: size of matrix
 * 
 * output:
 * pointer for the matrix
*/
int **allocate_matrix(int size)
{
    int **matrix = new (nothrow) int*[size];
    if (matrix == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    return matrix;
}

//-----------------------------------------------------------------------------
/**
 * this function use to allocate memory for integer array
 * 
 * parameters:
 * size: size of array
 * 
 * output:
 * pointer for the array
*/
int *allocate_array(int size)
{
    int *arr = new (nothrow) int[size];
    if(arr == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    return arr;
}

//-----------------------------------------------------------------------------
/**
 * this function use to cpoy data between to arrays
 * 
 * paramters:
 * *dest: pointer for the destenation array
 * *src: pointer for the source array
 * size: the length of the array
*/
void copy_array(int *dest, const int *src, int size)
{
    for (int i = 0; i < size; i++)
        dest[i] = src[i];    
}

/**
 * this function use to check if one array contains othe array
 * contains means that the arrays are equals from the beginning
 * 
 * parameters:
 * *arr1: pointer for the containning array
 * *arr2: pointer for the array contained in arr1
 * arr1_len: size of arr1
 * arr2_len: size of arr2
 * 
 * output:
 * 0: not contains
 * 1: contains
*/
int array_contains(const int *arr1, const int *arr2, int arr1_len, int arr2_len)
{
    if (arr1_len < arr2_len)
        return 0;

    for (int i = 0; i < arr2_len; i++)
        if (arr1[i] != arr2[i])
            return 0;

    return 1;
}

//-----------------------------------------------------------------------------
/**
 * this function use to print the content of the int matrix
 * 
 * parameters:
 * &data: reference for a data struct instance
*/
void print_data(Data& data)
{
    for (int i = 0; i < data._num_of_lines; i++)
    {
        for (int j = 0; j < data._lines_len[i]; j++)
            cout << data._data[i][j] << " ";

        cout << endl;
    }
    
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that used by this program
*/
void free_memory(Data& data)
{
    for (int i = 0; i < data._num_of_lines; i++)
        delete[] data._data[i];

    delete[] data._data;
    delete[] data._lines_len;
    
}