use strict;  # To ensure consistent good coding style
use warnings; # Warnings
use diagnostics; # More descriptive warnings
# use => similar to #include in C++ 
#--------------------------------------------------------------------------------
# 3 primary data types in Perl:
# 	- scalar, $ = single value NOT mathematical scalar
#		number, string, reference
# 	- arrays, @ = ordered list of scalars, indexed using integers
# 	- hashes, % => indexed using strings (keys) 
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# Scalars
#--------------------------------------------------------------------------------
my $nickName = 'Ovid';
my @cats = ( 'Valentin', 'Arthur');
my $nick = $nickName;

# To declare multiple variables simultaneously 

my ( $a, $b ) =  ( 22, 'abc' );

print $nick;

# 'no substitution here $b prints $b '
# "has substitution here $b prints abc'

print int(4.39 * 100); # gives 4.38 as it is stored as 4.389999 and int just drops the decimal part without any rounding

#--------------------------------------------------------------------------------
# Scalar References
#--------------------------------------------------------------------------------

my $haha = 'lalam';
my $refHaha = \$haha;
print "$$refHaha\n";

#--------------------------------------------------------------------------------
# Arrays
#--------------------------------------------------------------------------------
my @even = ( 2, 4, 6, 8, 10);

my $firstElement = $even[0]; # Note how you are accessing a 'scalar' of the array even

my $evenLen = @even; # Gives you length of even which is 5 as you are converting from array to scalar without accessing any element

# Array Slices
my @men = @even[1,3];# (4,6,8)

for my $element (@even) {
	print "$element\n";
}

# OR 

# $_ => Accessing each element in for loop individually
for (@even) {
	print "$_\n";
}

#--------------------------------------------------------------------------------
# Array References
#--------------------------------------------------------------------------------
# Reference array with scalar
my @arrA = qw(jester clown motley);
my $arrARef =  \@arrA; # Assign reference of array arrA to scalar of arrARef
# Copy array 
my @copyOfArrA = @$arrARef;  # Create a copy, '@' dereferences the entire reference, it is similar to '*' operator in C
# Access elements of array 
my $firstEle = $arrARef->[0]; # note:  $arrARef->[0] == $$arrARef[0] == ${$arrARef}[0]
print "$firstEle\n"; 

for my $fool ( @$arrARef) { 
	print "$fool\n";
}

#--------------------------------------------------------------------------------
# Anonymous Arrays => Multi-dimensional arrays in C++
#--------------------------------------------------------------------------------

# 2D Arrays
my @results = (
	[ 12, 19, 4 ],
	[ 454, 2, 42 ],
	[ 6, 9, 13, 44 ],
);

# Note: It automatically gives the reference to the first row without using '\'
my $aRef1 = $results[0];

# Accessing the individual element
my $number = $aRef1->[2]; 
# note: can also reference indefinitely using -> -> -> ... -> m times for m-dimensional array
my $number2 = $results[0]->[2];




#--------------------------------------------------------------------------------
# Array functions
#--------------------------------------------------------------------------------
# push() # push to end of array
# pop() # pop from end of array
# shift() # push to beginning of array
# unshift() # pop from beginning of array

#--------------------------------------------------------------------------------
# Hash
#--------------------------------------------------------------------------------
my %people = (
	"Alice", 1,
	"Bob", 2,
	"Ovid", "lala",
);
print $people{'Alice'}; # Note: Use curly braces

for my $name ( keys %people ) {
	print "$name is $people{$name} \n";
}

#--------------------------------------------------------------------------------
# Hash References
#--------------------------------------------------------------------------------
# Similarly, use '\' to assign to reference.  However, this time you use '%' to dereference instead of '@' as of arrays

my %words = (
	dog => "adog", 
	cat => "acat",
	mouse => "mouse",
);

my $wordRef = \%words;
my $copyOfWord = %$wordRef;
my $firstElem = $wordRef->{dog}; # note: $wordRef->{dog} == $$wordRef{dog} == ${$wordRef}{dog} 
print "$firstElem\n";

#--------------------------------------------------------------------------------
# Anonymous Hashes => Multi-dimensional Hashes
#--------------------------------------------------------------------------------

my $sales = {
	monday => { jim => 2, mary => 1 },
	tuesday => { jim => 3, mary => 5},
};

my $numSales = $sales->{monday}->{mary};

#--------------------------------------------------------------------------------
# Hash Functions
#--------------------------------------------------------------------------------
# delete() => Remove a key value pair
# exists() => Check if a key exist
# keys() => Iterate over all keys
# values() => Inspect value of a hash
# each() => To iterate over keys and values of a hash


# dclone() => To make a deep copy
#--------------------------------------------------------------------------------

# note: for = foreach 
# last => 'break' in C++
# next => 'continue' in C++ 
# continue => Something totally different in Perl and doesn't need to be used
#--------------------------------------------------------------------------------
# Built-In Variables/Functions
#--------------------------------------------------------------------------------
# $1, $2 => Sub petterns extracted from regular expressions
# @_ => Parameters passed into subroutines
# $_ => Accessing each element in for loop individually
# $@ => Default eval error variable 
# $! => Error message variable (error messages gets stored in this variable) 
# $/ => Delimiter for while loop iterator for files, used by chomp() to remove any character that matches $/

my $numberOfSides ||= 6; # ||= => Assign only if not already assigned a value, acts as default value

# wantarray() => Lets you know if subroutine returns nothing, a scalar, or a list
# die() => exit out from function  and prints to stderr

#--------------------------------------------------------------------------------
# String Functions
#--------------------------------------------------------------------------------
# chop() => Get last character of string
# chomp() => Removes newlines from the end of strings
# . => string concatenation => "haha"."baba" => "hahababa"
# chr() => Converts integer to ASCII/UNICODE representation
# index() => Finds first index of substring => index STR, SUBSTR
# rindex() => Similar but find last index of substring
# lc() => Lower case
# uc() => Upper case

#--------------------------------------------------------------------------------
# Subroutines => Functions in C++
#--------------------------------------------------------------------------------
# my $result = &random_die_roll; # Calling function with '&' means you are not passing in any arguments, it'll use the existing argument alreadu om @_
# my $nextArgument = shift @_;  # A common way to get next argument and pop front of arguments array 


#--------------------------------------------------------------------------------
# Returning data from subroutines
#--------------------------------------------------------------------------------
# Return true or false
# return 1; => true
# return; == return 0; == return undef; => return empty list => false

# Returning multiple data 
# my ( $ dataOne, $dataTwo ) = subRoutineName(); 
# sub subRoutineName { 
	# code here 
	# return ( $returnDataOne, $returnDataTwo );
# }

#--------------------------------------------------------------------------------
# Subroutine References => Function pointers in C
#--------------------------------------------------------------------------------
# sub => subroutine 

# Similar to assigning function to variables in Javascript
my $add_two = sub {
	my $number = shift;
	return $number + 2;
};
print $add_two->(7);

print inc_list(1,2,3); # Call inc_list function defined below with arguments 1,2,3 passed in as an array

sub inc_list {
	my @numbers = @_;
	# For each element in the argument array passed in
	for (@numbers) {
		# Access that element and add one to it
		$_++;
	}
	return @numbers;
}

sub how_many {
	print "have\n";
}
# For loop goes from 1 to 5 inclusive incremented by 1
how_many() for 1 .. 5;
#--------------------------------------------------------------------------------
