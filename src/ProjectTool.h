// Author:     Hermit
// CreateTime: Mar 12, 2019 8:46 PM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

namespace tool
{
const int MAX_PATH_NAME = pathconf("/", _PC_NAME_MAX);
static char instance[256] = "\0";
static char fifopath[256] = "\0";
static char dbpath[256] = "\0";
const int mode = S_IWUSR | S_IRUSR | S_IXUSR |
                 S_IWGRP | S_IRGRP | S_IXGRP |
                 S_IWOTH | S_IROTH | S_IXOTH;
char* getInstancePath();
char* getFifoPath();
char* getDBPath();
} // end of namespace tool
