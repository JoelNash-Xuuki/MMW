#include <string>
#include "score.hpp"
#include <iostream>

using namespace std;

Score::Score(string fileName){
  this->wasRun= false;
  this->fileName= fileName;
  this->printScore();
}

string Score::readFileIntoString(const string& path) {
  ifstream input_file(path);
  if (!input_file.is_open()) {
    cerr << "Could not open the file - '"
      << path << "'" << endl;
   exit(EXIT_FAILURE);
  }
  return string((istreambuf_iterator<char>(input_file)), 
  		 istreambuf_iterator<char>());
}

void Score::printScore(){

  string notes= readFileIntoString("test.note");
  scoreFile.open(fileName);
  scoreFile << "\\version \"2.22.1\"" << endl;
  scoreFile << "<<" << endl;
  scoreFile << "  \\new Staff {" << endl;
  scoreFile << "    \\clef \"bass\" \\time 4/4" << endl;
  scoreFile << "      "<< notes << endl;  
  scoreFile << "  }" << endl;
  scoreFile << ">>";
  scoreFile.close();
}

void Score::testMethod(){
  this->wasRun = true;
}

