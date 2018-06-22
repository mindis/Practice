# Note: Below doesn't really work yet, no idea why, it doesnt open address at 1044 and doesnt load class
#mvn exec:exec -Dexec.executable="java" -Dexec.args="-classpath %classth -Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=1044 com.librecPracticeThree.app.TestLibrecThree"

# Below works
mvn clean
mvn package
# Line below runs it normally
# ./target/LibRecPracticeThreeDemo 
# line below debugs it
java -agentlib:jdwp=transport=dt_socket,address=8000,server=y,suspend=y -jar target/LibRecPracticeThreeDemo 

# Now open up a new terminal and run 
jdb -attach localhost:8000
# Get possible commands
help
# Set a breakpoint at line 39 of the packageName.className
stop at com.librecPracticeThree.app.TestLibrecThree:39
# Run the debugger
run
# Step through it (goes into each function)
step 
# Next through it (runs over each function and stays in current method)
next

# List local variables
locals

# print a local variable
print localVarA

# get information from an array
dump arrA
print arrA
