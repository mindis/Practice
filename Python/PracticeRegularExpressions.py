import glob
# To find all pathnames matching a specified pattern according to rules used by the UNIX shell  (* , ? , []) 
# uses os.listdir() and fnmatch.fnmatch() 
# note: glob treats filenames beginning with (.) as special cases. 
# For tiled and shell variable expansions, 
# use os.path.expanduser() and os.path.expandvars()
import re # regular expressions 
# Specifies a set of strings that matches it 
# Check if a particular string matches a particular string and vice versa 

#
'''
What you type => 'e.g. of strings it matches' 
//// => '/'
. => Match 1 single character of anything except newline
last => 'last'
* => Match >= 0 repetitions of previously matched 
	e.g. ab* => a, ab, abbbb, abbbbbbbbb , etc.
+ => Match >= 1 repetitions of previously matched 
	e.g. ab+ => ab, abb, abbbbbb, etc.  
? => Match 0 or 1 repetition of previously matched 
	e.g. ab? => a, ab 
From '<H1>title</H1>'
	(Without ? => Match as much as possible)
		<.*> => <H1>title</H1>
	<With ? => Math as little as possible 
		<.*?> => <H1> 
{4} => Match exactly 4 repetitions of previously matched 
	a{5} => aaaaa
{4,6} => Matched anywhere from 4 to 6 repetitions of previously matched
	a{4,6} => aaaa, aaaaa, aaaaaa
{4,} => Matched >= 4 repetitions of previously matched
{,6} => Matched 0 <= x <= 6 repeittions of previously matched 
A|B => Matches regular expression that matches either regExp A or regExp B 
\ => Escape character for python's regular expression
	\* => *
[amk] => 'a', 'm', 'k'
[a-c] => 'a', 'b', 'c' 
[0-5][0-9] => 00, 01, ... , 09,10,11,...,50,51,...,59

[0-9A-Fa-f] => 0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f,A,B,C,D,E,F
Special Character has no meaning inside []
	[(+*)] => '(', '+', '*', ')'
[^5] => Match any character except 5 (note: must begin with ^) 
[()[\]{}] => '(' , ')', '[', ']', '{', '}' 
(?=...) => Matches before only if after matches ...
	e.g. Isaac (?=Asimov) => Matches 'Isaac' only if followed by 'Asimov'
(?!...) => Matches before only if after doesn't match ...
	e.g. Isaac (!=Asimov) => Matches 'Isaac' only if NOT followed by 'Asimov'
AND A LOT MORE, REFER TO DOC. IF NEED MORE HELP 
'''

#-------------------------------------------------------------------------------------------------------------------------
# Testing compilation works 
print "hello"
#-------------------------------------------------------------------------------------------------------------------------
# Glob practice 
print glob.glob('./*[0-9].py')
#-------------------------------------------------------------------------------------------------------------------------
# Regular Expressions (re) practice
# ^ Matches start of string 
# $ => Matches end of string

result = re.search('(?<=abc)def', 'abcdef')
print result.group(0)

'''
result = re.search(pattern, string)
	Returns 1st matched pattern, if any. Otherwise, returns None
result = re.match(pattern,string)
	Return matched pattern at the beginning of the string. Otherwise, returns None

result = re.search(pattern, string)
if result:
	Do things only if matched and not None. 



'''







