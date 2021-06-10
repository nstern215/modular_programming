//-----------------------------include section---------------------------------
#include <iostream>
#include <cmath>

//-----------------------------using section-----------------------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

//-----------------------------struct section----------------------------------
struct Node {
    int _data;
    struct Node *_next,
                *_prev;
};

//-----------------------------functions pointers------------------------------
typedef Node*(*get_next_node)(const Node*);
typedef bool(*check_node)(int num);

//-----------------------------functins section--------------------------------
void build_list(Node*& head);
Node* create_node(int data);
bool is_prime(int num);
bool is_palindrom(int num);
bool is_positive(int num);
Node* move_forward(const Node* node);
Node* move_backward(const Node* node);
void find_node(const Node* head, get_next_node next, check_node check);
void free_memory(Node* head);

//-----------------------------------------------------------------------------
int main()
{
    Node* head = nullptr;
    build_list(head);

    find_node(head, move_forward, is_positive);
    find_node(head->_prev, move_backward, is_positive);
    find_node(head, move_forward, is_prime);
    find_node(head->_prev, move_backward, is_prime);
    find_node(head, move_forward, is_palindrom);
    find_node(head->_prev, move_backward, is_palindrom);

    cout << endl;

    free_memory(head);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
/**
 * this function use to build a linked list
 * each node point to the next and to the prev node
 * the prev of the first node is the last node in the list
 * the next of the last node is the first node in the list
 * 
 * parameters:
 * head - reference for a pointer that point to the head of the list
*/
void build_list(Node*& head)
{
    //use to point to the last node in the list
    Node* last = nullptr;
    int input;

    cin >> input;

    while(!cin.eof())
    {
        Node* node = create_node(input);
        if (head == nullptr)
        {
            head = node;
            last = head;
        }
        else
        {
            last->_next = node;
            node->_prev = last;
            last = node;
        }

        cin >> input;
    }

    last->_next = head;
    head->_prev = last;
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a new node
 * 
 * parameters:
 * data - data of the node
 * 
 * output:
 * pointer for the new node
*/
Node* create_node(int data)
{
    Node* node = new (nothrow) Node;
    
    if (node == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    node->_data = data;
    node->_next = nullptr;
    node->_prev = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
void find_node(const Node* head, get_next_node next, check_node check)
{
    //if the head node is null the is no relevant result
    if (head == nullptr)
        cout << 0 << " ";

    //save the current checked node
    Node* current = (Node*)head;

    if (check(current->_data))
    {
        cout << current->_data << " ";
        return;
    }
    
    //if the current(first node in this case) node is fit the requirements,
    //start scanning the list until find a node or 
    //get the given head of the list
    current = next(current);
    while(current != head)
    {
        if (check(current->_data))
        {
            cout << current->_data << " ";
            return;
        }

        current = next(current);
    }

    cout << 0 << " ";
}

//-----------------------------------------------------------------------------
/**
 * this function use to return the next node in the list
 * 
 * parameters:
 * node - pointer to the list
 * 
 * output:
 * pointer for the next node in the list
*/
Node* move_forward(const Node* node)
{
    return node->_next;
}

//-----------------------------------------------------------------------------
/**
 * this function use to return the previous node in the list
 * 
 * parameters:
 * node - pointer to the list
 * 
 * output:
 * pointer for the previous node
*/
Node* move_backward(const Node* node)
{
    return node->_prev;
}

//-----------------------------------------------------------------------------
/**
 * this function use to check if a number is a prime number
 * 
 * parameters:
 * num - num to check for prime
 * 
 * output:
 * true if the num is prime
 * false - otherwise
*/
bool is_prime(int num)
{
    if (num <= 2)
        return false;

    for (int i = 2; i < num / 2; i++)
        if (num % i == 0)
            return false;
    

    return true;
}

//-----------------------------------------------------------------------------
/**
 * this recursive functin use to check if the given number is palindrom
 * 
 * paramters:
 * num - num to check for palindrom
 * 
 * output:
 * true if palindrom
 * otherwise false
*/
bool is_palindrom(int num)
{
    num = abs(num);

    //if the num is a single digit
    if (num / 10 == 0)
        return true;

    //extract num of digits and the first digit of the number
    int num_of_digits = (int) log10(num);
    int first_digits = (int) num / pow(10, num_of_digits);
    int last_digits = num % 10;
    
    return first_digits == last_digits &&
            is_palindrom(num - first_digits*pow(10, num_of_digits));
}

//-----------------------------------------------------------------------------
/**
 * this function use to check if the given number is positive
 * and not equal to 0
 * 
 * paramters:
 * num - num to check
 * 
 * output:
 * true if bigger than 0
 * otherwise false
*/
bool is_positive(int num)
{
    return num > 0;
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that used by the program
 * 
 * parameters:
 * head - pointer for the head of the list
*/
void free_memory(Node* head)
{
    if (head == nullptr)
        return;

    //fiattach the link between the last and first nodes
    head->_prev->_next = nullptr;    

    Node* temp = head;

    while(temp != nullptr)
    {
        head = head->_next;

        temp->_next = nullptr;
        temp->_prev = nullptr;
        delete temp;

        temp = head;
    }
}