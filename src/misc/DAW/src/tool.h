#include <string.h>
#include <iostream>

#include "csound.hpp"

using namespace std;

class tool{
    private:
    Csound* cs;
    string orc;
    string sco;

    public: 
    virtual tool();
    virtual ~tool(){}
    virtual string getOrc() = 0;
    virtual string getSco() = 0;
    virtual string setOptions() = 0;
    virtual Csound* getCs(string op);
    virtual ~tool(){};
};
