// Author:     Hermit
// CreateTime: Mar 12, 2019 8:47 PM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include "ProjectTool.h"

namespace tool 
{
char* getInstancePath() {
    if (strlen(instance) > 0)
        return instance;
    chdir("../");
    char *path = getcwd(NULL, 0);
    sprintf(instance, "%s/instance", path);
    free(path);
    if (access(instance, F_OK)) {
        if ((mkdir(instance, mode)) != 0) {
            printf("Can't make directory %s\n", instance);
            exit(1);
        }
    }
    return instance;
}

char* getFifoPath() {
    if (strlen(fifopath) > 0)
        return fifopath;
    sprintf(fifopath, "%s/fifo", getInstancePath());
    if (access(fifopath, F_OK)) {
        if ((mkdir(fifopath, mode)) != 0) {
            printf("Can't make directory %s\n", fifopath);
            exit(1);
        }
    } 
    return fifopath;
}

char* getDBPath() {
    if (strlen(dbpath) > 0) 
        return dbpath;
    sprintf(dbpath, "%s/db", getInstancePath());
    if ((access(dbpath, F_OK)) != 0) {
        if ((mkdir(dbpath, mode)) != 0) {
            printf("Can't make directory %s\n", dbpath);
            exit(1);
        }
    }
    printf("%s\n", dbpath);
    sprintf(dbpath, "%s/Account.db", dbpath);
    return dbpath;
}
} // end of namespace tool
