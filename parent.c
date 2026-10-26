#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
int desp1 [2], desp2[2], fd;
char filename [8] = {'\0'}, buffer [200] = {'\0'};

pipe(desp1);
pipe (desp2);

pid_t pid;
pid = fork();

if(pid>0)
{
close (desp1[0]);
close (desp2[1]);

write(desp1[1], "abc.txt", 7);
close (desp1[1]);

read(desp2[0], buffer, sizeof(buffer));
printf("The parent has received contents of file from child\n");
printf("The contents of the file are:\n");
printf("%s", buffer);

close (desp2[0]);
}



else
{
close(desp1[1]);
close (desp2[0]);

read(desp1[0], filename, sizeof(filename));
printf("Filename read by child process\n");
close (desp1[0]);

fd = open(filename, O_RDONLY);

read(fd, buffer, sizeof(buffer));
printf("Contents of file read by child\n");
close(fd);

write(desp2[1], buffer, sizeof(buffer));
close (desp2[1]);
}
}

