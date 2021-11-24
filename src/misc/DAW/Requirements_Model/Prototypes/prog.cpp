#include <stdio.h>
#include "csound.hpp"
#include <string>
#include <cstdio>
#include <cerrno>
#include <iostream>

std::string get_file_contents(const char *filename)
{
  std::FILE *fp = std::fopen(filename, "rb");
  if (fp)
  {
    std::string contents;
    std::fseek(fp, 0, SEEK_END);
    contents.resize(std::ftell(fp));
    std::rewind(fp);
    std::fread(&contents[0], 1, contents.size(), fp);
    std::fclose(fp);
    return(contents);
  }
  throw(errno);
}

int main(){

std::string orc = get_file_contents("orc/Doo-wop.orc");
std::string sco = get_file_contents("sco/Doo-wop/Doo-wop.sco");	

//create an instance of Csound
Csound* csound = new Csound();

//set CsOptions
csound->SetOption("-odac");

//compile orc.
csound->CompileOrc(orc.c_str());

//compile sco
csound->ReadScore(sco.c_str());

//prepare Csound for performance
csound->Start();

//perform entire score
csound->Perform();	

//free Csound object
delete csound;

return 0;
}



