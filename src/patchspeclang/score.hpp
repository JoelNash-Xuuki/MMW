#include <string>
#include <fstream>

using namespace std;

#ifndef Score_H
#define Score_H
class Score{
  public:
	bool wasRun; 
    string fileName;	
  public:
	Score(string name);
	ofstream scoreFile;
    string readFileIntoString(const string& path);
    void printScore();
	void testMethod();
};
# endif

