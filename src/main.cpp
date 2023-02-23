#include <string>
#include <iostream>
#include "plugin.h"

//======================================================================
// platform specific code
//======================================================================

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

static std::string library_file_name(const std::string& name) {
    return name+".dll";
};

static void* load_library(const std::string& library_name) {
	return reinterpret_cast<void*>(LoadLibraryA(library_name.c_str()));
}

static void* library_symbol(void* library,const std::string&symbol){
    return reinterpret_cast<void*>(
			GetProcAddress(HMODULE(library, LPCSTR(symbol.c_str())));
}

#else //UNIX
#include <dlfcn.h>
#ifdef __APPLE__

static std::string library_file_name(const std::string& name) {
    return  std::string("./lib" + name + ".dylib");
};

#else

static std::string library_file_name(const std::string& name) {
    return  std::string("./lib" + name + ".so");
};

#endif


static void* load_library(const std::string& library_name) {
    return dlopen(library_name.c_str(), RTLD_NOW);
};

static void* library_symbol(void* library,const std::string&symbol){
    return dlsym(library, symbol.c_str());
};
#endif


//======================================================================
// InitCtx
//======================================================================

static void func1(const std::string &name) {
    std::cout << "FUNC1 "<<name<<std::endl;
}

static void func2(const TestPlugin::CallBack &cb) {
    std::cout << "Callback" << cb(1)<<std::endl;
}



static const TestPlugin::InitContext _init_ctx {
    TestPlugin::version,
    func1,
    func2
};






bool test_lib(const std::string & name){
    std::cout << "* test_lib "<<name<<std::endl;
    const std::string file_name = library_file_name(name);
    std::cout << " file_name = "<<file_name<<std::endl;
    void * lib = load_library(file_name);
    std::cout << " library = "<<lib<<std::endl;
    if(!lib) return false;
    void * symbol = library_symbol(lib,"__plugin_test_init");
    std::cout << " symbol = "<<symbol<<std::endl;
    if(!symbol) return false;
    reinterpret_cast<void (*)(const TestPlugin::InitContext&)>(symbol)(_init_ctx);

    std::cout << " ok"<<std::endl;
    return true;

};



int main() {

    bool ok = true;
    
    ok &= test_lib("plugin1");
    ok &= test_lib("plugin2");
    ok &= !test_lib("plugin3");

    std::cout << (ok?"PASSED":"FAILLED") << std::endl;

    return ok?0:1;
};