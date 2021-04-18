/*
 * Ex #1: Sentences and strings
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program read sentences from the user and store in a mtrix
 * inside a struct
 * then, the program break each sentence into strings
 * each string is only one word (split the sentence by the space)
 * 
 * input:
 * num of rows in the matrix and content of each row
 *
 * output:
 * sum of the matrix
 */

//-------------------include section-------------------------------------------
#include <iostream>
#include <iomanip>
#include <cstring>

//-------------------using section---------------------------------------------
using std::cin;
using std::setw;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

//------------------struct section---------------------------------------------
struct Sentences
{
   char **_data;
   int _num_of_sentences;
};

//------------------functions section------------------------------------------
char **allocate_matrix(int size);
void read_sentences(Sentences& sentences);
int count_strings(const Sentences& sentences);
int count_strings_in_sentence(const char *sentence);
void free_memory(Sentences& sentences, Sentences *strings);
Sentences *sentences_to_strings(const Sentences& sentences);
void print_sentences(const Sentences* sentences);

//------------------constant section-------------------------------------------
const int SENTENCE_MAX_LEN = 1000;

int main()
{
    //variables
    int num_of_sentences;
    Sentences sentences;
    Sentences *strings;

    //read num of sentences
    cin >> num_of_sentences;
    cin.get();

    //allocating memory for the matrix and initialize the struct
    sentences._data = allocate_matrix(num_of_sentences);
    sentences._num_of_sentences = num_of_sentences;

    read_sentences(sentences);

    strings = sentences_to_strings(sentences);

    print_sentences(strings);

    free_memory(sentences, strings);
}

//------------------functions section------------------------------------------

/**
 * this function use to allocate memory for char matrix
 * the matrix is a char pointer for an array of char pointers
 * 
 * parameters:
 * size: the size of the matrix (or, size of the array)
 * 
 * output:
 * matrix pointer
*/
char **allocate_matrix(int size)
{
    char **arr = new (nothrow) char*[size];

    if(arr == nullptr)
        cerr << "Failed to allocate memory" << endl;

    return arr;
}

//-----------------------------------------------------------------------------
/**
 * this function use read sentences from the user into the struct
 * each sentence is a full input line
 * with max length that set by SENTENCE_MAX_LEN
*/
void read_sentences(Sentences& sentences)
{
    char sentence[SENTENCE_MAX_LEN];
    
    for (int i = 0; i < sentences._num_of_sentences; i++)
    {
        cin.getline(sentence, SENTENCE_MAX_LEN);
    
        //allocate memory for the sentence in the matrix
        char *str = new (nothrow) char[SENTENCE_MAX_LEN];
        if (str == nullptr)
            cerr << "Failed to allocate memory" << endl;

        //copy the string to the allocated memory
        strcpy(str, sentence);
    
        sentences._data[i] = str;
    }
}

//-----------------------------------------------------------------------------

/**
 * this functio use to break sentences into strings.
 * first the function count the require space and allocating memory
 * than, for each sentence, the function look for spaces, and by the spaces
 * break the sentence into strings
 * 
 * paremters:
 * sentences: reference for the struct
 * 
 * output:
 * pointer for a new struct contains the strings
*/
Sentences *sentences_to_strings(const Sentences& sentences)
{
    Sentences *strings = new (nothrow) Sentences;
    //num of strings in sentences matrix
    int num_of_strings = count_strings(sentences);
    strings->_num_of_sentences = num_of_strings;
    //allocating new matrix for the strings
    strings->_data = new (nothrow) char*[num_of_strings];
    if (strings->_data == nullptr)
        cerr << "Failed to allocate memory" << endl;

    int str_index = 0; //use as index in the new matrix
    int len = 0; // use to calculate the string length in the sentence

    //in each iteration, break one sentence into strings
    for (int i = 0; i < sentences._num_of_sentences; i++)
        for (int j = 0; sentences._data[i][j] != '\0'; j++)
        {
            if (!isspace(sentences._data[i][j]))
                len++;
            //if the next char is space or null => end of strin
            if (isspace(sentences._data[i][j + 1]) || 
                sentences._data[i][j + 1] == '\0')
            {
                //allocating memory for the string
                strings->_data[str_index] = new (nothrow) char[len + 1];
                if (strings->_data[str_index] == nullptr)
                    cerr << "Failed to allocate memory" << endl;         

                //copy the chars that belong to this specific string
                //into the new strings matrix
                for (int k = 0; k < len; k++)
                    strings->_data[str_index][k] = 
                        sentences._data[i][j - len + 1 + k];

                len = 0;
                str_index++;

            }

        }


    return strings;
}

//-----------------------------------------------------------------------------

/**
 * this function use to count how many strings are in the sentences matrix
 * 
 * parameters:
 * sentences: reference for sentences struct
 * 
 * output:
 * num of sentences
*/
int count_strings(const Sentences& sentences)
{
    int count = 0;
    for (int i = 0; i < sentences._num_of_sentences; i++)
        count += count_strings_in_sentence(sentences._data[i]);

    return count;
}

//-----------------------------------------------------------------------------

/**
 * this function use to count strings in one sentence
 * 
 * paramters:
 * sentence: pointer for a string (or a sentence)
 * 
 * output:
 * num of strings in the given sentence
*/
int count_strings_in_sentence(const char *sentence)
{
    int count = 0;

    for (int i = 0; sentence[i] != '\0'; i++)
        if (isspace(sentence[i]) || sentence[i + 1] == '\0')
            count++;


    return count;
}

//-----------------------------------------------------------------------------
/**
 * releasing the allocated memory
 * 
 * parameters:
 * sentences: reference for senteces from the user
 * strings: pointer for sentences struct contains strings
*/
void free_memory(Sentences& sentences, Sentences *strings)
{
    for (int i = 0; i < sentences._num_of_sentences; i++)
        delete[] sentences._data[i];

    delete[] sentences._data;

    for (int i = 0; i < strings->_num_of_sentences; i++)
        delete[] strings->_data[i];

    delete[] strings->_data;
    delete strings;
}

//-----------------------------------------------------------------------------

/**
 * this function use to print the strings
 * 
 * paramters:
 * sentences: pointer for a sentences struct
*/
void print_sentences(const Sentences* sentences)
{
    for (int i = 0; i < sentences->_num_of_sentences; i++)
        cout << sentences->_data[i] << endl;   
}