//--------------------------include section------------------------------------
#include <iostream>

//--------------------------using section--------------------------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

//--------------------------constant variables---------------------------------
const int NUM_OF_GRADES = 7;
const int CLASS_SIZE = 10;
const int NUM_OF_COURSES = 10;

//--------------------------struct section-------------------------------------
struct Stud
{
    int _stud_id;
    int _grades[NUM_OF_GRADES];
    double _height;
};

struct Course
{
    int _course_id;
    double _credit_point;
    unsigned int _hours_of_course;
};

struct Avg_result
{
    double _avg;
    int _max_index;
};

//--------------------------functions pointer----------------------------------
typedef bool(*get_double_elem_func)(const void* data, int index,
     double& value);
typedef void*(*get_elem_func)(const void* arr, int index);
typedef bool(*read_elem_func)(void* elem);

//--------------------------functions section----------------------------------
void* get_stud(const void *arr, int index);
bool read_stud(void *elem);

void* get_course(const void *arr, int index);
bool read_course(void *elem);

void* get_grade(const void *arr, int index);
bool read_grade(void *elem);

bool get_credit_point(const void* data, int index, double& value);
bool get_hours_of_cours(const void* data, int index, double& value);
bool get_height(const void* data, int index, double& value);
bool get_stud_avg(const void* data, int index, double& value);
bool get_double_from_int_elem(const void *elem, int index, double& value);
double get_avg_from_avg_result(const void *result, int index);

void read_data(void *arr, int data_len, get_elem_func get_elem,
     read_elem_func read_elem);

Avg_result calc_avg(const void* data, int data_len,
     get_double_elem_func get_elem);

//-----------------------------------------------------------------------------
int main()
{
    struct Stud studs[CLASS_SIZE];
    struct Course courses[NUM_OF_COURSES];

    read_data(studs, CLASS_SIZE, get_stud, read_stud);
    read_data(courses, NUM_OF_COURSES, get_course, read_course);

    Avg_result grades_avg = calc_avg(studs, CLASS_SIZE, get_stud_avg);
    Avg_result height_avg = calc_avg(studs, CLASS_SIZE, get_height);
    Avg_result credit_point_avg = calc_avg(&courses, NUM_OF_COURSES,
         get_credit_point);
    Avg_result hours_avg = calc_avg(&courses, NUM_OF_COURSES,
         get_hours_of_cours);

    cout << grades_avg._avg << " "
         << height_avg._avg << " "
         << credit_point_avg._avg << " "
         << hours_avg._avg << " "
         << studs[grades_avg._max_index]._stud_id << " "
         << courses[hours_avg._max_index]._course_id<< endl;

    return EXIT_SUCCESS;
}

//--------------------------functions section----------------------------------
/**
 * this generic function use to read data into an array
 *
 * parameters:
 * arr - pointer for the array
 * data_len - array size
 * get_elem - pointer for a function to get a pointer for an elem
 *  in a given index
 * read_elem - pointer for a function to read an elem
*/
void read_data(void *arr, int data_len, get_elem_func get_elem,
               read_elem_func read_elem)
{
    for (int i = 0; i < data_len && read_elem(get_elem(arr, i)); i++);
}

//-----------------------------------------------------------------------------
/**
 * this function use to retrive the address of a stud elem in an array
 *
 * paramters:
 * arr - pointer for the array
 * index - index of the elem
 *
 * output:
 * pointer for the elem in the given index
*/
void* get_stud(const void *arr, int index)
{
    return (Stud*)arr + index;
}

//-----------------------------------------------------------------------------
/**
 * this function use to retrive the address of a stud elem in an array
 *
 * paramters:
 * arr - pointer for the array
 * index - index of the elem
 *
 * output:
 * pointer for the elem in the given index
*/
void* get_course(const void *arr, int index)
{
    return (Course*)arr + index;
}

//-----------------------------------------------------------------------------
bool read_stud(void *elem)
{
    Stud *stud = (Stud*) elem;

    cin >> stud->_stud_id;
    if (stud->_stud_id != 0)
    {
        read_data(stud->_grades, NUM_OF_GRADES, get_grade, read_grade);

        cin >> stud->_height;
    }

    return stud->_stud_id != 0;
}

//-----------------------------------------------------------------------------
bool read_course(void *elem)
{
    Course *course = (Course*) elem;

    cin >> course->_course_id;

    if (course->_course_id != 0)
    {
        cin >> course->_credit_point;
        cin >> course->_hours_of_course;
    }

    return course->_course_id != 0;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get pointer for an element in int array
 *
 * parameters:
 * arr - pointer for the array
 * index - the index of the element in the array
 *
 * output:
 * pointer for the element
*/
void* get_grade(const void *arr, int index)
{
    return (int*)arr + index;
}

//-----------------------------------------------------------------------------
/**
 * this function use to read int value into given pointer
 *
 * parameters:
 * elem - pointer for the element
 *
 * output:
 * bool value
*/
bool read_grade(void *elem)
{
    int grade;
    cin >> grade;
    *((int*)elem) = grade;
    return grade != -1;
}

//-----------------------------------------------------------------------------
/**
 * this generic function use to calculate the avarage of given array
 * the function returns a struct that contain the avg
 * and and index of the cell with the highest value in the array
 *
 * parameters:
 * data - pointer for the array
 * data_len - the size of the array
 * get_elem - pointer for a func that extract the relevant property from the
 * array, in the givven index, for the avg
 *
 * output:
 * avg_result struct
*/
Avg_result calc_avg(const void* data, int data_len,
                    get_double_elem_func get_elem)
{
    Avg_result result;
    int i = 0;
    double sum = 0;
    double value = 0;
    double biggest_value = value;
    int biggest_value_index = i;

    for(; i < data_len; i++)
    {
        if (get_elem(data, i, value))
        {
            sum += value;
            if (value > biggest_value)
            {
                biggest_value = value;
                biggest_value_index = i;
            }
        }
        else
            break;
    }

    result._avg = i != 0 ? sum / i : 0;
    result._max_index = biggest_value_index;

    return result;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get the credit point of given course
 *
 * parameters:
 * data - generic pointer for a given course struct
 *
 * output:
 * credit point
*/
bool get_credit_point(const void* data, int index, double& value)
{
    Course *course = (Course*)data + index;
    value = course->_credit_point;
    return course->_course_id != 0;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get the amount of hours of given course
 *
 * parameters:
 * data - a generic point for a given course struct
 *
 * output:
 * hours of course
*/
bool get_hours_of_cours(const void* data, int index, double& value)
{
    Course *course = (Course *)data + index;
    value = course->_course_id != 0 ? (double)course->_hours_of_course : 0;
    return course->_course_id != 0;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get the height of given student
 *
 * parameters:
 * data - a generic pointer for a given student struct
 *
 * output:
 * student height
*/
bool get_height(const void* data, int index, double& value)
{
    Stud *stud = (Stud*)data + index;
    value = stud->_height;
    return stud->_stud_id != 0;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get the double value from int pointer
 * paramters:
 * elem - generic pointer
 *
 * output:
 * double value
*/
bool get_double_from_int_elem(const void *elem, int index, double& value)
{
    int *data = (int *)elem + index;
    value = (double)*data;
    return value != -1;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get the avg value from given avg_result
 *
 * parameters:
 * result - generic point for the avg_result struct
 *
 * output:
 * avg
*/
bool get_avg_from_avg_result(const void *result, int index, double& value)
{
    Avg_result *avg_result = (Avg_result *)result + index;
    value = avg_result->_avg;
    return avg_result->_avg != 0;
}

//-----------------------------------------------------------------------------
/**
 * this function use to get avg of student grades
 * 
 * parameters:
 * data - pointer for the array
 * index - index of the student in the array
 * value - the avg
 * 
 * output:
 * is the value\element is relevant for the average
 */
bool get_stud_avg(const void* data, int index, double& value)
{
    Stud *stud = (Stud *)data + index;

    if (stud->_stud_id == 0)
        return false;

    Avg_result result = calc_avg(stud->_grades, NUM_OF_GRADES,
         get_double_from_int_elem);
    value = result._avg;

    return true;
}