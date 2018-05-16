/*//
// This program converts from basic type, int (meters) to user-defined Distance (feet & inches) class vice-versa
// Lessons:  Conversion Constructor & Overloading Conversion Operator (static_cast<float>)
// This program converts from basic type, string to user-defined String class vice-versa
// Lessons: Conversion Constructor & Overloading Conversion Operator (static_cast<char*>)
// Conversion Constructor == Default Copy Constructor (uses one-argument constructor whose argument is the object
                                                            of the source class)

// Data Conversion
// Conversion between basic type to user-defined type.
// = assigns user-defined objects to another, provided they're the same type.
// implicit conversion
    // ex: float j = 10.2;
    //     int   i = 2;
    //     int   k = i + j (k will be 12.2 ( a float) )
// explicit conversion => intended conversion
// ex: casting
#include <iostream>
using namespace std;
#include <string.h>

class Distance
{
    private:
        const float MTF; // METERS TO FEET ratio (for conversion)
        int feet;
        float inches;
    public:
        // constructors
        Distance() : feet(0), inches(0.0), MTF(3.280833F) {}
        // takes in meters and converts to feet and inches.
        // constructor with one argument
        // Conversion Constructor
            // => assumes that one argument is in meters.
        Distance(float meters) : MTF(3.2803833F) // Conversion from Basic too User-Defined
        { // convert meters to distance
            float fltfeet = MTF * meters; // convert to fltfeet => feet + (inches * 12).
            feet = int(fltfeet);
            inches = 12 * (fltfeet - feet) ;
        }
        Distance(int ft, float in) : feet(ft), inches(in), MTF(3.280833F) {}
        // Methods
        void showdist() const
        {
            cout << feet << "\'-" << inches << '\"';
        }
        void setdist()
        {
            cout << "\nEnter feet: "; cin >> feet;
            cout << "\nEnter inches: "; cin >> inches;
        }

        // Overloading Conversion Operator
        // operator can be called with both explicit/implicit cast.
        operator float() const // Conversion from User-Defined to Basic.
        { // converts Distance to meters.
            float fracfeet = inches/12; // convert inches to feet
            fracfeet += static_cast<float>(feet); // add the feet
            return fracfeet/MTF; // convert to meters (float => basic)
        }
};

class String
{
    private:
        enum {SZ = 80};
        char str[SZ];
    public:
    String() {str[0] = '\0';}
    // one argument Conversion Constructor
    // converts C's string to user-defined class String
    String ( char s[]) {strcpy(str, s); }
    void display() const
    {cout << str;}

    // Conversion Operator
    operator char*()
    { return str; } // converts user-defined class String to C's string
};


// note: distance = feet & inches based on Distance class.
int main()
{
    // Conversion between basic (meters) to user-defined (Distance)
    // initialize mtrs as float
    float mtrs;
    // 1 argment costructor to convert meters to distance.
    Distance dist1 = 2.35F; // gets converted to feet and inches implicitly
    cout << "\ndist1 = "; dist1.showdist();
    // convert distance to meters explicitly.
    mtrs = static_cast<float>(dist1); // gets converted to int (meters) explicityly
    cout << "\ndist1 = " << mtrs << " meters\n";
    // 2 argument constructor for distance
    Distance dist2(5, 10.25);
    mtrs = dist2; // convert distance to meters implicitly.
    cout << "\ndist2 = " << mtrs << " meters\n";
    // dist2 = mtrs; // ERROR!! won't convert meters to distance!!

    // Conversion between basic (string) to user-defined (String)
    String s1; // user-defined String
    char xstr[] = "Joyeux Noel! ";
    // 1-argument constructor, converts string (basic) to String (user-defined).
    s1 = xstr; // converts string to String implicitly (using Conversion Constructor)
    s1.display(); // method to print out user-defined string.
    String s2 = "Bonne Annee!";
    // conversion from String(user-defined) to string (basic)
    cout << static_cast<char*>(s2); // able to display user-defined string by normal methods
                                    // by converting it to C's string (basic) first.
    cout << endl;
    return 0;
}
//*/
