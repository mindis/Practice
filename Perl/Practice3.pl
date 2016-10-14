#!/usr/bin/perl 
# To find out the version of perl 
# >> perl -v 
# To get more info about a command
# >> perldoc IO::File
# >> perldoc perlvar
# >> perl Practice1.pl`
# This program 
#-------------------------------------------------------------------
# Perl is design for:
# 1. Text Processing 
# 	=> Lots of web applications built in Perl 
# 2. Higher Level than C 
# 3. Very flexible and can do a great deal of things 
# 4. perl is the interpreter for Perl 
# Variables in Perl: 
# i) scalar => holds 1 single value ($)
# ii) array => holds multiple values (@) 
# iii) hash => holds multiple values (%) 
#-------------------------------------------------------------------
# Perl Special Variables
# $_ = Default Input
# $1 , $2, etc. = Pattern Results
# $! = System error number or string
# $@ = eval() error
# $$ = Process ID (PID) 
# $0 = Program name
# @_ = List of arguments for subroutine
# @ARGV = List of commandline arguments
# @INC = List of path Perl searches for libraries and modules
# %ENV = Hash of environment variables 
# To get the complete list of special variables 
# >> perldoc perlvar
#-------------------------------------------------------------------
# Perl Special Constants
# __FILE__ = name of current file
# __LINE__ = current line number of code 
# __PACKAGE__ = name of module 
# __END__ = end the script at that line, so everything below that script is commented out 
#-------------------------------------------------------------------
# Always include this in every Perl program
use strict; 
use warnings; 
#-------------------------------------------------------------------

main(@ARGV); 

sub main
{
	#-------------------------------------------------------------------
	# An assignment
	my @var = ( "forty-two", 42, 40+2); 
	# An expression 
	my $x = 24; 
	# Basically, if result is a scalar (1 value) => Use '$'
	# 	     if result is a list (> 1 value) => Use '@'
	#-------------------------------------------------------------------
	# unless => if statement that executes if condition is false
	unless( $x > 25 and $x < 100) 
	{
		message("SOON: number is out of range");
		# Join all the values in array @var using ":" as delimiter and set it as a string 
		message(join(":", @var)); 
	}
	#-------------------------------------------------------------------
	# Postfix
	# Output statement only if conditional given after holds 
	$x = 42; 
	message ("SOON NUMBER IN RANGE") if( $x > 25 and $x < 100); 
	#-------------------------------------------------------------------
	$x = undef; # set x to be undefined 
	if (defined isnum($x)) 
	{
		message("x is a number ($x)");
	}
	else 
	{
		message("x is not a number"); 
	}
	#-------------------------------------------------------------------
	$x = '42'; # set x to be a number 42 
	if (defined isnum($x)) 
	{
		message("x is a number ($x)");
	}
	else 
	{
		message("x is not a number"); 
	}
	#-------------------------------------------------------------------
	# Practice working with hash 
	my %hash = ( "this" => "foo", "that" => "bar", "other" => "baz");
	# Go through each keys and its corresponding values as a list 
	# But the order it comes out will be random by using 'each' 
	# To get in proper order, apply 'foreach' and 'sort' instead
	while(my ($k, $v) = each %hash) 
	{
		# Output thekey and value pair 
		message("$k is $v"); 
	}
	# Output one key value pair
	message($hash{"that"});
	#-------------------------------------------------------------------
	# Practice working with arrays 
	my @array = (1 .. 10);  # @array = (1,2,3,4,5,6,7,8,9,10)
	message("@array");
	# Join only the 1st, 4th, and 7th element (note: Elements starts from 0) 
	message(join(',', @array[1,4,7]));
	#-------------------------------------------------------------------
	# Practice working with regular expressions 
		# =~ => The pattern match operator (to be used with $varName) 
		# /wordThatExist/ => Match all lines with the exact word, 'wordThatExist'
		# s/wordThatExist/substitutedWord => Match all lines with the exact word, 'wordThatExist' and substitute that word with the word 'substitutedWord' 
						# Note: It always search and modify the first word only 
						# Use /wordThatExist/g     or    s/wordThatExist/substitutedWord/g => Search and modify each occurence of word in each line 	
	#-------------------------------------------------------------------
	# Subroutine to receive multiple arguments 
	my $s = "haha";
	my $y = 42; 
	my $z = "zee";
	messageMultiple($s, $y, $z);
	#-------------------------------------------------------------------
	# Subroutine to return values
	my $num = addnum(2,4); 
	message("$num\n");
	#-------------------------------------------------------------------
	# Values and References (Pointers)
	# 1. Scalar Reference
	my $value = "Haha";
	my $reference = \$value; 
	my $copyRef = $reference; 
	message("$$reference");
	$value = "baba";
	message("$$copyRef");
	#-------------------------------------------------------------------
}

# Subroutine to add 2 numbers
sub addnum
{
	($a, $b) = @_; 
	return $a + $b; 
}

# Subroutine that receives multiple arguments
sub messageMultiple 
{
	my ($m, $y, $z) = @_;
	print("$m $y $z \n");
}

# Subroutine to print to the screen 
sub message
{
	# Get the parameter into $m
	my $m  = shift or return; 
	print("$m\n");
}

# Subroutine to tell if a variable is a number
sub isnum
{
	# Get the parameter into n 
	my $n = shift; 
	return $n unless defined $n; 
	if ($n =~ /[^0-9]/) 
	{
		return undef; 
	}
}
