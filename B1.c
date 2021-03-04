#include <My_head.h>
struct msgbuf{
    long mtype;
    char mtext[1024];

};
int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int msgid=msgget(2333,0666|IPC_CREAT);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf m;
    memset(&m,0,sizeof(m));
    while(1){
        int ret=msgrcv(msgid,&m,sizeof(m.mtext),0,0);//类型1是自己的输入
        ERROR_CHECK(ret,-1,"msgrcv");
        if(m.mtype==1){
            puts("我说：");
            puts(m.mtext);
            memset(&m,0,sizeof(m));

        }
        else if(m.mtype==2){
            puts("                                            对方说:");
            printf("                                                ");
            puts(m.mtext);
            memset(&m,0,sizeof(m));

        }
        else if(m.mtype==3){
            int ret=msgctl(msgid,IPC_RMID,NULL);
            ERROR_CHECK(ret,-1,"msgctl");
            puts("聊天结束");
            pid_t pid;
            pid_t ppid;
            // pid=getpid();
            //     //ppid=getppid();
            //         //kill(pid,SIGKILL);
            //             //kill(ppid,SIGKILL);
                             break;
            //                     
        }


    }return 0;
}
