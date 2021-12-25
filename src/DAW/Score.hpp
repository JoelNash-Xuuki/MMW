#include <string>
#include <fstream>

/*

- read notes in.
- write score file

*/

using namespace std;

#ifndef Score_H
#define Score_H
class Score{
  public:
	bool wasRun; 
    string scoreFileName;	
  public:
	Score(string name);
	ofstream scoreFile;
    string readFileIntoString(const string& path);
    void printScore();
	void storeFileAsString();
};
# endif

