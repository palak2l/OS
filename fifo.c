a.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
	int fd, fd1;
	int i = 0;
	int ch;
	char buffer[200];
	FILE *fp;

	mkfifo("fifo1", 0666);
	
	fd = open("fifo1", O_WRONLY);
	
	printf("Enter data:\n");

	while((ch = getchar()) != '#')
	{
		buffer[i] = ch;
		i++;
	}
	buffer[i] = '#';

	write (fd, buffer, sizeof(buffer));
	close(fd);
	
	memset(buffer, '\0', sizeof(buffer));
	//Read data from fd1 descriptor
	
	fd1 = open("fifo2", O_RDONLY);
	
	read(fd1, buffer, sizeof(buffer));
	
	//file open
	fp = fopen(buffer, "r+");
	
	if (fp == NULL)
	{
	    printf("File cannot be opened\n");
	    return 1;
	}

	// read file
	char line[200];

	while (fgets(line, sizeof(line), fp) != NULL)
	{
	    printf("%s", line);
	}
	
	//file close
	fclose(fp);
	
	//fifo close
	close(fd1);

}

















b.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
	int fd, fd1;
	int i = 0;
	int lines = 0;
	int words = 0; 
	int characters = 0;
	char buffer[200];

	fd = open("fifo1", O_RDONLY);

	read(fd, buffer, sizeof(buffer));
	close(fd);
	
	printf("Received data:\n");
	printf("%s", buffer);

	for(int i = 0; buffer[i] != '#'; i++)
	{
		if(buffer[i] == '\n') {
			lines++;
			words++;
			characters++;
		}
		else if(buffer[i] == ' ') {
			words++;
			characters++;
		}
		else {
			characters++;
		}
	}
	
	memset(buffer, '\0', sizeof(buffer));

	FILE *fp;

	fp = fopen("text.txt", "w+");
	
	fprintf(fp, "character count : %d \n", characters);
	fprintf(fp, "word count : %d \n", words);
	fprintf(fp, "lines count : %d \n", lines);
	
	fclose(fp);
	
	mkfifo("fifo2", 0666);
	
	fd1 = open("fifo2", O_WRONLY);
	
	write(fd1, "text.txt", 8);
	close(fd1);
}




