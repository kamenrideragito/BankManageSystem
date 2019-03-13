// Author:     Hermit
// CreateTime: Mar 12, 2019 8:47 PM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include "ProjectTool.h"

namespace tool 
{
const int MAX_PATH_NAME = pathconf("/", _PC_NAME_MAX);
char instance[256] = "\0";

char* getInstancePath() {
    if (strlen(instance) > 0)
        return instance;
    int mode = S_IWUSR | S_IRUSR | S_IXUSR |
               S_IWGRP | S_IRGRP | S_IXGRP |
               S_IWOTH | S_IROTH | S_IXOTH;
    chdir("../");
    char path[MAX_PATH_NAME];
    getcwd(path, sizeof(path));
    sprintf(instance, "%s/instance", path);
    if (access(instance, F_OK)) {
        if ((mkdir(instance, mode)) != 0) {
            printf("Can't make directory %s\n", instance);
            exit(1);
        }
    }
    return instance;
}
} // end of namespace tool
