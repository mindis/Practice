# git clone librecGitRepo
# cd into librecGitRepo

# Run all test
mvn test
# Run a single test, by specifying which test to run
mvn test -Dtest=net.librec.recommender.cf.rating.NMFTestCase
mvn test -Dtest=net.librec.recommender.cf.ranking.WRMFTestCase
