#include <string>
#include "ScoreTest.h"

using namespace std;


void ScoreTest::testMethod(){
  Score s= Score("doc/test.ly");
  s.testMethod();
  test_(s.wasRun == true);
}

