#!/usr/bin/perl 
use strict; 
use warnings; 
use diagnostics; # More descriptive warnings
#--------------------------------------------------------------------------------
# Regular Expressions
#--------------------------------------------------------------------------------
# =~ => binding operator 
# !~ => Negated binding operator
# m() => Matching operator (same as binding except now you can use / without escaping it with \)
# index => Exact matching operator

=pod
All operators are greedy (Matches as much as possible) 
* => >= 0
+ => >= 1
. => Match anything once 
? => {0, 1}
{x,y} => x <= , <= y
{1,} => >= 1
{,10} => <= 10
{3} => == 3
\1 => rematched whatever that was matched before from $1 => Back-References
() => Use () to capture the data you want and access using $1, $2 ... 
	Can also access using a name you give it instead of $1, $2 if you use ?<name> 

[abc] => Match a or b or c 
	note: Inside [], only   -]\^$   are considred special, everything else like    .    doesnt do anything special, . matches a . in this case
| => Grouping, match regexp a or b for a|b

\d => Unicode Digit
\D => NOT Unicode Digit
\s => whitespace
\S => NOT whitespace 
\A => Beginning of string
\w => Matches any alphanumeric character and _ 
\b => Matches when transition from word and non-word character
	e.g. /\D\d{3}-\d{4}-\d{3}\D/ matches " 555-4444-333 " but doesnt match " 555-4444-333" as the next \D has nothing to match and must match something, so use \b
	 => /\b\D\d{3}-\d{4}-\d{3}\D\b/
/x => Ignore unescaped whitespace
/i => Case-insensitive match
/g => Keep matching till no more matching
	e.g. Word counting for wards that ends with 'at' 
		my $silly = ‘The fat cat sat on the mat’;
		my $at_words = 0;
		$at_words++ while $silly =~ /\b\w+at/g;

^ => Matches start of string
$ => Matches end of string
/m => Multiline mode => ^ and $ willl match again after every \n in a string

To make regular expressions easier to read, use /x modifier and it will ignore all whitespace (unless escaped with \) 
	e.g.
	my $name_and_age = qr{
	Name:
	\s+ # 1 or more whitespace
	(.*?) # The name in $1
	\s+ # 1 or more whitespace
	Age:
	\s+ # 1 or more whitespace
	(\d+) # The age in $2
	}x;

#--------------------------------------------------------------------------------
Substitution
#--------------------------------------------------------------------------------
s/regularExpression/replacementText/
	eg. To change all abc to def
		my $main_course = “A well-done abc filet mignon”;
		$main_course =~ s/abc/def/;
		print $main_course.
s/regularExpression/replacementText/g 
	This changes globally (match and replace as many global instance as possible

(?=$regex) => Lookahead Anchors (Followed by this regexp but don't replace this regexp)
	e.g.  To replace all xxxyyy with ---yyy
		my $string = ‘xxxyyyxxxbbbxxxyyy’;
		$string =~ s/
		xxx # match xxx
		(?=yyy) # followed by yyy, but not included in the match
		/---/xg;
		print $string;

(?!$regex) => Lookbehind Anchors (Followed after this regexp but don't replace this regexp)



=cut


main(@ARGV); 
sub main
{
	my $s = 'There is 1 date 10/25/95 in here somewhere.';
	my $mo = undef;
	my $day = undef; 
	my $year = undef; 
	my $wholedate = undef; 

	print "\$s=$s\n";
	$s =~ /(\d{1,2})\/(\d{1,2})\/(\d{2,4})/;
	print "Trick 1: \$1=$1, \$2=$2, \$3=$3,\n",
	      "         \$\`=",$`," \$\'=",$',"\n";
	($mo, $day, $year) =
	     ( $s =~ /(\d{1,2})\/(\d{1,2})\/(\d{2,4})/ );
	print "Trick 2: \$mo=$mo, \$day=$day, \$year=$year.\n";
	($wholedate,$mo, $day, $year) =
	     ( $s =~ /((\d{1,2})\/(\d{1,2})\/(\d{2,4}))/ );
	print "Trick 3: \$wholedate=$wholedate, \$mo=$mo, ",
	      "\$day=$day, \$year=$year.\n";
}
