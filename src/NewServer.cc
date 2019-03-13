// Author:     Hermit
// CreateTime: Mar 13, 2019 8:24 PM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <thread>

#include "MissionController.h"
#include "ProjectTool.h"


void doProcess(mission::dataPack data) {
    mission::Receipt *result = new mission::Receipt;
    mission::parsing(data, result);
    char *out = new char(256);
    sprintf(out, "%s/%d.fifo", tool::getFifoPath(),
                               data.sessionid);
    mkfifo(out, tool::mode);
    int wfd = open(out, O_WRONLY);
    write(wfd, result, sizeof(mission::Receipt));
    delete result;
}

void start() {
    char path[256];
    sprintf(path, "%s/server.fifo", tool::getFifoPath());
    mkfifo(path, tool::mode);
    int rfd = open(path, O_RDONLY);
    while(true) {
        mission::dataPack *data = new mission::dataPack;
        while((read(rfd, data, sizeof(mission::dataPack))) > 0)
        {
            mission::dataPack tmp = *data;
            std::thread t(&doProcess, tmp);
            t.detach();
        }
        delete data;
    }
}

int main() {
    start();    
    return 0;
}
