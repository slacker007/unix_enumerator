// @real_slacker007
// Enumerate UNIX Systems

#include <unistd.h>  // Current PID & PPID Library
#include <stdio.h>   // I/O
#include <stdlib.h>  // Memory Allocation 
#include <fcntl.h>
#include <stdbool.h> // Boolean Functions
#include <sys/types.h>
#include <sys/stat.h> // File Handling
#include <dirent.h>  // Directory Handling
#include <string.h> // String Functions

#define MAX_PID 50  // Size of buffer to read the MAX PID for the system
#define MAX_LN 24 // Max size of filename for process

int get_process_info(char *test); // Enumerate Process info
int get_process_mem_stats(char *pid); // Enumerate Proc Mem Stats
bool startsWith(const char *str, const char *pre); // Search Line for String



bool startsWith(const char *str, const char *pre){	// Function to search string from the beginning looking for prefix matches
	size_t lenpre = strlen(pre), // Get the length of string prefix
	       lenstr = strlen(str); // Get the lenght of full string
	return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0; // compare length of prefix and full string then compare strings 
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
      
        char line_buff[250];	// Buffer for lines read from file
	char full_p[55];	// Buffer for path to proc status
	sprintf(full_p, "%s/status\0",test); // Append filename (status to prev path
        FILE *fp = fopen(full_p, "r");	// Declaration & Initialization of file pointer
	FILE *fp2 = fopen("enum_data.txt", "a+");    // Declaration & Initialization of output file pointer

	// Loop though open file and test each line with if statements
        while (fgets(line_buff, sizeof(line_buff), fp) != NULL){ 
                if (!feof(fp)){	// Ensure End of File has not been reached
			// Extracts Certain Process Data and writes to output file (fp2)
			if(startsWith(line_buff, nm) != NULL){
				fputs(line_buff, fp2);}
                	else if(startsWith(line_buff, st) != NULL){
                        	fputs(line_buff, fp2);}
			else if(startsWith(line_buff, pid) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, ppid) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, tid) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, tpid) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, uid) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, gid) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, fsz) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, thr) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vpk) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vsz) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vlk) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vhw) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vrs) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vdd) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vstk) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vexe) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vlib) != NULL){
				fputs(line_buff, fp2);}
			else if(startsWith(line_buff, vpte) != NULL){
				fputs(line_buff, fp2);}}
		else { // if End of File is reached 
			fclose(fp);  // Close process file
			fclose(fp2); // Close output file
			return 0;}}

	fputs("---------------------------------------\n", fp2);  // Write line to seperate process info
return 0; // Exit Function
}

int get_process_mem_stats(char *pid){
	char p_strg[50];
	char l_buff[150];
	int fd;
	int column = 0; // column for proc mem stats
	int max_col = 65;
	ssize_t n;	// variable for amount of bytes read into buffer

	sprintf(p_strg, "%s/statm\0", pid);
	FILE *fp3 = fopen(p_strg, "r"); // Open File for Process Mem Stats
	FILE *fp2 = fopen("enum_data.txt", "a+");

	fd = open(pid, O_RDONLY); // open process file for (pid) return file descriptor into (fd)
		if (fd == -1){
			printf("Error, File Open");}
	
	n = read(fd, l_buff, sizeof(l_buff)); // Read in Data from process stat file

	// Loop though open file and test each line with if statements
        if (fgets(l_buff, sizeof(l_buff), fp3) != NULL){ 
		char *prsd = strtok(l_buff, " "); // Break Memory Stats into Columns
		while (prsd != NULL){ // Continue until no more data is gone
			char col_name[max_col]; // Create local variable of size (max_col)
			switch (column){ // test column variable to determine which column data belongs
				// case statements to compare values against value of column
				// when case is met copy  string into (col_name) variable
				case 0:
					strcpy(col_name, "Process Size:\t");
					break;
				case 1:
					strcpy(col_name, "Size of Process in Physical Memory:\t");
					break;
				case 2:
					strcpy(col_name, "Shared Memory:\t");
					break;
				case 3:
					strcpy(col_name, "Size of Loaded Executable Code:\t");
					break;
				case 4:
					strcpy(col_name, "Size of Shared Mapped Libraries:\t");
					break;
				case 5:
					strcpy(col_name, "Memory used by the process for stack:\t");
					break;
				case 6:
					strcpy(col_name, "# of Dirty Pages pages of memory modified by the executable:\t");
					break;
			}
			char write_line[65];
			sprintf(write_line, "%s%s\n", col_name, prsd);
			fputs(write_line, fp2);
			column += 1;
			prsd = strtok(NULL, " ");
		}
		fputs(p_strg, fp2);
		fputs("\n---------------------------------------\n", fp2);  // Write line to seperate process info
		fclose(fp2);}
return 0;
}

int main(void){

	DIR *dir;	// Variable Declaration for Directory
	DIR *dp;	
	struct dirent *ent; // Variable Declaration for Directory struct
	int p_cnt = 0; // Counter to track number of processes
        int sys_max_pid; // max int value for a pid on current system
	int fd = 0; // file handle
	char pid_buffer[MAX_PID];  // buffer to read contents of pid_max file
	ssize_t n  = 0; // variable for return val of file read function
	
        // Get the max # of running processes possible for this sys
        fd  = open("/proc/sys/kernel/pid_max", O_RDONLY);
	n = read(fd, pid_buffer, MAX_PID); // Read Max_Pid from file
	close(fd); // Close File 
	sys_max_pid = atoi(pid_buffer); // convert the string val of pid to an INT
	char p_arry[sys_max_pid][24]; // MultiDimensional array to hold processes
	printf("MAX PID VALUE: %s", &pid_buffer); // Debug STMT to print MAX # of Pids
	
	// Get Current PID
	pid_t p_id;   // var for current pid of this process
	pid_t pp_id; // var for parent pid of this process
	p_id = getpid(); // current pid
	pp_id = getppid(); // parent pid 
	printf("Current Process -> PID: %d PPID %d\n", p_id, pp_id); // DBG STMT

	// Get process directories
	dir = opendir("/proc/");
	while ((ent = readdir(dir)) != NULL){	// Loop through process Directory
		if (isdigit(*ent->d_name)){	// If the Directory is made up of numeric digits
		char temp1[20] = "/proc/"; 	// Declaration & Initialization of temp1 Arrary of processes 
		strcat(temp1, ent->d_name);	// Append the process ID to the root path
		strcpy(p_arry[p_cnt], temp1);	// Append final path to the Array at position (p_cnt)
		p_cnt += 1;}}			// Incriment to the next position in array 
	(void)closedir(dir);			// Close '/proc/' Directory
	
	for (int i = 0; i < p_cnt - 1; i++){	// For loop to enumerate process information for each value in process array
		get_process_info(p_arry[i]);	// Call to get_process_info function that passes in absolute path to process
		get_process_mem_stats(p_arry[i]);
	}	 

return 0;					// return (exit from function)
}
