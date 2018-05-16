/* //
//
// This program determines your current location based on
// your input ('n', 's', 'e', 'w')
// Lessons: used of exit() and getche()
#include <iostream>
#include <process.h> // for exit()
#include <conio.h> // for getche()
#include <stdio.h>
using namespace std;
void position();
void position2();

int main()
{
    position();
    position2(); // bug infinite loop, super bug!!
    int speed;
    cout << "\n Enter 33, 45, or 78: ";
    cin >> speed;
    switch (speed)
    {
        case 33:
            cout << "LP album\n";
            break;
        case 45:
            cout << "Single selection \n";
            break;
        case 78:
            cout << "Obsolete format\n";
            break;
    }
    return 0;

}

void position()
{
    // Gets current position of player depending on input
    char dir='a';
    int x=10, y = 10;
    cout << "Type Enter to quit\n";
    while (dir!= '\r')
    {
        cout << "\nYour location is " << x << ", " << y;
        cout << "\n Press direction key (n, s, e, w): ";
        dir = getche(); // get a character
        if (dir =='n')
            y++;
        else if (dir == 's')
            y--;
        else if (dir =='e')
            x++;
        else if (dir =='w')
            x--;
    }
}

void position2()
{
        // using switch statement
    char dir= 'b'; //initializing
    cout << "Please enter again" ;
    int x = 10, y = 10;
    while (dir!= '\r')
    {
        cout << "\n Your location is " << x << ", " << y;
        cout << "\nEnter direction (n,s,e,w): ";
        dir = getche(); // get a character
        switch (dir)
        {
            case 'n': ++y; break;
            case 'w': --x; break;
            case 's': --y; break;
            case 'e': ++x; break;
            case '\r': cout << "Exiting\n";break;
            default: cout << "\ntry again\n"; break;
        }
        if ( x == 7 && y == 11)
        {
            cout << "\n you found the treasure!";
        }
    }
    printf("hahaha");
}
//*/
