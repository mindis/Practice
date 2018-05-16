/*
//
// This program demonstrates use of this keyword by calling the its own address.
// Lessons: this = a pointer to the object itself
// This program demonstrates use of returning by reference using the keyword this
    // cause it is safer to do so.
// Lessons: If return by reference, always return using keyword this.

// Returning by reference
// Cannot return an object by reference because the object that was local will be destroyed when function returns.
// Permanent object is needed to return by reference.
// An object's member function is destroyed every time they're called.
// Returning by reference the object of the member function is safer as the object doesn't get destroyed when function ends.
// this pointer allows this to happen. It also avoids creation of extra objects.
#include <iostream>
using namespace std;

class where
{
    private:
        char charray[10];
    public:
        void reveal()
            {
                cout << "\nMy object's address is " << this;
            }
};

class alpha
{
    private:
        int data;
    public:
        alpha() {}
        alpha(int d) : data(d) {}
        // methods
        void display()
        {
            cout << data;
        }
        // overloading assignment (=) operator
        // alpha& => returns by reference
        // alpha => returns by value
        alpha& operator = (alpha& a)
        {
            data = a.data;
            cout << "\nAssignment operator invoked";
            return *this; // return a copy of this alpha
        }
};

int main()
{
    // this pointer
    where w1, w2, w3;
    w1.reveal();
    w2.reveal();
    w3.reveal();
    cout << endl;
    // Demonstrating return by reference
    alpha a1(37);
    alpha a2, a3;
    a3 = a2 = a1;
    cout << "\na2="; a2.display();
    cout << "\na3="; a3.display();
    cout << endl;
    return 0;
}
//*/
