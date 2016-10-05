// @real_slacker007
// Enumerate UNIX Systems

#include <unistd.h>  // Current PID & PPID Library
#include <stdio.h>   // I/O
#include <stdlib.h>  // Memory Allocation 
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> // File Handling
#include <dirent.h>  // Directory Handling
#include <string.h> // String Functions

#define MAX_PID 50  // Size of buffer to read the MAX PID for the system
#define MAX_LN 50 // Max size of data for process attribute

int get_process_info(char *test); // Enumerate Process info
int lst_procs();

struct Proc_Info{
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
	struct Proc_Info *next;	// Pointer to the next entry
};

struct Proc_Info *top_of_list; // This is the top of the list 
struct Proc_Info *list_location; // This is the location during list operations
	
int main(void){
	int cnt;
	DIR *dir;
	struct dirent *ent;
	
	char p_arry[5100][20];
	int p_cnt = 0;

        //Linked List 
	top_of_list = malloc(sizeof(struct Proc_Info));
	top_of_list -> next = 0;
	//Initialize L-List w/ dummy vals
        strcpy(top_of_list -> p_name, "..");
        strcpy(top_of_list -> p_state, "..");
        strcpy(top_of_list -> p_thread_grp, "..");
        strcpy(top_of_list -> p_pid, "..");
        strcpy(top_of_list -> p_ppid, "..");
        strcpy(top_of_list -> p_tracer_pid, "..");
        strcpy(top_of_list -> p_threads, "..");
        strcpy(top_of_list -> p_fd_size, "..");
        strcpy(top_of_list -> p_uid, "..");
        strcpy(top_of_list -> p_gid, "..");
        strcpy(top_of_list -> p_vmPeak, "..");
        strcpy(top_of_list -> p_vmSize, "..");
        strcpy(top_of_list -> p_vmLck, "..");
        strcpy(top_of_list -> p_vmHWM, "..");
        strcpy(top_of_list -> p_vmRSS, "..");
        strcpy(top_of_list -> p_vmData, "..");
        strcpy(top_of_list -> p_vmStk, "..");
        strcpy(top_of_list -> p_vmExe, "..");
	strcpy(top_of_list -> p_vmLib, "..");
	strcpy(top_of_list -> p_vmPTE, "..");

	pid_t p_id;   // var for current pid of this process
	pid_t pp_id; // var for parent pid of this process
	p_id = getpid(); // current pid
	pp_id = getppid(); // parent pid 

	printf("Current Process -> PID: %d PPID %d\n", p_id, pp_id); //dbg
//	char *test = "/proc/1/status"; // Dbg
	//printf("Dbg1 %d\n", 1);
	//get_process_info(test);
	//printf("Dbg2 %d\n", 2);
	//lst_procs();
	//printf("DBG: %d\n", 3);
	int ctrl = 1; 
	dir = opendir("/proc/");
	while ((ent = readdir(dir)) != NULL){	
		if (isdigit(*ent->d_name)){
		//(void)closedir(dir);
		char temp1[20] = "/proc/";
		strcat(temp1, ent->d_name);
		strcat(temp1, "/status");
		strcpy(p_arry[p_cnt], temp1);
		p_cnt += 1;}}
	(void)closedir(dir);		
	
	for (int i = 0; i < p_cnt - 1; i++){
		get_process_info(p_arry[i]);}

return 0;
}
/*
int lst_procs(){
	DIR *dp;
	struct dirent *eptr;
	int ctr = 0;
        int sys_max_pid; // max int value for a pid on current system
	int fd = 0; // file handle
	char pid_buffer[MAX_PID];  // buffer to read contents of pid_max file
	ssize_t n  = 0; // variable for return val of file read function

        // Get the max # of running processes possible for this sys
	printf("DBG: %d\n", 4);
        fd  = open("/proc/sys/kernel/pid_max", O_RDONLY);
	if (fd == -1){
		printf("Open %d\n", 0);}
	else
		printf("FD = %d\n", fd);

	n = read(fd, pid_buffer, MAX_PID);
	close(fd);
	printf("Bytes Read: %d DATA: %s", (int) n,  &pid_buffer);
	sys_max_pid = atoi(pid_buffer); // convert the string val of pid to an INT
	
	char process_dirs[sys_max_pid + 1]; // an array with max number of entries set to value of max num of pids
	printf("MAX: %d\n", sys_max_pid);
	dp = opendir ("/proc/");
	if (dp != NULL){
		printf("DBG: %d\n", 5);
		while (eptr = readdir (dp) != NULL){
			printf("In while %d", ctr);
			if (isdigit(*eptr->d_name)){ // check if integer is in the dir name
				char p_dir[15] = "/proc/"; 
				strcat(p_dir, eptr->d_name); // combine root proc dir with subdir of process
				process_dirs[ctr] = p_dir; // append proc dir to array
				printf("--->%s\n", process_dirs[ctr]); //Dbg
				printf("p_dir: %s\n", p_dir);
				printf("pointer: %s\n", eptr->d_name);
				ctr += 1;}}
		(void) closedir(dp);}
	else{
		perror ("Unable to open Dir");
		printf("ERROR %d", 1);}
return 0;
}
*/
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

        char line_buff[250];
        FILE *fp = fopen(test, "r");
	FILE *fp2 = fopen("enum_data.txt", "a+");
	int ret = 0;

        while (fgets(line_buff, sizeof(line_buff), fp) != NULL){
                if (!feof(fp)){
			if(strstr(line_buff, nm) != NULL){
				fputs(line_buff, fp2);}
                	else if(strstr(line_buff, st) != NULL){
                        	fputs(line_buff, fp2);}
			else if(strstr(line_buff, pid) != NULL){
				fputs(line_buff, fp2);}
		//else if(strstr(line_buff, tid) != NULL){
			//strcpy(list_location -> p_thread_grp, line_buff);
		//	fprintf(fp2, line_buff);}
		}
		else {
			fclose(fp);
			fclose(fp2);
			return 0;}
	}
		/*
	 	else if(strstr(line_buff, pid) != NULL){
			strcpy(list_location -> p_pid, line_buff);}
		else if(strstr(line_buff, ppid) != NULL){
			strcpy(list_location -> p_ppid, line_buff);}
		else if(strstr(line_buff, tpid) != NULL){
			strcpy(list_location -> p_tracer_pid, line_buff);}
		else if(strstr(line_buff, uid) != NULL){
			strcpy(list_location -> p_uid, line_buff);}
		else if(strstr(line_buff, gid) != NULL){
			strcpy(list_location -> p_gid, line_buff);}
		else if(strstr(line_buff, fsz) != NULL){
			strcpy(list_location -> p_fd_size, line_buff);}
		else if(strstr(line_buff, thr) != NULL){
			strcpy(list_location -> p_threads, line_buff);}
		else if(strstr(line_buff, vpk) != NULL){
			strcpy(list_location -> p_vmPeak, line_buff);}
		else if(strstr(line_buff, vsz) != NULL){
			strcpy(list_location -> p_vmSize, line_buff);}
		else if(strstr(line_buff, vlk) != NULL){
			strcpy(list_location -> p_vmLck, line_buff);}
		else if(strstr(line_buff, vhw) != NULL){
			strcpy(list_location -> p_vmHWM, line_buff);}
		else if(strstr(line_buff, vrs) != NULL){
			strcpy(list_location -> p_vmRSS, line_buff);}
		else if(strstr(line_buff, vdd) != NULL){
			strcpy(list_location -> p_vmData, line_buff);}
		else if(strstr(line_buff, vstk) != NULL){
			strcpy(list_location -> p_vmStk, line_buff);}
		else if(strstr(line_buff, vexe) != NULL){
			strcpy(list_location -> p_vmExe, line_buff);}
		else if(strstr(line_buff, vlib) != NULL){
			strcpy(list_location -> p_vmLib, line_buff);}
		else if(strstr(line_buff, vpte) != NULL){
			strcpy(list_location -> p_vmPTE, line_buff);}}*/

return 0;
}







