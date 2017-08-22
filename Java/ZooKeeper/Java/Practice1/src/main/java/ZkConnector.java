package com.zookeeperPracticeOne.app;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.Watcher; 
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher.Event.KeeperState;
import java.io.IOException;

public class ZkConnector {
    private ZooKeeper zk;
    private java.util.concurrent.CountDownLatch connSignal = new java.util.concurrent.CountDownLatch(1);
    public ZooKeeper connect(String host) throws IOException, InterruptedException, IllegalStateException {
        // host, number of milliseconds, 
        zk = new ZooKeeper(host, 5000, new Watcher() {
            public void process(WatchedEvent event) {
               if (event.getState() == KeeperState.SyncConnected) {
                   connSignal.countDown();
               } 
            }
        });
        connSignal.await(); 
        return zk; 
    }
    public void close() throws InterruptedException {
        zk.close();
    }
};
