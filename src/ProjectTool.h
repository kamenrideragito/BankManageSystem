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
char* getInstancePath();
char* getFifoPath();
} // end of namespace tool
