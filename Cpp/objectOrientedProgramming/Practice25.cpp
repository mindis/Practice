/*//
// CONTINUE FROM PG 594
// This program
// Lessons:

// Stream Classes
// stream = flow of data
// <<  from istream
// >>  from ostream
// cout => standard output stream
// Manipulators = formatting instructions inserted directly into a stream
// Flags:
// i) skipws => skip whitespace on input
// ii) left => left-adjust output (EX: [12.34    ])
// iii) right => right-adjust output (EX: [      12.34])
// iv) internal => upse padding between sign or base indicator or number
// v) dec => convert to decimal
// vi) oct => convert to octal
// vii) hex => convert to hexadecimal
// viii) boolalpha => convert bool to "true" or "false" string
// ix) showbase => Use base indicator on output (0 for octal, 0x for hex)
// x) showpoint => Show decimal point on output
// xi) uppercase => Use uppercase X, E and hex output letters (ABCDEF), the default is lower case
// xii) showpos => Display + before positive integers
// xiii) scientific => Use exponential format on floating-point output [9.1234E2]
// xiv) unitbuf => Flush all streams after insertion
// xv) stdio => Flush stdout, stderror after insertion

int main()
{
    cout.setf(ios::left);
    cout >> "This text is left-justified";
    cout.unsetf(ios::left); // restore to default
}


//*/
