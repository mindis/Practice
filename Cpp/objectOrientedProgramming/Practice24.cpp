/*
//
// This program demonstrates use of dynamic_cast in polymorphism.
// Lessons: dynamic_cast allows upcast and downcast with limitations.
        // Upcast: Only gets the base part during casting
        // Downcast: let a child class object pointed by a parent class pointer,
                                                // into a base class pointer.
// This program demonstrates use of typeid.
// typeid => obtain information about the type of an unknown object

// Note: parent class has to be polymorphic (contains virtual functions) for dynamic_cast to work.
// Note: You will need compiler to enable Run-Time Type Information (RTTI) (Visual C++ needs this to be turned on manually)

// Dynamic pointer allows you to cast upwards and downwards in the inheritance tree in limited ways.
#include <iostream>
#include <typeinfo> // for dynamic_cast, typeid()
using namespace std;

// Demonstrating dynamic_cast polymophically
class Base
{
    virtual void vertFunc() {} // for dynamic cast
};

class Derv1 : public Base {};
class Derv2 : public Base {};

// check if pUnknown points to a Derv1
bool isDerv1(Base *pUnknown) // can take in any pointer from Base onwards.
{
    Derv1 *pDerv1;
        // note:( = not == ) -> !0 if pDerv1 did point to Derv1, 0 if it pointed elsewhere.
    if ( pDerv1 = dynamic_cast<Derv1*>(pUnknown))
        return true;
    else return false;
}

// Showing limitations of dynamic_cast
class Base2
{
    protected:
        int ba;
    public:
        Base2() : ba(0) {}
        Base2(int b) : ba(b) {}
        virtual void vertFunc() {} // needed for dynamic cast
        void show() { cout << "Base2: ba=" << ba << endl;}
};

class Derv3 : public Base2
{
    private:
        int da;
    public:
        Derv3(int b, int d) : da(d)
        {
            ba = b; // note how it gets to automatically assign ba since ba is defined as protected in Base2 class
        }
        void show() {cout << "Derv: ba=" << ba << ", da=" << da << endl;}
};

// Using typeid() operator
class Base3
{
    virtual void virtFunc() {} // for typeid
};

class Derv4 : public Base3 {};
class Derv5 : public Base3 {};

void displayName(Base3* pB)
{
    cout << "pointer to an object of "; // display name of class
    cout << typeid(*pB).name() << endl; // pointed to by pB
}

int main()
{
    // Demonstrating dynamic_cast polymophically
    Derv1 *d1 = new Derv1;
    Derv2 *d2 = new Derv2;
    if ( isDerv1(d1)) // should output previous
        cout << "d1 is a member of the Derv1 class\n";
    else
        cout << "d1 is not a member of the Derv1 class\n";
    if ( isDerv1(d2)) // should output latter
        cout << "d2 is a member of the Derv1 class\n";
    else
        cout << "d2 is not a member of the Derv1 class\n";

    // Showing limitations of dynamic_cast
    Base2* pBase2 = new Base2(10); // pointer to Base2
    Derv3* pDerv3 = new Derv3(21, 22); // pointer to Derv3
    // upcast: derived to base => parent pointer to child, cast child pointer upwards
    pBase2 = dynamic_cast<Base2*>(pDerv3); // limitation: only ends up getting the base part
    pBase2->show(); // "Base: ba=21"
    pBase2 = new Derv3(31, 32);
    // downcast: base to derived => child pointer to parent, cast parent pointer downwards
    pDerv3 = dynamic_cast<Derv3*>(pBase2); // simply changes parent pointer of child object to child pointer.
    pDerv3->show(); // "Derv: ba=31, da = 32"

    // Using typeid to know more information about the type of an unknown object.
    Base3* pBase3 = new Derv4;
    displayName(pBase3);
    pBase3 = new Derv5;
    displayName(pBase3);
    return 0;
}
//Conclusion
// Upcast: Only gets the base part during casting
// Downcast: let a child class object pointed by a parent class pointer, into a base class pointer.
//*/
