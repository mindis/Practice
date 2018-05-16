/*
//
// This program demonstrates polymorphism using virtual functions.
// Lessons: without virtual, pointer's functions gets called, with virtual, object's functions gets called.
    // an abstract class is a class with pure virtual functions.
// Lessons:  pure virtual function (virtual function with expression = 0 attached to it
                // without any definition.

// Virtual Functions
// Virtual => existing in appearance but not reality
// calling a function of one class to call a function of a different class
// Able to perform an operation using the same function call
// on objects of different classes using an array with parent pointers.
// Polymorphism (different forms) => functions that have same appearance
                                // but different actual functions called.

#include <iostream>
using namespace std;

// Without using Virtual Functions
class Base
{
    public:
        void show() { cout << "Base\n";}
};

class Derv1: public Base
{
    public:
        void show() {cout << "Derv1\n";}
};

class Derv2: public Base
{
    public:
        void show() {cout << "Derv2\n";}
};

class Base2
{
    public:
        virtual void show() // making the function virtual
        // makes the object pointed by pointer's member function be executed.
        // dynamic binding = late binding => the compiler decides which method to call
            // at runtime.
        {
            cout << "Base2\n";
        }
};

class Derv3 : public Base2
{
    public:
        void show()
        {
            cout << "Derv3\n";
        }
};

class Derv4 : public Base2
{
    public:
        void show()
        {
            cout << "Derv4\n";
        }
};

// Abstract class
//   to make an abstract class ( no objects),
    // place at least one "pure virtual" function (expression = 0 ) added to declaration
    // for consistency, make all virtual functions in the base class pure.
class Base3
{
    public:
        virtual void show() = 0; // pure virtual function (virtual function with expression = 0 attached to it
                                 // without any definition.
        // you must override pure virtual function in all derived classes which
                // instantiates objects
        // classes that do not overried pure virtual functions become abstract classes themselves
            // thus, you can't instantiate objects from it (though you can still derive classes)
};

class Derv5 : public Base3
{
    public:
        void show()
        {
            cout << "Derv5\n";
        }
};

class Derv6 : public Base3
{
    public:
        void show()
        {
            cout << "Derv6\n";
        }
};

int main()
{
    // Without Virtual Functions
    Derv1 dv1;
    Derv2 dv2;
    Base *ptr;
    // note that pointer of parent class can always point to base class
    ptr = &dv1; // at this point, compiler knows which method to call
                // early binding = static binding => choosing functions during compilation
    // Unlike Java, function that is executed belongs to type of the pointer
    ptr->show();
    ptr = &dv2;
    ptr->show();

    // Using Virtual Functions
    Derv3 dv3;
    Derv4 dv4;
    Base2 *ptr2;
    ptr2 = &dv3; // at this point, compiler doesn't know which method to call,
                    // decision is deferred to runtime
                    // late binding = dynamic binding = chossing functions during runtime
    ptr2->show();
    ptr2 = &dv4;
    ptr2->show();

    // Using Pure Virtual Function (Abstract Class)
    //Base3 bad; // ERROR!! can't make objects from abstract class
    Base3 *arr[2];
    Derv5 dv5;
    Derv6 dv6;
    arr[0] = &dv5;
    arr[1] = &dv6;

    arr[0]->show();
    arr[1]->show();
    return 0;
}
//*/
