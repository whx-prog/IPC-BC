#include <My_head.h>

int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int shmid=shmget(IPC_PRIVATE,1024,S_IRUSR|S_IWUSR);
    ERROR_CHECK(shmid,-1,"shmget");
    if(fork()){
    char *p_addr=(char *)shmat(shmid,NULL,0);
        memset(p_addr,0,1024);
        strncpy(p_addr,"How are you",1024);
        printf("parent's write:%s\n",p_addr);
        sleep(2);
        wait(NULL);
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);

    }
    else {
        sleep(5);
        char *c_addr=(char *)shmat(shmid,NULL,0);
        printf("child read:%s\n",c_addr);
        exit(0);
    }
    return 0;
}

