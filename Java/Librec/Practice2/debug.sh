# Note: Below doesn't really work yet, no idea why, it doesnt open address at 1044 and doesnt load class
#mvn exec:exec -Dexec.executable="java" -Dexec.args="-classpath %classth -Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=1044 com.librecPracticeTwo.app.TestLibrecTwo"

# Below works
mvn clean
mvn package
# Line below runs it normally
# ./target/LibRecPracticeTwoDemo 
# line below debugs it
java -agentlib:jdwp=transport=dt_socket,address=8000,server=y,suspend=y -jar target/LibRecPracticeTwoDemo 

# Now open up a new terminal and run 
jdb -attach localhost:8000
# Get possible commands
help
# Set a breakpoint at line 39 of the packageName:className
stop at com.librecPracticeTwo.app.TestLibrecTwo:39
# Run the debugger
run
# Step through it
step 
