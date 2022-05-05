#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int mysystem(const char *command){

    if (command == NULL) return 2;

    // Assumindo um maximo de 20 argumentos
    int i=0, max=20, j;
    char **exec_args = malloc(max * sizeof(char *));
    char *string, *dup = strdup(command);

    //separa uma string em argumentos
    string=strsep(&dup, " ");

    while (string!=NULL){

        if (i>=max){

            max += max*0.5;
            exec_args = realloc(exec_args, max * sizeof(char *));
        }

        exec_args[i++] = string;
        string = strsep(&dup, " ");
    }

    exec_args[i] = NULL;

    //imprime a lista de argumentos
    for(j = 0; j < i; j++){
        
        write(0, exec_args[j], strlen(exec_args[j]));
        write(0, "\n", 1);
    }

    free(exec_args);
    free(dup);
    return 1;
}


int main() {

   int readFifo = open("fifo", O_RDONLY), tamanho = 1024, max = 1024,rd, fd, i, j;
   char buffer[tamanho];
   char **exec_args = malloc(max * sizeof(char *));


   if((fd = open("log.txt", O_APPEND | O_CREAT | O_TRUNC | O_WRONLY, 0640)) == -1){

       perror("Erro ao criar o fifo");
       return 2;
   }


   for(i=0; (rd = read(readFifo, buffer, tamanho)) > 0; i++){

      if (!strncmp(buffer, "exit", 4)) break;
      //write(1, buffer, rd);
      
      //if(mysystem(buffer) == 2) perror("Erro ao separar os argumentos");
      
      if (i>=max){

            max += max*0.5;
            exec_args = realloc(exec_args, max * sizeof(char *));
        }

        exec_args[i] = buffer;




      write(fd, buffer, rd);
      write(fd, "\n", 1);
   }


   for(j=0; j< i; j++){
        
        write(0, exec_args[j], strlen(exec_args[j]));
        write(0, " ", 1);
    }

   free(exec_args);
   close(readFifo);

   return 0;
}
