# Working with files 

#------------------------------------------------------------------------
# open()
#------------------------------------------------------------------------
# open fd, mode, filename, fd is the file descriptor you read and write to. 
# 			  mode is the mode you are reading or writing to file 
# mode: 
# 	>  => writing to file
# 	<  => Reading from file 
#	+< => Read-write mode

# <$fileDescriptor> turns the fileDescriptor into an iterator. Assigning to:
# 	$ (scalar) makes it return one line at a time
#	@ (array) will read every record in file separated by $/ variable, default value for $/ = (newline character for your operating system)
#		chomp() removes anything matching $/

# <> == <ARGV> => Reads from commandline arguments

=pod

# my $filename = 'chapter_9/targets.txt';
# open my $spies_to_espy, '<', $filename or die "Cannot open '$filename' for writing: $!";

while ( my $line = <$spies_to_espy> ) {
	next if $line =~ /^\s*#/; # skip comments!
	chomp($line);
	my ( $name, $case_number, $description )
	= split /\|/, $line;
	print “$name ($case_number): $description\n”;
}
close $spies_to_espy or die “Could not close ‘$filename’: $!”;
=cut


#------------------------------------------------------------------------
# File Test Operators
#------------------------------------------------------------------------
=pod
	-e => file exists ? 
	-f => Plain file ? 
	-d => A directory?
	-r => Readable file? 
	-w => Writable file? 
	-x => Executable file? 
	-z => Empty file? 
	-s => Size of file? 
=cut 

#------------------------------------------------------------------------
# seek()
#------------------------------------------------------------------------
# seek FileDescriptor, Offset, StartPoint
# StartPoint: 
# 	0 => Set new position in bytes to Offset
#	1 => Set new position in current position plus Offset
#	2 => Set new position to end of file plus Offset (where offset is normally a (-) value)

# tell() returns current position
# truncate() truncates the file to current position


