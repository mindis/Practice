/* //
// This program makes a Counter (count) class and increments it using ++ (prefix & postfix) operator
// This program makes a Distance (feet & inches) class and adds them using + operator.
// Lessons: Overloading Unary Operators, Overloading Binary Operators,
    // operators that cannot be overloaded

// Operator Overloading => changing the way operators (+, -, *, /, <= , +=) works..
// allows use of operators for user-defined types (classes, structs)
// Overloading Unary Operator  ( ++, --, -1)
#include <iostream>
using namespace std;

class Counter
{
    private:
        unsigned int count;
    public:
        Counter() : count(0)
        {}
        unsigned int get_count() {return count;}
        // tells compiler to call this member function (method)
        // whenever it sees a ++ operator.
        // return type void, no parameters.
        // it's basically like a method but with keyword operator and
        // you call it using ++
        void operator ++ () {++count;}
        // similar to overloaded functions, compiler distinguish
        // overloaded operators by data types.
        // in this case, the data type is Counter.
        // unfortunately, since return type is void, you can't use
        // c1 = c2++; (since c2++ does not return a value)
        // and you overload the same operator by changing it's return value
};

class Counter2
{
    private:
        unsigned int count;
    public:
        // constructors
        Counter2() : count(0) {}
        Counter2(int c) : count(c) {}
        // methods
        unsigned int get_count() {return count;}
        // overloaded operators
        Counter2 operator ++ () // increment count (prefix)
        {
            ++count;
            // returns an unnamed temporary object initialize
            // to this count.
            return Counter2(count);
        }
                        // note that int isn't an argument nor integer in this case
                        // it simply is the keyword to overload a postfix operator
        Counter2 operator ++ (int) // increment count (postfix)
        {
            // returns an unnamed temporary object initialize
            // to this count, then increment count
            return Counter2(count++);
        }
};

// Overloading Binary Operators

class Distance
{
    private:
        int feet;
        float inches;
    public:
        // Constructors
        Distance() : feet(0), inches(0.0) {}
        Distance(int ft, float in): feet(ft), inches(in) {}
        // Member Functions
        void getdist()
        {
            cout << "\n Enter feet: "; cin >> feet;
            cout << "\n Enter inches: "; cin >> inches;
        }
        // const signify that no variables should be
        // changed in this method.
        void const showdist()
        {
            cout << feet << "\'-" << inches <<'\"';
        }
        // prototype for overloading + operator
        // has return type Distance and takes one argument of type Distance
        // dist3 = dist1 + dist2;
        // dist1 is the member (left of + operator)
        // dist2 is the argument (right of + operator)
        // dist3 gets the return type from assignment.
        Distance operator  + ( Distance ) const ;
        // overloaded operators => number of arguments = number of operands - 1;
};
// defined here
Distance Distance::operator + (Distance d2) const
{
    int f = feet + d2.feet;
    float i = inches + d2.inches;
    if ( i >= 12.0)
    {
        i -= 12.0;
        f++;
    }
    // return a temporary Distance object initialize to f and i.
    return Distance(f,i);
}

int main()
{
    // Overloading Unary Operators
    Counter c1, c2;
    cout << "\nc1= " << c1.get_count();
    cout << "\nc2= " << c2.get_count();
    ++c1; ++c2; ++c2;
    cout << "\nc1= " << c1.get_count();
    cout << "\nc2= " << c2.get_count() << endl;

    Counter2 c3, c4;
    cout << "\nc3= " << c3.get_count();
    cout << "\nc4= " << c4.get_count();
    ++c3;
    c4 = ++c3;
    cout << "\nc3= " << c3.get_count();
    cout << "\nc4= " << c4.get_count() << endl;
    c4 = c3++;  // note that it's posfix operator.
    cout << "\nc4= " << c4.get_count();
    c4 = c3; // c3 gets incremented after assignment in previous.
    cout << "\nc4= " << c4.get_count() << endl;

    // Overloading Binary Operators
    Distance dist1, dist3, dist4;
    dist1.getdist();
    Distance dist2(11, 6.25);
    // using overloaded binary + operator
    dist3 = dist1 + dist2;
    dist4 = dist1 + dist2 + dist3;
    cout << "dist1 = ";  dist1.showdist(); cout<<endl;
    cout << "dist2 = ";  dist2.showdist(); cout<<endl;
    cout << "dist3 = ";  dist3.showdist(); cout<<endl;
    cout << "dist4 = ";  dist4.showdist(); cout<<endl;
    return 0;
}

// Operators that cannot be overloaded:
// i) dot operator(.)
// ii) scope resolution operator(::)
// iii) pointer to member operator (->)
// iv) Own Made operators (you can only overload existing operators)
//*/
