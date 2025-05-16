#include <stdio.h>
#include <unistd.h>

int main(){
    int pid;
    pid = fork();
    //якщо раптом форк не виконався
    if(pid < 0){
        printf("Forkn't\n");
        return 1;
    }
    //виконається в батьківському та дочірньому процесах
    else if(pid > 0){ //дод. число (id створеного дочірнього процесу) - батьківський
        printf("(Parent proc) Child ID: %d\n", pid);
    }
    else{ //0 - це дочірній процес
        printf("(Child proc) PID: %d\n", pid);
    }
}
