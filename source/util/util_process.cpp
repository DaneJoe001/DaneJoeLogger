#ifdef WIN32
#include "windows.h"
#elif __linux__
#include "unistd.h"
#endif

#include "util/util_process.hpp"

int DaneJoe::UtilProcess::get_pid()
{
#ifdef WIN32
    return int(GetCurrentProcessId());
#elif __linux__
    return int(getpid());
#else
    return -1;
#endif
}