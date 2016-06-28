#include "common.h"

int main(void){
    struct sockaddr_in sin, cin;
    socklen_t len = sizeof(cin);
    int lfd,cfd,fd;
    pid_t pid;
    int sock_opt = 1;
    int port;
    char path[MAX_LINE];
    struct stat statbuf;

    signal(SIGCHLD, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);

    printf("initializing ...\n");

    if(init(&sin, &lfd, &port, path) == -1){
        DEBUG_PRINT("error during initializing\n");
        exit(1);
    }

    while(1){
        DEBUG_PRINT("waiting connection ...\n");

        cfd = accept(lfd, (struct sockaddr *)&cin, &len);
        if(cfd == -1){
            perror("fail to accept");
            exit(1);
        }
        
        pid = fork();
        if(pid<0){
            perror("failed to fork");
            exit(1);
        }else if (pid==0){
            close(lfd);
        }

        if(get_path(cfd, path) == -1){
            DEBUG_PRINT("error during getting filepath\n");
            exit(1);
        }

        if(fstat(fd, &statbuf) < 0){
            perror("fail to get file status");
            exit(1);
        }
    
    
    }

}


