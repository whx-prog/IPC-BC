#include <My_head.h>

int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int msgid=msgget(rand(),0600|IPC_CREAT);
    ERROR_CHECK(msgid,-1,"msgget");
    return 0;
}

