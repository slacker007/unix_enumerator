// @real_slacker007
// Enumerate UNIX Systems

#include <unistd.h>  // Current PID & PPID Library
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#define MAX_PID 50  // Size of buffer to read the MAX PID for the system

main(){
	int fd = 0; // file handle
	char pid_buffer[MAX_PID];  // buffer to read contents of pid_max file
	ssize_t n  = 0; // variable for return val of file read function

	pid_t p_id;   
	pid_t pp_id;
	
	p_id = getpid();
	pp_id = getppid();

	printf("Current Process -> PID: %d PPID %d\n", p_id, pp_id);

return 0;
}


