#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd[2];
	char str_s[8];
	char* str_r=malloc(strlen(str_s)* sizeof(char));
	// make pipe descriptors
	pipe(fd);

	if(fork()>0)
	{
		//writing only in parent,so close read descriptor
		close(fd[0]);

		// sending on write-descritptor
		 printf("write string: \n");
		scanf("%s",str_s);
		// str_s[0] = 'a';
		// str_s[1] = 'n';
		// str_s[2] = 'u';
		// str_s[3] = 's';
		// str_s[4] = 'h';
		// str_s[5] = 'r';
		// str_s[6] = 'e';
		// str_s[7] = 'e';
		write(fd[1],str_s,strlen(str_s));

		printf("\nParent,send string:%s\n",str_s);
		// close the write descriptor
		close(fd[1]);
	}
	else
	{
		// child: reading only, so close the write-descriptor
		close(fd[1]);
		//now reading string 
		read(fd[0],str_r,sizeof(str_r));
		printf("\nChild, received string: %s\n", str_r);

		// close the read-descriptor
		close(fd[0]);
	}
	return 0;

}