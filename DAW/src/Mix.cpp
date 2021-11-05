#include "Mix.hpp"

Mix::Mix(){
    orc = "../src/mix.orc";
    sco = "../src/mix.sco";
}

Mix::Mix(const char* audio){
}


const char* Mix::getOrc() {
    return orc;
}

const char* Mix::getSco() {
    return sco;
}
