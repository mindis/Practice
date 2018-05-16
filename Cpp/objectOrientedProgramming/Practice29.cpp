/*
// ECE244 Finals Prep. , need to work with classes, so can't just use practice anymore,
// need more files.
// This program studies the uses of function templates
#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <sstream>
using namespace std;

//--------------------------------------------------------------------------------
// Function Prototypes
//--------------------------------------------------------------------------------
template <typename type>
void print(type *A, int length);

template <typename type> // Need this line before every template function
void insertionsort(type *A, int length);

int main ()
{
    // Templates works on both double, float, and strings
    int A[5] = {5,4,3,2,1};
    insertionsort(A, 5);
    print(A, 5);
    string catname;
    catname = "Spanky";
//    strcpy(catname, "Spanky"); // cant use C++ strings on char functions
//    catname("Spanky");  // cant use constructor after its made
    string haha("Spanky");
    return 0;
}

//--------------------------------------------------------------------------------
// Global Functions using Templates
//--------------------------------------------------------------------------------
template <typename type>
void print(type *A, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << A[i] << " ";
    }
    cout <<endl;
}

template <typename type>
void insertionsort(type *A, int length)
{
    if (length == 1) return;
    type temp;
    int j = 0;
    for (int i = 1; i < length; i++)
    {
        temp = A[i];
        j = i-1;
        while (j >= 0 && A[j] > temp)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = temp;
    }
}
// */
