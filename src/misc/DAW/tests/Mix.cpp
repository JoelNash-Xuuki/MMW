#include "Mix.hpp"

Mix::Mix(){
    orc = "orc";
    sco = "sco";
}

Mix::Mix(const char* audio){
    orc = "orc";
    sco = "sco";
}

const char* Mix::getOrc() {
    return orc;
}

const char* Mix::getSco() {
    return sco;
}
