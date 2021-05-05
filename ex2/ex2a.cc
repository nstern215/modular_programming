#include <iostream>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::nothrow;

struct Node
{
    int _value;
    Node *_next;
};

void read_data(Node*& head);
Node *create_node(int data);
void insert_node(Node*& head, Node *new_node);
void free_memory(Node *head);
int count_ndoes(Node *head);

int main()
{
    Node *head = nullptr;

    read_data(head);

    // Node *temp = head;
    // while(temp)
    // {
    //     cout << temp->_value << endl;
    //     temp = temp->_next;
    // }

    cout << count_ndoes(head) << endl;

    free_memory(head);

    return EXIT_SUCCESS;
}

void read_data(Node*& head)
{
    int input;

    cin >> input;

    while(input != 0)
    {
        insert_node(head, create_node(input));
        cin >> input;
    }
}

Node *create_node(int data)
{
    Node *node = new (nothrow) Node;

    if (node == nullptr)
    {
        cerr << "Failed to allocate memory for a new node" << endl;
        exit(EXIT_FAILURE);
    }

    node->_value = data;
    node->_next = nullptr;

    return node;
}

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

int count_ndoes(Node *head)
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
            if (!next)
                return 1;
            if (node->_value < next->_value)
                count++;
        }
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