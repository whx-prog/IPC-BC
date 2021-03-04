#include <My_head.h>
#include<time.h>
int fdw;
int fdr;
pid_t pid;
struct msgbuf{
    long mtype;
    char mtext[1024];

};
int My_msgsend(char *str,int msgtype);
void sigdel(int signum){
    // My_msgsend("有事忙，下次聊",3);
         close(fdw);
             close(fdr);
                 My_msgsend("有事忙，下次聊天",3);
                     kill(pid,SIGKILL);
    //                    // pid_t ppid=getppid();
    //                       // kill(ppid,SIGKILL);
    //                           return;
    //                           
}

int My_msgsend(char *str,int msgtype){
    int msgid=msgget(2333,IPC_CREAT|0666);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msg;
    memset(&msg,0,sizeof(msg));
    msg.mtype=msgtype;
    strcpy(msg.mtext,str);
    int ret=msgsnd(msgid,&msg,strlen(msg.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");

}

int main(int argc,char *argv[])
{  time(NULL);
    pid=getpid();
    signal(SIGINT,sigdel);
    ARGS_CHECK(argc,3);//chat2 1.pipe 2.:pipe
    fdw=open(argv[1],O_WRONLY);
    fdr=open(argv[2],O_RDONLY);
    puts("对话链接中。。。");
    time_t t;
    t=time(&t);
    printf("现在的时间是:%s\n对方成功进入对话！！！\n",ctime(&t));
    char str[1024]={0};
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
            My_msgsend("有事忙，下次聊",3);
            break;

        }
        else{
            if(FD_ISSET(fdr,&rdset)){
               // puts("他/她:");
                memset(str,0,1024);
                int ret= read(fdr,str,1024);
                if(ret==0){
                    puts("对方结束了对话");
        //            puts(str);
                    My_msgsend("下次再聊",3);
                    break;

                }
                My_msgsend(str,2); 
         //       puts(str);

            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
               // puts("我:");
                memset(str,0,1024);
                int ret=  read(STDIN_FILENO,str,1024);
                if(ret==0){
                    puts("自己退出了对话");
                    write(fdw,"有要忙，下次再聊\n",128);
                    My_msgsend("有事忙，下次聊",3);
                    break;

                }
                strcat(str,ctime(&t));
                write(fdw,str,strlen(str));
                My_msgsend(str,1);
                printf("\n");

            }

        }


    }
    close(fdw);
    close(fdr);
    return 0;
}
