#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

long long get_file_offset(int pid, const char *);

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Need one arg: PID\n");
        return 1;
    }
    int target_pid = atoi(argv[1]);
    // Для доступу до /proc/<pid>/fdinfo іншого процесу часто потрібні права root.
    char fd_dir_path[100];
    //зберігання щляху у fd_dir_path та відкриття директорії
    snprintf(fd_dir_path, sizeof(fd_dir_path), "/proc/%d/fd", target_pid);
    DIR *dir = opendir(fd_dir_path);
    if(!dir){
        fprintf(stderr, "Didn't open %s\n", fd_dir_path);
        return 1;
    }
    //виведення зсувів
    printf("File offsets for PID %d:\n", target_pid);
    struct dirent *item;
    while((item = readdir(dir)) != NULL){
        if(item->d_name[0] == '.') continue; //не виводяться батьківська та ця папки
        //перевірка, що дескриптор - число
        char *endptr;
        strtol(item->d_name, &endptr, 10);
        if(*endptr != '\0') continue; //не число - пропуск
        //зсув - поточна позиція у файлі
        long long offset = get_file_offset(target_pid, item->d_name);
        if(offset >= 0){
            printf("  fd %s: %lld\n", item->d_name, offset);
        }
        else{ //не вдалося прочитати
            printf("  fd %s: (Didn't read offset)\n", item->d_name);
        }
    }
    closedir(dir);
}
//отримання зсуву з файлу
long long get_file_offset(int pid, const char *fd_str){
    char path[100];
    snprintf(path, sizeof(path), "/proc/%d/fdinfo/%s", pid, fd_str);
    FILE *f = fopen(path, "r");
    if(!f) return -1; //файл не відкрився
    char line[100];
    long long offset = -1; //зсув
    while(fgets(line, sizeof(line), f)){
        if(strncmp(line, "offset=", 7) == 0){ //рядок з зсувом знайдено
            if(sscanf(line + 7, "%lld", &offset) == 1){ //розібрано
                break;
            }
            else{ //не розібрано
                offset = -2;
                break;
            }
        }
    }
    fclose(f);
    return offset;
}
