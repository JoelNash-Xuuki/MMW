#include <string.h>
#include <iostream>

using namespace std;

#ifndef TOOL_H
#define TOOL_H

class Tool{
    protected:
        const char* orc;
	const char* sco;
        
    public:
        Tool();
	Tool(const char* audio);
        virtual const char* getOrc() = 0;
        virtual const char* getSco() = 0;
};
#endif
