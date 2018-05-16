/*//
// This program demonstrates use of friend function to increase versatility of overload operators
// Lessons: (+) operator uses the (+) operator that is defined at its left side.
// Lessons:     // in member function, one object which + operator operates on must be member and second is an argument
                // in friend function, both objects must be arguments
                // Ex: d3 = 10.0 + d1; // (float + distance) treating both objects as arguments in friend + operator.
// This program demonstrates used of friend function

// From Distance class in Practice 6,
// Distance d3, d1;
// d3 = di + 10.0; // This works as the argument on the right of (+) operator is a float,
                    // it will be converted by 1-argument constructor to Distance
                    // which carries out the addition based overloaded + operator.
// d3 = 10.0 + d1; // This doesn't work because the object to be (+) operator is defined by the object
                    // in the left of the (+) operator. In this case, + operator defined in type float
                    // is not defined to add distance class operator. Thus, this will be a compiled error.

// Returns square of distance
// sqft = d3.square(); // will work as long square is defined in Distance class.
// sqft = square(d3); // this notation is a lot clearer, can be used by using friend functoin
#include <iostream>
using namespace std;

class Distance
{
    private:
        int feet;
        float inches;
    public:
        // constructor
        Distance() : feet (0), inches(0) {}
        // default conversion constructor
        Distance (float fltfeet)
        {
            feet = int(fltfeet);
            inches = 12 * (fltfeet - feet);
        }
        Distance( int ft, float in) : feet(ft), inches(in) {}
        // methods
        void showdist()
        {
            cout << feet << "\'" << inches << '\"';
        }
        // Overloading binary + operator
        friend Distance operator + (Distance, Distance); // made into friend
        friend float square(Distance);
};

Distance operator + (Distance d1, Distance d2)
{
    int f = d1.feet + d2.feet;
    float i = d1.inches + d2.inches;
    if (i >= 12.0)
    {
        i -= 12.0;
        f++;
    }
    // return new Distance with sum
    return Distance(f,i);
}

float square (Distance d) // notice how friend keyword is not needed outside the class
{
    float fltfeet = d.feet + d.inches/12;
    float feetsqrd = fltfeet * fltfeet;
    return feetsqrd;
}

int main()
{
    // Using friend function to increase versatility of overloaded + operator
    Distance d1 = 2.5, d2 = 1.25, d3;
    cout <<"\nd1 = "; d1.showdist();
    cout << "\nd2 = "; d2.showdist();
    d3 = d1 + 10.0; // distance + float;
    cout << "\nd3 = "; d3.showdist();
    // in member function, one object which + operator operates on must be member and second is an argument
    // in friend function, both objects must be arguments
    d3 = 10.0 + d1; // float + distance; // treating both objects as arguments in friend + operator.
    cout << "\nd3 = "; d3.showdist();
    cout << endl;
    // Using friend function
    float sqft = square(d3);
    cout <<"\nSquared d3 = " << sqft << "square feet\n";
    return 0;
}
//*/
