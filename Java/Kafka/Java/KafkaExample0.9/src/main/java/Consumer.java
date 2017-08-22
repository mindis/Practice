/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package kafka.examples;

import kafka.utils.ShutdownableThread;
import org.apache.kafka.clients.consumer.ConsumerConfig;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;

import java.util.Collections;
import java.util.Properties;

// Run on own thread
// note: Can manually assign partitions to it but can't do both auto and manual
public class Consumer extends ShutdownableThread {
    private final KafkaConsumer<Integer, String> consumer;
    private final String topic;

    public Consumer(String topic) {
        super("KafkaConsumerExample", false);
        Properties props = new Properties();
        props.put(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, "localhost:9092");
        props.put(ConsumerConfig.GROUP_ID_CONFIG, "DemoConsumer");
        // The consumer periodically commit the offset data so that in event of failure, not too many duplicated reads are done on same commit 
        // Autocommit uses at least once semantics
        // note: If you set auto commit to false, you need to commit yourself using consumer.commitSync()
        //      Doing this enables you to perform At Most Once or At Least Once semantics manually
        props.put(ConsumerConfig.ENABLE_AUTO_COMMIT_CONFIG, "true");
        // Make commit interval be once every 1 second
        props.put(ConsumerConfig.AUTO_COMMIT_INTERVAL_MS_CONFIG, "1000");
        // When multiple consumers in same group, each consumer is given a lock on a subset of partitions
        // After every rebalance, all members begin sending periodic heartbeat to group coordinator
        // Group coordinator marks members as dead if they don't submit heartbeat within specific time period (30 seconds as indicated below) 
        // Then, it signals rest of group to rejoin so partitions are reassigned
        // It also releases the lock of the dead members
        // Consumers only send heartbeat after a call to poll, so if there is no data => no poll, will rebalance! 
        props.put(ConsumerConfig.SESSION_TIMEOUT_MS_CONFIG, "30000");
        props.put(ConsumerConfig.KEY_DESERIALIZER_CLASS_CONFIG, "org.apache.kafka.common.serialization.IntegerDeserializer");
        props.put(ConsumerConfig.VALUE_DESERIALIZER_CLASS_CONFIG, "org.apache.kafka.common.serialization.StringDeserializer");
        consumer = new KafkaConsumer<>(props);
        this.topic = topic;
    }

    @Override
    public void doWork() {
        // Must include all the topics to subscribe to! Can't just add topics. 
        consumer.subscribe(Collections.singletonList(this.topic));
        // Poll (similar to select() from UNIX) 
        //     Fetch records based on current position 
        //     Initial position (earliest or latest offset for each partition)   
        //     Rebalance resets position to last committed offset
        //     1 second that the consumer will block while waiting for record in current position
        //          Can set to Long.MAX_VALUE and it will block forever till record available
        //          Can wake up earlier usine wakeup()
        //      Returns immediately if any data available
        ConsumerRecords<Integer, String> records = consumer.poll(1000);
        // ConsumerRecord
        //      key
        //      value
        //      topic
        //      partition
        //      offset
        for (ConsumerRecord<Integer, String> record : records) {
            System.out.println("Received message: (" + record.key() + ", " + record.value() + ") at offset " + record.offset());
        }
    }

    @Override
    public String name() {
        return null;
    }

    @Override
    public boolean isInterruptible() {
        return false;
    }
}
