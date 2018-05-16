/*
//
// This program demonstrates difference between virtual destructors and non-virtual destructors
// Lessons: Always use virtual destructors in highest parent class.
                // Destructors are like functions, if it's not virtual,
                // the pointer's destructor gets called.
// Not Using Virtual Destructor : will start deleting from the Parent of Object pointed to all the way upwards.
// Using Virtual Destructor : works on pointer from Current (hierarchy the virtual is declared)
                            // to child onwards and will delete all the way upwards to highest parent.
                            // if the pointer works (from current to lowest child)

// Alternate by making Base Destructor virtual and Derv Destructor Virtual to see how the lessons makes sense.

// Virtual Function & Virtual Destructor
#include <iostream>
using namespace std;

class person // an abstract class
{
    protected:
        char name[40];
    public:
        void getName()
        {
            cout <<"    Enter name: "; cin >> name;
        }
        void putName()
        {
            cout << "Name is " << name << endl;
        }
        // pure virtual functions
        virtual void getData() = 0;
        virtual bool isOutstanding() = 0;
};

class student : public person
{
    private:
        float gpa;
    public:
        void getData()
        {
            person::getName();
            cout << "   Enter student's GPA: "; cin >> gpa;
        }
        bool isOutstanding()
        {
            return (gpa>3.5) ? true : false;
        }
};

class professor : public person
{
    private:
        int numPubs;
    public:
        void getData()
        {
            person::getName();
            cout <<"Enter number of professor's publications: ";
            cin >> numPubs;
        }
        bool isOutstanding()
        {
            return (numPubs>100) ? true : false;
        }
};

// Basically, if base class destructor is virtual, it will delete from object pointed to upwards,
// If base class destructor is not virtual, it will delete from pointer type upwards.

// Virtual Destructor
// Base class destructor should always be virtual
// if you use delete with a base class pointer to a derived class object to destroy derived class object,
    // if the base-class destructor is NOT virtual, then delete (like a normal function)
    //  calls the destructor of base class instead of
    // derived class. This cause only the base part of object to be destroyed.

// Virtual & Non-Virtual Destructor
class Base
{
    public:
    // alternate both constructors by commenting one out to see output
       // ~Base() // non-virtual destructor
        virtual ~Base() // virtual destructor
        // declaring virtual constructor allows objects to be destroyed properly
            // when using base pointer to derived objects
        {
            cout << "Base destroyed\n";
        }
};

class Derv : public Base
{
    public:
        // will call the parent's class destructor too!
        ~Derv() // note how this is not virtual, as long as highest parent destructor is virtual,
                        // any destructor will destroy everything.
        {
            cout << "Derv destroyed\n";
        }
};

class ExtraDerv : public Derv
{
    public:
        // will call the parent's class destructor too!
        ~ExtraDerv() // note how this is not virtual
        {
            cout << "ExtraDerv destroyed\n";
        }
};
int main()
{
    // Virtual Function => polymorphism
    person *persPtr[100];
    int n = 0;
    char choice;

    do
    {
        cout <<"Enter student or professor (s/p): ";
        cin >> choice;
        if(choice == 's')
            persPtr[n] = new student; // make memory for student object
        else
            persPtr[n] = new professor; // make memory for professor object
        persPtr[n++]->getData();
        cout<<" Enter another (y/n)? ";
        cin >> choice;
    } while (choice == 'y');

    for (int j = 0; j < n; j++)
    {

        persPtr[j]->putName();
        if (persPtr[j]->isOutstanding())
            cout << "   This person is outstanding\n";
    }


    // Virtual and Non-Virtual Destructors
    Base *pBase = new ExtraDerv; // parent pointer to grandchild object
    Base *p2Base = new Derv;    // parent pointer to child object.
    Derv *pDerv = new ExtraDerv; // child pointer
    delete pBase; // invokes destructor (the destructor invoked depends if destructor of pointer is virtual or non-virtual.
    cout << endl;
    delete p2Base;
    cout << endl;
    delete pDerv; // still kills everything even if ~Derv() is not virtual.
    return 0;
}
//*/





