/*
 * Ex #2: Prime numbers
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * this program read numbers from the user, until input is equal to 0,
 * for each number the program will look for the smallest prime divider.
 * if the prime list doesnt conaints a node with this divider, the program will
 * add a new node with this prime,
 * then, the program add the number to the 'right' list of the prime
 * 
 * input:
 * int numbers until input equal 0
 *
 * output:
 * print the list
 * for each line the prime and then the numbers in the 'right' list
 */

//---------------------inlcude section-----------------------------------------
#include <iostream>
#include <math.h>

//---------------------using section-------------------------------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

//---------------------struct section------------------------------------------
struct Node {
   int _data ;
   struct Node *_next ;
} ;

struct Prime_Node  {
    int _prime ;
    struct Prime_Node *_next_prime ;
    struct Node  *_right ;
} ;

//---------------------functions section---------------------------------------
void read_data(Prime_Node*& head);
void add_num(Prime_Node*& head, int num);
Prime_Node *create_prime_node(int prime);
Node *create_node(int num);
int find_smallest_divider(int num);
Prime_Node *find_prime_node(Prime_Node **head, int prime);
void add_node(Node **head, int num);
void print_data(Prime_Node *node);
void free_memory_prime(Prime_Node *head);
void free_memory_node(Node *head);

//-----------------------------------------------------------------------------
int main()
{
    Prime_Node *p_head = nullptr;
    
    read_data(p_head);

    print_data(p_head);
    free_memory_prime(p_head);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
/**
 * this function use to read data from the user into linked list
 * 
 * paramters:
 * head: reference for a pointer that point to the head of the list
*/
void read_data(Prime_Node*& head)
{
    int input;

    cin >> input;

    while (input != 0)
    {
        add_num(head, input);
        cin >> input;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to add a new number to the list
 * 
 * the functino will look for the smallest prime that divide the number
 * add the prime to the prime list, if doesnt exist,
 * then add the number to the right list of the prime
 * 
 * parameters:
 * head: reference for a pointer that point to the head of the list
 * num: input num to add to the list
*/
void add_num(Prime_Node*& head, int num)
{
    int p_divider = find_smallest_divider(num);

    if (!head)
        head = create_prime_node(p_divider);
    
    Prime_Node *p_node = find_prime_node(&head, p_divider);
    add_node(&p_node->_right, num);
}

//-----------------------------------------------------------------------------
/**
 * this function use to find the smallest prime number that divide num
 * the smallest divider will always be prime
 * the smallest prime divider will be <= sqrt(num)
 * 
 * parameters:
 * num: num to find the divider
 * 
 * output:
 * the divider
*/
int find_smallest_divider(int num)
{
    for (int i = 2; i <= sqrtf32(num); i++)
        if (num % i == 0)
            return i;
    
    return num;
}

//-----------------------------------------------------------------------------
/**
 * this function use to find the prime node that equal to the prime parameter
 * 
 * if there are no prime node with the prime, the function will add a new
 * prime node in the correct place
 * 
 * than the function will return a pointer to the node
 * 
 * parameters:
 * head: pointer to pointer that point to the head of the prime node list
 * prime: the prime number
 * 
 * output:
 * a pointer to the prime node
*/
Prime_Node *find_prime_node(Prime_Node **head, int prime)
{
    if (!*head)
    {
        *head = create_prime_node(prime);
        return *head;
    }

    //look for the node; otherwise add a new prime node and keep
    //the list sorted
    while((*head)->_next_prime)
    {
        if ((*head)->_prime == prime)
            return (*head);
        
        if ((*head)->_prime < prime && prime < (*head)->_next_prime->_prime)
        {
            Prime_Node *new_prime = create_prime_node(prime);
            new_prime->_next_prime = (*head)->_next_prime;
            (*head)->_next_prime = new_prime;

            return new_prime;
        }

        head = &((*head)->_next_prime);
    }

    if (prime == (*head)->_prime)
        return (*head);

    Prime_Node *new_prime = create_prime_node(prime);

    if ((*head)->_prime < prime)
    {
        (*head)->_next_prime = new_prime;
        return new_prime;
    } else {
        new_prime->_next_prime = (*head);
        *head = new_prime;
        return *head;
    }    
}

//-----------------------------------------------------------------------------
/**
 * this function use to add a new node to the end of 'right' list
 * 
 * parameters:
 * head: pointer to pointer that point to the head of the list
 * num: the value of the new node
*/
void add_node(Node **head, int num)
{
    Node *node = create_node(num);

    if (!*head)
    {
        *head = node;
        return;
    }

    while ((*head)->_next)
        head = &((*head)->_next);
    
    (*head)->_next = node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a new prime node
 * 
 * parameters:
 * prime: the value of the new prime node
 * 
 * output:
 * pointer that point to the new prime node
*/
Prime_Node *create_prime_node(int prime)
{
    Prime_Node *node = new (nothrow) Prime_Node;
    
    if(!node)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }
    
    node->_prime = prime;
    node->_next_prime = nullptr;
    node->_right = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a new node
 * 
 * parameters:
 * num: the value of the new node
 * 
 * output:
 * pointer that point to the new node
*/
Node *create_node(int num)
{
    Node *node = new (nothrow) Node;

    if (!node)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    node->_data = num;

    node->_next = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to print the list:
 * for each prime node print the prime and then print the 'right' list
 * of the prime node
*/
void print_data(Prime_Node *node)
{
    Prime_Node *p_node = node;

    while(p_node)
    {
        cout << p_node->_prime << " ";

        Node *node = p_node->_right;

        while(node)
        {
            cout << node->_data << " ";
            node = node->_next;
        }

        cout << endl;

        p_node = p_node->_next_prime;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that use by the program.
 * for each prime node, release the 'right' node list and then
 * delete the prime node
 * 
 * parameters:
 * head: pointer that point to the head of the list
*/
void free_memory_prime(Prime_Node *head)
{
    Prime_Node *temp = head;

    while(temp)
    {
        head = head->_next_prime;
        free_memory_node(temp->_right);
        delete temp;
        temp = head;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that use by this program
 * 
 * parameters:
 * head: pointer that point to the head of the list
*/
void free_memory_node(Node *head)
{
    Node *temp = head;

    while(temp)
    {
        head = head->_next;
        delete temp;
        temp = head;
    }
}