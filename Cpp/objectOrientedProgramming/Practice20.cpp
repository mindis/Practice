/*//
// This program demonstrates friend classes.
// Lessons: A classA can used freely use all of another classB's data in classA's member functions
    // by declaring classA as a friend class in class B.
    // ex: friend class classA; // declared in class B.
// This proram demonstrates use of static functions for debugging
// Lessons: Destructors activates by default at end of program.
// Lessons: static functions allows classname to access it with scope resolution operator instead of objects.

//  Member functions of a class can all be made friends when you make the entire class a friend
#include <iostream>
using namespace std;

//================
// Friend Classes
//================
class alpha
{
    private:
        int data1;
    public:
    alpha() : data1(99) {}
    friend class beta; // all member functions in class beta can access private data class alpha
};

class beta
{
    public:
        // methods (can automatically access alpha datas as declared a friend class in class alpha)
        void func1(alpha a) { cout << "\ndata1 = " << a.data1;} //
};

//===================
// Static Functions
//===================

class gamma
{
    private:
        static int total; // total data is shared by all objects of this class
        int id;
    public:
        // constructor
        gamma()
        {
            total++;
            id = total;
        }
        // destructor
        ~gamma()
        {
            total--;
            cout << "Destroying ID number " << id << endl;
        }
        // Methods
        static void showtotal() // static function, allows classname to access it.
        {
            cout << "Total is " << total << endl;
        }
        void showid()
        {
            cout << "ID number is " << id << endl;
        }
};
int gamma::total = 0; // initializing total

int main()
{
    // Friend Classes
    alpha a;
    beta b;
    b.func1(a);
    cout << endl;
    // Static Functions
    gamma g1;
    // more reasonable to refer to static functions using class name instead of merely creating a dummy object
    // to use it.
    gamma::showtotal(); // using static functions, Called by class name.
    gamma g2, g3;
    gamma::showtotal();
    g1.showid();
    g2.showid();
    g3.showid();
    cout << "---------end of program--------------\n";
    // Destructor activates by default when program terminates.
    return 0;
}
//*/
