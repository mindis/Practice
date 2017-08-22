# Execute the task by running celery's worker function with -A argument which represents app
# >> celery -A practice1a worker --loglevel=info
# To get other commandline arguments for worker
# >> celery worker --help
# To know more about celery
# >> celery --help

from celery import Celery

app = Celery('practice1a', # current module which is name of file
        backend='rpc://', # store results from execution which is rabbitMQ
        broker='pyamqp://guest@localhost//') # broker to use which is set to rabbitMQ

@app.task
def add(x, y):
    return x + y
