#include "client/linux/handler/exception_handler.h"
#include <iostream>
#include <glog/logging.h>

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
void crash()
{
    int* a = nullptr;
    *a = 1;
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
    crash();
    return 0;
}