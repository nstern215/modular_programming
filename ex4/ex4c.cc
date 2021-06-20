/*
file: ex4c.cpp

The goal of this program is to create (initialize) dynamic array, sort it, print it 
and add new elements to it.

The array can be of any type. Specific in this exercise, Date or Time.

*/
#include "ex4c_given.h"

void my_exit(int line, const char* msg)
{
	cerr << "internal error in line " << line
		<< " ; " << msg << endl;
	exit(1);
}

// ***  Generic functions and types  ***
typedef bool  (*read_item)  (void*);
typedef void  (*print_item) (void*);
typedef int   (*comp_items) (const void*, const void*);
typedef void  (*swap_items) (void*, void*);
typedef void  (*copy_item)  (void*, const void*); // first arg is destination
typedef void* (*alloc_arr)  (int size);
typedef void* (*alloc_item) ();
typedef void  (*delete_arr) (void*&);
typedef void  (*delete_item)(void*&);
typedef void* (*get_elem)    (void* ptr, int index);


//*** Struct declarations ***
//struct to represent the data array
struct Arr_Struct {
	void* _arr;
	int     _size;
	int     _capacity;
};

struct Functions {
	read_item   _read_item;
	print_item  _print_item;
	comp_items  _comp_item;
	swap_items  _swap_item;
	copy_item   _copy_item;
	alloc_arr   _alloc_arr;
	alloc_item  _alloc_item;
	delete_arr  _delete_arr;
	delete_item _delete_item;
	get_elem     _get_elem;

};


/*===================================================
==  Date functions and Date Wrap Functions        ==*
===================================================*/
//==================================================
/**
 * this function use to execute the actual read date function
 * this function get a generic pointer, and after conversion,
 * read the data into the array
 * 
 * parameters:
 * arr - pointer to the array
 * 
 * output:
 * bool value, if the entered data is valid
*/
bool read_date_elem(void* arr) {
	return read_date(*(Date*)arr);

}
//==================================================
/**
 * this functio use to convert the generic pointer to
 * a Date pointer and than call the date point function
 * 
 * parameters:
 * arr - pointer for the array
*/
void print_data_elem(void* arr) {
	print_date(*(Date*)arr);
}
//==================================================
/**
 * this function use to convert two generic pointers to
 * Date pointer and then call the function to compare them
 * 
 * paramters:
 * date1, date2 - pointers for the dates elements to compare
 * 
 * output:
 * 1 if date1 > date2
 * -1 if date1 < date2
 * 0 if date1 = date2
*/
int comp_date_elem(const void* date1, const void* date2) {
	return comp_date(*(Date*)date1, *(Date*)date2);
}
//==================================================
/**
 * this function use to convert two generic pointers to
 * Date pointer and then call the swap function
 * 
 * parameters:
 * date1, date2 - pointers for dates elemets to swap the content
*/
void swap_data_elem(void* date1, void* date2) {
	swap_date(*(Date*)date2, *(Date*)date2);
}
//==================================================
/**
 * thid function use to copy content of a date element
 * 
 * parameters:
 * destinatin - the destination of the copy
 * source - the source of the copy
*/
void copy_date(void* destination, const void* source) {
	*(Date*)destination = *(Date*)source;
}
//==================================================
/**
 * this function use to allocate memory for the date array
 * 
 * parameters:
 * size - the require size of the array
*/
void* allocate_date_arr(int size) {

	void* new_arr = new (nothrow) Date[size];
	
  if (!new_arr) {
		cerr << "Failed to allocate memory" << endl;
		exit(EXIT_FAILURE);
	}

	return new_arr;
}
//==================================================
/**
 * this function use to allocate memory for the time array
 * 
*/
void* allocate_date_item() {

	void* new_item = new (nothrow) Date;
	
  if (!new_item) {
		cerr << "Failed to allocate memory" << endl;
		exit(EXIT_FAILURE);
	}

	return new_item;
}
//==================================================
/**
 * this function use to delete the date array
 * 
 * parameters:
 * arr - a referece to the pointer that point to the array
*/
void delete_date_arr(void*& arr) {
	delete[](Date*)arr;
}
//==================================================
/**
 * this function use to delete date elem
 * 
 * parameters:
 * arr - a referece to the pointer that point to the element
*/
void delete_date_item(void*& date) {
	delete (Date*)date;
}
//==================================================
/**
 * this function use to get a date item from the array
 * 
 * parameters:
 * arr - generic pointer for the array
 * index - the index of the date elem in the array
 * 
 * output:
 * pointer for the elem in the given index
*/
void* get_date(void* arr, int index) {
	return (Date*)arr + index;
}

/*===================================================
==  Time functions and Time Wrap Functions         ==
===================================================*/
/**
 * this function use to execute the actual read time function
 * this function get a generic pointer, and after conversion,
 * read the time into the array
 * 
 * parameters:
 * arr - pointer to the array
 * 
 * output:
 * bool value, if the entered data is valid
*/
bool read_time_elem(void* arr) {
	return read_time(*(Time*)arr);

}
//==================================================
/**
 * this functio use to convert the generic pointer to
 * a Time pointer and than call the time print function
 * 
 * parameters:
 * arr - pointer for the array
*/
void print_time_elem(void* arr) {
	print_time(*(Time*)arr);
}

//==================================================
/**
 * this function use to convert two generic pointers to
 * Time pointer and then call the function to compare them
 * 
 * paramters:
 * time1, time2 - pointers for the times elements to compare
 * 
 * output:
 * 1 if time1 > time2
 * -1 if time1 < time2
 * 0 if time1 = time2
*/
int comp_time_elem(const void* time1, const void* time2) {
	return comp_time(*(Time*)time1, *(Time*)time2);
}

//==================================================
/**
 * this function use to convert two generic pointers to
 * Time pointer and then call the swap function
 * 
 * parameters:
 * time1, time2 - pointers for dates elemets to swap the content
*/
void swap_time_elem(void* time1, void* time2) {
	swap_time(*(Time*)time1, *(Time*)time2);
}

//==================================================
/**
 * thid function use to copy content of a time element
 * 
 * parameters:
 * destinatin - the destination of the copy
 * source - the source of the copy
*/
void copy_time(void* destination, const void* source) {

	*(Time*)destination = *(Time*)source;

}
//==================================================
/**
 * this function use to allocate memory for the time array
 * 
 * parameters:
 * size - the require size of the array
*/
void* allocate_time_arr(int size) {

	void* new_arr = new (nothrow) Time[size];
	
  if (!new_arr)
  {
		cerr << "Failed to allocate memory" << endl;
		exit(EXIT_FAILURE);
	}

	return new_arr;
}
//==================================================
/**
 * this function use to allocate memory for the time array
 * 
*/
void* allocate_time_item() {

	void* new_item = new (nothrow) Time;

	if (!new_item) {
		cerr << "Failed to allocate memory" << endl;
		exit(EXIT_FAILURE);
	}

	return new_item;
}
//==================================================
/**
 * this function use to delete the time array
 * 
 * parameters:
 * arr - a referece to the pointer that point to the array
*/
void delete_time_arr(void*& arr) {
	delete[](Time*)arr;
}
//==================================================
/**
 * this function use to delete time elem
 * 
 * parameters:
 * arr - a referece to the pointer that point to the element
*/
void delete_time_item(void*& time) {
	delete (Time*)time;
}
//==================================================
/**
 * this function use to get a time item from the array
 * 
 * parameters:
 * arr - generic pointer for the array
 * index - the index of the time elem in the array
 * 
 * output:
 * pointer for the elem in the given index
*/
void* get_time(void* arr, int index) {
	return (Time*)arr + index;
}

/*===================================================
==         ex4c generic functions                 ==*
===================================================*/

//  ****  global variables ***
const Functions DATE_FUNCS = {
		read_date_elem,
		print_data_elem,
		comp_date_elem,
		swap_data_elem,
		copy_date,
		allocate_date_arr,
		allocate_date_item,
		delete_date_arr,
		delete_date_item,
		get_date,

};

const Functions TIME_FUNCS = {
		read_time_elem,
		print_time_elem,
		comp_time_elem,
		swap_time_elem,
		copy_time,
		allocate_time_arr,
		allocate_time_item,
		delete_time_arr,
		delete_time_item,
		get_time,

};

//==================================================
/**
 * this function use to change the array size
 * the array capcity will be multiple by 2
 * 
 * the function will create a new bigger array, copy all data to the
 * new array and delete the old array
 * 
 * parameters:
 * arr - a reference for the array
 * functions - a pointer fot the function by the selected data type
*/
void resize_arr(Arr_Struct& arr, const Functions* functions) {

	arr._capacity *= 2;

	//setting new array that has more capacity
	void* new_arr = functions->_alloc_arr(arr._capacity);

	//copying data from the old to the new array
	for (int i = 0; i < arr._size; ++i)
		functions->_copy_item(functions->_get_elem(new_arr, i),
			(functions->_get_elem(arr._arr, i)));

	//deleting the old one and pointing to the new one
	functions->_delete_arr(arr._arr);
	arr._arr = new_arr;

}
//==================================================
/**
 * this function use to read data from the uset into the data array
 * 
 * parameters:
 * arr - reference for the array
 * functions - a pointer fot the function by the selected data type
 * 
 * output:
 * bool value, true if the data insterted into the array
 * otherwise - fale, can cause by invalid data
*/
bool add_item(Arr_Struct& arr, const Functions* functions) {

	// allocating an item and verifying is an input that can be added to the
	// array
	void* temp = functions->_alloc_item();
	if (!functions->_read_item(temp)) {
		functions->_delete_item(temp);
		return false;
	}

	//sending the array to duplicate its capacity
	if (arr._size == arr._capacity)
		resize_arr(arr, functions);

	//copying data from the allocated item to the array and
	//deleting the temp item
	functions->_copy_item((functions->_get_elem(arr._arr, arr._size++)), temp);
	functions->_delete_item(temp);

	return true;
}
//==================================================
/**
 * this function use to initialize the data array by deleting
 * all existing content and set the capacity to 2
*/
void init_arr(Arr_Struct& arr, const Functions* functions) {

	//every time we initialize, we delete the previous array
	if (arr._arr)
		functions->_delete_arr(arr._arr);

	//initializing the array:
	arr._capacity = 2;
	arr._size = 0;
	arr._arr = functions->_alloc_arr(arr._capacity);

	//add_item returns 0 if the input is -1
	while (add_item(arr, functions));

}

//==================================================
/**
 * this function use to print the array metadata and content
 * 
 * parameters:
 * arr - reference for the array
 * functions - a pointer fot the function by the selected data type
*/
void print_arr(const Arr_Struct& arr, const Functions* functions)
{
	cout << "Size = " << arr._size
		<< " Capacity = " << arr._capacity << endl;

	for (int j = 0; j < arr._size; j++)
	{
		functions->_print_item(functions->_get_elem(arr._arr, j));

		cout << endl;
	}
}
//==================================================
/**
 * this function use to sort the data in the array
 * using bubble sort logic
 * 
 * parameters:
 * arr - reference fot the array
 * functions - a pointer fot the function by the selected data type
*/
void sort_arr(Arr_Struct& arr, const Functions* functions) {

	for (int round = 0; round < arr._size - 1; ++round) {
		for (int place = 0; place < arr._size - round - 1; ++place) {

			//setting 2 items to analize if they have to be swapped
			void* item1 = functions->_get_elem(arr._arr, place);
			void* item2 = functions->_get_elem(arr._arr, place + 1);
			if (functions->_comp_item(item1, item2) == 1)
				functions->_swap_item(item1, item2);
		}
	}
}
//==================================================
int main(int argc, char** argv)
{
	//setting a pointer that will point to a struct of functions
	// (in this case Date* or Time* functions
	const Functions* func_ptr = nullptr;

	//setting a struct that will have the array itself, its size and capacity
	Arr_Struct arr;
	arr._arr = nullptr;
	arr._capacity = 0;
	arr._size = 0;

	//selecting if we want Date* or Time* functions
	Type type = select_type();

	switch (type)
	{
	case DATE:  func_ptr = &DATE_FUNCS;
		break;
	case TIME: func_ptr = &TIME_FUNCS;
		break;
	default: my_exit(__LINE__, "bad Type");
	};

	while (true)
	{
		//selecting which activity the user wants to apply on the array
		Action act = select_action();

		switch (act)
		{
		case INIT:  init_arr(arr, func_ptr);
			break;
		case PRINT: print_arr(arr, func_ptr);
			break;
		case SORT:  sort_arr(arr, func_ptr);
			break;
		case ADD:   add_item(arr, func_ptr);
			break;
		case EXIT:
			if (arr._arr)
				func_ptr->_delete_arr(arr._arr);
			exit(0);
		default: my_exit(__LINE__, "bad action code");
		}
	}
}
//-----------------------------------------------