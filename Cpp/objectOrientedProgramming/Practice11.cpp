/*
//
// This program demonstrates inheritance
// Lessons: Only no argument constructor gets passed down.

// Inheritance
// code reusability, reliability, flexible
// Base class = parent class
// Derived class = children class
#include <iostream>
using namespace std;
#include<stdlib.h>
enum posneg {pos, neg};
// generalization = parent class is more general than child class.

class Counter
{
    protected: // derived class can only access members of base class if
               // the members are public or protected.
               // if not, they can access them based on member functions in base class
                    // access by based class.
        unsigned int count;
    public:
        // constructors
        Counter() : count(0) {}
        Counter(int c) : count(c) {}
        // methods
        unsigned int get_count() const {return count;}
        // overloaded ++ operator
        Counter operator ++ () // increment count (prefix)
        { return Counter(++count); }
};

// derived class extends baseclass
class CountDn : public Counter
{
    public:
        // If no constructor is given, it takes from parent by default.
        // NOTE: it only inherits the no argument constructor from parent class
        // any constructor with arguments won't be inherited.
        // As long as you don't override the methods from parent class,
        // derived class will inherit it.

        // Constructors
        // call constructor from base class
        CountDn() : Counter() {}
        CountDn(int c) : Counter(c) {}
        // Operator overloading
        CountDn operator -- () // decrement count (prefix)
        { return CountDn (--count); }
};

class Stack
{
    protected:
        enum{MAX = 3};
        int st[MAX];
        int top;
    public:
        Stack() {top == -1;}
        void push (int var)
            {st[++top] = var;}
        int pop() {return st[top--];}
};

class Stack2 : public Stack
{
    public:
        // To override a function,
            // declare the exact same function as parent.
            // Remember to implement the parent function
            // if needed by calling it in your own function.
        // note: same function as parent
                    // same name and argument
        void push(int var)
        {
            if (top >= MAX -1 )
                { cout << "\nError: stack is full"; exit(1); }
                // calling parent function
                Stack::push(var); // call push from Stack class using Stack class.
        }
        // note: same function as parent
            // same name and argument
        int pop()
        {
            if (top < 0 ) {cout << "\nError: stack is empty\n"; exit(1);}
            // calling parent function
            return Stack::pop(); // call pop from Stack class
            // note: without scope resolution (::), compiler will think this is a recursive
            // function instead.
        }
};

class Distance
{
    protected:
        int feet;
        float inches;
    public:
        Distance() : feet(0), inches(0.0) {}
        Distance (int ft, float in) : feet(ft), inches(in) {}
        void getdist()
        {
            cout << "\nEnter feet: "; cin >> feet;
            cout << "Enter inches: "; cin >> inches;
        }
        void showdist() const
            {cout << feet << "\'-" << inches << '\"'; }
};

class DistSign : public Distance
{
    private:
        posneg sign; // sign is either pos or neg (defined as enum at top)
    public:
        // constructors
        DistSign() : Distance() // call base constructor
            {sign = pos;}
        // 2 or 3 argument constructor
                    // the sign argument is optional since
                    // it is given a default value.
        DistSign(int ft, float in, posneg sg=pos) :
            Distance(ft, in) // call base constructor
            { sign = sg;}
        void getdist()
        {
            Distance::getdist();
            char ch;
            cout << "Enter sign ( + or - ): "; cin >> ch;
            sign = (ch == '+') ? pos : neg;
        }
        void showdist() const
        {
            cout << ( (sign==pos) ? "(+)" : "(-)");
            Distance::showdist();
        }
};

int main()
{
    CountDn c1;
    cout << "\nc1 = " << c1.get_count();
    ++c1; ++ c1; ++c1;
     // note that get_count() returns the count and not print it.
     // thus, you can cout the return value into stdout.
    cout << "\nc1 = " << c1.get_count();
    --c1; --c1;
    cout << "\nc1 = " << c1.get_count();
    cout << endl;

    CountDn c2(100);
    cout << "\nc2 = " << c2.get_count();
    CountDn c3 = --c2;
    cout << "\nc3 = " << c3.get_count();

    DistSign alpha;
    alpha.getdist();
    DistSign beta(11, 6.25);
    DistSign gamma(100, 5.5, neg);
    cout << "\nalpha = "; alpha.showdist();
    cout << "\nbeta = "; beta.showdist();
    cout << "\ngamma = "; gamma.showdist();
    Stack2 s1;
    s1.push(11);
    s1. push(22);
    s1.push(33);
    cout << endl << s1.pop();
    cout << endl << s1.pop();
    cout << endl << s1.pop();
    cout << endl << s1.pop();
    cout << endl;
    return 0;
}
//*/



