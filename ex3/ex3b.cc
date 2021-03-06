/*
 * Ex #3: tree of points
 * =============================================
 * Written by: Netanel Stern, id = 206342255, login = netanelst
 *
 * This program read numbers from the client untill eof and build
 * a search binary tree.
 * for each node the program read three numbers
 * one for the id of the node and two for the point (x,y)
 * 
 * the program look for the biggest sun tree that all of his nodes
 * are in the same part of a kartezic axises system
 *  
 * input:
 * numbers until eof
 *
 * output:
 * the point value of the root of the sub tree
 */

//----------------------------include section----------------------------------
#include <iostream>

//----------------------------using section------------------------------------
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

//----------------------------structs section----------------------------------
struct Point
{
    int _x;
    int _y;
};

struct Node {
    int _id ;
    struct Point * _data ;
    struct Node *_left;
    struct Node *_right ;
};

//----------------------------functions section--------------------------------
void build_tree(Node*& root);
Node* create_node(Point *point, int id);
Point* create_point(int x, int y);
void add_node(Node*& root, Node* node);
Node* find_sub_tree(const Node* root);
Node* find_biggest_sub_tree(const Node* root, int& size);
int check_quarter(const Point *point);
void free_memory(Node* root);

//-----------------------------------------------------------------------------
int main()
{
    Node *root = nullptr;

    build_tree(root);

    Node *sub = find_sub_tree(root);

    if (!sub)
        cout << "0 0" << endl;
    else
        cout << sub->_data->_x << " " << sub->_data->_y << endl;

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
    int id;
    int x;
    int y;

    cin >> id >> x >> y;
    while(!cin.eof())
    {
        Point* point = create_point(x, y);
        Node* node = create_node(point, id);

        add_node(root, node);

        cin >> id >> x >> y;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a new node
 * 
 * parameters:
 * point: pointer for point struct instance
 * id: the id of the node
 * 
 * output:
 * pointer for the new node
*/
Node* create_node(Point *point, int id)
{
    Node* node = new (nothrow) Node;

    if (node == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    node->_data = point;
    node->_id = id;
    node->_left = nullptr;
    node->_right = nullptr;

    return node;
}

//-----------------------------------------------------------------------------
/**
 * this function use to create a new point
 * 
 * parameters:
 * x: x axis value
 * y: y axis value
*/
Point* create_point(int x, int y)
{
    Point* point = new (nothrow) Point;

    if (point == nullptr)
    {
        cerr << "Failed to allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    point->_x = x;
    point->_y = y;

    return point;
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
    else if (node->_id <= root->_id)
        add_node(root->_left, node);
    else
        add_node(root->_right, node);
}

//-----------------------------------------------------------------------------
/**
 * this function use to find biggest sub tree that all points
 * are in the same part of kartezic axises system
 * 
 * paramters:
 * root: pointer to the head of the tree
 * 
 * output:
 * pointer to the head of the biggest sub tree
*/
Node* find_sub_tree(const Node* root)
{
    int size = 0;
    return find_biggest_sub_tree(root, size);
}

//-----------------------------------------------------------------------------
/**
 * this recursive function use to find biggest sub tree that all points
 * are in the same part of kartezic axises system
 * 
 * paramters:
 * root: pointer to the head of the tree
 * size: reference to the size of the tree
 * 
 * output:
 * pointer to the head of the biggest tree
*/
Node* find_biggest_sub_tree(const Node* root, int& size)
{
    if (root == nullptr)
    {
        size = 0;
        return nullptr;
    }

    Node *big_l, *big_r;
    int size_l, size_r;
    int root_q, left_q, right_q;

    //check the part in the axises system that each point belongs
    root_q = check_quarter(root->_data);
    left_q = root->_left ? check_quarter(root->_left->_data) : root_q;
    right_q = root->_right ? check_quarter(root->_right->_data) : root_q;

    //check for sub tree in the right and left sun
    big_l = find_biggest_sub_tree(root->_left, size_l);
    big_r = find_biggest_sub_tree(root->_right, size_r);

    //if left and right suns and the root belong to same part in the grid
    if (root_q == left_q && root_q == right_q &&
         root->_left == big_l && root->_right == big_r)
    {
        size = size_l + size_r + 1;
        return (Node*)root;
    }
    else if (size_l >= size_r)
    {
        size = size_l;
        return big_l;
    }
    else
    {
        size = size_r;
        return big_r;
    }
}

//-----------------------------------------------------------------------------
/**
 * this function use to check which part of the grid the point belong
 * 
 * paramters:
 * point: pointer for a point
 * 
 * output:
 * the part in the grid
*/
int check_quarter(const Point *point)
{
    if (point->_x < 0)
    {
        if (point->_y < 0)
            return 1;
        else
            return 2;
    } else {
        if (point->_y >= 0)
            return 3;
        else
            return 4;
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
    delete root->_data;
    delete root;
}