/*
 * Ex #3: biggest tree with even numbers
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program read numbers from the client untill eof and build
 * a search binary tree.
 * 
 * the program will look for the biggest sub tree that the
 * amount of even numbers are much bigeer than the amount of 
 * odd numbers
 *  
 * input:
 * numbers until eof
 *
 * output:
 * the value of the root of the sub tree
 */

//----------------------------include section----------------------------------
#include <iostream>

//----------------------------using section------------------------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;
using std::min;

//----------------------------structs section----------------------------------
struct Node
{
    int _data;
    Node* _left;
    Node* _right;
};

//----------------------------function section---------------------------------
void build_tree(Node*& root);
Node* create_node(int data);
void add_node(Node*& root, Node* node);
Node* find_sub_tree(const Node* root);
Node* find_biggest_sub_tree(const Node* root, int& size, int& even, int& odd);
void free_memory(Node* root);

//-----------------------------------------------------------------------------
int main()
{
    Node *root = nullptr;
    
    build_tree(root);

    Node* head = find_sub_tree(root);

    if (head == nullptr)
        cout << "NOT FOUND";
    else
        cout << head->_data << endl;

    free_memory(root);

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
/**
 * this functio use to build a search binary tree
 * 
 * parameters:
 * head: reference for a pointer that point to the root of the tree
*/
void build_tree(Node*& root)
{
    int input;
    cin >> input;

    while (!cin.eof())
    {
        Node *node = create_node(input);
        add_node(root, node);

        cin >> input;
    }
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
    Node *node = new (nothrow) Node;

    if (node == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    node->_data = data;
    node->_left = nullptr;
    node->_right = nullptr;

    return node;
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
void add_node(Node*& root, Node* node)
{
    if (!root)
        root = node;
    else if (node->_data <= root->_data)
        add_node(root->_left, node);
    else
        add_node(root->_right, node);
}

//-----------------------------------------------------------------------------
/**
 * this function use to find biggest sub tree that the amount of even numbers
 * are much bigger then the amount of odd numbers
 * 
 * paramters:
 * root: pointer to the head of the tree
 * 
 * output:
 * pointer to the head of the biggest sub tree
*/
Node* find_sub_tree(const Node* root)
{
    int size, even, odd;
    size = even = odd = 0;

    return find_biggest_sub_tree(root, size, even, odd);
}

//-----------------------------------------------------------------------------
/**
 * this recursive function use to find biggest sub tree 
 * that the amount of even numbers
 * are much bigger then the amount of odd numbers
 * 
 * paramters:
 * root: pointer to the head of the tree
 * size: reference to the size of the tree
 * even: reference to the amount of even numbers in the tree
 * odd: reference to the amount of odd numbers in tht tree
 * 
 * output:
 * pointer to the head of the biggest tree
*/
Node* find_biggest_sub_tree(const Node* root, int& size, int& even, int& odd)
{
    //initialize value
    size = even = odd = 0;

    if (root == nullptr)
        return nullptr;

    Node *big_l, *big_r;
    int size_l, even_l, odd_l;
    int size_r, even_r, odd_r;

    //check for the biggest sub tree in the left and right subs
    big_l = find_biggest_sub_tree(root->_left, size_l, even_l, odd_l);
    big_r = find_biggest_sub_tree(root->_right, size_r, even_r, odd_r);

    //use to check if the left and right suns can be join to one tree
    //(with the roor), and to do more checks to determine which
    //sub tree is relevanr
    int odd_even_diff = (even_l + even_r) - (odd_l + odd_r);
    
    //if there are no sub tree with even numbers and the root is odd
    if ((even_l + even_r) == 0 && root->_data % 2 != 0)
    {
        size = size_l + size_r + 1;
        even = 0;
        odd = odd_l + odd_r + 1;
        return nullptr;
    }

    //in case that both of suns are a potential sub tree, or only one of them,
    //but with even root they can join to a bigger sub tree.
    //except in case that the size of one of the suns is 0, then
    //the bigger sun is the relevant sub tree
    if (odd_even_diff > 1 || (odd_even_diff == 0 && root->_data % 2 == 0) ||
        (odd_even_diff == 1 && root->_data % 2 == 0 
            && min(size_l, size_r) != 0))
    {
        size = size_l + size_r + 1;
        even = even_l + even_r;
        odd = odd_l + odd_r;
        if (root->_data % 2 == 0)
            even++;
        else
            odd++;
        return (Node*)root;
    }
    
    //otherwhise-in total of both suns there are more odds than evens,
    //then look for the relevant sub tree
    if (even_l > odd_l)
    {
        if (big_l)
        {
            size = size_l;
            even = even_l;
            odd = odd_l;
        }
        return big_l;
    }
    else
    {
        if (big_r)
        {
            size = size_r;
            even = even_r;
            odd = odd_r;
        }
        return big_r;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to release the memory that used by the program
 * this function is recursive - 
 * first recall to delete left node (or left sub-tree)
 * then recall to delete right node (or right sub-tree)
 * then delete the root
*/
void free_memory(Node* root)
{
    if (!root)
        return;

    free_memory(root->_left);
    free_memory(root->_right);
    delete root;
}