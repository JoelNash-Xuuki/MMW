#include <string.h>
#include <iostream>

#include "Tool.hpp"

#ifndef MIX_H
#define MIX_H

class Mix: public Tool{
    public:
	Mix();
	Mix(const char* audio);
        const char* getOrc() override;
        const char* getSco() override;
	void writeOrc();
};

#endif
