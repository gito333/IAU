#include <stdio.h>

#define NAME_SIZE 20

int main()
{
    int fd[2];
    int pid;
    pipe(fd)
    for(int i=0; i < 4; i++) {
       pid = fork(); 
       if (pid < 0)
       {
           close(fd[0]);
           close(fd[1]);
           printf("Error\n");
           exit(1);
       }
       else if (pid == 0){
           if (j ==0 ){
               close(fd[1]);
               execute();
               close(fd[0]);
               return 0;
           }
            close(fd[0]);
            distribute();
            close(fd[1]);
            return 0;
       }
    }
    pid_t child;
    int status;
    for (int i = 0; i < 4;  i++) {
        child = wait(&status);
    }
    close(fd[0]);
    close(fd[1]);
    return 0;
}
void distribute(int i, int fd){
    DIR *dirp;
    struct dirent *dp;
    
    
    dirp = opendir("directori_" + i);
    if (directori_i == NULL){
        close(fd);
        exit(1);
    }
    while ((dp = readdir(dirp)) == NULL) {
        if (*strcmp(dp->d_name, ".") == 0 ||*strcmp(dp->d_name, "..") == 0 )
        continue;
        if (write(fd, dp->d_name, NAME_SIZE) != NAME_SIZE){
            perror("error writing");
            close(fd);
            exit(1);
        }
    }
    return;
}
void execute(int fd) 
{
    int pid;
    char name[NAME_SIZE];
    while(read(fd, name, NAME_SIZE) == 20){
        pid = fork();
        switch(pid) {
            case -1:
                perror("error\n");
                close(fd);
                break;
            case 0:
                close(fd);
                execvp(name, name, NULL);
                perror("Error\n");
                break;
            default:
                wait(NULL))
        }
    }
    return;
}
