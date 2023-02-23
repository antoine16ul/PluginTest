#include "plugin.h"
#include <iostream>



int callback(int v) {
    return v+100;
};

TEST_PLUGIN_INIT{
    std::cout <<"LOADING PLUGIN1 "<<ctx.version <<std::endl;
    ctx.func1("from plugin1");
    ctx.func2(callback);

};

