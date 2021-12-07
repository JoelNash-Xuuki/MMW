#include <string>
#include <iostream>

#include <stdio.h>
#include <cstdio>
#include <cerrno>

#include "csound.hpp"

#include "Tool.hpp"
#include "Mix.hpp"
#include "Rec.hpp"

using namespace std;

string get_file_contents(const char *filename){
  FILE *fp = fopen(filename, "rb");
  if (fp)
  {
    string contents;
    fseek(fp, 0, SEEK_END);
    contents.resize(std::ftell(fp));
    rewind(fp);
    fread(&contents[0], 1, contents.size(), fp);
    fclose(fp);
    return(contents);
  }
  throw(errno);
}

int main(int argc, char* argv[]){

    Tool* t;
    Mix m;
    Rec r;

    string orc;
    string sco;   

    while(argc > 1){
	if(argv[1][0] == '-'){
	    if(argv[1][1] == 'm'){
		t = &m;
		orc = get_file_contents(m.getOrc());
		sco = get_file_contents(m.getSco());
            }
	    else if(argv[1][1] == 'r'){
		t = &m;
		orc = get_file_contents(r.getOrc());
		sco = get_file_contents(r.getSco());
            }
        }
        argc--;
    }

    Csound* csound = new Csound();

    csound->SetOption("-+rtaudio=jack");
    csound->SetOption("-iadc");
    csound->SetOption("-odac.wav");
    csound->SetOption("-B512");
    csound->SetOption("-b128");

    csound->CompileOrc(orc.c_str());
    csound->ReadScore(sco.c_str());
    csound->Start();

    csound->Perform();	
    delete csound;

    return 0;
}




