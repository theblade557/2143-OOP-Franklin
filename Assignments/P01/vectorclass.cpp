#include <iostream>

class Vector {
private:
    int *array;
    int index;
    int size;
    char fileName[40];

    bool Full();   // array has all slots filled
    bool Empty();  // array is empty
    void Resize(); // grow array

public:
    Vector();               // default constructor
    Vector(int);            // specify vector size
    Vector(const Vector &); // copy constructor
    Vector(int *, int);     // create vector given array of items

    void push(int);        // add item to vector
    int pop();             // remove item from vector
    void print();          // print the vector
    void pushAt(int, int); // push value at specific location
};

Vector::Vector(int *A, int size) {

}

Vector::Vector(/*string filename*/) {

}

Vector::Vector(const Vector &v) {
    
}
