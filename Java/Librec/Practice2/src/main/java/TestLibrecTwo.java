package com.librecPracticeTwo.app;

// Java Imports
import java.util.List; 
import java.util.ArrayList;

// Librec Imports
import net.librec.conf.Configuration;
import net.librec.data.model.TextDataModel;
import net.librec.recommender.RecommenderContext;

import net.librec.similarity.RecommenderSimilarity;
import net.librec.similarity.PCCSimilarity;
import net.librec.recommender.Recommender;
import net.librec.recommender.cf.ItemKNNRecommender;

import net.librec.eval.RecommenderEvaluator;
import net.librec.eval.rating.RMSEEvaluator;

import net.librec.filter.GenericRecommendedFilter;
import net.librec.recommender.item.RecommendedItem;

// public class TestZkConnection {
public class TestLibrecTwo {
    private static LibrecTwo lrTwo; 
    public static void main(String[] args) throws Exception {
        System.out.println("Testing librec One");

        // Build data model
        Configuration conf = new Configuration();
        String dataLocation = "/root/Github/RecommendationSystems/sclrecommender/data/movielens";
        /* 
        conf.set("dfs.data.dir", dataLocation);
        conf.set("data.input.path", "ml-100k/u.data");
        // */
        //
        conf.set("dfs.data.dir", dataLocation);
        // Librec only splits by tabs and no other delimiter
        // so manually created a copy of the file, and replaced all old delimiters of "::" to " "
        // conf.set("data.input.path", "ml-1m/ratings.dat"); 
        conf.set("data.input.path", "ml-1m/ratingsLibrec.dat");
        // */

        TextDataModel dataModel = new TextDataModel(conf);
        dataModel.buildDataModel();

        // Build recommender context
        // contains data model, configuration, similarity matrix
        RecommenderContext context = new RecommenderContext(conf, dataModel);

        // Build similarity
        conf.set("rec.recommender.similarity.key" ,"item");
        RecommenderSimilarity similarity = new PCCSimilarity();
        similarity.buildSimilarityMatrix(dataModel);

        // Set similarity into recommender context
        context.setSimilarity(similarity);

        // Build recommender algorithm
        conf.set("rec.neighbors.knn.number", "5");
        Recommender recommender = new ItemKNNRecommender();
        recommender.setContext(context);

        // Run recommender algorithm
        // Run algorithm on the recommender context.
        // Basically, every algorithm takes in a recommender context.
        // Basically, every algorithm takes in a and an evaluator. 
        recommender.recommend(context);

        // Evaluate the recommended result
        RecommenderEvaluator evaluator = new RMSEEvaluator();
        System.out.println("RMSE:" + recommender.evaluate(evaluator));

        // Set id list of filter
        List<String> userIdList = new ArrayList<>();
        List<String> itemIdList = new ArrayList<>();

        // Filter the recommended result
        // to include all item for user 1
        // and all users for item 70
        System.out.println("All items of user 1, also all users of item 70");
        userIdList.add("1");
        itemIdList.add("70");

        List<RecommendedItem> recommendedItemList = recommender.getRecommendedList();
        GenericRecommendedFilter filter = new GenericRecommendedFilter();
        filter.setUserIdList(userIdList);
        filter.setItemIdList(itemIdList);
        recommendedItemList = filter.filter(recommendedItemList);

        // Print filter result
        for (RecommendedItem recommendedItem : recommendedItemList) {
            System.out.println(
                    "user:" + recommendedItem.getUserId() + " " +
                    "item:" + recommendedItem.getItemId() + " " +
                    "value:" + recommendedItem.getValue()
            );
        }

        // Can also filter based on a single item or a single user
        userIdList = new ArrayList<>();
        itemIdList = new ArrayList<>();

        // Filter the recommended result
        // By specifying results of user and item
        System.out.println("All items of user 2");
        userIdList.add("2");

        recommendedItemList = recommender.getRecommendedList();
        filter.setUserIdList(userIdList);
        filter.setItemIdList(itemIdList);
        recommendedItemList = filter.filter(recommendedItemList);


        // Print filter result
        for (RecommendedItem recommendedItem : recommendedItemList) {
            System.out.println(
                    "user:" + recommendedItem.getUserId() + " " +
                    "item:" + recommendedItem.getItemId() + " " +
                    "value:" + recommendedItem.getValue()
            );
        }
        System.out.println("Done Testing");
    }
}
