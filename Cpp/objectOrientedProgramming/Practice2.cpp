/* //
// This program counts the number of words based on user input.
// Lessons: A cool algorithm to get number of words. Keyword enum.
#include <iostream>
#include <conio.h> // for getche()
using namespace std;

struct part
{
    int modelnum;
    int partnum;
    float cost;
};

enum itsaWord { NO, YES }; // NO = 0, YES = 1

int wordcount();
int parts();

// Using structures.
int main()
{
    wordcount();
    parts();
    return 0;
}

int parts()
{
    part part1;
    part1.modelnum = 6244;
    part1.partnum = 373;
    part1.cost = 217.55F;
    cout << "Model " << part1.modelnum;
    cout << ", part" << part1.partnum;
    cout << ", cost $" << part1.cost <<endl;
    return 0;
}

// Doesn't include tabs
int wordcount()
{
    itsaWord isWord = NO; // in C, you need to write enum itsaWord isWord = NO (need keyword enum)
    char ch = 'a';
    int wordcount = 0;
    cout << "Enter a phrase:\n";
    do
    // NOTE HOW IT IS ELSE IF, SO IF MULTIPLE SPACES or enters are given,
    // it all still counts as one word only.
    {
        // get a character without using pressing enter.
        ch = getche();
        // if the character is space or enter
        if (ch== ' ' || ch == '\r')
        {
            // and if isWord == YES
            if ( isWord == YES)
            {
                // add the wordcount
                wordcount++;
                // set isWord to NO
                isWord= NO;
            }
        }
        else if (isWord == NO)
            isWord = YES;
    } while (ch!='\r');
    cout << "\n---Word count is " << wordcount << "---\n";
    return 0;
}
// Conclusion
// enum are used to create user-defined types that is limited to a fixed list of values (represented by integers)
// C++ treats enum types as integers
// enum direction {north, south, east, west);
// direction dir1 = south;
// cout << dir1; // OUTPUT WILL BE 1
// examples of enumerations:
    // i) enum months {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec}
    // ii) enum switch { off, on };
    // iii) enum meridian {am, pm};
    // iv) enum chess { pawn, knight, bishop, rook, queen, king};
    // v) enum coins { penny, nickel, dime, quarter, half-dollar, dollar};

// Besides that, enum are also used to create static constant variables as some compilers (Visual C++)
// does not allow:
// static const int MAX = 10;
// thus, we do:
// enum { MAX = 10 };
// instead.

// Note: you did not cover Overloaded Functions (functions behave differently based on types and number of parameters)
//*/
