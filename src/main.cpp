#include "client/linux/handler/exception_handler.h"
#include <iostream>

static bool dumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                        void* context,
                        bool succeeded)
{
    std::cout << "Dump path:" << descriptor.path() << std::endl;
    return succeeded;
}
void crash()
{
    int* a = nullptr;
    *a = 1;
}
int main(int argc, char* argv[])
{
    google_breakpad::MinidumpDescriptor descriptor("/tmp");
    google_breakpad::ExceptionHandler eh(descriptor, nullptr, dumpCallback, nullptr, true, -1);
    crash();
    return 0;
}