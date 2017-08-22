# KafkaExample0.9

A 'Hello World' example for Kafka0.9   

### Steps:
1. Change mainClass in pom.xml to SimpleConsumerDemo to run the other main function.  

2. Get the dependencies and compile  

    ```bash
    mvn package
    ```

3. Download kafka from website (must be 0.9 version), extract it to anywhere and cd into that directory containing bin and config. 

4. Start ZooKeeper Server  
    - make sure zookeeper.properties in configuration has same port and ip as KafkaProperties.java file (port:9092, ip:2181)  

    ```bash
    /bin/zookeeper-server-start.sh ./config/zookeeper.properties
    ```

5. Start Kafka  Server  
    - make sure kafka.properties in configuration has same port and ip as KafkaProperties.java file  

    ```bash
    ./bin/kafka-server-start.sh ./config/server.properties
    ```

    - The really-executable-jar plugin allows you to execute this jar file, execute it  

    ```bash
    ./target/kafka-experiment-0.0.1-SNAPSHOT.jar
    ```
