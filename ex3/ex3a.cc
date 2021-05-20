#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

struct Node
{
    int _data;
    Node* _left;
    Node* _right;
};

void build_tree(Node*& head);
void add_node(Node*& head, Node* node);
Node* create_node(int data);
int count_equal_left(Node* head);
void free_memory(Node* head);

int main()
{
    Node* head = nullptr;

    build_tree(head);

    cout << count_equal_left(head);

    free_memory(head);

    return EXIT_SUCCESS;
}

void build_tree(Node*& head)
{
    int input;
    cin >> input;

    while(!cin.eof())
    {
        Node* node = create_node(input);

        if(head == nullptr)
            head = node;
        else
            add_node(head, node);

        cin >> input;
    }
}

void add_node(Node*& head, Node* node)
{
    if (head == nullptr)
        head = node;
    else if (node->_data <= head->_data) {
        add_node(head->_left, node);
    } else {
        add_node(head->_right, node);
    }
}

Node* create_node(int data)
{
    Node* node = new (nothrow) Node;

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

int count_equal_left(Node* head)
{
    if (head == nullptr)
        return 0;

    if (head->_left && head->_data == head->_left->_data)
        return 1 + count_equal_left(head->_left) + count_equal_left(head->_right);
    else
        return 0 + count_equal_left(head->_left) + count_equal_left(head->_right);
}

void free_memory(Node* head)
{
    if (!head)
        return;

    free_memory(head->_left);
    free_memory(head->_right);
    delete head;
}