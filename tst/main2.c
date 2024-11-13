#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int byte_read;
char *get_next_line(int fd)
{

    char *s;
    s = malloc( 4 * sizeof(char));
    if(s == NULL)
        return NULL;
    byte_read = read(fd,s,3);
    if(byte_read <= 0)
        return NULL;
    s[byte_read] = '\0';

        return s;
    free(s);
}

int main()
{
    char *next_line;
    int count = 0;
    int fd = open("file.txt",O_RDONLY);
    if(fd == -1)
    {
        printf("not open");
    }
    while(1)
    {
        if(next_line == NULL)
            break; 
    next_line = get_next_line(fd);
    
    count++;
    printf("[%d] = \e[36m%s\e[0m\n",count,next_line);
    }
    close(fd);
}
