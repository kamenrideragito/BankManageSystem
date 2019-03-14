// Author:     Hermit
// CreateTime: Mar 13, 2019 8:24 PM
// Eamil:      LasNoire23@gmail.com
// MyPage:     None

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#include <thread>

#include "MissionController.h"
#include "ProjectTool.h"


void daemonize(const char *cmd) {
    int                 i, fd0, fd1, fd2;
    pid_t               pid;
    struct rlimit       rl;
    struct sigaction    sa;

    umask(0);
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        printf("%s: Can't get file limit", cmd);
        exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("%s: Can't fork", cmd);
        exit(1);
    }
    else if (pid != 0)
        exit(0);

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        printf("%s: Can't ignore SIGHUP", cmd);
        exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("%s: Can't fork", cmd);
        exit(1);
    }
    else if (pid != 0)
        exit(0);

    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++) {
        close(i);
    }

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
               fd0, fd1, fd2);
        exit(1);
    }
}    

void doProcess(mission::dataPack data) {
    mission::Receipt result;
    mission::parsing(data, &result);
    char out[256];
    sprintf(out, "%s/%d.fifo", tool::getFifoPath(),
                               data.sessionid);
    mkfifo(out, tool::mode);
    int wfd = open(out, O_WRONLY);
//    printf("data: %s\n%d\n%d\n%d\n%s\n%s\n%d\n",
//                    data.cardid,
//                    data.operation,
//                    data.amount,
//                    data.sessionid,
//                    data.account.id,
//                    data.account.password,
//                    data.account.amount);
//    printf("result: \n \
//            operation: %c\n \
//            success: %d\n \ 
//            value: %d\n \
//            id: %s\n \
//            password: %s\n \
//            amount:  %d\n",
//                    result.operation, 
//                    result.success,
//                    result.value,
//                    result.account.id,
//                    result.account.password,
//                    result.account.amount);
    write(wfd, &result, sizeof(mission::Receipt));
    sleep(2);
    close(wfd);
}

void start() {
    char path[256];
    sprintf(path, "%s/server.fifo", tool::getFifoPath());
    mkfifo(path, tool::mode);
    int rfd = open(path, O_RDONLY);
    while(true) {
        mission::dataPack data;
        while((read(rfd, &data, sizeof(mission::dataPack))) > 0)
        {
            std::thread t(&doProcess, data);
            t.detach();
        }
    }
}

int main() {
    start();    
    return 0;
}
