#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *args[]){

    if (argc>1){

        int writingEndFifo = open("fifo", O_WRONLY);

        for (int i=1 ; i<argc ; i++){
            write(writingEndFifo, args[i], strlen(args[i]));
            //write(writingEndFifo, " ", 1);
        }
        close(writingEndFifo);
    }


    return 0;
}
