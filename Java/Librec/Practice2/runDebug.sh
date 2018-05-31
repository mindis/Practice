# Note: Below doesn't really work yet, no idea why, it doesnt open address at 1044 and doesnt load class
#mvn exec:exec -Dexec.executable="java" -Dexec.args="-classpath %classth -Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=1044 com.librecPracticeTwo.app.TestLibrecTwo"

# Below works
mvn clean
mvn package
./target/LibRecPracticeTwoDemo 
java -agentlib:jdwp=transport=dt_socket,address=8000,server=y,suspend=y -jar target/LibRecPracticeTwoDemo 

# Now open up a new terminal and run 
# >> jdb -attach localhost:8000
# Then you can run
# >> help
# >> run
