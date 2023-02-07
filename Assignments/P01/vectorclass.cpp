#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    public:
        int data;
        Node* next;
    
    Node() {
        data = 0;
        next = nullptr;
    }
    Node(int x) {
        data = x;
        next = nullptr;
    }
};

class Vector {
    private:
        Node* Head;
        Node* Tail;
    
    public:
        Vector();               // default constructor
        Vector(int);            // specify vector size
        Vector(const Vector &); // copy constructor
        Vector(int *, int);     // create vector given array of items
        Vector(string fileName);

        void push(int);
        void print();
        void pushFront(int);            // adds single value at front of this.list
        void pushFront(const Vector &); // adds entire other.list to front of this.list
        void pushRear(int);             // adds single value to rear of this.list
        void pushRear(const Vector &);  // adds entire other.list to rear of this.list
        void inOrderPush(int);          // adds single value to proper location in order to maintain order (ascending or descending)
        int popFront();                 // removes single value from front of list
        int popRear();                  // removes single value from rear of list
        int popAt(int);                 // removes single value from an indexed location if index between 0 and size of list -1
        int find(int);                  // find location of item (index) if it exists
        int popAt(int);                 // then use index to remove them
};
Vector::Vector() {
     // makes the Vector empty
     Head = Tail = nullptr;
}

Vector::Vector(const Vector &other) {
    Head = Tail = nullptr;

    Node *temp = other.Head;

    while (temp != nullptr)
    {
    push(temp->data);
    temp = temp->next;
    }
}

Vector::Vector(string fileName) {
    int data;
    Head = Tail = nullptr;
    ifstream fin;
    fin.open(fileName);

    while (fin >> data) {
        this->push(data);
    }
}

void Vector::push(int value) {
    Node *tempPtr = new Node(value);

    // handles empty Vector
    if (Head == nullptr)
    {
    Head = Tail = tempPtr;
    }
    else
    {
    // append to rear
    Tail->next = tempPtr; // adds it to end
    Tail = tempPtr;       // points tail to the new last node
    }
}

void Vector::print()
{
    Node *temp = Head;
    while (temp != nullptr)
    {
    cout << temp->data;
    if (temp->next != nullptr)
    {
        cout << "->";
    }
    temp = temp->next;
    }
    cout << endl;
}

void Vector::pushFront(int value) {
    Node *temp = new Node(value);
    if(Head == nullptr) {
        Tail = temp;
        Head = temp;
    }
    else {
        temp->next = Head;
        Head = temp;
    }
}


void Vector::pushFront(const Vector &other) {
    Node *travel = other.Head;

    while (travel) {
        this->pushFront(travel->data);
        travel = travel->next;
    }
}

void Vector::pushRear(int value) {
    Node *temp = new Node(value);
    if(Head == nullptr) {
        Tail = temp;
        Head = temp;
    }
    else {
        Tail->next = temp;
        Tail = temp;
    }
}

void Vector::pushRear(const Vector &other) {
    Node *travel = other.Tail;

    while (travel) {
        this->pushRear(travel->data);
        travel = travel->next;
    }
}

void Vector::inOrderPush(int value) {
    Node *temp = new Node(value);
    if(Head == nullptr) {
        Tail = temp;
        Head = temp;
    }
    else if(temp->data < Head->data) {
        pushFront(value);
    }
    else {
        Node *traverse = Head;
        
        while(traverse->next && traverse->next->data < temp->data) {
            traverse = traverse->next;
            if(traverse->next == nullptr)
                pushRear(value);
            else {
                temp->next = traverse->next;
                traverse->next = temp;
            }
        }
    }
}
