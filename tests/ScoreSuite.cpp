#include <iostream>
#include "Suite.h"
#include "ScoreTest.h"

using namespace std;
using namespace TestSuite;

int main() {
    Suite suite("Score Suite");
	suite.addTest(new ScoreTest);
    suite.run();
    long nFail = suite.report();
    suite.free();
    return nFail;
}
