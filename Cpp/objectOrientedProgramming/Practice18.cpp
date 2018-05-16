/*
//
// This program demonstrates how child classes shares a copy of parent by declaring the parent virtual
    // to solve error in multiple inheritance.
// This program demonstrates how friend functions is used to allow outside class to access data members
            // of a class.
// Lessons: Friendfunctions allow outside class to access the private data members of the class
                    // in some of their functions(called friend functions).

// Virtual Base class & Friend Functions
// problems with multiple inheritance
#include <iostream>
using namespace std;

//=======================
// Virtual Base Class
//=======================

class Parent
{
    protected:
        int basedata;
};

class Child1 : public Parent {};
class Child2 : public Parent {};
class Grandchild : public Child1, public Child2
{
    public:
        int getdata()
            {
               // return basedata; // ERROR!!ambiguous , compile error will occur if
                    // Grandchild attemps to access basedata in Parent.
                    // because both Child1 and Child2 inherits different copies of
                    // data (known as subobject) from Parent.
                    // Thus, Grandchild won't know which basedata to access.
            }
};

// To prevent this problem, we make both childs virtual base classes
class Parent2
{
    protected:
        int basedata;
};

class Child3 : virtual public Parent2 {}; // shares copy of Parent2
class Child4 : virtual public Parent2 {}; // shares copy of Parent2
class Grandchild2 : public Child3, public Child4
{
    public:
        int getdata()
        {
            return basedata; // not error, only one copy of parent
        }
};

//================================
// Friend Functions
//================================
// Act as bridges between 2 classes
    // adds flexibility but prevents data hiding
    // if you use a lot of friend functions, your need to improve your design

class beta; // needed for friend function declaration in class alpha

class alpha
{
    private:
        int data;
    public:
        // constructor
        alpha() : data(3) {}
        // friend function
        // to allow outside class to access private data of class alpha
        friend int frifunction(alpha, beta); // keyword friend
};

class beta
{
    private:
        int data;
    public:
        // constructor
        beta() : data(7) {}
        // to allow outside class to access private data of class beta
        friend int frifunction(alpha, beta); // friend function
};

// declaration
// we want frifunction to have access to both private data members,
    // so it's declared with friend keyword in both classes
// declaration can be anywhere (private or public)
int frifunction(alpha a, beta b)
{       // imagine if frifunction() is used in class beta,
        // it wont be able to use notation a.data in this function
            // if it wasn't declared as a friend function in class alpha.
    return (a.data + b.data);
}

int main()
{
    alpha aa;
    beta bb;
    // note how frifunction is used in main, we have to declare it in both classes (beta and alpha)
    // to allow mian to use datas from both class.
    cout << frifunction(aa, bb) << endl;
    return 0;
}
// Conclusion:
// friend function must be declared in the class whose member that the function accessed.
// Since we can't change the source code for a class, you can't access it's member through friend function
    // since you can't declare that function as friend in that class.
// To make a function a friend function, only the function declaration in the class is preceded by keyword friend
// Class definition and calls to function are written normally
//*/
