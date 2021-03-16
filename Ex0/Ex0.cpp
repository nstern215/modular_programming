/*
 * Ex #0: File encryption
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program reading from the user names of 3 files:
 * inputFilename, encryptionKeyFilename, encryptedFileFilename
 *
 * the program reading characters from the input file, and using the data
 * from the encryption key file, it encrypts the file and send the encrypted
 * data to the output file
 *
 * input:
 * names of 3 file: inputFilename, encryptionKeyFilename, encryptedFileFilename
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

//----------------functions section
bool open_files(char inputFilename[], char keyFilename[], char outputFilename[], ifstream& inputIsr, ifstream& keyIst, ofstream& outputOstr);
void close_files(ifstream& inputIsr, ifstream& keyIst, ofstream& outputOstr);
void encrypt_file(ifstream& inputFile, ifstream& encryptionKeyFile, ofstream& outputFile);

//----------------constant section----------------
const int FILENAME_LENGTH = 100;
const int CHAR_ENCRYPT_KEY_SIZE = 3;
const int LINE_SIZE = 100;

int main()
{
	//----------------variables section----------------
	ifstream inputFile;
	ifstream encryptionKeyFile;
	ofstream encryptedFile;

	char inputFilename[FILENAME_LENGTH];
	char encryptionKeyFileName[FILENAME_LENGTH];
	char encryptedFileFilename[FILENAME_LENGTH];

	cout << "Enter input filename, encryption key filename, output filename" << endl;

	cin >> setw(FILENAME_LENGTH) >> inputFilename
		>> setw(FILENAME_LENGTH) >> encryptionKeyFileName
		>> setw(FILENAME_LENGTH) >> encryptedFileFilename;

	if (!open_files(inputFilename, encryptionKeyFileName, encryptedFileFilename, inputFile, encryptionKeyFile, encryptedFile))
		return EXIT_FAILURE;

	encrypt_file(inputFile, encryptionKeyFile, encryptedFile);

	close_files(inputFile, encryptionKeyFile, encryptedFile);
	
	return EXIT_SUCCESS;
}

//----------------functions implementation-----------------

/*
 * this function use to open files
 * 
 * parameters:
 * inputFilename: path to input file
 * keyFilename: path encryption key file
 * outputFilename: path to output file
 * inputIstr: reference for input file
 * keyIstr: reference for encryption key file
 * outputOstr: reference for output file
 *
 * output:
 * If all files has open success - true
 * Otherwise - false
 */
bool open_files(char inputFilename[], char keyFilename[], char outputFilename[], ifstream& inputIsr, ifstream& keyIst, ofstream& outputOstr)
{
	inputIsr.open(inputFilename);
	if(!inputIsr.is_open())
	{
		cerr << "Cannot open input file " << inputFilename << endl;
		return false;
	}

	keyIst.open(keyFilename);
	if(!keyIst.is_open())
	{
		cerr << "Cannot open encryption key file " << keyFilename << endl;
		return false;
	}

	outputOstr.open(outputFilename);
	if (!outputOstr.is_open())
	{
		cerr << "Cannot open output file " << outputFilename << endl;
		return false;
	}

	return true;
}

/*
 * This function uses to close the open files
 * parameters:
 * inputIstr: reference for input file
 * keyIstr: reference for encryption key file
 * outputOstr: reference for output file
 */
void close_files(ifstream& inputIsr, ifstream& keyIst, ofstream& outputOstr)
{
	inputIsr.close();
	keyIst.close();
	outputOstr.close();
}

/*
 * this function uses to encrypt the input file
 *
 * parameters:
 * inputIstr: reference for input file
 * keyIstr: reference for encryption key file
 * outputOstr: reference for output file
 *
 * the function reading a single char from the input file. if this character is not an alphanumeric char,
 * its send to the output file and the function continue to the next char in the file.
 *
 * if it is, the function starting to read chars from the encryption key file.
 * for each character in the key, it check if there is another alphanumeric char after (ex. space is possible)
 * if, it check if the char from the input file and the char from the key are equal, and if so, the char from
 * the input replacing by the *next* char from the key
 */
void encrypt_file(ifstream& inputFile, ifstream& encryptionKeyFile, ofstream& outputFile)
{
	//outputChar use to store the output char (original from input or encrypted)
	char inputChar, outputChar, encryptChar;

	inputChar = inputFile.get();
	
	while(!inputFile.eof())
	{
		outputChar = inputChar;

		//if the char is not relevant for the encryption, skip to the next iteration
		if (!isalpha(outputChar))
		{
			outputFile << outputChar;

			inputChar = inputFile.get();
			
			continue;
		}
		
		encryptChar = encryptionKeyFile.get();
		//reading chars from the encryption key and look for a match with the char from the input file
		while(!encryptionKeyFile.eof())
		{
			if (isalpha(encryptionKeyFile.peek()))
			{
				if (inputChar == encryptChar)
				{
					outputChar = encryptionKeyFile.peek();
					break;
				}
			}
			
			encryptChar = encryptionKeyFile.get();
		}

		//set back the pointer to the beginning of the encryption key file
		encryptionKeyFile.clear();
		encryptionKeyFile.seekg(-encryptionKeyFile.tellg(), std::ios::cur);

		outputFile << outputChar;
		
		inputChar = inputFile.get();
	}
}
