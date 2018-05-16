/*//
// This program demonstrates the use of friend functions, variables in storing number of reference to a unique string
    // user-defined strings by reference and overloading assignment and copy constructor
// Lessons: Increase efficiency using pointers. (Overloading Assignment Operator is a must)

// The purpose of this program is to increase efficiency in storing strings, as its basically storing a pointer
    // to the strings and not making a whole new copy of the string which uses up a lot of memory everytime.
#include <iostream>
#include <cstring>
using namespace std;

// This class keep track of the number of unique strings
class strCount
{
    private:
        // Attributes
        int count; // number of unique strings
        char* str; // pointer to string stored
        friend class String; // to allow String class to see its variables
        // Constructor
        strCount(char* s)
        {
            int length = strlen(s);
            str = new char[length+1];
            strcpy(str, s);
            count = 1;
        }
        // Destructor
        ~strCount()
        {
            delete[] str;
        }
};

class String
{
    private:
        strCount *psc; // a pointer to class strCount, aggregation.
    public:
        // Constructor
        String()
        {
            psc = new strCount("NULL");
        }

        String(char* s)
        {
            psc = new strCount(s);
        }

        // NO IDEA WHY IT IS AN ERROR WHEN THIS IS RELEASED,
        // BUT IT STILL WORKS WITH THE DEFAULT COPY CONSTRUCTOR,
        // MIGHT NOT BE DOING WHAT IT IS SUPPOSE TO BE DOING THOUGH.. (keeping track of count)
        // Overloading Copy Constructor
        //String(String& S)
        //{
        //    psc = S.psc;
        //   (psc->count)++;
        //}

        // Destructor
        ~String()
        {
            if (psc->count == 1) // if this object is the last pointer
                delete psc; // to a particular string, delete the strCount
            else
                (psc->count)--; // else decrement the count
        }

        // Methods
        void display()
        {
            cout << psc->str; // print string
            cout << " (addr=" << psc << ")"; // print address of the string
        }

        // Overloading Assignment Operator
        String& operator = (String &S)
        {
            if (this == &S) return *this; // if self-assignment, return immediately. (if not, error occurs if it's the only str)
            cout << "\nAssignment";
            if (psc->count == 1) // if the string which is going to be assigned to new string
                                    // is the last pointer to its old value
                delete psc; // delete strCount
            else
                (psc->count)--; // else, decrement the count
            psc = S.psc; // update its count to the new string
            (psc->count)++; // increase the count of the new string.
            return *this; // return by reference to allow multiple assignments (EX; s1 = s2 = s3;)
        }
};

int main()
{
    String s3 = "When the fox preaches, look at your geese."; // Copy constructor
    cout << "\ns3=";
    s3.display();
    String s1;
    s1 = s3; // assignment operator
    cout << "\ns1=";
    s1.display();
    String s2(s3);
    cout << "\ns2=";
    s2.display();
    // Multiple Assignment using keyword this
    s1 = s2 = s3;
    cout << "\ns1="; s1.display();
    cout << "\ns2="; s2.display();
    cout << endl;
    return 0;
}
//*/
