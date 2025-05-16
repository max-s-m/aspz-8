#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(){
    int pipefd[2];
    pipe(pipefd); //створюється pipe
    //дескриптор запису неблокуючий
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    char buff[100000]; //великий буфер
    memset(buff, 'A', sizeof(buff));
    size_t count = write(pipefd[1], buff, sizeof(buff));
    printf("Requested: %ld, Written: %ld\n", sizeof(buff), count);
}
