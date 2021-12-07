#include <iostream>
#include "Suite.h"
#include "Sieve.h"
#include "DateTest.h"
#include "ScoreTest.h"

using namespace std;
using namespace TestSuite;

int main() {
    Suite suite("TestSuite Test");
	suite.addTest(new ScoreTest);
    suite.run();
    long nFail = suite.report();
    suite.free();
    return nFail;
}
