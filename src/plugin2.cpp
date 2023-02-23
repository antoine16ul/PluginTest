#include "plugin.h"
#include <iostream>



int callback(int v) {
    return v+100;
};

TEST_PLUGIN_INIT{
    std::cout <<"LOADING PLUGIN2 "<<ctx.version <<std::endl;
    ctx.func1("from plugin2");
    ctx.func2(callback);

};


