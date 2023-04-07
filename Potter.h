#ifndef POTTER_H
#define POTTER_H
#include <iostream>
#include "Moving.h"


using namespace std;

class Potter:public Moving {
    public:
        Potter(const char*,char);
};
#endif
