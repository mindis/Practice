/*//
// This program demonstrates Aggregation
// Lessons: A class can use all of another class methods and datas
    // by having a data of the other class as one of its members
    // It's similar to array class in python.
        // the array will always have built-in methods getlength etc.
        // its like how an array in a struct will always allow
        //  any instance of the struct to use all of array's built-in functions
        //  like getlength etc..ads
// Lessons: Aggregation uses dot operator when using methods from its stored classes.

// Demonstrates Aggregation (similar to interfaces)
// Inheritance => is-a relationship
// Aggregation => has-a relationship
// Aggregation = one object is an attribute of another
//      A class within another class
// Composition => consists-of relationship
#include <iostream>
#include <string>
using namespace std;

// Relationships
//class student
//{};
//class employee
//{};
//class manager
//{
//   student stu; // stu is an object of class student
//   employee emp; // emp is an object of class employee
//};
//class scientist
//{
//    student stu; // stu is an object of class student
//    employee emp; // emp is an obect of class employee
//};
//class laborer
//{
//    employee emp; // emp is an object of class employee
//};

class student
{
    private:
        string school;
        string degree;

        void getedupriv() // private member function
        {
            cout << "   Enter name of school or university: ";
            cin >> school;
            cout << "   Enter highest degree earned\n";
            cout << "   (Highschool, Bachelor's, Master's, PhD: ";
            cin >> degree;
        }
    public:
        void getedu()
        {
            cout << "   Enter name of school or university: ";
            cin >> school;
            cout << "   Enter highest degree earned\n";
            cout << "   (Highschool, Bachelor's, Master's, PhD: ";
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
        string name;
        unsigned long number;
    public:
        void getdata()
        {
            cout << "\n Enter last name: "; cin >> name;
            cout << "   Enter number: "; cin >> number;
        }
        void putdata() const
        {
            cout << "\n Name: " << name;
            cout << "\n Number: " << number;
        }
};

// A manager has-a employee and student.
class manager
{
    private:
        string title;
        double dues;
        employee emp; // has an object of type employee
        student stu; // has an object of type student
    public:
        void getdata()
        {
            emp.getdata();
            cout << "   Enter title: "; cin >> title;
            cout << "   Enter golf club dues: "; cin >> dues;
            stu.getedu();
            // stu.getedupriv(); // ERROR!! can't access private member functions outside class.
        }
        void putdata() const
        {
            emp.putdata();
            cout << "\n Title: " << title;
            cout << "\n Golf club dues: " << dues;
            stu.putedu();
        }
};

// A scientist has-a employee and student
class scientist
{
    private:
        int pubs;
        employee emp;
        student stu;
    public:
        void getdata()
        {
            emp.getdata(); // note how its using dot operator instead of (scope resolution::) operator

            cout << "   Enter number of pubs: "; cin >> pubs;
            stu.getedu();
        }
        void putdata() const
        {
            emp.putdata();
            cout << "\n Number of publications: " << pubs;
            stu.putedu();
        }
};

class laborer
{
    private:
        employee emp;
    public:
        void getdata()
        { emp.getdata();}
        void putdata() const
        {emp.putdata();}
};

int main()
{
    manager m1;
    scientist s1, s2;
    laborer l1;

    cout << endl;
    cout << "\nEnter data for manager 1";
    m1.getdata();

    cout << "\nEnter data for scientist 2";
    s2.getdata();
    cout << "\nEnter data for laborer 1";
    l1.getdata();

    cout << "\n Data on manager 1";
    m1.putdata();
    cout << "\n Data on scientist 1";
    s1.putdata();
    cout << "\n Data on scientist 2";
    s2.putdata();
    cout << "\nData on laborer1 ";
    l1.putdata();
    cout << endl;
    return 0;
}
// Composition => has all characteristics of aggregation and
//                  i) part may belong to only one whole
//                  ii) lifetime of part is same as lifetime of whole

// Software Tools Developer => creates general-purpose programming tool (ex: Allegro 5)
// Application Developers => using the software tools created for real life application.
//*/
