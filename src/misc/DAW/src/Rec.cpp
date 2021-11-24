#include "Rec.hpp"

Rec::Rec(){
    orc = "../src/rec.orc";
    sco = "../src/rec.sco";
}

Rec::Rec(const char* audio){
    orc = "../src/rec.orc";
    sco = "../src/rec.sco";
}

const char* Rec::getOrc() {
    return orc;
}

const char* Rec::getSco() {
    return sco;
}
