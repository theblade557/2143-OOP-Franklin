/*****************************************************************************
 *
 *  Author:           Collin Franklin
 *  Email:            collin.franklin.2003@gmail.com
 *  Label:            A03
 *  Title:            Basic Project Organization
 *  Course:           CMPS 2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        Assignment to learn how to comment and banner code properly
 *
 *  Usage:
 *        
 *
 *  Files:            
 *        main.cpp
 * 
 *****************************************************************************/

#include <iostream>

using namespace std;

/**
 * CircularArrayQue
 *
 * Description:
 *      This class is used to create a circular array queue
 *
 * Public Methods:
 *           CircularArrayQue()
 *           CircularArrayQue(int size)
 *      void push(int item)
 *      int pop()
 *
 * Private Methods:
 *      void init(int size = 0)
 *      bool Full()
 *
 * Usage:
 *
 *       CircularArrayQue C(15);                // Create a queue of size 15
 *                                            
 *
 *       C.Pop();                               // Removes the first index in C
 *
 *
 *       C.Push(12);                            // Pushes the number 12 to the back of the queue
 *
 * 
 *       cout << C << endl;                     // Prints out the entire queue to the console
 *
 */

class CircularArrayQue {
private:
    int *Container;
    int Front;
    int Rear;
    int QueSize; // items in the queue
    int CurrentSize;
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

    bool Full() {
        return CurrentSize == QueSize;
    }

public:
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }

    void Push(int item) {
        if (!Full()) {
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;
        } else {
            cout << "FULL!!!!" << endl;
        }
    }

    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};


ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    C1.Push(12);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}