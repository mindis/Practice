# git clone librecGitRepo
# cd into librecGitRepo

# Change the default configuration to use movielens100k instead of filmtrust
vim core/src/main/resources/librec-default.properties 
# Replace the line
data.input.path=filmtrust/rating
# with
data.input.path=movielens/ml-100k

# Not sure if need to change other lines such as below:
#rec.recommender.isranking=false
#rec.recommender.isranking=true

# Run all test
mvn test
# Run a single test, by specifying which test to run
mvn test -Dtest=net.librec.recommender.cf.rating.NMFTestCase
mvn test -Dtest=net.librec.recommender.cf.ranking.WRMFTestCase

