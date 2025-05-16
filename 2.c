#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    const char *fname = "test_lseek.txt";
    //створюється файл і записуються дані
    int fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0600);
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(fd, data, sizeof(data));
    //дескриптор не закривається, використовується далі для lseek

    lseek(fd, 3, SEEK_SET); //покажчик на 3-й байт
    char buff[4];
    size_t num_read = read(fd, buff, sizeof(buff)); //читається 4 байти

    printf("Read %zd B. Buff: ", num_read);
    for(size_t i=0; i<num_read; i++){
        printf("%u ", buff[i]);
    }
    printf("\n");
    close(fd);
    unlink(fname);
}
