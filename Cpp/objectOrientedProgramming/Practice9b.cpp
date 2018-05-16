/*//
// This program converts from user-defined time12(am,pm) class to user-defined time24(24hours clock) class only
// Lessons: Conversion Routine in Destination Class ( conversion constructor defined in destination class)

// Conversion Routine in Destination Class
#include <iostream>
using namespace std;

// needs to be defined first since time12 uses it in Conversion Constructor
class time24 // Source Class ( in main())
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
                // needed for conversion routine from destination class.
        int getHrs() const { return hours;}
        int getMins() const { return minutes;}
        int getSecs() const { return seconds;}
};

// am , pm
class time12 // Destination Class ( in main())
{
    private:
        bool pm; // true => pm, false => am
        int hrs; // 1-12
        int mins; // 0-59
    public:
        // constructors
        time12() : pm(true), hrs(0), mins(0) {}
        time12(bool ap, int h, int m) : pm(ap), hrs(h), mins(m) {}
        // Conversion Constructor (located in destination class)
        // assume 1 argument constructor to take in time 24
        time12(time24);

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

// defining one argument constructor
time12::time12 (time24 t24)
{
    int hrs24 = t24.getHrs();
    pm = t24.getHrs() < 12 ? false: true;
    mins = (t24.getSecs() < 30 )? t24.getMins() : t24.getMins() + 1;
    if (mins == 60)
    {
        mins = 0;
        ++hrs24;
        if (hrs24 == 12 || hrs24 == 24)
            pm = (pm==true)? false: true; // toggle am/pm
    }
    hrs = (hrs24 < 13) ? hrs24 : hrs24 - 12; // convert hrs
    if(hrs == 0)
    {
        hrs = 12; pm = false;
    }
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
        // using user-defined conversion operator in time 12
       // conversion routine in destination class using
        time12 t12 = t24;  // 1 argument operator conversion constructor.
        // display 12 hour time
        cout << "\n12-hour time: ";
        t12.display();
        cout << "\n\n";
    return 0;
}

// Conclusion:
// Thus, you can choose either one-argument constructor in destination class (time12(time24))
// or conversion operator in source class. (operator time12() const)

// However, if you were to use a library of classes without being able to alter its source code,
// you will need to adapt to the library class used.

// in C++
    // i) One-argument Constructor => change Basic to User-defined type or user-defined to user-defined type
        // ex: Distance  dist = 36; // converts 36(basic) to Distance ( user-defined)

    // ii) Conversion Operator => change User-defined to Basic type  or user-defined to user-defined type
        // ex: int x = static_cast<int> dist;  // converts dist (User-defined) to int (basic)
//*/
