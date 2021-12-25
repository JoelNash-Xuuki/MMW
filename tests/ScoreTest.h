#include "Test.h"
#include "../src/DAW/Score.hpp"

class ScoreTest : public TestSuite::Test {
  public:
    void setUp();
	void run() override;
	void testReadFileIntoString();
	void testPrintScore();
	void testStoreFileAsString();
};
