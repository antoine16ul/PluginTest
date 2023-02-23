
#ifndef __plugin_h__
#define __plugin_h__
#define __TPENTRYPOINT __plugin_test_init
#ifdef _WIN32
#define TEST_PLUGIN_INIT extern "C" _declspec(dllexport) void __TPENTRYPOINT(const TestPlugin::InitContext & ctx)
#else
#define TEST_PLUGIN_INIT extern "C" void __TPENTRYPOINT(const TestPlugin::InitContext & ctx)
#endif

#include <string>

namespace TestPlugin{

    using CallBack = int(*)(int);

    constexpr int version = 5;

    struct InitContext {
        const int version;
        void (* func1) (const std::string &);
        void (* func2) (const CallBack&);

    };


};






#endif
