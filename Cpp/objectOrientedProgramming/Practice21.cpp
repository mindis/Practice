/*//
// This program shows the difference between the assignment (=) operator and copy (=) constructor
            // and how to prohibit copying
// Lessons: copy constructor creates a new copy of the variable, assignment simply gives value to a variable that already exists.
// This program overloads the assignment (=) operator and shows how it is used.
// Lessons: Assignment operator (=) is only invoked when you use (=) operator in an assignment without initialization.
           //  when you use (=) as an initialization, it does not invoke the (=) assignment operator.
                    // instead, it invokes the copy constructor
// Lessons: Assignment operator (=) is not inherited
// This program overloads the copy constructor (=) operator and shows how it is used.
// Lessons: default copy constructor = default member by member copying.

// Overloading Assignment Operator & Copy Constructor
#include <iostream>
using namespace std;

class alpha
{
    private:
        int data;
    public:
        // constructors
        alpha() { }
        alpha (int d) : data(d) {}
        // overloading copy constructor
        alpha(alpha& a) // Note: You MUST pass in reference as argument in a copy constructor.
                        // because if you use a value instead, the compiler NEEDS the copy constructor
                        // to create the value for this copy constructor.
                        // Thus, this results in an error as the copy constructor calls itself.
                        // As a result, it calls itself recursively until the compiler runs out of memory.
        {
            data = a.data;
            cout << "\nCopy constructor invoked";
        }
        // methods
        void display()
        {
             cout << data;
        }
        // overloading assignment operator
        void operator = (alpha &a)
        {
            data = a.data;
            cout << "\nAssignment operator invoked";
          //  return alpha(data);
        }
};

// Preventing Assignment and Copy Constructor
class beta
{   // to prevent assignment/ copy constructor, define them as private.
    // you don't have to define the functions since they will never be called.
    private:
        int data;
        beta& operator = (beta&);
        beta(beta&);
    public:
        // constructors
        beta() : data(0) {}
};

int main()
{
    // Overloading Assignment Operator & Overloading Copy Constructor
    alpha a1(37); // initialize with assignment
    alpha a2; // initialize
    // use assignment operator to set value of a2.
    a2 = a1; // different with conversion operator, invoked using (=) operator
    cout << "\na2 = ";
    a2.display();
    // Initialize
    alpha a3 = a2; // does NOT invoke assignment operator (copies initialization, not an assignment)
            // same effect as alpha a3(a2);
            // invokes copy constructor
    cout <<"\na3 = ";
    a3.display();
    cout << endl;
    beta b1, b2;
    // ERRORS!! Copy constructor and Assignment operator are private.
    // b1 = b2; // assignment
    // beta b3(b1); // copy constructor
    return 0;
}
// Conclusion:
// Assignment operator(=) is unique as it is not inherited.
// Copy Constructor creates a new copy of the variable, Assignment operator simply assigns values to a variable already created.
// Copy constructor is invoked ewhen:
    // i) an object is defined, EX: alpha a = b;
    // ii) arguments are passed by value to functions (when a function makes a copy of a parameter passed in as arguments).
                // Note: Copy constructor is not invoked if argument was passed in by reference. (no copy create)
    // iii) values are returned from functions, EX: return a;
// Destructors are automatically activated if copy constructors are used in a function.
    // To be safe, always pass in values by reference.
// You can prohibit copying by overloading the copy constructor and assignment operator as private.
//*/
