#include <stdio.h>
#include <iostream>
#include "csound.hpp"
#include <string>

using namespace std;

int main(){
  Csound* csound = new Csound();
  csound->CompileCsd("iydhoti.csd");
  csound->Start();
  csound->Perform();	
  delete csound;
  return 0;
}

