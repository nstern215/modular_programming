/*
file: ex4c_given.cpp
*/

#include "ex4c_given.h"

// *** global variables ***
const char* actions[] = {
  [INIT]   = "Init",
  [PRINT]  = "Print",
  [SORT]   = "Sort",
  [ADD]    = "Read Another",
  [EXIT]   = "Exit",
                        };
const int NUM_ACTIONS = sizeof(actions) / sizeof(actions[0]);

const char* types[] = {
  [DATE]   = "Date",
  [TIME]   = "Time",
                      };
const int NUM_TYPES = sizeof(types) / sizeof(types[0]);                        


/***************************
    Date functions  
***************************/
bool read_date(Date& date)
{
  cout << "Enter Date: " << std::flush;
  char ignore_ch;
  cin >> date._year;  
  if (date._year < 0)
    return false;
  
  cin >> ignore_ch
      >> date._month >> ignore_ch
      >> date._day;
  return true;
}
  
//-----------------------------------------
void print_date(const Date& date)
{
  cout << std::right << setfill('0') 
       << setw(2) << date._day << '/'
       << setw(2) << date._month << '/'
       << date._year
       << setfill(' ');
}

//-----------------------------------------
int comp_date(const Date d1, const Date d2)
{
  if (d1._year  > d2._year)  return 1;
  if (d1._year  < d2._year)  return -1;
  if (d1._month > d2._month) return 1;
  if (d1._month < d2._month) return -1;
  if (d1._day   > d2._day)   return 1;
  if (d1._day   < d2._day)   return -1;
  return 0;
}

//-----------------------------------------
void swap_date(Date& d1, Date& d2)
{
  Date temp = d1;
  d1 = d2;
  d2 = temp;
}

/***************************
    Time functions  
***************************/
bool read_time(Time& time)
{
  cout << "Enter Time: " << std::flush;
  cin >> time._hour;  
  if (time._hour < 0 || time._hour > 23)
    return false;
  
  char ignore_ch;
  cin >> ignore_ch
      >> time._minute >> ignore_ch
      >> time._second;
  return true;
}

//-----------------------------------------
void print_time(const Time& time)
{
  cout << std::right << setfill('0')
       << setw(2) << time._hour << ':'
       << setw(2) << time._minute << ':'
       << setw(2) << time._second
       << setfill(' ');
}

//-----------------------------------------
int comp_time(const Time t1, const Time t2)
{
  if (t1._hour   > t2._hour)   return 1;
  if (t1._hour   < t2._hour)   return -1;
  if (t1._minute > t2._minute) return 1;
  if (t1._minute < t2._minute) return -1;
  if (t1._second > t2._second) return 1;
  if (t1._second < t2._second) return -1;
  return 0;
}

//-----------------------------------------
void swap_time(Time& t1, Time& t2)
{
  Time temp = t1;
  t1 = t2;
  t2 = temp;
}


/***************************
    Select functions  
***************************/
Type select_type()
{
  int type;
  while (true)
  {
    cout << "select the type:" << endl;
    for (int j = 0; j < NUM_TYPES; j++)
      cout << std::left << setw(8) << types[j] << " : " << j << endl;
    cout << "Your selection: " << std::flush;
    cout.flush();
    cin >> type;
    if (type >= 0 && type < NUM_TYPES)
      break;
    cout << "*** Wrong Selection. ***" << endl << endl;
  }
  cout << "You selected \"" << types[type] 
       << '\"' << endl << endl;
  return Type (type);
}

//-----------------------------------------
Action select_action()
{
  int act;
  while (true)
  {
    cout << endl << "select the action:" << endl;
    for (int j = 0; j < NUM_ACTIONS; j++)
      cout << std::left << setw(14) << actions[j] << " : " << j << endl;
    cout <<"Your selection: " << std::flush;
    cin >> act;
    if (act >= 0 && act < NUM_ACTIONS)
      break;
    cout << "*** Wrong Selection. ***" << endl << endl;
  }
  cout << "You selected \"" << actions[act] 
       << '\"' << endl << endl;
  return Action (act);
}