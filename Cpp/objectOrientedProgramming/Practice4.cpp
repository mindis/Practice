/* //
// This program uses classes to implement a simple Stack Data Structure that has member functions push() and pop()
// Lessons: Introduction to arrays, stacks, and structs.
// ARRAYS
#include <iostream>
using namespace std;
const int SIZE = 4;

struct part
{
    int modelnum;
    int partnum;
    float cost;
};

// arrays as members to class
// not that class Stack is similar to struct Stack.
// You can create an array of this type if you want to
// EX: int x[4];; // similar to
//      Stack haha[3];

class Stack
{
    enum {MAX = 10}; // define MAX = 10;
    int st[MAX]; // make an array of 10 values
    int top; // number of elements in stack
    public:
    Stack() // constructor
    {
        top = 0;
    }
    void push(int var)
    {
        st[++top] = var;
    }
    int pop()
    {
        return st[top--];
    }
};

void array();
void array_of_structs();

int main(void)
{
    array();
    array_of_structs();
    Stack s1;
    s1.push(11);
    s1.push(22);
    cout << "1: " << s1.pop() << endl;
    cout << "2: " << s1.pop() << endl;
    Stack s2[2]; // arrays of objects
    s2[0].push(22);
    s2[1].push(32);
    cout << " s2 1: " << s2[0].pop() << endl;
    cout << " s2 2: " << s2[1].pop() << endl;
    return 0;
}

void array()
{
    int age[4];
    for (int j=0; j<4; j++)
    {
        cout << "Enter age: ";
        cin >> age[j];
    }
    for( int j=0; j<4; j++)
        cout << "You entered " << age[j] << endl;
}

void array_of_structs()
{
    int n;
    part apart[SIZE];
    for (n = 0; n < SIZE; n++)
    {
        cout << endl; // prints out newline which ends the buffer.
        cout << "Enter model number: ";
        cin >> apart[n].modelnum;
        cout << "Enter part number: ";
        cin >> apart[n].partnum;
        cout << "Enter cost: ";
        cin >> apart[n].cost;
    }
    cout << endl;
    for (n =0; n<SIZE; n++)
    {
        cout << "Model " << apart[n].modelnum;
        cout << " Part " << apart[n].partnum;
        cout << " Cost" << apart[n].cost << endl;
    }
}
//*/
