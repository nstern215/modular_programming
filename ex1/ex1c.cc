#include <iostream>

using std::nothrow;
using std::cin;
using std:: cout;
using std::endl;

struct Data {
    int** _data;
    int _num_of_lines;
    int* _lines_len;
};

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

int main()
{
    Data data;
    int input;

    allocate_data(&data);

    cin >> input;

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

void allocate_data(Data *data) {
    data->_num_of_lines = 0;
    data->_data = new (nothrow) int*[data->_num_of_lines];
    data->_lines_len = new (nothrow) int[data->_num_of_lines];
}

void read_line(Data &data) {
    int line_len;
    cin >> line_len;

    int *line = new (nothrow) int[line_len];

    for (int i = 0; i < line_len; i++)
        cin >> line[i];
    
    add_line(data, line, line_len);

    delete[] line;
}

void add_line(Data &the_data, const int new_line[], int line_len) {
    int compare_results = 0;
    int i = 0;
    for (; i < the_data._num_of_lines; i++)
    {
        if (the_data._lines_len[i] >= line_len) {
            compare_results = array_contains(the_data._data[i], new_line, the_data._lines_len[i], line_len);

            if (compare_results == 1)
                return;
        } else {
            compare_results = array_contains(new_line, the_data._data[i], line_len, the_data._lines_len[i]);

            if (compare_results == 1)
                break;
        }
    }

    if (compare_results == 0)
    {
        allocate_new_line(the_data);
        the_data._lines_len[the_data._num_of_lines] = line_len;
        the_data._data[the_data._num_of_lines] = new (nothrow) int[line_len];
        copy_array(the_data._data[the_data._num_of_lines], new_line, line_len);
        the_data._num_of_lines++;
    } else {
        delete[] the_data._data[i];
        the_data._data[i] = new (nothrow) int[line_len];
        copy_array(the_data._data[i], new_line, line_len);
        the_data._lines_len[i] = line_len;
    }    
}

void allocate_new_line(Data &data) {
    int new_size = data._num_of_lines + 1;
    
    int **matrix = new (nothrow) int*[new_size];
    int *line_len = new (nothrow) int[new_size];

    for (int i = 0; i < data._num_of_lines; i++) {
        matrix[i] = data._data[i];
        data._data[i] = nullptr;

        line_len[i] = data._lines_len[i];
    }

    delete[] data._data;
    data._data = matrix;

    delete[] data._lines_len;
    data._lines_len = line_len;
}

void copy_array(int *dest, const int *src, int size) {
    for (int i = 0; i < size; i++)
        dest[i] = src[i];    
}

/*
* check if arr1 contains arr2
*/
int array_contains(const int *arr1, const int *arr2, int arr1_len, int arr2_len) {
    if (arr1_len < arr2_len)
        return 0;

    for (int i = 0; i < arr2_len; i++)
        if (arr1[i] != arr2[i])
            return 0;

    return 1;
}

void print_data(Data& data) {
    for (int i = 0; i < data._num_of_lines; i++)
    {
        for (int j = 0; j < data._lines_len[i]; j++)
        {
            cout << data._data[i][j] << " ";
        }

        cout << endl;
    }
    
}

void free_memory(Data& data) {
    for (int i = 0; i < data._num_of_lines; i++)
        delete[] data._data[i];

    delete[] data._data;
    delete[] data._lines_len;
    
}