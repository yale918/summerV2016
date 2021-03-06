
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

//#define BufSize 8096
#define bufferSize 8096
int main(){
    int create_socket, new_socket;
    socklen_t addrlen;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    struct sockaddr_in address;


    //int file_fd;
    //long ret;
    //static char buffer[BUFSIZE+1];


    if((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
        printf("The socket was created\n");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15000);

    if(bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){
        printf("Binding Socket\n");
    }
    
    while(1){
        if (listen(create_socket, 10) < 0){
            perror("server: listen");
            exit(1);
        
        }

        if((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0){
            perror("server: accept");
            exit(1);
        }

        if(new_socket > 0){
            printf("The Client is connected...\n");
        }
        
        recv(new_socket, buffer, bufsize, 0);
        //printf("%s\n", buffer);
        
        //write(new_socket, "hello world\n", 12);
        
        //if((file_fd = open(&buffer[5], O_RDONLY))==-1)
        //    write(fd, "Failed to open file", 19);

        int file_fd,ret;
        char buff[bufferSize];
        
        sprintf(buff, "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
        write(new_socket, buff, strlen(buff));

        file_fd = open ("./index.html", O_RDONLY );

        if(file_fd==-1)
            printf("failed to open file\n");
        else
            printf("success to open file\n");

        while((ret = read(file_fd, buff, bufferSize))>0){
            write(new_socket,buff,ret);
        }
    
                


        
        
        
        close(new_socket);
    
    }
    close(create_socket);
    
    return 0;
}



