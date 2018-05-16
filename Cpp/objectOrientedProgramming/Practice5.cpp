/* //
// This program makes user-defined Strings and allows operands on them.
// This program also shows how to use c++ strings and its built-in functions:
    // getline(str1,str2,terminating character)
    // str.erase(int start, int end)
    // str.replace(int start, int end, str)
    // str.insert(int pointOfInsert, str)
    // str.append(int numberOfxToAppend, char x)
    // str.find(str)
    // str.find_first_of(str)
    // str.find_first_not_of(str)
// Lessons: Using overloaded binary operators ( +, -, * , / )
// Strings
#include <iostream>
#include <string> // C++ string header files.
#include <string.h> // strpy(), strcat()
#include <stdlib.h> // exit()
// i) s.erase
// ii) s.replace
// iii) s.insert
// iv) s.append
// note that the string class is similar to string.h header file such that
// you can't add 2 strings with merely operators
// Ex: s1 = s2 + s3 (WRONG!!)
// but you can do so by defining your own string function
// and using Overloaded Binary Operators.
using namespace std;
void string1();

class String
{
    private:
        enum {SZ = 80}; // size
        char str[SZ]; // makes a string
    public:
        // constructors
        String() {strcpy(str,"");}
        String (char s[]) {strcpy (str,s);}
    void display() const
        { cout << str; }
    String operator + (String ss) const
    {
        String temp;
        //  str that calls + operator, str that is being called
        if (strlen(str) + strlen(ss.str) < SZ)
        {
            strcpy(temp.str, str);
            strcat(temp.str, ss.str);
        }
        else
        {
            cout << "\nString overflow"; exit(1);
        }
        return temp;
    }
    // note: can't use return String(string);
    // as we need access to temporary String to concatenate argument string to it.
    // not just for initializing.
};


int main()
{
    string1();
    // Overloading own String Class
    String s1 = "\nMerry Christmas! ";
    String s2 = "Happy new year!";
    String s3;
    s1.display(); cout<<endl;
    s2.display(); cout<<endl;
    s3.display(); cout<<endl;
    s3 = s1 + s2;
    s3.display(); cout << endl;
    return 0;
}

void string1()
{
    string full_name , nickname, address;
    string greeting("Hello, "); // initializing new string
    cout << "Enter your full name: ";
    // reads embedded blanks
    getline(cin, full_name); // built-in function for strings.
    cout << "Your full name is: " << full_name << endl;
    cout << "Enter your nickname: ";
    cin >> nickname;
    greeting += nickname; // note how you can just add names lke that
    cout << greeting << endl;
    cout << "Enter address on separate lines\n"
    << "Terminate with $ \n";
    // reads from cin, to address, and terminates when sees $
    getline(cin, address, '$');
    cout << "Your address is: " << address << endl;
    int n;
    n = full_name.find("Chee"); // returns index of first Chee it finds
    n = full_name.find_first_of("aeriouAEIOU"); // returns index of first vowel it finds.
    n = full_name.find_first_not_of("aeiouAEIOU"); // returns index of first consonant it finds.
    string s1= "hahaha", s2= "mamama";
    s1.erase(0,3); // removes hah
    s1.replace(0,3,s2); // replaces aha with mamama
    s1.insert(0,s2); // inserts mamama at the beginning
    // (starts from index, number of char removes)
    s1.erase(s1.size()-1, 1); // removes a
    // (number of char i to append, i)
    s1.append(3, '!');  // appends "!!!"
    cout << "s1: " << s1 << endl;
}

// still lacking string compare which you were too lazy to learn
//*/
