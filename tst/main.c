#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int byte_read;

void get_next_line(int fd)
{
	char *buff;
    buff = malloc(4 * sizeof(char));
	byte_read = read(fd,buff,3);
    if(byte_read == -1)
    
    {
             printf("not read file ");
    }
    buff[byte_read] = '\0';
	printf("%d\n%s",byte_read , buff);
    
    
    free(buff);

}


int main()
{
	int fd = open("file.txt",O_CREAT |O_RDONLY,0664);
	
	if(fd == -1)
	{

		printf("not open");
        return 1;
	}
	
	get_next_line(fd);
    
   close(fd);
}


