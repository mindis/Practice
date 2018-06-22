package com.librecPracticeThree.app;

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

public class TestLibrecThree {
    private static LibrecThree lrThree; 
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

        /*
        Main purpose is to check Python's code is right. 
        TODO: Figure out how to split movielens data by given test set. 
        TODO: This way, to compare, all I need to do is output a ratings.csv containing
              only the test ratings (with same userId, itemId available in entire training)
        I can run the same algorithm on same split using Java here
        Similarly, can check using same split on Python
        conf.set("inputDataPath", conf.get("dfs.data.dir") + "/test/given-testset");
        conf.set(Configured.CONF_DATA_COLUMN_FORMAT, "UIR");
        conf.set("data.testset.path", "/test/given-testset/test/ratings_0.txt");
        convertor = new TextDataConvertor(conf.get(Configured.CONF_DATA_COLUMN_FORMAT), conf.get("inputDataPath"));
        convertor.processData();
        GivenTestSetDataSplitter splitter = new GivenTestSetDataSplitter(convertor,conf);
        splitter.splitData();
        assertEquals(splitter.getTrainData().size(), 35491-10435);
        assertEquals(splitter.getTestData().size(), 10435);
        */

        // Build recommender context
        // contains data model, configuration, similarity matrix
        RecommenderContext context = new RecommenderContext(conf, dataModel);
        System.out.println("Done building context");

        // Build similarity
        conf.set("rec.recommender.similarity.key" ,"item");
        RecommenderSimilarity similarity = new PCCSimilarity(); // Pearson Cross Correlation
        similarity.buildSimilarityMatrix(dataModel);

        // Set similarity into recommender context
        context.setSimilarity(similarity);

        System.out.println("Done building similarity");

        // Build recommender algorithm

        // Rating recommender
        //
        //conf.set("rec.neighbors.knn.number", "80");
        //Recommender recommender = new ItemKNNRecommender();
        // */

        // Ranking Recommender
        // Set hyperparameters for MatrixFactorization class (parent of WRMF)
        // Values below are from benchmark released online
        // https://www.librec.net/release/v1.3/example.html
        // alpha=1.0 (i think this is weight coefficient)
        // factors=20, reg=0.015, max.iter=10
        // calculated NDCG was 0.631 on the site for ml100k
        // Set values according to those used in benchmarks
        conf.set("rec.iterator.maximum", "10");
        conf.set("rec.factor.number", "20");
        conf.set("rec.user.regularization", "0.015f");
        conf.set("rec.item.regularization", "0.015f");
        conf.set("rec.wrmf.weight.coefficient","1.0");
        
        // Values below are gotten from the default configuration file for WRMF test files
        // pathToLibrec/librec/core/src/main/resources/rec/cf/ranking/wrmf-test.properties 
        /* //
        rec.recommender.class=wrmf
        rec.iterator.maximum=20
        rec.user.regularization=0.01
        rec.item.regularization=0.01
        rec.factor.number=10
        rec.recommender.isranking=true
        rec.recommender.ranking.topn=10
        rec.wrmf.weight.coefficient=4.0
        // */ 
        // confidence weight coefficient, alpha in original paper

        // Values below are gotten from Matirx Factorization default values in code
        // It takes in default values if nothing was set
        /*
        numIterations = conf.getInt("rec.iterator.maximum",100);
        learnRate = conf.getFloat("rec.iterator.learnrate", 0.01f);
        maxLearnRate = conf.getFloat("rec.iterator.learnrate.maximum", 1000.0f);
        regUser = conf.getFloat("rec.user.regularization", 0.01f);
        regItem = conf.getFloat("rec.item.regularization", 0.01f);
        numFactors = conf.getInt("rec.factor.number", 10);
        isBoldDriver = conf.getBoolean("rec.learnrate.bolddriver", false);
        decay = conf.getFloat("rec.learnrate.decay", 1.0f);
        */

        Recommender recommender = new WRMFRecommender();

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

        // Returns the list of items that is recommended by this recommender
        // The list is sorted by ranking if ranking evaluation and setTopK was set
        // Otherwise, the list is unsorted item:rating pair
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
