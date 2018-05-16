/*
//
// Midterm Prep & Final Prep (Scroll Down)
1.
Class members are private by default
2.
At the end of classes, you have ";"!!!
3.
in make, if you touch an executable, nothing happens, you'll not recompile it.
4.
make -f anyname // to make a makefile named "anyname"
5.
always remember to destroy variables after exciting a function and destroy main variables then global variables
after exiting a program.
6. Note:
        you cant use class functions as if they were global!! always
            class.function()!! Never function() right away
7. If a member function is called const at end,
 e.g.: return type name(argtype arg) const!!! // this last const
 means that you cant change any data of the class calling this function,
 you cant change any member data which are values, but u can change the values that it pointer points to,
 though you can't change the pointer to point  to someone new.w
 same for if arg is const (const argtype arg). can only change values that pointer points to not what it points to itself.

8. note:
     if in class its member is
    int * x; a pointer to integer , means that in constructor you have to create int objects with new
    x = new int;

    if in class its member is
    int *x;
    x = new int [n]; is also right cause its just pointing to the first element.
    so if int **x;
    x = new int[n] is wrong cause need type int**
    so need
    x = new int *[n]; so that it is the right type. n means u have an array of it but you'll only point to the first object.
    or
    x = new int *; is also right cause right type and now you dont have an array, only pointing to one.

9.

e.g.
class d
{
private:
        int count;
        e ** thearray;
};

class e
{
private:
        int count;
            char* name
};

THIS MEANS DESTRUCTOR of D have to dleete each element
d::~d()
{
    for (int i = 0; i < count; i ++)
        delete array[i]; This deletes each element object
    delete [] thearray; delete the array itself
}

e::~e()
{
    delete name; Note!! Always delete the variable name and not its type!! not delete char!! its delete name;
}

note: if its *array that means dont have to delete everything, just delete[] ,
but if **array, means have to delete everything using for loop!!


10. Note!!!

Every pointer must be initialize before use.

so if
C *c;
c->data = data; // error!!
need
c = new C;

11. Note!!
user/suzy -> user/bill/lala // move from first to second
=> cd ../bill/lala

12. Debugging
Step => execute current command and stops before next command
step over=> executes functions as 1 command without going through it
step into => step into the function commands

13. note:
    * n = new ...
    * m  = new ...
    n = m ; -> memory leak occurs here not end of function
    delete n ;
    delete m ; -> double delete
    memory leak -> lost memory
    double delete -> point same memory and delete twice
    no new but look at data -> deletion of stack memory.

// IMPORTANT
14. COpy CONSTRUCTOR !!! IF ANY ORIGINAL VALUES CHANGE,
THIS MEANS THAT EACH TIME U CALL A FUNCTION WHOSE ARGUMENTS REQUIRE THAT CLASS TYPE,
THE COPY CONSTRUCTOR GETS CALLED ON THAT VARIABLE THAT U PASS IN!!
SO THE VARIABLE U PASS IN CHANGES!!
REFER ECE244 MIDTERM 2008 Q6!!.

15.
note: when solving problems with scoping
it will confuse u by using same names, before solving, separate the names first like local x becomes x1 instead.
note: local x does not become x1 if it was not declared again and simply assigned!!!

if in local it says
    int x = ... it means its really int x1 = ...;
but if in local it says
    x = ... it means its really x = ... (reassign global x);
keep track of every variable at all times!!

// IMPORTANT
16. note: When returning an object by reference in copy constructor,
always return *this; NOT return this;

when copying deep copy for pointers, always note that it may be a pointer to an array
of objects, so initialize as an array, do for loop to copy each one by one.

17.
//  Note: cin.fail() just not just fail b type, it also fails by end of file
while (cin >> num)
 cout << num << endl;
if (cin.fail()) // it does not fail just by type, it also fails by end of file
    if (cin.eof())
        cout << "end of file reached"<< end;
    else
        cout << "invalid input" << endl;

// IMPORTANT
18.
copy constructor gets called when:
i) new instance:
    class A = B; where both A and B are values and not pointers
                // note: its iniitalize A to B  , not just giving A that already exist to B
                // A = B  means use assignment operator as given in #22 below
ii) pass in by value to function
iii) return by value from function (return this is an example)

// IMPORTANT
 19.
print(); in member function is ERROR! print() must have return type in C++
->
void print();

20.
note: when defining = operator, need to assign it as part of member function


return type classname::operator (operator symbol) (const classname &)
e.g.

DayOfYear& DayOfYear::operator = (const DayOfYear & src)
{
        return (*this);
}

21.
note: when defining constructors, can't have any return type.

22. Note: for assignment operator, only get called for
may13 = may14; if both of these are values
if both may13 and may 14 are pointers, assignment operator does not get called, nothing gets called.

DayOfYear may13 = may14; Calls copy constructor not assignment operator,
note: may14 and may13 are values not pointers.
if both are pointers, again nothing happens.

// Very Very Important
23. Note;

For Assignment Operator(=) !!
assignment operator can return by reference or value
Case 1: Return by reference
    Classname& operator = (const Classname &haha); although can define as
Case 2: Return by value
    Classname& operator = (const Classname haha); makes use of copy constructor
         need return (*this)
        if return by value, copy constructor will be called in end, means it will be called again
                            and not just when passing in as argument by value
            in this case, need return this in code.
For copy constructor !!
copy constructor like normal constructor cannot have return value_type => return by reference
Classname(const Classname&other); and must pass in by reference. cause if return by value it will call itself infinitely

//------------------------------------------------------------------------------------------------
// Final Prep
//------------------------------------------------------------------------------------------------
0. Refer to final exam study project in ECE244/ownworks/finalexamstudy folder
1.Always pass in stream object by reference.
2. Derived class can add member data and methods but cannot remove them. Can only override & overload.
3. Private members of base class cannot be accessed by derived class but protected members can.
4. Derived class inherits member data & funcs from base
    Except copy constructor, , assignment operator.
    // Not sure about destructor, according to prof. it is not inherited, but testing codeblocks says otherwise
    // what really happens according to google search is that, terminology
    // you do not inherit destructors, but derived class destructor will automatically call
    // base class destructor after it is executed.
    // Similarly for default constructor, a class constructor always calls its parent class constructor
    // before doing anything
So it inherits everything else
Including default constructor, all other constructors of class A

It's a matter of terminology; ctors and dtors are not inherited, in the sense
that the ctor/dtor of B will not be borrowed from A's interface.
A class has at least one constructor, and has exactly one destructor.

Constructors:
B does not inherit constructors from A;
Unless B's ctor explicitely calls one of A's ctor, the default ctor from A will be called
automatically before B's ctor body (the idea being that A needs to be initialized before B gets created).

Destructors:
B does not inherit A's dtor;
After it exits, B's destructor will automatically call A's destructor.

5. Note: Accessed and inherits are 2 totally different things.
    One is whether or not you have the variable,
    Other is whether or not you can use the variable in a certain scope
6.Virtual Destructor
// IMPORTANT VIRTUAL DESTRUCTOR CASES!!!!!
// Cases to play with when restudy:
// what happens when A-> B (pointer A points to object B and gets deleted)
//                   A-> C
//                   B-> C
// Case1 : Only  Destructor Class1a() is virtual
// Case2 : Only  Destructor Class1b() is virtual
// Case3 : Both  Destructor are virtual
// Case4: Both destructor are non virtual
// This thm. has not been fully tested. But it is right so far for this file.
// THM: To sum up all cases, if pointer is above destructor class declared virtual in family hierarchy,
// act as non virtual, => execute pointer func.
// If pointer is below or same as destructor class declared virtual in family hierarchy,
// act as virtual . => execute obj func
// Basically all that matters is which oldest parent in hierarchy has a virtal destructor and see if pointers
// are above or below that parent.
IMPORTANT NOTE: Question 7 Final ece244 2012.
If at class it says virtual ~classname();
but when giving definition, it just says
classname::~classname();
it means the destructor is virtual!! Always note: always look at h file to know if destructor is virtual!!

7. Note: if no = operator or some operator defined, will see if given constructor that takes in that type
8. But note, there is always a default = operator given, so will never call copy constructor, the default
= operator does shallow copy!
9.
Inorder ->  left, current, right
must be from smallest to largest
            so must appear ascending
            left all the way till now, then myself, then right
Preorder -> current, left, right

Postorder -> left, right, current


10. Note: in any code block, as long as you use a pointer to make new object,
constructor is called depending on pointer and object, constructor will always automatically call parent constructor
before calling itself if not given one. Take Note!!!
But if you dont delete the pointer, the destructor wont be called. memory is lost

In any codeblock, as long as you make a new object,
constructor is called!!
but if you dont delete the object, destructor will be called at end of code block!

11. Note: It will be an error if default constructor is not defined and you have derived classes!
This is cause every derived constructor must call the parent constructor before executing itself.
If called explicitly in code, use that given constructor, if not called explicitly,
it will automatically call the parent's default constructor.

12. Hash Table => Sacrifice memory for speed
Load factor = stored elements/ size of hash table
Hash Functions -> h(key) = i
m = size of hash table, needs to be at least double the number of elements stored
 and needs to be a prime number if not probings will just jump around same values
A) Closed Hashing
i) Linear Probing
if collision try
    (i+1) % m
if collision try
    (i+2) % m
    ...


ii) Quadratic Probing
if collision try
    (i+(1^2) % m
if collision try
    (i+(2^2) % m
    ...

iii) Cubic Probing
if collision try
    (i+(1^3) % m
if collision try
    (i+(2^3) % m
    ...

iv) Double Hashing  => 2 hash functions
    Try h1(key),
if collision try
    (h1(key) + h2(key)) % m
if collision try
    (h1(key) + 2h2(key)) % m
if collision try
    (h1(key) + 3h2(key)) % m

B) Open Hashing
i) Hashing with chaining
(arrays with linked list)

Note: If there is no collision, the number of probes is 1

13. Static member function is static means it can be accessed via an object, or accessed without an object.
It does not have a this pointer, which means it can only use static data of a class.
But to use it in main(), you will need to tell which class it is from.
so example
if
    static haha(); // a static func. means that
    ClassName object1;
    object1.haha(); // calling static func with objects
    ClassName::haha(); // calling static func without objects

14.
THM: (Not tested yet)
private inheritance makes all protected and public members from base private.
protected inheritance makes all public and protected members from base protected

15.
For binary search tree, if it is balanced,
worst case is logn
if not balanced (could be linked list)
worst case is n


16. Why doesnt C++ make every member function virtual
Takes up memory space and if want to call based on pointer's value instead of objects value.

17.Insertion sort is better than quicksort if array is already sorted
In fact, if array is:
i) sorted
ii) reversely sorted
iii) All same number (special case of i) and ii))
quicksort will take n^2 time instead of nlogn if its initial pivot is the largest or smallest element.
to overcome this, pivot is normally randomized


18. Checking for self assignment in overloading = operator.
mv = mv; // will be crazy error  if do not have below
  MyClass& MyClass::operator=(const MyClass &rhs) {
    // Check for self-assignment!
    if (this == &rhs)      // Same object?
      return *this;        // Yes, so skip assignment, and just return *this.

19.
friend void operator << (ostream& out, const TreeDB& rhs); // WRONG!! can't output void!! it outputs to an output stream!!

friend ostream& operator<< (ostream& out, const TreeDB& rhs); // right

20. Note: in bst, inserts are simple, always find empty node and go in there
, only deletions need replacement with max of left tree or min of right tree.

21. To force a derived calss to implement a virtual method from a base class,
declare that virtual method as a pure virtual method which makes the base class an abstract class.
Abstract class can't be instantiated.
virtual method() = 0;// pure virtual method

22.If BST has height h,
the max. number of leaves it can have is 2^h.
the max. number of nodes it can havce is  N = (2^(h+1) - 1)
Note: working backwards shows that the height is always logN.
23. Merge sort complexity is nlogn cause 2^(logn) in front is a n which is less than nlogn
24. Any constant^(logn) = n
25. If not sure about recurrence relation, always start from 0!!
26.

// */
