#include "Rec.hpp"

Rec::Rec(){
    orc = "orc";
    sco = "sco";
}

Rec::Rec(const char* audio){
    orc = "orc";
    sco = "sco";
}

const char* Rec::getOrc() {
    return orc;
}

const char* Rec::getSco() {
    return sco;
}
