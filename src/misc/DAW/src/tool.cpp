#include <string.h>
#include "tool.h"
#include "csound.hpp"

using namespace std;

tool::tool(){
    cs = new Csound();
}

Csound tool::getCs(string op){
	cs->SetOption(op);
}
