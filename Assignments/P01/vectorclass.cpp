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
        Vector(string fileName);// create a vector given a file

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

    Vector::Vector(int *A, int size) {
        int data;
        Head = Tail = nullptr;
        for (int i = 0; i < size; i++) {
            data = A[i];
            push(data);
        }
    }

    Vector::Vector(string fileName)
{
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

int Vector::popFront() {
    Node *temp = new Node();
    int val;

    temp = Head;
    Head = Head->next;
    val = temp->data;
    delete temp;
    return val;    
}

int Vector::popRear() {
    Node *temp = new Node();
    Node *traverse = new Node();
    int val;
    while (traverse->next && traverse->next->data < temp->data)
    {
        traverse = traverse->next;
        if (traverse->next == nullptr)
            val = traverse->data;
    }
    return val;
}

int Vector::popAt(int loc) {
    
}

int Vector::find(int val) {
    Node *traverse = new Node();
    int loc = 0;
    while(traverse) {
        if(traverse->data == val) {
            return loc;
        }
        traverse = traverse->next;
        loc++;
    }
}

int main() {
    // int x = 0;

    // Vector v1;
    // v1.pushFront(18);
    // v1.pushFront(20);
    // v1.pushFront(25);
    // v1.pushRear(18);
    // v1.pushRear(20);
    // v1.pushRear(25);
    // v1.print();
    // // [25, 20, 18, 18, 20, 25]

    // int A[] = {11, 25, 33, 47, 51};
    // Vector v2(A, 5);
    // v2.print();
    // // [11, 25, 33, 47, 51]

    // v2.pushFront(9);
    // // v2.inOrderPush(27);
    // v2.pushRear(63);
    // v2.print();
    // // [9, 11, 25, 33, 47, 51, 63]

    // v1.pushRear(v2);
    // v1.print();
    // // [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]

    // x = v1.popFront();
    // x = v1.popFront();
    // x = v1.popFront();
    // v1.print();
    // // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
    // cout << x << endl;
    // // 18

    // x = v1.popRear();
    // x = v1.popRear();
    // x = v1.popRear();
    // v1.print();
    // // [18, 20, 25, 9, 11, 25, 27, 33]
    // cout << x << endl;
    // // 47

    // x = v2.popAt(3);
    // v2.print();
    // // [9, 11, 25, 33, 47, 51, 63]
    // cout << x << endl;
    // // 27

    // x = v2.find(51);
    // cout << x << endl;
    // // 5

    // x = v2.find(99);
    // cout << x << endl;
    // // -1

    // Vector v3(v1);
    // v3.print();
    // // [18, 20, 25, 9, 11, 25, 27, 33]

    // v3.pushFront(v2);
    // v3.print();
    // //[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

    // Vector v4("input.dat");
    // v4.pushRear(v3);
    // v4.print();
    // // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]
}