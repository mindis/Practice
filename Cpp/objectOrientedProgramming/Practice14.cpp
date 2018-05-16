/*
//
// This program demonstrates problems (2 parent class having the same function name)
        //with multiple inheritance and how to solve it.
// Lessons: The problem is solved by declaring which method to call
    // EX: C.A::gfsdet(); instead of C.get();
// Lessons:  // Since funcA() and funcB() in parent class A and B are declared public/protected
            // the function funcC() in its derived class is able to access it using A::funcA() & B::funcB();
            // you can't do A::funcA() in main/other functions if funcA() is declared private/protected
            // however, you can access it through getC() in main/other functions
                // since funcC() is declared public

// handling constructors with multiple inheritance
#include <iostream>
#include <string>
using namespace std;
class Type
{
    private:
        string dimensions;
        string grade;
    public:
        // constructors
        Type() : dimensions ("N/A"), grade("N/A") {}
        Type(string di, string gr) : dimensions(di), grade(gr) {}
        // methods
        void gettype()
        {
            cout <<" Enter nominal dimensions (2x4 etc.): ";
            cin >> dimensions;
            cout << " Enter grade (rough, const, etc.): ";
            cin >> grade;
        }
        void showtype() const
        {
            cout << "\n   Dimensions: " << dimensions;
            cout << "\n   Grade: " << grade;
        }
};

class Distance
{
    private:
        int feet;
        float inches;
    public:
        Distance() : feet(0), inches(0.0) {}
        Distance (int ft, float in) : feet(ft), inches(in) {}
        void getdist()
        {
            cout << "   Enter feet: "; cin >> feet;
            cout << "   Enter inches: "; cin >> inches;
        }
        void showdist() const
        {
            cout << feet << "\'-" << inches << '\"';
        }
};

class Lumber : public Type, public Distance
{
    private:
        int quantity;
        double price;
    public:
        // constructors;
        Lumber() : Type(), Distance(), quantity(0), price(0.0) {}
        Lumber( string di, string gr, int ft, float in, int qu, float prc):
            Type(di, gr), Distance(ft, in),
            quantity(qu), price(prc)
            {}
        // methods
        void getlumber()
        {
            // Since gettype() and getdist in parent class is public/protected
                // the function getlumber() in its derived class is able to access it.
            // you can't do Type::gettype() in main/other functions if gettype() is declared private/protected
            // however, you can access it through getlumber() in main/other functions since getlumber() is
                // public
            // able to call its parents methods by using its parents to call.
            Type::gettype(); // note how its not just gettype() nor Lumber.gettype()
            Distance::getdist();
            cout << "   Enter quantity: "; cin >> quantity;
            cout << "   Enter price per piece: "; cin >> price;
        }
        void showlumber() const
        {
            Type::showtype();
            cout << "\n Length: ";
            Distance::showdist();
            cout << "\n  Price for " << quantity << " pieces: $" << price * quantity;
        }
};

// Problems with multiple inheritance,
// 2 base class with same method that is not defined in derived class
class A
{
    public:
        void show() {cout << "Class A\n";}
};

class B
{
    public:
        void show() {cout << "Class B\n";}
};

class C: public A, public B
{
};

int main()
{
    // Constructors with multiple inheritance
    Lumber siding;
    cout << "\nSiding data:\n";
    siding.getlumber();

    Lumber studs( "2x4", "const", 8, 0.0, 200, 4.45F);
    cout << "\nSiding"; siding.showlumber();
    cout << "\nStuds"; studs.showlumber();
    cout << endl;

    // Functions with multiple inheritance
    C objC;
    // objC.show(); // ERROR, will not compile, does not know which base class method to call
    // resolved with scope resolution operator
    objC.A::show();
    objC.B::show();
    return 0;
}
//*/
