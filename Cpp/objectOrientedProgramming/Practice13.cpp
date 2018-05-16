/*
//
// This program demonstrates the difference between privately derived class(default) and publicly derived class
// Lessons:       Type       | private data |  protected data     |  public data
// Function privately derived|  NO          |   YES               |     YES
// Function publicly derived |  NO          |   YES               |     YES
// Data     privately derived|  NO          |   NO                |     YES
// Data     publicly derived |  NO          |   NO                |     NO  // Only difference betwee private & public child.

// class base class : access specifier derived class
// class B : public A
// class C : private A
// public specifies that objects of derived class
// are able to access public member functions of base class
// private specifies objects of derived class
// cannot access public member functions of base class
// thus, no member of base class is accessible to objects of
// derived class

// public => extends base class
// private => information hiding

#include <iostream>
using namespace std;

// Functions in derived class can access protected and public data from base class
// Objects in derived class cannot access protected and private members of base class

class A
{
    // Datas
    private:
        int privdataA;
    protected:
        int protdataA;
    public:
        int pubdataA;
        // method
        int getprivdataA() {return privdataA;}
};

// publicly derived
class B : public A
{
    public:
        void funct()
        {
            int a;
            // a = privdataA; // ERROR, function can't access private member
            a = protdataA; // note how it is directly accessing data from class A
                                // (only if it is used in a function in the derived class
                                // protected allows derived class's function to acces it
            a = pubdataA;
           // a = A::privdataA; // ERROR!!
           a = A::getprivdataA(); // WORKS!, cause getprivdataA() is declared public/protected in A.
        }
};

// if you don't specify access specifier, private by default
// privately derived
class C : private A
{
    public:
        // function can access protected and public data from base class
        void funct()
        {
            int a;
            // a = privdataA; // ERROR, functions can't access private member.
            a = protdataA;
            a = pubdataA;
        }
};

// Difference with publicly derived and privately derived class
// Objects in publicly derived can only access public members of base class
// Objects in privately derived class cannot access any members from base class

// Multiple Inheritance = a class derived > 1 base class
class D
{
};
class E
{
};
class F : public D, public E
{
};

// Considered a function outside any class.
int main()
{
    int a;
    A objA;
    // a = objA.privdataA; //ERROR!!! you can't access privdata of a class outside class
    // objects can only access public members from base class
    B objB; // is publicly inherited from A.
    // a = objB.privdataA; // ERROR, can't access private data fom a class using publicly derived class b
                                //(cause it is not used in a function from derived class)
    // a = objB.protdataA; // ERROR
    a = objB.pubdataA;
    // a = objB.A::privdataA; // ERROR!!! can't access privdataA using parent class regardless.
                                        // can only do so by calling A::getprivdataA() (a public member function from A)
                                        //  in B's member function

    // objects of privately derived class cannot access any members
    // from baseclass including public
    C objcC; // is privately inherited from A
    // a = objC.privdataA; // ERROR
    // a = objC.protdataA; // ERROR
    // a = objC.pubdataA; // ERROR
        // Errors, cause objC can't access anydata from class if declared privately derive
            // will only be able to access public & protected data from classA using its member functions.
    return 0;
}
// Conclusion:
// A member function of a class can always access class members (public or private).
// Object of class A can only access public members of A.
// An object of a class declared externally can only invoke public members (using . operator)
    // In main() or any other function that is not a member of A, the statement:
                        // objA.funcA(); // ERROR!! unless funcA() is public.
// You can access any class's priv data using a public member function in that class.
// Lets just say cause the member function is public, you can use it anywhere.
        // and since member functions of a class can access priv data's of a class,
            // that member function allows you to access it through it.
            // but you can't access the privdata directly (. operator)
            // as long as you are outside the class. (in main function, etc..)
//*/
