/*
//
// This program prevents accidental conversion of one-argument constructor using keyword explicit.
// This program allows const object to change its data with keyword mutable.
// Lessons:  keyword explicit, keyword mutable

// Preventing conversions with explicit

// One-argument conversion might implicitly
//      convert a single value to another type

#include <iostream>
using namespace std;

class Distance
{
    private:
        const float MTF;
        int feet;
        float inches;

    public:
        // constructors
        Distance() : feet(0), inches(0.0), MTF(3.280833F) {}
        // Conversion Constructor
        // keyword explicit prevents accidental cast from code.
        explicit Distance(float meters) : MTF (3.280833) // takes in meters(int) and converts to distance
        {
            float fltfeet = MTF * meters;
            feet = int(fltfeet);
            inches = 12* (fltfeet - feet);
        }
        // methods
        void showdist()
        {
            cout << feet << "\'-" << inches << '\"';
        }
};

// function prototype
void fancyDist(Distance d);

// mutable keyword is to allow const objects to be mutable
// Ownership = one object is an attribute of another
//              object remain unchanged but its owner may change.

class scrollbar
{
    private:
        int size;
        // note: mutable string owner
        mutable string owner; // to allow owner to be changed even if an object of scrollbar
                                    // was set to const
    public:
        // constructor
        scrollbar(int sz, string own) : size(sz), owner(own){}
        // methods
        void setSize(int sz) { size = sz; }
        void setOwner (string own) const {owner = own;} // note: set to const
        int getSize() const {return size;}
        string getOwner() const {return owner;}
};

int main()
{
    // Explicit keyword
    void fancyDist(Distance); // prints distance
    Distance dist1(2.35F);
    // Distance  dist2 = 2.35F; // ERROR, if constructor is eplicit
    // cout << "\ndist2 = "; dist2.showdist();
    cout << "\ndist1 = "; dist1.showdist();
    float mtrs = 3.0F;
    cout << "\ndist1 ";
    // fancyDist(mtrs); // ERROR, if constructor is explicit, cause fancyDist can't work with non-Distance types
                        // if constructor was not explicity,
                        // fancyDist will automatically convert meters to Distance.
                        // thus, fancyDist can work.

    // Mutable Keyword
    const scrollbar sbar(60, "Window1");
    // sbar.setSize ( 100); // ERROR, can't change const objects, set to constant on above line.
    sbar.setOwner("Window2"); // still able to change owner depite beingc onstant.
    cout << sbar.getSize() << ", " << sbar.getOwner() << endl;
    // owner attribute can change even if object is const.
    // to permit this, it is made mutable.
    // logical constness = in theory, it can't be modified, in practice, it can.
    return 0;
}

void fancyDist(Distance d)
{
    cout << "(in feet and inches = ";
    d.showdist();
    cout << endl;
}

// Conclusion
// constructor given keyword explicit cannot be used in implicit data conversion situations
// data member in a class given keyword mutable can be changed
        // even if its object (an instance of a class) is const
//*/





