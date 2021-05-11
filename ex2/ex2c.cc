#include <iostream>
#include <math.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::nothrow;

struct Node {
   int _data ;
   struct Node *_next ;
} ;

struct Prime_Node  {
    int _prime ;
    struct Prime_Node *_next_prime ;
    struct Node  *_right ;
} ;

void add_num(Prime_Node*& head, int num);
Prime_Node *create_prime_node(int prime);
Node *create_node(int num);
int find_smallest_divider(int num);
Prime_Node *find_prime_node(Prime_Node **head, int prime);
void add_node(Node **head, int num);
void print_data(Prime_Node *node);
void free_memory_prime(Prime_Node *head);
void free_memory_node(Node *head);

int main()
{
    Prime_Node *p_head = nullptr;
    int input;

    cin >> input;

    while (input != 0)
    {
        add_num(p_head, input);
        cin >> input;
    }

    print_data(p_head);
    free_memory_prime(p_head);

    return EXIT_SUCCESS;
}

void add_num(Prime_Node*& head, int num)
{
    int p_divider = find_smallest_divider(num);

    if (!head)
        head = create_prime_node(p_divider);
    
    Prime_Node *p_node = find_prime_node(&head, p_divider);
    add_node(&p_node->_right, num);
}

int find_smallest_divider(int num)
{
    for (int i = 2; i <= sqrtf32(num); i++)
        if (num % i == 0)
            return i;
    
    return num;
}

Prime_Node *find_prime_node(Prime_Node **head, int prime)
{
    if (!*head)
    {
        *head = create_prime_node(prime);
        return *head;
    }

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