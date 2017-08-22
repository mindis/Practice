# note: Logs are generated in directory (absolute path) 
/tmp/kafka-logs

# To do an actual reset from scratch, you need to remove zookeeper files and kafka logs that are stored persistently 
rm -rf /tmp/zookeeper
rm -rf /tmp/kafka-logs

# Start Zookeeper at port localhost:2181
./bin/zookeeper-server-start.sh ./config/zookeeper.properties
# Start Kafka at port: localhost:9092
./bin/kafka-server-start.sh ./config/server.properties


# Note: Each port number in a hostname (localhost) is a broker
#       Each localhost itself is a node
#       Multiple nodes normally means each node runs a different machine
#       Multiple brokers means each broker (portNum=9092 for e.g.) runs on the same machine (host=localhost)
#       Use multiple nodes if want to make use of more machines
#       Use multiple brokers if want to make use of more cores on the same machine

#------------------------------------------------------------------------------------------------------------------------------------------
# kafka-topics.sh
#------------------------------------------------------------------------------------------------------------------------------------------
# More info. 
./kafka-topics.sh --help

# Create a topic called topicName with 20 partitions and 2 replicas
./kafka-topics.sh --create --topic topicName --partitions 20 --replication-factor 2 --zookeeper localhost:2181

# List all available topics
./kafka-topics.sh --list --zookeeper localhost:2181

# More info. for all available topics
./kafka-topics.sh --describe --zookeeper localhost:2181

# Delete topic called topicName
./kafka-topics.sh --delete --topic topicName --zookeeper localhost:2181

# Increase number of partitions for topicName (can't decrease for Kafka currently)
./kafka-topics.sh --alter --topic topic3 --partitions 5 --zookeeper localhost:2181
#------------------------------------------------------------------------------------------------------------------------------------------
# kafka-reassign-partitions.sh
#------------------------------------------------------------------------------------------------------------------------------------------

# Generate a good partition reassignment
    # List of brokers : "0,1,2"
    # topicToMove.json contains list of topic names to re-assign partitions
    # zookeeper: is current running zookeeper instance
./kafka-reassign-partitions.sh --generate --broker-list "0" --topics-to-move-json-file topicToMove.json --zookeeper localhost:2181

# Execute ree-assign partitions according to reassignmentFile.json
./kafka-reassign-partitions.sh --zookeeper localhost:2181 --reassignment-json-file reassignmentFile.json --execute

# Verify that re-assignment was successful
./kafka-reassign-partitions.sh --zookeeper localhost:2181 --reassignment-json-file reassignmentFile.json --verify

#------------------------------------------------------------------------------------------------------------------------------------------
# kafka-preferred-replica-election.sh
#------------------------------------------------------------------------------------------------------------------------------------------
# Automatically re-balance partitions
./kafka-preferred-replica-election.sh --zookeeper localhost:2181
#------------------------------------------------------------------------------------------------------------------------------------------
# kafka-console-producer.sh
#------------------------------------------------------------------------------------------------------------------------------------------
# Start sending messages to broker 9092 and topic topicName (must have been created already) 
    ./bin/kafka-console-producer.sh --broker-list localhost:9092 --topic topicName
    # Then, start sending any messages
    lala
    baba
    kaka

# Send messages to both broker 9092 and 9093
./bin/kafka-console-producer.sh --broker-list localhost:9092, localhost:9093 --topic topicName
#------------------------------------------------------------------------------------------------------------------------------------------
# kafka-console-consumer.sh
#------------------------------------------------------------------------------------------------------------------------------------------
# Consume messages from beginning of topic
./kafka-console-consumer.sh --zookeeper localhost:2181 --from-beginning --topic topicName
# Consume messages from last left off
./kafka-console-consumer.sh --zookeeper localhost:2181 --topic topicName
