#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

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

void build_tree(Node*& root);
Node* create_node(Point *point, int id);
Point* create_point(int x, int y);
void add_node(Node*& root, Node* node);
Node* find_biggest_sub_tree(Node* root, int& size);
int check_quarter(Point *point);
int count_nodes(Node* root);
void free_memory(Node* root);

int main()
{
    Node *root = nullptr;
    int size = 0;

    build_tree(root);

    Node *sub = find_biggest_sub_tree(root, size);

    if (!sub->_left && !sub->_right)
        cout << "0 0" << endl;
    else
        cout << sub->_data->_x << " " << sub->_data->_y << endl;

    free_memory(root);

    return EXIT_SUCCESS;
}

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

        if (!root)
            root = node;
        else
            add_node(root, node);

        cin >> id >> x >> y;
    }
}

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

void add_node(Node*& root, Node* node)
{
    if (!root)
        root = node;
    else if (node->_id <= root->_id)
        add_node(root->_left, node);
    else
        add_node(root->_right, node);
}

Node* find_biggest_sub_tree(Node* root, int& size)
{
    if (root == nullptr)
    {
        size = 0;
        return nullptr;
    }

    Node *big_l, *big_r;
    int size_l, size_r;
    int root_q, left_q, right_q;

    root_q = check_quarter(root->_data);
    left_q = root->_left ? check_quarter(root->_left->_data) : root_q;
    right_q = root->_right ? check_quarter(root->_right->_data) : root_q;

    big_l = find_biggest_sub_tree(root->_left, size_l);
    big_r = find_biggest_sub_tree(root->_right, size_r);

    if (root_q == left_q && root_q == right_q && root->_left == big_l && root->_right == big_r)
    {
        size = size_l + size_r + 1;
        return root;
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

int check_quarter(Point *point)
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

int count_nodes(Node* root)
{
    if (!root)
        return 0;

    return 1 + count_nodes(root->_left) + count_nodes(root->_right);
}

void free_memory(Node* root)
{
    if (!root)
        return;

    free_memory(root->_left);
    free_memory(root->_right);
    delete root->_data;
    delete root;
}