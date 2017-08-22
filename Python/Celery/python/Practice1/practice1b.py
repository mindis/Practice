# Execute by running:
# >> practice1b.py # This queues a task to rabbitMQ
# >> practice1b.py # This queues another task to rabbitMQ
# >> celery -A practice1a worker --loglevel=info # This finally runs celery to take out both tasks

from practice1a import add 

x = 2
y = 3
# Call task using the delay function an it returns the result asynchronously
# note: You need to set the Results Backend to the backend you are using. 
#       use rpc if you want to send messages back as RabbitMQ again
asynchronousResult = add.delay(x, y)
print asynchronousResult 

returnsTrueIfTaskHasFinishedProcessingAndFalseOtherwise = asynchronousResult.ready()
print returnsTrueIfTaskHasFinishedProcessingAndFalseOtherwise 

