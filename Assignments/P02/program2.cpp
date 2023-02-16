/*****************************************************************************
 *
 *  Author:           Collin Franklin
 *  Title:            Singly linked list vector implementation
 *  Course:           2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        Uses a singly linked list as the backend for an STL like "vector"
 *        class definition.
 *
 *  Usage:
 *        Use it like a linked list now. More like a vector next program
 *
 *  Files: TBD
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void openFiles(ifstream &infile, ofstream &outfile);
void printHeading(ofstream &outfile);

struct Node
{
public:
    int data;
    Node *next;

    Node()
    {
        data = 0;
        next = nullptr;
    }
    Node(int x)
    {
        data = x;
        next = nullptr;
    }
};

class Vector
{
private:
    Node *Head;
    Node *Tail;

public:
    Vector();                // default constructor
    Vector(int);             // specify vector size
    Vector(const Vector &);  // copy constructor
    Vector(int *, int);      // create vector given array of items
    Vector(string fileName); // create a vector given a file

    void push(int);
    void print(ofstream &);
    void pushFront(int);            // adds single value at front of this.list
    void pushFront(const Vector &); // adds entire other.list to front of this.list
    void pushRear(int);             // adds single value to rear of this.list
    void pushRear(const Vector &);  // adds entire other.list to rear of this.list
    void inOrderPush(int);          // adds single value to proper location in order to maintain order (ascending or descending)
    int popFront();                 // removes single value from front of list
    int popRear();                  // removes single value from rear of list
    int popAt(int);                 // removes single value from an indexed location if index between 0 and size of list -1
    int find(int);                  // find location of item (index) if it exists

    friend ostream &operator<<(ostream &, const Vector &);
    friend fstream &operator<<(ofstream& , const Vector &);
    Vector &operator+(const Vector &);
    Vector operator==(const Vector &);
    Vector operator= (const Vector &);
};

// makes the Vector empty
Vector::Vector()
{
    Head = Tail = nullptr;
}

// creates a list with the values of another list
Vector::Vector(const Vector &other)
{
    Head = Tail = nullptr;

    Node *temp = other.Head;

    while (temp != nullptr)
    {
        push(temp->data);
        temp = temp->next;
    }
}

// creates a list with a value and a size
Vector::Vector(int *A, int size)
{
    int data;
    Head = Tail = nullptr;
    for (int i = 0; i < size; i++)
    {
        data = A[i];
        push(data);
    }
}

// creates a list with a file
Vector::Vector(string fileName)
{
    int data;
    Head = Tail = nullptr;
    ifstream fin;
    fin.open(fileName);

    while (fin >> data)
    {
        this->push(data);
    }
}

// Pushes a value into the list
void Vector::push(int value)
{
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

// Prints the list to both the console and to the output file
void Vector::print(ofstream &outfile)
{
    Node *temp = Head;
    while (temp != nullptr)
    {
        outfile << "[" << temp->data << "]";
        cout << temp->data;
        if (temp->next != nullptr)
        {
            outfile << " ";
            cout << "->";
        }
        temp = temp->next;
    }
    outfile << endl;
    cout << endl;
}

// Push a value to the front of the list
void Vector::pushFront(int value)
{
    Node *temp = new Node(value);
    if (Head == nullptr)
    {
        Tail = temp;
        Head = temp;
    }
    else
    {
        temp->next = Head;
        Head = temp;
    }
}

// Pushes a vector to the front of the list
void Vector::pushFront(const Vector &other)
{
    Node *travel = other.Head;

    while (travel)
    {
        this->pushFront(travel->data);
        travel = travel->next;
    }
}
// Pushes a value to the end of the list
void Vector::pushRear(int value)
{
    Node *temp = new Node(value);
    if (Head == nullptr)
    {
        Tail = temp;
        Head = temp;
    }
    else
    {
        Tail->next = temp;
        Tail = temp;
    }
}
// Pushes to the rear of the list the other vector
void Vector::pushRear(const Vector &other)
{
    Node *travel = other.Head;

    while (travel)
    {
        this->pushRear(travel->data);
        travel = travel->next;
    }
}

// pushes a value in order
void Vector::inOrderPush(int value)
{
    Node *temp = new Node(value);
    if (Head == nullptr)
    {
        Tail = temp;
        Head = temp;
    }
    else if (temp->data < Head->data)
    {
        pushFront(value);
    }
    else
    {
        Node *traverse = Head;

        while (traverse->next && traverse->next->data < temp->data)
        {
            traverse = traverse->next;
            if (traverse->next == nullptr)
                pushRear(value);
            else
            {
                temp->next = traverse->next;
                traverse->next = temp;
            }
        }
    }
}

// pops the first value in the list
int Vector::popFront()
{
    Node *temp = new Node();
    int val;

    temp = Head;
    Head = Head->next;
    val = temp->data;
    delete temp;
    return val;
}

// pops the last value in the list
int Vector::popRear()
{
    Node *temp = new Node();
    Node *traverse = new Node();
    int val;
    if (Head == nullptr)
    {
        return 0;
    }
    if (Head->next == nullptr)
    {
        delete Head;
        return 0;
    }

    temp = Head;
    while (temp->next->next)
    {
        temp = temp->next;
    }

    val = temp->data;

    delete temp;

    return val;
}

// pops the value at a location you give
int Vector::popAt(int loc)
{
    Node *traverse = new Node();
    Node *temp = new Node();
    int val;
    for (int i = 0; i < loc - 1; i++)
    {
        traverse = traverse->next;
    }
    temp = traverse->next;
    val = temp->data;
    delete temp;
    return val;
}

// finds the location of a value you give
int Vector::find(int val)
{
    Node *traverse = new Node();
    int loc = 0;
    while (traverse)
    {
        if (traverse->data == val)
        {
            return loc;
        }
        traverse = traverse->next;
        loc++;
    }
}

Vector :: ostream &operator<<(ostream &os, const Vector &rhs)
    {
        Node *temp = rhs.Head; // temp pointer copies head

        while (temp)
        { // this loops until temp is NULL
          // same as `while(temp != NULL)`

            os << temp->data; // print data from Node
            if (temp->next)
            {
                os << "->";
            }
            temp = temp->next; // move to next Node
        }
        os << endl;
        return os;
    }

/**
 * Main Driver
 *
 * For this program, the main driver was used to test the vector class
 *
 */

int main()
{

    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {10, 20, 30};

    Vector v1(a1, 5);
    Vector v2(a2, 3);

    ofstream fout;
    fout.open("output.txt");

    // cout << v1[2] << endl;
    // // writes out 3

    // v1[4] = 9;
    // // v1 now = [1,2,3,4,9]

    cout << v1 << endl;
    // writes out [1,2,3,4,9] to console.

    fout << v1 << endl;
    // writes out [1,2,3,4,9] to your output file.

    // Vector v3 = v1 + v2;
    // cout << v3 << endl;
    // // writes out [11,22,33,4,9] to console.

    // v3 = v1 - v2;
    // cout << v3 << endl;
    // // writes out [-9,-18,-27,4,9] to console.

    // v3 = v2 - v1;
    // cout << v3 << endl;
    // // writes out [9,18,27,4,9] to console.

    // v3 = v2 * v1;
    // cout << v3 << endl;
    // // writes out [10,40,90,4,9] to console.

    // v3 = v1 * v2;
    // cout << v3 << endl;
    // // writes out [10,40,90,4,9] to console.

    // v3 = v1 / v2;
    // cout << v3 << endl;
    // // writes out [0,0,0,4,9] to console.

    // v3 = v2 / v1;
    // cout << v3 << endl;
    // // writes out [10,10,10,4,9] to console.

    // cout << (v2 == v1) << endl;
    // // writes 0 to console (false) .

    // MyVector v4 = v1;
    // cout << (v4 == v1) << endl;
    // // writes 1 to console (true) .
}