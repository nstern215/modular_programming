/*
 * Ex #0: Files merging
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program reading from the user names of 3 files:
 * input_filename1, input_filename2, output_filename
 *
 * the program reading the entries from the input files
 * comparing the students names from each entry and printing the
 * merged result to the output file
 *
 * each entry contains student name and grades
 *
 * input:
 * names of 3 file: input_filename1, input_filename2, output_filename
 *
 * output:
 * content of merged files
 */

//---------------------include section-------------------
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

//---------------------using section---------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::ifstream;
using std::ofstream;

//---------------------constant section-------------------
const int FILENAME_LENGTH = 100;
const int MAX_LINE_SIZE = 200;

//---------------------functions section------------------
bool open_input_file(char filename[], ifstream& ifstr);
bool open_output_file(char filename[], ofstream& ostr);
void close_files(ifstream& input_file1, ifstream& input_file2,
    ofstream& output_file);
void merge_files(ifstream& input_file1, ifstream& input_file2,
    ofstream& output_file);
int compare_students(char student1[], char student2[]);
void copy_to_output(ifstream& input_file, ofstream& output_file);

int main()
{
    char input_filename1[FILENAME_LENGTH];
    char input_filename2[FILENAME_LENGTH];
    char output_filename[FILENAME_LENGTH];

    ifstream input_file1;
    ifstream input_file2;
    ofstream output_file;

    cin >> setw(FILENAME_LENGTH) >> input_filename1;
    if(!open_input_file(input_filename1, input_file1))
	{
		cerr << "Input file not found" << endl;
		exit(EXIT_FAILURE);
	}
    
    cin >> setw(FILENAME_LENGTH) >> input_filename2;
    if(!open_input_file(input_filename2, input_file2))
	{
		cerr << "Input file not found" << endl;
		exit(EXIT_FAILURE);
	}
    
    cin >> setw(FILENAME_LENGTH) >> output_filename;
	if (!open_output_file(output_filename, output_file))
		exit(EXIT_FAILURE);

    merge_files(input_file1, input_file2, output_file);
    close_files(input_file1, input_file2, output_file);
	
    return EXIT_SUCCESS;
}

//-------------------------functions implementation------------

/*
 * this function use to open an input file
 *
 * parameters:
 * filename: path to input file
 * ifstr: reference for input file
 *
 * output:
 * if file has open success - true
 * otherwise - false
 */
bool open_input_file(char filename[], ifstream& ifstr)
{
	ifstr.open(filename);
	return ifstr.is_open();
}

/*
 * this function use to open an input file
 *
 * parameters:
 * filename: path to output file
 * ostr: reference for output file
 *
 * output:
 * if file has open success - true
 * otherwise - false
 */
bool open_output_file(char filename[], ofstream& ostr)
{
	ostr.open(filename);
	return ostr.is_open();
}

/*
 * This function use to close open files
 *
 * parameters:
 * input_file1: reference for input_file1
 * input_file2: reference for input_file2
 * output_file: reference for output_file
 */
void close_files(ifstream& input_file1, ifstream& input_file2,
    ofstream& output_file)
{
    input_file1.close();
    input_file2.close();
    output_file.close();
}

/*
 * this function use to merge two input files
 * in each iteration, the function comparing lexicographic the student name
 * and based on the comparing result the function decide which line print
 * to the output file.
 * in case of equal names, the grades from the first file will print
 * first and then from the second file.
 * when one file is in the end, the leftover lines will copy to the output
 */
void merge_files(ifstream& input_file1, ifstream& input_file2,
    ofstream& output_file)
{
    char student_entry1[MAX_LINE_SIZE];
    char student_entry2[MAX_LINE_SIZE];

    int compare_results = 0;

	while (!input_file1.eof() || !input_file2.eof())
	{
		//read the next line\s based on the comparing results
        if (compare_results == -1)
            input_file1.getline(student_entry1, MAX_LINE_SIZE);
        else if (compare_results == -2)
            input_file2.getline(student_entry2, MAX_LINE_SIZE);
        else
        {
            input_file1.getline(student_entry1, MAX_LINE_SIZE);
            input_file2.getline(student_entry2, MAX_LINE_SIZE);
        }

        compare_results = compare_students(student_entry1, student_entry2);

        if (compare_results == -1) {
	        output_file << student_entry1 << endl;
	        cout << student_entry1 << endl;
	    }
        else if (compare_results == -2) {
	        output_file << student_entry2 << endl;
	        cout << student_entry2 << endl;
	    }
        else //merge equal lines
        {
			// printing the entry without line break in the end
			for (size_t i = 0; i < strlen(student_entry1) - 1; i++) {
				output_file << student_entry1[i];
				cout << student_entry1[i];
			}
            
        	//the compare_results is the index where the student name ends
            //and grades begin
            for (size_t i = compare_results; i < strlen(student_entry2); i++) {
         		output_file << student_entry2[i];
         		cout << student_entry2[i];
			}
         		
            output_file << endl;
            cout << endl;
        }
	}

    if (compare_results == -1) {
        output_file << student_entry2 << endl;
        cout << student_entry2 << endl;
	}
    else if (compare_results == -2) {
        output_file << student_entry1 << endl;
        cout << student_entry1 << endl;
    }

    copy_to_output(input_file1, output_file);
    copy_to_output(input_file2, output_file);
}

/*
 * this function use to copy input file content to the output
 * the copy is not necessarily from the beginning of the file
 *
 * parameters:
 * input_file: reference for file to copy from
 * output_file: reference for file to copy to
 */
void copy_to_output(ifstream& input_file, ofstream& output_file)
{
    char line[MAX_LINE_SIZE];

    while (!input_file.eof())
    {
        input_file.getline(line, MAX_LINE_SIZE);
        output_file << line << endl;
        cout << line << endl;
    }
}

/*
 * This function use to compare two students entries by student name
 * the function comparing each character,
 * by comparing the numeric value of each char
 *
 * if the fist student is lexicographic bigger the function return -1
 * if the second student is lexicographic bigger the function return -2
 * if the students are equals the function return the index
 * where the student name ends
 *
 * parameters:
 * student1: student1 entry
 * student2: student2 entry
 *
 * output:
 * -1 if student1 bigger that student2
 * -2 number smaller than 0 if student1 smaller that student2
 * positive number if student1 and student2 are equals
 */
int compare_students(char student1[], char student2[])
{
    int counter = 0;

    while(student1[counter] != '\n' || student2[counter] != '\n')
    {
        if (!isalpha(student1[counter]) && !isalpha(student2[counter]))
            return counter;
        if (student1[counter] < student2[counter])
            return -1;
        if (student1[counter] > student2[counter])
            return -2;
        
		counter++;
    }
	
    return counter;
}
