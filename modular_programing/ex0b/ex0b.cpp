/*
 * Ex #0: File dencryption
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program reading from the user names of 2 files:
 * encrypted_filename, input_file
 *
 * the program reading characters from the input file, and using the data
 * from the encryption key file, it encrypts the file and send the encrypted
 * data to the output file
 *
 * the program summering the amount of instances of the chars in the files,
 * sorting the chars by the num of instances, and base on this information
 * setting decryption key and printing the decrypted file
 *
 * input:
 * names of 2 file: encrypted_filename, input_file
 *
 * output:
 * content of decrypted file
 */

//------------------include section------------------
#include <fstream>
#include <iostream>
#include <iomanip>

//------------------using section------------------
using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::setw;
using std::ifstream;

//------------------constant section------------------
const int FILENAME_LENGtH = 100;
const int LETTERS_AMOUNT = 26;
const int COLUMNS = 2; //num of columns in 2d array using to count chars
const int LETTER_INDEX_COLUMN = 0;
const int LETTER_AMOUNT_COLUMN = 1;
const char BASE_LETTER_ID = 'a';

//------------------functions section------------------
bool open_files(char input_filename[], char encrypted_filename[], 
    ifstream& input_file, ifstream& encrypted_file);
void close_files(ifstream& input_file, ifstream& encrypted_file);
void decrypt_file(ifstream& encrypted_file, ifstream& input_file);
void count_chars_in_file(ifstream& ifstr, 
    int chars_sum[LETTERS_AMOUNT][COLUMNS]);
void initial_chars_sum_array(int arr[LETTERS_AMOUNT][COLUMNS]);
void order_array_by_char_instances(int arr[LETTERS_AMOUNT][COLUMNS]);
void analyze_file(ifstream& ifstr, 
    int chars_sum_array[LETTERS_AMOUNT][COLUMNS]);

int main()
{
    char encrypted_filename[FILENAME_LENGtH];
	char input_filename[FILENAME_LENGtH];

    ifstream input_file;
    ifstream encrypted_file;

    cout << "Enter encrypted filename and input filename" << endl;

    cin >> setw(FILENAME_LENGtH) >> encrypted_filename
        >> setw(FILENAME_LENGtH) >> input_filename;

	if(!open_files(input_filename, encrypted_filename, input_file, 
        encrypted_file))
        return EXIT_FAILURE;

    decrypt_file(encrypted_file, input_file);

    close_files(encrypted_file, input_file);
	
    return EXIT_SUCCESS;
}

//------------------functions implementation------------------

/*
 * this function use to open files
 *
 * parameters:
 * encrypted_filename: path to encrypted file
 * input_filename: path to input file
 * input_file: reference for input file
 * encrypted_file: reference for encrypted file
 *
 * output:
 * If all files has open success - true
 * Otherwise - false
 */
bool open_files(char input_filename[], char encrypted_filename[],
    ifstream& input_file, ifstream& encrypted_file)
{
    input_file.open(input_filename);
    if(!input_file.is_open())
    {
        cerr << "input file to decrypt was not found" << endl;
        return false;
    }

    encrypted_file.open(encrypted_filename);
	if(!encrypted_file.is_open())
	{
        cerr << "plain file was not found" << endl;
        return false;
	}
	
    return true;
}

/*
 * This function uses to close the open files
 * parameters:
 * input_file: reference for input file
 * encrypted_file: reference for encrypted file
 */
void close_files(ifstream& input_file, ifstream& encrypted_file)
{
    input_file.close();
    encrypted_file.close();
}

/*
 * this function uses to initial chars array
 * by setting the first column with the char code (as an int value)
 * and the second column, counter column, to 0
 *
 * parameters:
 * arr: array for initialization
 */
void initial_chars_sum_array(int arr[LETTERS_AMOUNT][COLUMNS])
{
	for (int i = 0; i < LETTERS_AMOUNT; i++)
	{
		arr[i][LETTER_INDEX_COLUMN] = BASE_LETTER_ID + i;
        arr[i][LETTER_AMOUNT_COLUMN] = 0;
	}
}

/*
 * this function uses to count instances of characters in the file
 * and summarize into 2d array.
 * In the array, the first column store the numeric code of the char
 * the second column store the amount of instances
 *
 * parameters:
 * ifstr: reference for the input file
 * chars_sum: the array used to store the summarized chars
 * 
 */
void count_chars_in_file(ifstream& ifstr, 
    int chars_sum[LETTERS_AMOUNT][COLUMNS])
{
    char input_char = ifstr.get();

    while (!ifstr.eof())
    {
	    if(isalpha(input_char))
            //the array index runs from 0 to 25. index 0 for 'a', 1 for 'b' etc
            //to find the correct index for each letter, need to subtract
            //the integer value of 'a', (the first index),
            //from the input_char variable
            chars_sum[input_char - 'a'][LETTER_AMOUNT_COLUMN]++;

        input_char = ifstr.get();
    }

	//reset the reading pointer to the beginning of the file
    ifstr.clear();
    ifstr.seekg(-ifstr.tellg(), std::ios::cur);
}

/*
 * this function uses to sort the chars instances array into descending order
 * using bubble sort
 * the value the function look for, is in the second column in the array
 * that represent the amount of instances of the char in the file
 *
 * parameters: array to sort
 */
void order_array_by_char_instances(int arr[LETTERS_AMOUNT][COLUMNS])
{
    int letter_index;
    int letter_amount;

    for (int i = LETTERS_AMOUNT; i > 0; i--)
        for (int j = LETTERS_AMOUNT - i; j > 0; j--)
            if (arr[j][1] > arr[j - 1][LETTER_AMOUNT_COLUMN])
            {
                letter_index = arr[j][LETTER_INDEX_COLUMN];
                letter_amount = arr[j][LETTER_AMOUNT_COLUMN];

                arr[j][LETTER_INDEX_COLUMN] = arr[j - 1][LETTER_INDEX_COLUMN];
                arr[j][1] = arr[j - 1][LETTER_AMOUNT_COLUMN];

                arr[j - 1][LETTER_INDEX_COLUMN] = letter_index;
                arr[j - 1][LETTER_AMOUNT_COLUMN] = letter_amount;
            }
}

/*
 * this function uses to analyze the content of the file
 * by counting the number of instances of each alphabetic chars,
 * initializing the chars sum array, and put the results into the array
 * when the data is in the array, the array is sorted, using bubble sort,
 * to descending order array by the num of instances of each char
 * (second column)
 *
 * parameters:
 * ifstr: reference to the file for the analyzing action
 * char_sum_array: array that saves amount of instances of chars in the file
 */
void analyze_file(ifstream& ifstr, 
    int chars_sum_array[LETTERS_AMOUNT][COLUMNS])
{
    initial_chars_sum_array(chars_sum_array);

    count_chars_in_file(ifstr, chars_sum_array);

    order_array_by_char_instances(chars_sum_array);
}

/*
 * this function doing the decryption action on the encrypted file
 * first, encrypted and input files sent to analyze by the analyze function
 *
 * during the analyzing action, the chars array are set in order we can use
 * to decrypt chars by looking for the index of the encrypted char in the
 * encrypted_file_chars_array and take the equivalent char
 * with the same array index
 * in the input_file_chars_array
 *
 * parameters:
 * encrypted_file: file to decrypt
 * input_file: plain file
 */
void decrypt_file(ifstream& encrypted_file, ifstream& input_file)
{
    int encrypted_file_chars_array[LETTERS_AMOUNT][COLUMNS];
    int input_file_chars_array[LETTERS_AMOUNT][COLUMNS];

    analyze_file(encrypted_file, encrypted_file_chars_array);
    analyze_file(input_file, input_file_chars_array);

    char encrypted_char = encrypted_file.get();
    //decrypted_char used to set the char will send to output,
	//decrypted or original
	char decrypted_char = encrypted_char; 
	
    while(!encrypted_file.eof())
	{
		for (int i = 0; i < LETTERS_AMOUNT; i++)
            if (encrypted_file_chars_array[i][LETTER_INDEX_COLUMN] 
                == encrypted_char)
            {
                decrypted_char = 
                    input_file_chars_array[i][LETTER_INDEX_COLUMN];
                break;
            }

        cout << decrypted_char;

        encrypted_char = encrypted_file.get();
        decrypted_char = encrypted_char;
	}
}
