/* //
// This program creates a class Distance (feet & inches) and a member function to add
// the Distances.
// Lessons: Introduction to Classes ( Constructor, Destructor, Member functions, private datas)
// Lessons: Reasons for const
// Classes
#include <iostream> // for cout, cin
using namespace std;
// interface = the way classes are accessed
// abstract class = class without value
// base class = superclass
// derived class = subclass
// specifier = definition of a class
class smallobj // define a class
{
    private: // data are hidden outside class
        int data;
    public:  // can be accessed outside class
        // these are the (member functions = methods) for the class
        // methods are the only way data's in a class
        // can be accessed.
        void setdata(int d)
        { //member functions that are defined in a class are inline functions
            data = d;
        } // member functions that are not defined in a class are not inline functions. (will see later)
        void showdata()
        {
            cout << "Data is " << data << endl;
        }
};

class part
{
    private:
        int modelnum;
        int partnum;
        float cost;
    public:
        void setpart(int mn, int pn, float c)
            {
                modelnum = mn;
                partnum = pn;
                cost = c;
            }
        void showpart()
        {
            cout << "Model " << modelnum;
            cout << ", part " << partnum;
            cout << ", costs $" << cost << endl;
        }
};

// counter in C is stored as a global variable, not safe as might be changed
// counter in C++ can only be accessed by its member functions.
// constructors are used to initialize the values of an object so that it doesn't have to be accessed many times
class Counter
{
    private:
        unsigned int count; // variable count
        unsigned int count2; // another variable
    public: // constructor with no arguments, set count = 0 , count2 = 1;
        Counter() : count(0), count2(1) // constructor, notice how it must have the
                                        // exact same name as its class
        {} // empty body  , constructors must have no return value.
        ~Counter() // destructor, preceded by tilde == ~
        {}  // has same name as constructor , no return value nor arguments
        // only want to destroy an object
        // deallocates the memory
        void inc_count() { count++;} // increment count
        int get_count() { return count;}
};

class Distance
{
    private:
        int feet;
        float inches;
    public:
        // notice we have 2 constructors, this is known as
        // Overloaded Constructors
        Distance(): feet(0), inches(0.0)
        {} // default constructor = constructor with no arguments
        Distance(int ft, float in): feet(ft), inches(in)
        {} // 2 arguments constructor
        void getdist()
        {
            cout << "\n Enter feet: "; cin >> feet;
            cout << "Enter inches: "; cin >> inches;
        }
        const void showdist() // const cause data will not be altered
        {
            cout << feet << "\'-" << inches << '\"';
        }
        void add_dist(Distance, Distance); // declaration
        // note, not defined in class to prevent inline
        Distance add_dist2(Distance);
        // member functtion that returns a distance
};

// add the distance of 2 object Distance
// no return value, but it's a function of a class.
// so an instance of a class will call it.
// inches and feet belong to the class that calls it.
void Distance::add_dist(Distance d2, Distance d3)
{ // function name preceded by scope resolution operator (::)
    // :: = specifying what class something is associated with.
    // void is the return type of the member function.
    inches = d2.inches + d3.inches; // add the inches
    // note about member function,
    // besides member function,
    // the data for an object can also be accessed when
    // the object is called. In this case,
    // distance d2 and distance d3's data can be accessed
    // by calling them.
    feet = 0;
    if (inches >= 12.0) // if inches exceed 12,
    {                   // decrease inches and increase feet
        inches -= 12.0;
        feet++;
    }
    // the total feet from both inches adds the feet of both distances.
    feet += d2.feet + d3.feet;
}

// returns a Distance object.
// it is a method, so it's called by an instance of class Distance.
// inches & feet belongs to the instance that calls this method.
Distance Distance::add_dist2(Distance d2)
{ // the :: signifies that this function belongs to class Distance
    Distance temp;
    temp.inches = inches + d2.inches;
    if(temp.inches >= 12.0)
    {
        temp.inches -= 12.0;
        temp.feet = 1;
    }
    temp.feet += feet + d2.feet;
    return temp;
}

// the only difference with class and structs is that
// class members are initialize to private by default
// struct members are initialize to public by default
// static members variables are shared among every single class
// member variables are non-static by default, each class has its own variable.

int main()
{
    smallobj s1, s2; // define 2 objects of class smallobj
    s1.setdata(1066);
    s2.setdata(1776);
    s1.showdata();
    s2.showdata();
    part part1;
    part1.setpart(55, 22, 234.55);
    part1.showpart();
    Counter c1, c2; // define and initialize
    // able to initialize due to constructors
    cout << "\nc1= " << c1.get_count();
    cout << "\nc2= " << c2.get_count();
    c1.inc_count();
    c2.inc_count();
    c2.inc_count();
    cout << "\nc1=" << c1.get_count(); //display again
    cout << "\nc2=" << c2.get_count();
    cout << endl;
    //
    Distance dist1, dist3;
    Distance dist2(11, 6.25);
    dist1.getdist();
    dist3.add_dist(dist1, dist2);
    cout << "\n dist1 = "; dist1.showdist();
    cout << "\n dist2 = "; dist2.showdist();
    cout << "\n dist3 = "; dist3.showdist();
    cout << endl;
    Distance dist4(dist1); // default copy constructor built in C++
    cout << "\n dist4 = "; dist4.showdist();
    dist4 = dist1.add_dist2(dist2); // member function that returns an object as value
    cout << "\n dist4 = "; dist4.showdist();
    return 0;
}

// Const
// class Distance (as above)
// int main()
//{
//  const Distance football (300, 0); // initialize constant football field length
// football.getdist(); // ERROR!!!! getdist() is not constant in definition, can't be used againts const objects
// football.showdist(); // can be used againts const objects since showdist(0 is constant in definition)
//*/
