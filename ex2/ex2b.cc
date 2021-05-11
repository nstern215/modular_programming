/*
 * Ex #1: Numbers in linked list - jumpping
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * this program read numbers from the user, the first number is an id
 * and the seccond is jump number (positive or negative)
 * for each input the program add a new node to the list and each node
 * connected to the node before and the node after
 * 
 * the progarm will run over the list with 'jumps':
 * for each node, the id will print and the program will jump,
 * by the '_jump' value, nodes backward or farward depence on the sign
 * of the jump.
 * 
 * the run will stop if the jump is 0 or 15 ids have been printed,
 * the earlier.
 * 
 * input:
 * couples of number, first for id second for jump
 * jump 0 will be the last input
 *
 * output:
 * ids of the nodes
 */

//---------------------inlcude section-----------------------------------------
#include <iostream>

//---------------------using section-------------------------------------------
using std::nothrow;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

//---------------------struct section------------------------------------------
struct Node {
   int _id;
   int _jump;
   Node * _next,
        *_prev ;
};

//---------------------constant variables section------------------------------
const int N = 15;

//---------------------functions section---------------------------------------
void read_data(Node*& head);
Node *create_node(int id, int jump);
void add_node(Node*& head, Node *node);
void make_chain(Node*& head);
void print_list(Node* head);
void free_memory(Node *head);

//-----------------------------------------------------------------------------
int main()
{
    Node* head = nullptr;
    read_data(head);

    print_list(head);

    free_memory(head);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
/**
 * this function use to read the id and the jump value into a linked list
 * 
 * paramters:
 * head: reference for a pointer that point to the head of the list
*/
void read_data(Node*& head)
{
    int id;
    int jump;
    
    while(true)
    {
        cin >> id >> jump;
        add_node(head, create_node(id, jump));

        if (jump == 0)
            break;
    }

    make_chain(head);
}

//-----------------------------------------------------------------------------
/**
 * this funcion is use to create a new node
 * 
 * paramters:
 * id: the id of the new node
 * jump: the jump value of the new node
 * 
 * output:
 * a pointer for the new node
*/
Node *create_node(int id, int jump)
{
    Node *node = new (nothrow) Node;

    if (node == nullptr)
    {
        cerr << "Failed to allocate memory for a new node" << endl;
        exit(EXIT_FAILURE);
    }


    //initialize the node properties
    node->_id = id;
    node->_jump = jump;
    node->_next = nullptr;
    node->_next = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to add a new node to the end of list
 * 
 * parameters:
 * head: reference for a pointer that point to the head of the list
 * node: a pointer to node to add
*/
void add_node(Node*& head, Node *node)
{
    if (!head)
        head = node;
    else
    {
        Node *temp = head;

        while(temp->_next)
            temp = temp->_next;
        
        temp->_next = node;
        node->_prev = temp;
    }   
}

//-----------------------------------------------------------------------------
/**
 * this function use to connect the first and last nodes in the list
 * to make a chain:
 * first node previous will point to the last node in the chain
 * last node next will point to the first node in the chain
 * 
 * paramters:
 * head: reference for a pointer that point to the head of the list
*/
void make_chain(Node*& head)
{
    Node *temp = head;

    while(temp->_next)
        temp = temp->_next;

    temp->_next = head;
    head->_prev = temp;
}

//-----------------------------------------------------------------------------
/**
 * this function use to print the list with jumps
 * 
 * for each node, the id will print and the program will jump,
 * by the '_jump' value, nodes backward or farward depence on the sign
 * of the jump.
 * 
 * the run will stop if the jump is 0 or 15 ids have been printed,
 * the earlier.
 * 
 * paramters:
 * head: pointer to the head of the list
*/
void print_list(Node* head)
{
    cout << head->_id << " ";

    Node *temp = head;
    int jump = 0;
    
    for (int i = 0; i < N - 1; i++)
    {
        jump = temp->_jump;

        if (jump == 0)
            break;

        for (int j = 0; j < abs(jump); j++)
        {
            if (jump > 0)
                temp = temp->_next;
            else
                temp = temp->_prev;
        }

        cout << temp->_id << " ";
    }

    cout << endl;
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that used by the program
 * 
 * paramters:
 * head: pointer to the head of the list
*/
void free_memory(Node *head)
{
    Node *temp = head;
    head->_prev->_next = nullptr;
    
    while(temp)
    {
        
        head = head->_next;
        
        if (head)
            head->_prev = nullptr;
        
        delete temp;
        temp = head;
    }
}
