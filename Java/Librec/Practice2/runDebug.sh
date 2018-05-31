# Note: Below doesn't really work yet, no idea why, it doesnt open address at 1044 and doesnt load class
mvn exec:exec -Dexec.executable="java" -Dexec.args="-classpath %classth -Xdebug -Xrunjdwp:transport=dt_socket,server=y,suspend=n,address=1044 com.librecPracticeTwo.app.TestLibrecTwo"

