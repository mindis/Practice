# On first terminal run
# It will give you a port number, assume its 8000
mvnDebug clean install

# Second terminal run
jdb -attach localhost:8000
