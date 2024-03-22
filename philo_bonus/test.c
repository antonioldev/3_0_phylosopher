#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
	int i;
	int test = 0;
	pid_t id;

	sem_t *fork_avaible = sem_open("/my_semaphore", O_CREAT | O_RDWR, 0644, 5);
	for (i = 0; i < 5; i++)
	{
		id = fork();
		if (id == -1)
			exit(EXIT_FAILURE);
		if (id == 0)
		{
			printf("--%i child process %d\n",i, getpid());//test
			//sem_t *test = sem_open("/my_semaphore", O_CREAT | O_RDWR, 0644, 5);
			test++;
			printf("%d\n", test);
			return(0);
			//exit(EXIT_SUCCESS);
		}
		else if (id > 0)
		{
			waitpid(id, NULL, 0);
			printf("A test\n");
			usleep(1000000);
			printf("The first test is ........  %i\n", test);
			
		}
	}
	//printf("The first test is ........  %i\n", test);
	sem_close(fork_avaible);
	sem_unlink("/my_semaphore");

}//https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/?ref=lbp