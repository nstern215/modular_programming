#include <iostream>

using std::nothrow;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

struct Node {
   int _id;
   int _jump;
   Node * _next,
        *_prev ;
};

const int N = 15;

void read_data(Node*& head);
Node *create_node(int id, int jump);
void add_node(Node*& head, Node *node);
void make_chain(Node*& head);
void print_list(Node* head);
void free_memory(Node *head);

int main()
{
    Node* head = nullptr;
    read_data(head);

    print_list(head);

    free_memory(head);

    return EXIT_SUCCESS;
}

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

Node *create_node(int id, int jump)
{
    Node *node = new (nothrow) Node;

    if (node == nullptr)
    {
        cerr << "Failed to allocate memory for a new node" << endl;
        exit(EXIT_FAILURE);
    }

    node->_id = id;
    node->_jump = jump;
    node->_next = nullptr;
    node->_next = nullptr;

    return node;
}

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

void make_chain(Node*& head)
{
    Node *temp = head;

    while(temp->_next)
        temp = temp->_next;

    temp->_next = head;
    head->_prev = temp;
}

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