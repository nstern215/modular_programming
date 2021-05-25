/*
 * Ex #3: Node and sub node
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program read numbers from the client untill eof and build
 * a search binary tree.
 * Then, the program count how many nodes exists that the node
 * and his left sun values are equal, then print the result
 * 
 * input:
 * numbers until eof
 *
 * output:
 * how many nodes exists that the node
 * and his left sun values are equal
 */

//----------------------------include section----------------------------------
#include <iostream>

//----------------------------using section------------------------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

//----------------------------struct section-----------------------------------
struct Node
{
    int _data;
    Node* _left;
    Node* _right;
};

//----------------------------functions section--------------------------------
void build_tree(Node*& head);
void add_node(Node*& head, Node* node);
Node* create_node(int data);
int count_equal_left(Node* head);
void free_memory(Node* head);

//-----------------------------------------------------------------------------
int main()
{
    Node* head = nullptr;

    build_tree(head);

    cout << count_equal_left(head);

    free_memory(head);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
/**
 * this functio use to build a search binary tree
 * 
 * parameters:
 * head: reference for a pointer that point to the root of the tree
*/
void build_tree(Node*& head)
{
    int input;
    cin >> input;

    while(!cin.eof())
    {
        //create new node
        Node* node = create_node(input);
        //add the node to the tree
        add_node(head, node);

        cin >> input;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to add a new node to the tree
 * the function is a recursive function, in each call the function
 * check if the node value is bigger equal or smaller to the current
 * node value then decide where to connect the node to the tree
 * 
 * parameters:
 * head: reference for a pointer that point to the root of the tree
 * node: pointer for the new node
*/
void add_node(Node*& head, Node* node)
{
    if (head == nullptr)
        head = node;
    else if (node->_data <= head->_data)
        add_node(head->_left, node);
    else
        add_node(head->_right, node);
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a new node
 * 
 * parameters:
 * data: the value of the new node
 * 
 * output:
 * pointer for the new node
*/
Node* create_node(int data)
{
    //allocate memory for the new node
    Node* node = new (nothrow) Node;

    if (node == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    //initialize node properties
    node->_data = data;
    node->_left = nullptr;
    node->_right = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to count how many nodes exists that the value of the node
 * and his left sun are equal.
 * 
 * the function is recursive - first check the current node
 * then recall the function with the right and left suns
 * 
 * paramters:
 * head: pointer for the root of the tree
 * 
 * output:
 * counter result
*/
int count_equal_left(Node* head)
{
    if (head == nullptr)
        return 0;

    //if the node and left sun value are equal
    if (head->_left && head->_data == head->_left->_data)
        return 1 + count_equal_left(head->_left) + 
            count_equal_left(head->_right);
    else
        return 0 + count_equal_left(head->_left) + 
        count_equal_left(head->_right);
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that used by the program
 * this function is recursive - 
 * first recall to delete left node (or left sub-tree)
 * then recall to delete right node (or right sub-tree)
 * then delete the root
*/
void free_memory(Node* head)
{
    if (!head)
        return;

    free_memory(head->_left);
    free_memory(head->_right);
    delete head;
}