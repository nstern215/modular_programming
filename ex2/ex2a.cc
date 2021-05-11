/*
 * Ex #2: Numbers in linked list
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program read numbers from the user and build a linked list.
 * each node contains a pointer for the node after and the node before
 * then, check how many numbers bigger than the number in the node before,
 * and smaller than the number in the node after
 * 
 * the program will print the result
 * 
 * input:
 * int numbers until eof
 *
 * output:
 * how many numbers bigger than the number in the node before
 * and smaller than the number in the node after
 */

//---------------------inlcude section-----------------------------------------
#include <iostream>

//---------------------using section-------------------------------------------
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::nothrow;

//---------------------struct section------------------------------------------
struct Node
{
    int _value;
    Node *_next;
};

//---------------------functions section---------------------------------------
void read_data(Node*& head);
Node *create_node(int data);
void insert_node(Node*& head, Node *new_node);
void free_memory(Node *head);
int count_nodes(Node *head);

//-----------------------------------------------------------------------------

int main()
{
    Node *head = nullptr;

    read_data(head);

    cout << count_nodes(head) << endl;

    free_memory(head);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
/**
 * this function use to read the numbers form the user and build a linked
 * list for the numbers
 * 
 * prameters:
 * head: reference for pointer that point to the head of the list
*/
void read_data(Node*& head)
{
    int input;

    cin >> input;

    while(!cin.eof())
    {
        insert_node(head, create_node(input));
        cin >> input;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a single node for the list
 * 
 * parameter:
 * data: the value of the node
 * 
 * output:
 * a pointer for the new node
*/
Node *create_node(int data)
{
    Node *node = new (nothrow) Node;

    //check if memory allocated
    if (node == nullptr)
    {
        cerr << "Failed to allocate memory for a new node" << endl;
        exit(EXIT_FAILURE);
    }

    //initialize node properties
    node->_value = data;
    node->_next = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to insert a new node to the end of the list
 * 
 * parameters:
 * head: reference for a pointer that point to the head of the list
 * new_node: pointer for the new node to add
*/
void insert_node(Node*& head, Node *new_node)
{
    if (head == nullptr)
        head = new_node;
    else
    {
        Node *pointer = head;

        while(pointer->_next)
            pointer = pointer->_next;

        pointer->_next = new_node;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to count how many numbers in the list are bigger
 * than the number in the node before and smaller than the number
 * in the node after
 * 
 * paramters:
 * head: a pointer to the head of the list
 * 
 * output:
 * counter result
*/
int count_nodes(Node *head)
{
    if (!head)
        return 0;

    Node *previous = nullptr;
    Node *node = head;
    Node *next = head->_next;
    int count = 0;

    while(node)
    {
        if (!previous)
        {
            //the list contains only one node
            if (!next)
                return 1;
            //the node is the first node in the list
            if (node->_value < next->_value)
                count++;
        }
        //the node is the last node in the list
        else if (!next)
        {
            if (node->_value > previous->_value)
                count++;
        }
        else
        {
            if (node->_value > previous->_value && node->_value < next->_value)
                count++;
        }

        previous = node;
        node = next;
        next = next ? next->_next : nullptr;
    }

    return count;
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory used by the program
*/
void free_memory(Node *head)
{
    Node *temp = head;

    while(temp)
    {
        head = head->_next;
        delete temp;
        temp = head;
    }
}