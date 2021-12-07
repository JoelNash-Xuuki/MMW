#include <string.h>
#include <iostream>

#include "Tool.hpp"

#ifndef REC_H
#define REC_H

class Rec: public Tool{
    public:
	Rec();
	Rec(const char* audio);
        const char* getOrc() override;
        const char* getSco() override;
};

#endif
