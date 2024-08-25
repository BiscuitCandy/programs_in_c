#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/resource.h>

void exec_child(char* argv[]);

typedef struct rusage resusg;
typedef struct timeval tmvl;

int main(int argc, char *argv[]) {

     pid_t pid;
     resusg usage;
     tmvl strt_tm, end_tm;
     
     int status;
     double usr_tm, sys_tm, elspd_tm;
     
     if (argc < 2) {
     
     	fprintf(stderr, "Usage: %s cmd [args]\n", argv[0]);
     	return -1;
     	
     }
     
     
     gettimeofday(&strt_tm, NULL);
     pid = fork();
     
     if (pid == 0) {
     
     	// child process
     	exec_child(argv);
     
     }
     
     else if (pid < 0) {
     
     	fprintf(stderr, "ERROR: FORK\n");
     	return -1;
     
     }
     
     else {

		wait4(pid, &status, 0, &usage);

		gettimeofday(&end_tm, NULL);


		usr_tm = (double)usage.ru_utime.tv_sec + (double)usage.ru_utime.tv_usec/1000000;

		sys_tm = (double)usage.ru_stime.tv_sec + (double)usage.ru_stime.tv_usec/1000000;

		elspd_tm = (double)(end_tm.tv_sec - strt_tm.tv_sec) + (double)(end_tm.tv_usec - strt_tm.tv_usec)/1000000;

		fprintf(stdout, "USER CPU TIME: %.6f\n", usr_tm);
		fprintf(stdout, "SYSTEM CPU TIME: %.6f\n", sys_tm);
		fprintf(stdout, "ELAPSED WALL CLOCK TIME: %.6f\n", elspd_tm);
	
	}     
	

     return 0;
     
}

void exec_child(char* argv[]) {

	execvp(argv[1], &argv[1]);
	fprintf(stderr, "ERROR: EXECVP\n");

}
