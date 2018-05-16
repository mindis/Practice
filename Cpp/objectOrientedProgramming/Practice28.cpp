/*
//
// This program studies the uses of function templates
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

//--------------------------------------------------------------------------------
// Function Prototypes
//--------------------------------------------------------------------------------
template <typename type>
type sum(type *a, int size);

template <typename type> // Need this line before every template function
void print(type *A, int length);

template <typename type>
void insertionsort(type *A, int length);

int main ()
{
    // Templates works on both double, float, and strings
    int A[5] = {5,4,3,2,1};
    insertionsort(A, 5);
    print(A, 5);
    cout << sum (A, 5) <<endl;


    double B[3] = {3.4, 5.6, 7.9};
    insertionsort(B, 3);
    print(B, 3);
    cout << sum (B, 3) <<endl;


    string C[3] = {"haha", "baba", "caca"};
    insertionsort(C, 3);
    print(C, 3);
    cout << sum (C, 3) <<endl;
    return 0;
}

//--------------------------------------------------------------------------------
// Global Functions using Templates
//--------------------------------------------------------------------------------
template <typename type>
type sum(type *a, int size)
{
    int i;
    type sum;
    // type sum = 0; // This line doesn't work on strings
    for ( i = 0; i < size; i++) {sum += a[i];}
    return sum;
}

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

// Note:
// int A[5] = {5,4,3,2,1};
// A = insertionsort(A, 5); is an error cause you cant assign
// the new A which is A[5] to a return value. Unless A was a pointer, not an array.
// */
