#-------------------------------------------------------
# Latest
#-------------------------------------------------------
Just refer to Practice/Java/Librec/PracticeTwo, it works
#-------------------------------------------------------
# Outdated 1
# Update com.librecPracticeTwo.app.TestLibrecTwo with packageName.className
mvn exec:exec -Dexec.executable="java" -Dexec.args="-classpath %classth -Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=1044 com.librecPracticeTwo.app.TestLibrecTwo"
#-------------------------------------------------------
# Outdated 2
# On first terminal run
# It will give you a port number, assume its 8000
mvnDebug clean install # but this doesn't really detect anything from maven compilation, so not sure what this is for.
# Second terminal run
jdb -attach localhost:8000
#-------------------------------------------------------
