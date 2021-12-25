#include <string>
#include "ScoreTest.h"

using namespace std;

void ScoreTest::run(){
  this->testReadFileIntoString();
 // this->testPrintScore();
 // this->testStoreFileAsString();
}

void ScoreTest::testReadFileIntoString(){
  Score score= Score("doc/ly/test.ly");
  string s= score.readFileIntoString("doc/Score/test.score");
  test_(s == "c\n");
}

void ScoreTest::testPrintScore(){
  test_(true);
}

void ScoreTest::testStoreFileAsString(){
  test_(true);
}
