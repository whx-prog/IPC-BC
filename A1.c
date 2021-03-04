#include <My_head.h>
typedef struct shareM{
    int shmtype;
    char str[1024];
}SHM;
int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int shmid=shmget(6666,4096,S_IRUSR|S_IWUSR|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    SHM *p_addr=(SHM *)shmat(shmid,NULL,0);
    while(1){
   // memset(p_addr->str,0,1024);
    if(p_addr->shmtype==1){
   // strncpy(p_addr->str,"How are you",1024);
    puts("我说");
    puts(p_addr->str);
    memset(p_addr,0,4096);
    }else if(p_addr->shmtype==2){
        puts("                                                  对方说");
        printf("                                                   ");
        puts(p_addr->str);
        memset(p_addr,0,4096);
    }else if(p_addr->shmtype==3){
        puts("聊天结束");
        shmctl(shmid,IPC_RMID,NULL);
        pid_t ppid;
        pid_t pid;
        //ppid=getppid();
       // kill(ppid,SIGKILL);
       //pid=getpid();
       //kill(pid,SIGKILL);
        break;
    }
}
   return 0;
}
