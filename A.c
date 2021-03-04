#include <My_head.h>
#include<time.h>
int fdr;
int fdw;
pid_t pid;
typedef struct shareM{
    int shmtype;
    char str[1024];

}SHM;

int My_Sh_send(char *str,int type){
    int shmid=shmget(6666,4096,S_IRUSR|S_IWUSR|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    SHM *p_addr=(SHM *)shmat(shmid,NULL,0);
    memset(p_addr->str,0,1024);
    strcpy(p_addr->str,str);
    p_addr->shmtype=type;

}

void sigdel(int signum){
    close(fdw);
    close(fdr);
    My_Sh_send("有事忙，下次聊",3);
    kill(pid,SIGKILL);
    // pid_t ppid=getppid();
    //     //kill(ppid,SIGKILL);
    //        // My_Sh_send("有事忙下次聊",3);
    //            //unlink("1.fifo");
    //                //unlink("2.fifo");
    //
    return;
    //                    
}

int flag=0;
int main(int argc,char *argv[])
{  time(NULL);
    pid=getpid();
    signal(SIGINT,sigdel);
    ARGS_CHECK(argc,3);//chat1 1.pipe 2.pipe
    fdr=open(argv[1],O_RDONLY);
    fdw=open(argv[2],O_WRONLY);
    puts("对话连接中。。。。");
    time_t t;
    t=time(&t);
    printf("现在的时间是:%s\n对方成功进入对话！！！\n",ctime(&t));
    char str[1024]={0};
    char buf[128]={0};
    fd_set rdset;
    struct timeval timeout;
    while(1){
        t=time(&t);
        timeout.tv_sec=60;
        timeout.tv_usec=500000;
        FD_ZERO(&rdset);
        FD_SET(fdr,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        int sret= select(fdr+1,&rdset,NULL,NULL,&timeout);
        if(sret==0){
            puts("超时，对话结束");
            My_Sh_send("超时，对话结束",3);
            break;

        }
        else {
            if(FD_ISSET(fdr,&rdset)){
        //        puts("他/她:");
                memset(str,0,1024);
                int ret= read(fdr,str,1024);
                if(ret==0){
                    puts("对方结束了对话");
            //        puts(str);
                    My_Sh_send("有事忙，下次聊",3);
                    break;

                }
                My_Sh_send(str,2);
             //   puts(str);

            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                memset(str,0,1024);
    //            puts("我");
                int ret;
               // write(fdw,ctime(&t),strlen(ctime(&t)));
                ret= read(STDIN_FILENO,str,1024);

                if(ret==0){
                    puts("自己退出了对话");
                    write(fdw,"有事要忙，下次再聊\n",128);
                    My_Sh_send("有事忙，下次聊",3);
                    break;
                }
                // write(fdw,"我说")
               strcat(str,"                              ");
                strcat(str,ctime(&t));
                write(fdw,str,strlen(str));
                My_Sh_send(str,1);
                printf("\n");
            }
        }

    }
    close(fdw);
    close(fdr);
    return 0;
}

