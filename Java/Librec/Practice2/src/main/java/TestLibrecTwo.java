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
// Rating recommender
import net.librec.recommender.cf.ItemKNNRecommender;
// Ranking recommender
import net.librec.recommender.cf.ranking.WRMFRecommender;


import net.librec.eval.RecommenderEvaluator;
// Rating evaluator
import net.librec.eval.rating.RMSEEvaluator;

// Ranking evaluator
import net.librec.eval.ranking.NormalizedDCGEvaluator;

import net.librec.filter.GenericRecommendedFilter;
import net.librec.recommender.item.RecommendedItem;
import net.librec.recommender.item.RecommendedList;

// public class TestZkConnection {
public class TestLibrecTwo {
    private static LibrecTwo lrTwo; 
    public static void main(String[] args) throws Exception {
        System.out.println("Testing librec One");

        // Build data model
        Configuration conf = new Configuration();
        String dataLocation = "/root/Github/RecommendationSystems/sclrecommender/data/movielens";
        conf.set("dfs.data.dir", dataLocation);

        // 20m
        // Similarly, change ',' to ' ' and got rid of first line
        //conf.set("data.input.path", "ml-20m/ratings.csv");
        // Note: Out of memory error, Librec doesn't handle large datasets well
        conf.set("data.input.path", "ml-20m/ratingsLibrec.csv");

        // 1m
        // Librec only splits by tabs and no other delimiter
        // so manually created a copy of the file, and replaced all old delimiters of "::" to " "
        // conf.set("data.input.path", "ml-1m/ratings.dat"); 
        conf.set("data.input.path", "ml-1m/ratingsLibrec.dat");

        // 100k
        conf.set("data.input.path", "ml-100k/u.data");

        TextDataModel dataModel = new TextDataModel(conf);
        dataModel.buildDataModel();
        System.out.println("Done building data model");

        // Build recommender context
        // contains data model, configuration, similarity matrix
        RecommenderContext context = new RecommenderContext(conf, dataModel);
        System.out.println("Done building context");

        // Build similarity
        conf.set("rec.recommender.similarity.key" ,"item");
        RecommenderSimilarity similarity = new PCCSimilarity();
        similarity.buildSimilarityMatrix(dataModel);

        // Set similarity into recommender context
        context.setSimilarity(similarity);

        System.out.println("Done building similarity");

        // Build recommender algorithm

        // Rating recommender
        //
        conf.set("rec.neighbors.knn.number", "80");
        Recommender recommender = new ItemKNNRecommender();
        // */

        // Ranking Recommender
        //Recommender recommender = new WRMFRecommender();

        recommender.setContext(context);

        System.out.println("Done setting context from recommender");

        // Ranking instead of rating prediction
        // Setting this will not calculate rmse
        // not setting this however, will not calculate ranking
        // you can only do one or the other BUT not both.
        // unless you run recommendation again from scratch
        // so just make 2 different files for future
        conf.set("rec.eval.enable", "true");
        conf.set("rec.recommender.isranking", "true");
        conf.set("rec.recommender.ranking.topn", "10");

        // Run recommender algorithm
        // Run algorithm on the recommender context.
        // Basically, every algorithm takes in a recommender context, and also evaluator. 
        recommender.recommend(context);

        System.out.println("Done recommending");

        /* //
        // Evaluate the recommended result
        RecommenderEvaluator evaluatorRmse = new RMSEEvaluator();
        System.out.println("RMSE: " + recommender.evaluate(evaluatorRmse));
        // */


        RecommenderEvaluator evaluatorNdcg = new NormalizedDCGEvaluator();
        // Must set evaluator manually here for it to work.
        //evaluatorNdcg.setTopN(-1);
        evaluatorNdcg.setTopN(10);
        System.out.println("NDCG: " + recommender.evaluate(evaluatorNdcg));
        // RecommendedList recommendedItemList = recommender.getRecommendedList();
        // System.out.println("NDCG: " + evaluator.evaluate(context, recommendedItemList));

        List<RecommendedItem> recommendedItemList = recommender.getRecommendedList();
        // Set id list of filter
        List<String> userIdList = new ArrayList<>();
        List<String> itemIdList = new ArrayList<>();

        // Filter the recommended result
        // to include all item for user 1
        // and all users for item 70
        System.out.println("All items of user 1, also all users of item 70");
        userIdList.add("1");
        itemIdList.add("70");


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
