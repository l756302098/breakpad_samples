#include "client/linux/handler/exception_handler.h"
#include <iostream>
#include <glog/logging.h>
#include "../include/math.h"

static const char* EXE_NAME = "breakpad_samples";
static void FailureHandle(const char* data, int size) {
    LOG(ERROR) << std::string(data, size);
}

static bool dumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                        void* context,
                        bool succeeded)
{
    std::cout << "Dump path:" << descriptor.path() << std::endl;
    LOG(INFO) << "Dump path:" << descriptor.path();
    return succeeded;
}

int main(int argc, char* argv[])
{
    //glog
    google::InitGoogleLogging(EXE_NAME);
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(FailureHandle);
    FLAGS_log_dir = "/home/li/log";
    //breakpad
    google_breakpad::MinidumpDescriptor descriptor("/tmp");
    google_breakpad::ExceptionHandler eh(descriptor, nullptr, dumpCallback, nullptr, true, -1);
    try
    {
        math m;
        m.add(1,2);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr <<'other error. \n';
    }
    
    return 0;
}