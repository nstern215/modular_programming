/*
 * Ex #0: File encryption
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program reading from the user names of 3 files:
 * input_filename, encryptionkey_filename, encryptedFileFilename
 *
 * the program reading characters from the input file, and using the data
 * from the encryption key file, it encrypts the file and send the encrypted
 * data to the output file
 *
 * input:
 * names of 3 file: encryptionkey_filename, input_filename, encryptedFileFilename
 *
 * output:
 * encrypted content in the output file
 */

//----------------include section----------------
#include <iostream>
#include <iomanip>
#include <fstream>

//----------------using section----------------
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::setw;
using std::ifstream;
using std::ofstream;

//----------------constant section----------------
const int FILENAME_LENGTH = 100;

//----------------functions section
bool open_files(char input_filename[], char key_filename[], char output_filename[], ifstream& input_isr, ifstream& key_ist, ofstream& output_ostr);
void close_files(ifstream& input_isr, ifstream& key_ist, ofstream& output_ostr);
void encrypt_file(ifstream& input_file, ifstream& encryption_key_file, ofstream& output_file);
char encrypt_char(char to_encrypt, ifstream& encryption_key_file);

int main()
{
	//----------------variables section----------------
	ifstream input_file;
	ifstream encryption_key_file;
	ofstream encryptedFile;

	char input_filename[FILENAME_LENGTH];
	char encryptionkey_filename[FILENAME_LENGTH];
	char encryptedFileFilename[FILENAME_LENGTH];

	cout << "Enter encryption key filename, input filename, output filename" << endl;
	
	cin >> setw(FILENAME_LENGTH) >> encryptionkey_filename
		>> setw(FILENAME_LENGTH) >> input_filename
		>> setw(FILENAME_LENGTH) >> encryptedFileFilename;

	if (!open_files(input_filename, encryptionkey_filename, encryptedFileFilename, input_file, encryption_key_file, encryptedFile))
		return EXIT_FAILURE;

	encrypt_file(input_file, encryption_key_file, encryptedFile);

	close_files(input_file, encryption_key_file, encryptedFile);
	
	return EXIT_SUCCESS;
}

//----------------functions implementation-----------------

/*
 * this function use to open files
 * 
 * parameters:
 * input_filename: path to input file
 * key_filename: path encryption key file
 * output_filename: path to output file
 * inputIstr: reference for input file
 * key_istr: reference for encryption key file
 * output_ostr: reference for output file
 *
 * output:
 * If all files has open success - true
 * Otherwise - false
 */
bool open_files(char input_filename[], char key_filename[], char output_filename[], ifstream& input_isr, ifstream& key_ist, ofstream& output_ostr)
{
	input_isr.open(input_filename);
	if(!input_isr.is_open())
	{
		cerr << "Cannot open input file " << input_filename << endl;
		return false;
	}

	key_ist.open(key_filename);
	if(!key_ist.is_open())
	{
		cerr << "Cannot open encryption key file " << key_filename << endl;
		return false;
	}

	output_ostr.open(output_filename);
	if (!output_ostr.is_open())
	{
		cerr << "Cannot open output file " << output_filename << endl;
		return false;
	}

	return true;
}

/*
 * This function uses to close the open files
 * parameters:
 * inputIstr: reference for input file
 * key_istr: reference for encryption key file
 * output_ostr: reference for output file
 */
void close_files(ifstream& input_isr, ifstream& key_ist, ofstream& output_ostr)
{
	input_isr.close();
	key_ist.close();
	output_ostr.close();
}

/*
 * this function uses to encrypt the input file
 *
 * parameters:
 * inputIstr: reference for input file
 * key_istr: reference for encryption key file
 * output_ostr: reference for output file
 *
 * the function reading a single char from the input file. if this character is not an alphanumeric char,
 * its send to the output file and the function continue to the next char in the file.
 *
 * if it is, the function sending the char for encryption
 */
void encrypt_file(ifstream& input_file, ifstream& encryption_key_file, ofstream& output_file)
{
	char output_char;
	char input_char = input_file.get();
	
	while(!input_file.eof())
	{
		//if the char is not relevant for the encryption, sent for encryption, otherwise, use the original char
		if (isalpha(input_char))
			output_char = encrypt_char(input_char, encryption_key_file);
		else
			output_char = input_char;

		output_file << output_char;
		
		input_char = input_file.get();
	}
}

/*
 * this function uses to encrypt one char at a time
 *
 * the function starting to read chars from the encryption key file.
 * for each character in the key, it check if there is another alphanumeric char after (ex. space is possible)
 * if, it check if the char from the input file and the char from the key are equal, and if so, the char from
 * the input replacing by the *next* char from the key
 */
char encrypt_char(char to_encrypt, ifstream& encryption_key_file)
{
	char encrypt_key_char = encryption_key_file.get();
	char output_char = to_encrypt; //output_char use to store the output char (original from input or encrypted)

	//reading chars from the encryption key and look for a match with the char from the input file
	while (!encryption_key_file.eof())
	{
		if (isalpha(encryption_key_file.peek()))
		{
			if (to_encrypt == encrypt_key_char)
			{
				output_char = encryption_key_file.peek();
				break;
			}
		}

		encrypt_key_char = encryption_key_file.get();
	}

	//set back the pointer to the beginning of the encryption key file
	encryption_key_file.clear();
	encryption_key_file.seekg(-encryption_key_file.tellg(), std::ios::cur);

	return output_char;
}
