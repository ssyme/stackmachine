#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char filename[20];
    if (argc == 2)
    {
	strcpy(filename, argv[1]);
    }
    else
    {
	puts("Expected filename as arg...");
	return 1;
    }


    FILE *fp;
    
    if (!(fp = fopen(filename, "r")))
	return 1;
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *program = malloc(fsize + 1);
    fread(program, 1, fsize, fp);
    fclose(fp);

    program[fsize] = 0;

    printf("%s\n", program);

    return 0;
}
