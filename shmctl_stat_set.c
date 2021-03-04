#include <My_head.h>

int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int shmid=shmget(12345,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    struct shmid_ds buf;
    int ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("Curuid=%d,mode=%o,size=%ld,nattch_num=%ld\n",
           buf.shm_cpid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    buf.shm_perm.mode=0666;
    ret=shmctl(shmid,IPC_SET,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("New_Mode=%o\n",buf.shm_perm.mode);
    return 0;
}

