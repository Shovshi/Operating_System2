#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>

#define BUFFER_SIZE 1024

int copy(char *file1, char *file2, int vFlag, int fFlag)
{
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "rw");


    // File exists
    if (f2) 
    {
        if (fFlag == 0 && vFlag == 0)
        {
            fclose(f1);
            fclose(f2);
            return 1;
        }
        else if (fFlag == 0 && vFlag == 1)
        {
            printf("target file exist\n");
            fclose(f1);
            fclose(f2);
            return 1;
        }
        else if (fFlag == 1 && vFlag == 0)
        {
            f2 = fopen(file2, "w");
            char buffer[BUFFER_SIZE];
            size_t num_read = 0;

            while ((num_read = fread(buffer, 1, BUFFER_SIZE, f1)) > 0)
            {
                fwrite(buffer, 1, num_read, f2);
            }

            fclose(f1);
            fclose(f2);
            return 0;
        }
        else if (fFlag == 1 && vFlag == 1)
        {
            f2 = fopen(file2, "w");
            char buffer[BUFFER_SIZE];
            size_t num_read = 0;

            while ((num_read = fread(buffer, 1, BUFFER_SIZE, f1)) > 0)
            {
                fwrite(buffer, 1, num_read, f2);
            }

            fclose(f1);
            fclose(f2);
            printf("success\n");
            return 0;
        }
    }
    // File does not exist
    else
    {
        f2 = fopen(file2 , "w");

        if (vFlag == 1)
        {
            char buffer[BUFFER_SIZE];
            size_t num_read = 0;

            while ((num_read = fread(buffer, 1, BUFFER_SIZE, f1)) > 0)
            {
                fwrite(buffer, 1, num_read, f2);
            }

            fclose(f1);
            fclose(f2);
            printf("success\n");
            return 0;
        }
        else
        {
            char buffer[BUFFER_SIZE];
            size_t num_read = 0;

            while ((num_read = fread(buffer, 1, BUFFER_SIZE, f1)) > 0)
            {
                fwrite(buffer, 1, num_read, f2);
            }

            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
}

int main()
{
    int i;
    char *argv[10];
    char command[1024];
    char *token;
    int result;

    while (1)
    {
        printf("hello: ");
        fgets(command, 1024, stdin);
        command[strlen(command) - 1] = '\0'; // replace \n with \0

        /* parse command line */
        i = 0;
        token = strtok(command, " ");
        while (token != NULL)
        {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;

        /* Is command empty */
        if (argv[0] == NULL)
            continue;

        if (strcmp(argv[0], "copy") == 0)
        {
            if (i == 3)
            {
                result = copy(argv[1] , argv[2], 0 , 0);
            }
            else if(i == 5)
            {
                result = copy(argv[1] , argv[2], 1 , 1);
            }
            else if(i == 4)
            {
                if(strcmp(argv[3], "-f") == 0)
                {
                    result = copy(argv[1], argv[2], 0 , 1);
                }
                else
                {
                    result = copy(argv[1], argv[2], 1 , 0);
                }
            }
        }

        /* for commands not part of the shell command language */
        if (fork() == 0)
        {
            execvp(argv[0], argv);
            wait(NULL);
        }
    }
}