/*
//
//
// This program demonstrates the ability of a child class to still use
    // its parents method and access it's parents data.

// Lessons: A child function can always invoke its parents methods regardless of public/private
            // by calling the method using its parent.
            //ex: getBla() { parent::haha(); } // will NOT work if haha is declared private.
// Lessons: Inheritance uses scope resolution operator when using methods from its parent classes.
// Lessons: Scoping methods/data from a class can only be accessible depends on where it is
    // called. Being called the exact same form objA::protdataA can only work if its called
        // anywhere in its class hierarchy but wont work if its called anywhere outside its class
            // hierarchy.
// parent with > 1 child
#include <iostream>
using namespace std;
const int LEN = 80;

// Multiple Inheritance

// relationships
//class student
//{ };
//class employee
//{ };
//class manager: private employee, private student
//{ };
//class laborer: public employee
//{ };

class student
{
    private:
        char school[LEN];
        char degree[LEN];
    public:
        // public functions to allow derived class
        // to access private member datas (school, degree)
        void getedu()
        {
            cout << " Enter name of school or university: ";
            cin >> school;
            cout << " Enter highest degree earned\n";
            cout << "  (Highschool, Bachelor's, Master's, PhD): ";
            cin >> degree;
        }
        void putedu() const
        {
            cout << "\n School or university: " << school;
            cout << "\n Highest degree earned: " << degree;
        }
};

class employee
{
    private:
        char name[LEN];
        unsigned long number;
    public:
        void getdata()
            {
                cout << "\n Enter last name: "; cin >> name;
                cout << " Enter number: "; cin >> number;
            }
        void putdata()
            {
                cout << "\n Name: " << name;
                cout << "\n Number: " << number;
            }
};

class manager : private employee, private student
{
    private:
        char title[LEN];
        double dues;
    public:
        void getdata()
        {
            employee::getdata(); // call function using parent class , will only if its public, or protected, not when its private
                                        // as it is parent calling the function not manager::getdata()
            cout << " Enter title: "; cin >> title;
            cout << " Enter golf club dues: "; cin >> dues;
            student::getedu();
        }
        void putdata()
        {
            employee::putdata();
            cout << "\n Title: " << title;
            cout << "\n Golf club dues: " << dues;
            student::putedu();
        }
};

class scientist : private employee, private student
{
    private:
        int pubs;
    public:
        void getdata()
        {
            employee::getdata();
            cout << " Enter number of publications: "; cin >> pubs;
            student::getedu();
        }
        void putdata()
        {
            employee::putdata();
            cout << "\n Number of publications: " << pubs;
            student::putedu();
        }
};

// derived class extending derived class
class laborer: public employee
{ // laborer is exactly the same as employee
  // no extra methods or members
};

class foreman : public laborer
{
    private:
        float quotas;
    public:
        void getdata()
        {
            laborer::getdata(); // note how laborer can do getdata cause it was declared public
                                    // in class laborer
            cout << " Enter quotas: "; cin >> quotas;
        }
        void putdata()
        {
            laborer::putdata();
            cout << "\n Quotas: " << quotas;
        }
};

int main()
{
    manager m1, m2;
    scientist s1, s2;
    laborer l1;
    foreman f1;
    cout << endl;
    cout << "\nEnter data for manager 1";
    m1.getdata();

    cout << "\nEnter data for manager 2";
    m2.getdata();

    cout << "\nEnter data for scientist 1";
    s1.getdata();

    cout << "\nEnter data for laborer 1";
    l1.getdata();

    cout << "\nEnter data for foreman 1";
    f1.getdata();


    cout << "\nData on manager 1"; m1.putdata();
    cout << "\nData on manager 2"; m2.putdata();
    cout << "\nData on scientist 1"; s1.putdata();
    cout << "\nData on laborer 1"; l1.putdata();
    cout << endl;
    cout << "\nData on foreman 1"; f1.putdata();
    cout << endl;
    return 0;
}
// */
