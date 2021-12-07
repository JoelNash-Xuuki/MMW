#include "Test.h"
#include "../src/Score.hpp"

class ScoreTest : public TestSuite::Test {

  void run(){
    this->testMethod();
  }

  public:
    void testMethod();
	void testStoreFileAsString();

};
