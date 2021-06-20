/*
file: ex4c_given.h
*/

#include <iostream>
#include <iomanip> // for formatting the output
#include <stdlib.h>
#include <fstream>
// #include "debug.cpp"
#include <cstring>
#include <new>

using std::endl;
using std::cout;
using std::cerr;
using std::cin;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::ifstream;
using std::nothrow;
using std::flush;

//*** Enum declarations ***
enum Action {INIT, PRINT, SORT, ADD, EXIT};
enum Type {DATE, TIME};

//*** Constant declarations ***
const int NAME_LEN = 10;


//*** Struct declarations ***
struct Date{
  int _year;
  int _month;
  int _day;
};

struct Time{
  short _hour;
  short _minute;
  short _second;
};


// *** function prototypes 
bool  read_date(Date& date1);
void  print_date(const Date& date);
int   comp_date(const Date d1, const Date d2);
void  swap_date(Date& d1, Date& d2);
void  copy_date(Date& dest, const Date& src);
void* alloc_date_arr(int size);
void* item_date_at(void* ptr, int indx);

bool  read_time(Time& time);
void  print_time(const Time& time);
int   comp_time(const Time t1, const Time t2);
void  swap_time(Time& t1, Time& t2);
void  copy_time(Time& dest, const Time& src);
void* alloc_time_arr(int size);
void* item_time_at(void* ptr, int indx);

Type select_type();
Action select_action();




