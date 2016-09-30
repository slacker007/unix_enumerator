// @real_slacker007
// Enumerate UNIX Systems

#include <unistd.h>  // Current PID & PPID Library
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> // File Handling
#include <string.h> // String Functions

#define MAX_PID 50  // Size of buffer to read the MAX PID for the system
#define MAX_LN 50 // Max size of data for process attribute

int get_process_info(char *test); // Enumerate Process info


typedef struct{
	char p_name[MAX_LN];	// Name of command run by process
	char p_state[MAX_LN];	// State of process
	char p_thread_grp[MAX_LN];	// thread group ID
	char p_pid[MAX_LN];	// actual process ID
	char p_ppid[MAX_LN];	// parent process ID
	char p_tracer_pid[MAX_LN];	// PID of tracing process
	char p_threads[MAX_LN];	// # of threads in thread group
	char p_fd_size[MAX_LN];	// # of file descriptor slots currently allocated
	char p_uid[MAX_LN];	// real, effective UIDS
	char p_gid[MAX_LN];	// real, effective GIDS
	char p_vmPeak[MAX_LN];	// Peak Virtual Mem size
	char p_vmSize[MAX_LN];	// Current Virtual Mem Size
	char p_vmLck[MAX_LN];	// Locked Mem
	char p_vmHWM[MAX_LN];	// Peak Resident set size
	char p_vmRSS[MAX_LN];	// Current Resident set size
	char p_vmData[MAX_LN];	// Data Segment Size
	char p_vmStk[MAX_LN];	// Stack Size
	char p_vmExe[MAX_LN];	// Text Size
	char p_vmLib[MAX_LN];	// Shared Lib Size
	char p_vmPTE[MAX_LN];	// Size of page table
} Proc_Info;


int main(void){
	int fd = 0; // file handle
	char pid_buffer[MAX_PID];  // buffer to read contents of pid_max file
	ssize_t n  = 0; // variable for return val of file read function

	pid_t p_id;   // var for current pid of this process
	pid_t pp_id; // var for parent pid of this process
	p_id = getpid(); // current pid
	pp_id = getppid(); // parent pid 

	printf("Current Process -> PID: %d PPID %d\n", p_id, pp_id); //dbg
	
	fd  = open("/proc/sys/kernel/pid_max", O_RDONLY);
	/*if (fd == -1)
		errExit("open");*/
	n = read(fd, pid_buffer, MAX_PID);
	printf("Bytes Read: %d DATA: %s\n", (int) n,  &pid_buffer);
	char *test = "/proc/1/status";
	get_process_info(test);
	
	int system_max_pid;
	system_max_pid = atoi(pid_buffer); // convert the string value of pid to an INT
return 0;
}

int get_process_info(char *test){
	
	// Process Attributes
        char *nm = "Name:";
        char *st = "State:";
        char *tid = "Tgid:";
        char *pid = "Pid:";
        char *ppid = "PPid:";
        char *tpid = "TracerPid:";
        char *uid = "Uid:";
        char *gid = "Gid:";
        char *fsz = "FDSize:";
        char *thr = "Threads:";
        char *vpk = "VmPeak:";
        char *vsz = "VmSize:";
        char *vlk = "VmLck:";
        char *vhw = "VmHWM:";
        char *vrs = "VmRSS:";
        char *vdd = "VmData:";
        char *vstk = "VmStk:";
        char *vexe = "VmExe:";
        char *vlib = "VmLib:";
        char *vpte = "VmPTE:";

        char line_buff[50];
        FILE* fp = fopen(test, "r");
        Proc_Info process;
        while (fgets(line_buff, sizeof(line_buff), fp) != NULL){
                if(strstr(line_buff, nm) != NULL){
                        strcpy(process.p_name, line_buff);
                        printf("%s", process.p_name);}
                else if(strstr(line_buff, st) != NULL){
                        strcpy(process.p_state, line_buff);
                        printf("%s", process.p_state);}
		else if(strstr(line_buff, tid) != NULL){
			strcpy(process.p_thread_grp, line_buff);
			printf("%s", process.p_thread_grp);}
                
        }


return 0;
}







