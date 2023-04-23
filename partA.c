#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>


int checkLetter(char c1 , char c2)
{
    if((c1 > 'a' && c1 < 'z') && (c2 >'A' && c2 <'Z'))
    {
        if(c2 + 32 == c1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if((c1 > 'a' && c1 < 'z') && (c2 >'a' && c2 <'z'))
    {
        if(c1 == c2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if((c1 > 'A' && c1 < 'Z') && (c2 >'a' && c2 <'z'))
    {
        if(c1 + 32 == c2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if((c1 > 'A' && c1 < 'Z') && (c2 >'A' && c2 <'Z'))
    {
        if(c1 == c2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int compare(char *file1, char *file2 , int vFlag , int iFlag)
{
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if(f1 == NULL || f2 == NULL)
    {
        printf("ERROR OPENING FILES\n");
        return 0;
    }

    char c1 , c2;

    // We are in the case where the i and v flag are both 0
    if(vFlag == 0 && iFlag == 0)
    {
        while((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2) != EOF))
        {
            if(c1 != c2)
            {
                return 0;
            }
        }
        if(((c1 = fgetc(f1)) == EOF && (c2 = fgetc(f2)) != EOF) || ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) == EOF))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    // We are in the case where the i flag is set to 0 and v flag set to 1
    if(vFlag == 1 && iFlag == 0)
    {
        printf("case v == 1 , i == 0\n");
        while((c1 = fgetc(f1)) != EOF && ((c2 = fgetc(f2)) != EOF))
        {
            printf("While iterating\n");
            printf("This is c1:%c\n" , c1);
            printf("This is c2:%c\n" , c2);
            if(c1 != c2)
            {
                printf("not equal\n");
                return 0;
            }
        }
        if((c1 = fgetc(f1)) == EOF && (c2 = fgetc(f2)) == EOF)
        {
            printf("equal\n");
            return 1;
        }
        if(((c1 = fgetc(f1)) == EOF && (c2 = fgetc(f2)) != EOF) || ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) == EOF))
        {
            printf("not equal\n");
            return 0;
        }
        else
        {
            printf("equal\n");
            return 1;
        }
    }

    // We are in the case where the v flag is set to 1 and i flag is set to 1 aswell
    if(vFlag == 1 && iFlag == 1)
    {
        while((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF)
        {
            if(!checkLetter(c1,c2))
            {
                printf("not equal");
                return 0;
            }
        }
        if(((c1 = fgetc(f1)) == EOF && (c2 = fgetc(f2)) != EOF) || ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) == EOF))
        {
            printf("not equal\n");
            return 0;
        }
        else
        {
            printf("equal\n");
            return 1;
        }
    }

    // We are in the case where i flag is set to 1 and v flag is set to 0
    if(vFlag == 0 && iFlag == 1)
    {
         while((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2) != EOF))
        {
            if(!checkLetter(c1,c2))
            {
                return 0;
            }
        }
        if(((c1 = fgetc(f1)) == EOF && (c2 = fgetc(f2)) != EOF) || ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) == EOF))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

}



int main() {
	int i;
	char *argv[10];
	char command[1024];
	char *token;
    int result;

	while (1) {
	    printf("hello: \n");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0
        
	    /* parse command line */
	    i = 0;
	    token = strtok (command," ");
	    while (token != NULL)
	    {
        printf("in second while\n");
		argv[i] = token;
		token = strtok (NULL, " ");
		i++;
	    }
	    argv[i] = NULL;

	    /* Is command empty */ 
	    if (argv[0] == NULL){
        printf("is empty\n");
		continue;
        }
       
        if (strcmp(argv[0], "cmp") == 0)
        {
            if (i == 3)
            {
                printf("Case where i = 3\n");
                result = compare(argv[1] , argv[2], 0 , 0);
            }
            else if(i == 5)
            {
                printf("Case where i = 5\n");
                result = compare(argv[1] , argv[2], 1 , 1);
            }
            else if(i == 4)
            {
                printf("Case where i = 4\n");
                if(strcmp(argv[3], "-i") == 0)
                {
                    printf("case -i\n");
                    result = compare(argv[1], argv[2], 0 , 1);
                }
                else
                {
                    printf("case -v\n");
                    result = compare(argv[1], argv[2], 1 , 0);
                }
            }
          



        }
	    /* for commands not part of the shell command language */ 
	    if (fork() == 0) { 
		execvp(argv[0], argv);
        printf("inside fork\n");
		wait(NULL);
	    }    
	}
    return result;
}
