#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>


void Sort(int a[], int n, int order)
{
    int i, j, temp;
    for(i=0; i<=n-1 ; i++)
    {
        for(j=i+1; j<n; j++)
        {
                        if((order == 1 && a[i] > a[j]) || (order == 2 && a[i] < a[j])) 
                        {
                                temp = a[i];
                                a[i] = a[j];
                                a[j] = temp;
            }
        }
    }
}   
int main()
{
    pid_t pid;           //unsigned int
    int status;
    int i=10;
    int a[] = {5,2,8,1,9};
    int n = 5;
    int x;
    
    pid=fork();
    



    if(pid==0)
    {
        //sleep(2);
        i=i*10;
        
        printf("\n I value in Child =%d",i);
        printf("\n This is child process with id =%d",getpid());
        printf("\n child's parent process with id =%d",getppid());
        
        Sort(a, n, 1);
        printf("\n Array in Ascending order: ");
        for(x=0; x<n; x++){
                printf("%d ", a[x]);
            }
            printf("\n");
            exit(0);
    }
    else
    {
        sleep(2);
        system("ps");
        wait(&status);
        system("ps");
        i=i+5;
        
        printf("\n I value in Parent =%d",i);
        printf("\n This is Parent process with id =%d",getpid());
        printf("\n Parent's child process with id =%d",pid);
        
        Sort(a, n, 2);
        printf("\n Array in Descending order: ");
        for(x=0; x<n; x++){
                printf("%d ", a[x]);
            }
            printf("\n");
    }

}


