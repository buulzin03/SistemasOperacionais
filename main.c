#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        printf("Ocorreu um erro");
        return 1;
    }

    int id = fork();

    if (id == 0)
    {
        close(fd[0]);

        char c[30];
        int opc = 0;
        while (opc != 1)
        {

            printf("\nDigite uma mensagem:  ");
            fgets(c, 30, stdin);

            fflush(stdin);
            write(fd[1], &c, 30);



            printf("Deseja sair? 1-sim, 2-nao: ");
            scanf("%d", &opc);
            fflush(stdin);
        }

        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        wait(NULL);

        char y[30];
        int nb_read;
        nb_read = -1;
        int count = 0;

        while (nb_read != 0)
        {
            //retorna o numero de bytes lidos
            nb_read = read(fd[0], &y, 30);


            //Colocando um terminador na posiçao final da linha
            y[nb_read] = '\0';

            printf("Esta eh a mensagem %d: %s", count, y);
            count++;
        }
        close(fd[0]);
    }

    return 0;
}