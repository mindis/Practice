/*//
// This program converts from user-defined time12(am,pm) class to user-defined time24(24hours clock) class only
// Lessons: Conversion Between User-Defined and User-Defined Types
            // Conversion Routine in Source Class ( conversion operator defined in source class)

// Conversion between user-defined and user-defined types.
// destination class (class that receives the value converted)
// source class (class that provides the value to convert)
// ex: objecta = objectb; // objecta => destination class,
                          // objectb => source class.
// NOTE: you can only have either one!! You can't define the same thing in 2 different ways.
// i) Conversion routine in source class (using conversion operator)
// ii) Conversion routine in destination class (using 1-argument constructor)

#include <iostream>
using namespace std;

// Conversion Routine in Source Class

// am , pm
class time12 // Destination Class (in main())
{
    private:
        bool pm; // true => pm, false => am
        int hrs; // 1-12
        int mins; // 0-59
    public:
        // constructors
        time12() : pm(true), hrs(0), mins(0) {}
        time12(bool ap, int h, int m) : pm(ap), hrs(h), mins(m) {}

        // methods
        void display() const
        {
            cout << hrs << ':';
            if (mins < 10) cout << '0'; // extract zero for "01"
            cout << mins << ' ';
            string am_pm = pm? "p.m." : "a.m.";
            cout << am_pm;
        }
};

class time24 // Source Class (in main())
{
    private:
        int hours;
        int minutes;
        int seconds;
    public:
        // constructors
        time24() : hours(0), minutes(0), seconds(0) {}
        time24(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}
        // methods
        void display() const
        {
            if (hours < 10) cout << '0';
            cout << hours << ':';
            if (minutes < 10) cout << '0';
            cout << minutes << ':';
            if (seconds < 10) cout << '0';
            cout << seconds;
        }
        // public methods to allow data to be access by other classes.
        int getHrs() const { return hours;}
        int getMins() const { return minutes;}
        int getSecs() const { return seconds;}

        // Conversion operator (located in source class)
        operator time12() const; // only operator that can be created ( nameOfDestinationClass conversion operator)
};

// conversion operator from time24 to time12.
// operator belongs to time24 cause it is used on object time24.
time24::operator time12() const
{
    int hrs24 = hours;
    bool pm = hours < 12? false: true;
    // assume seconds doesn't matter in time 12
    //  if seconds > 30, minute + 1
    int roundMins = seconds < 30? minutes: minutes + 1;
    // if 60 minutes
    if (roundMins == 60)
    {
        roundMins = 0;
        ++hrs24;
        if( hrs24 == 12 || hrs24 == 24)
            pm = (pm==true)? false : true; // change the pm to am or am to pm
    }
    int hrs12 = (hrs24 < 13) ? hrs24 : hrs24 - 12;
    if (hrs12 == 0)
    {
        // convert to am if needed.
        hrs12 = 12;
        pm = false;
    }
    return time12(pm, hrs12, roundMins);
}

int main()
{
    int h, m, s;
        cout << "Enter 24-hour time: \n";
        cout << "   Hours (0 to 23): "; cin>> h;
        if (h > 23) return (1); // error
        cout << "   Minutes: "; cin >> m;
        cout << "   Seconds: "; cin >> s;

        // initialize time24 based on values given
        time24 t24(h, m, s);
        cout << "You entered: ";
        t24.display();

        // implicit conversion to time12
        // using user-defined conversion operator in time24
        time12 t12 = t24; // Conversion routine in source class.
            // t12 (destination class)
            // t24 (source class)
        // display 12 hour time
        cout << "\n12-hour time: ";
        t12.display();
        cout << "\n\n";
    return 0;
}
//*/

