#pragma once
#include "accout.h"

class Proxy {
    Proxy(Accout* accout) :accout_(accout) {};
    ~Proxy() {};
    Accout* GetAccout() {
        return accout_;
    }
private:
    Accout* accout_;
};