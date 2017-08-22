package com.zookeeperPracticeOne.app;
import org.apache.zookeeper.ZooKeeper; 
import org.apache.zookeeper.KeeperException;
import java.io.IOException;
import java.util.List; 
import java.util.ArrayList;

public class TestZkConnection {
    public static void main(String[] args) throws IOException, InterruptedException, KeeperException {
        zkc = new ZkConnector(); 
        zk = zkc.connect("localhost");
        znodeList = zk.getChildren("/", true);
        for (String znode: znodeList) {
            System.out.println(znode);
        }
    }
    private static ZooKeeper zk;
    private static ZkConnector zkc; 
    private static List<String> znodeList = new ArrayList<String>(); 
}
