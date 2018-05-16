/*//
// This program demonstrates new and delete keyword
// Lessons: A class can contain a pointer to its own type but not an object of its own type.

// You skipped the a lot of Chapter 10 (pointers),
// it has interesting topics like parsing, data structures, double pointers, etc..
// Do them if you have time.
// Using new operator (similar to malloc => allocates memory for a pointer)
//          (similar to new in Java, Java is basically allocating memory when it uses keyword new)
#include <iostream>
#include <cstring>
using namespace std;
const int* a; // a is a pointer to constant int
int c = 3;
int* const b = &c; // b is a constant pointer to int

int main()
{
    char *str = "Blablabla";
    int len = strlen(str);
    char *ptr;
    // keyword new
    // returns a pointer to a section of memory large enough to hold the string str, whose length is len.
    ptr = new char[len+1];
    strcpy(ptr, str);
    cout << "ptr=" << ptr << endl;
    // keyword delete
    // returns memory pointed by ptr to operating system
    delete[] ptr; // release ptr's memory
        // [] indicates we are deleting an array
    return 0;
}

// a class can contain a pointer to an object of its own type
// but cannot contan an object of its won type.

class sample
{
    sample *ptr; // pointer to own class object
    // sample obj; // ERROR! cannot contain object of own type.
};
//*/
