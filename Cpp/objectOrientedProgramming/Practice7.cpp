/*//
// This program overloads the < and += operator for Distance( feet & inches)
// This program overloads the == operator for user-defined String class.
// This program overloads the [] operator for user-defined saferay class.
// Lessons: Overloading Comparison Operator & Subscript Operator
// Lessons: Return by reference (returning &int for function)

// Comparison Operator  (< , > )
// Subscript Operator []
#include <iostream>
#include <string.h>
#include <stdlib.h> // for exit()
using namespace std;
const int LIMIT = 20;

class Distance
{
    private:
        int feet;
        float inches;
    public:
        // constructors
        Distance() : feet(0), inches(0.0) {}
        Distance(int ft, float in) : feet(ft), inches(in) {}
        void getdist()
        {
            cout << "\nEnter feet: "; cin >> feet;
            cout << "Enter inches: "; cin >> inches;
        }
        void showdist() const
        {
            cout << feet << "\'-" << inches << '\"';
        }
        // overloading operators
        bool operator < (Distance) const; // compare distance
        //
        void operator += (Distance);
};

bool Distance::operator < (Distance d2) const
{
    float bf1 = feet + inches/12;
    float bf2 = d2.feet + d2.inches/12;
    return (bf1 < bf2) ? true : false;
}

void Distance::operator += (Distance d2)
{
    feet += d2.feet;
    inches += d2.inches;
    if (inches >= 12.0)
    {
        inches -= 12.0;
        feet++;
    }
// you can do dist3 = dist1 += dist2;
// if you provide a return value
// you can end the operator +=() definition with:
// return Distance(feet,inches);  // nameless object initialized to values and returned.
}

class String
{
    private:
        enum {SZ = 80};
        char str[SZ];
    public:
        // constructors
        String () {strcpy(str, "");}
        String (char s[]) {strcpy (str, s);}
        // methods
        void display() const{cout << str;}
        void getstr() {cin.get(str, SZ);}
        // overloaded comparison operator
        bool operator == (String ss) const
        {return (strcmp(str,ss.str) == 0) ? true: false;}
};

// Overloading subscript [] operator
class safearay
{
    private:
        int arr[LIMIT];
    public:
        // set value element
        void putel(int n, int elvalue)
        {
            if (n < 0 || n > LIMIT)
                {cout << "\nIndex out of bounds"; exit(1);}
            arr[n] = elvalue;
        }
        int getel(int n) const
        {
            if ( n < 0 || n >= LIMIT)
                {cout << "\nIndex out of bounds"; exit(1);}
            return arr[n];
        }

        // you can use same member function
        // to both insert data and print it.
        // return by reference

        // This method returns a memory address of a variable
        // similar to returning a pointer, just that you return a variable,
        // and the memory address of that variable will be given instead.
        int& access(int n)
        {
            if (n < 0 || n > LIMIT)
            {
                cout << "\nIndex out of bounds"; exit(1);
            }
            return arr[n];
        }

        // Access arrays by overloading [] operator

        // return the memory address of an int (allows user to return a normal int variable in code, but
                                                // function returns the memory address of the int variable instead)
        int& operator [] (int n) // return by reference
        {
            if (n < 0 || n > LIMIT)
            {
                cout << "\nIndex out of bounds"; exit(1);
                return arr[n];
            }
        }
};

int main()
{
    // Comparison Operators

    String s1 = "yes";
    String s2 = "no";
    String s3;
    cout << "\nEnter 'yes' or 'no': ";
    s3.getstr();
    if(s3 == s1)
        cout << "You typed yes\n";
    else if (s3 == s2)
        cout << "You typed no\n";
    else
        cout << "You didn't follow instructions\n";

    Distance dist1;
    dist1.getdist();
    Distance dist2(6,2.5);
    cout << "\ndist1 = "; dist1.showdist();
    cout << "\ndist2 = "; dist2.showdist();
    if(dist1 < dist2) // overloaded < operator
    {
        cout << "\ndist1 is less than dist2";
    }
    else
        cout << "\ndist1 is greater than (or equal to) dist2";
    cout << endl;

    dist1 += dist2;
    cout << "\nAfter addition:";
    cout << "\ndist1 = "; dist1.showdist();
    cout << endl;

    // Subscript Operator
    safearay sa1;
    for (int j = 0; j < LIMIT; j++)
        sa1.putel(j, j*10);
    for (int j = 0; j < LIMIT; j++)
        cout << "Element " << j << " is " << sa1.getel(j) << endl;

    // inserting values by reference using access method.
    // the member function is on the left of =
        // whereas the value on the right of =
        // will be assigned to the variable
        // returned by the function.
    // In other words, you can assign values to the return value of the
    //              member function access()
    cout << "Accessing using one member function" <<endl;
    for (int j = 0; j < LIMIT; j++)
    {
        // access(j) returns a reference
        sa1.access(j) = j*10;
    }
    // printing values by reference using access method.
    for (int j = 0; j < LIMIT; j++)
    {
        int temp = sa1.access(j);
        cout << "Element " << j << " is " << temp << endl;
    }
    cout << "Accessing using overload [] operator" << endl;

    for(int j = 0; j < LIMIT ; j++)
    {
        // note how you can use normal subscipt methods
        // for own defined class safearay.
        sa1[j] = j*10;
    }
    for (int j = 0; j < LIMIT ; j++ )
    {
        int temp = sa1[j];
        cout << "Element " << j << " is " << temp << endl;
    }
    return 0;
}
//*/
