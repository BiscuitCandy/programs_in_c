#include<stdio.h>
#include<time.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

typedef struct dirent d_dirent;
typedef struct stat d_stat;

int count[24] = {0};

void display_status();
int is_dir(d_dirent* );

void count_mdfd_files(const char *dir_name, time_t curr_tm) {
	
	DIR *dir;
	d_dirent *de;
	d_stat buffer_stat;
	
	time_t mdfd_tm;
	char path[128];
	char temp_path_var[200];
	
	int h;

	if ((dir = opendir(dir_name)) == NULL) {

		fprintf(stderr, "ERROR: opendir error \n");
		exit(1);

	}

	while ((de = readdir(dir)) != NULL) {
	
		snprintf(path, sizeof(path), "%s/%s", dir_name, de->d_name);

		if (lstat(path, &buffer_stat) == -1) {

		fprintf(stderr, "ERROR: stat");
		continue;

		}

		
	if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
		
			continue;
		
		}
				
	if (is_dir(de) == 1){
				
		count_mdfd_files(path, curr_tm);
	
		}
		
	else {
		
		mdfd_tm = buffer_stat.st_mtime;

		if ((curr_tm- mdfd_tm) < 3600 * 24) {

			h = (curr_tm - mdfd_tm) / 3600;
			count[h % 24]++;
			
			}
				
		}

	
	}

	closedir(dir);
}

void display_status() {

	char time_string[128];
	int i;

	for (i = 23; i > -1; i--) {
	
		clock_t temp = time(NULL) - i * 3600;
		
		strftime(time_string, 128, "%a %b %d %H:%M:%S %Y", localtime(&temp));
		
		fprintf(stdout, "%s: %d\n", time_string, count[i]);
	
	}

}

int is_dir(d_dirent* de) {

	if (de->d_type == DT_DIR) 
		return 1;
	return -1;

}

int main(int argc, char *argv[]) {
	char *dir_name = ".";

	if (argc == 2) {
		
		dir_name = argv[1];
	
	}

	count_mdfd_files(dir_name, time(NULL));
	
	display_status();

	return 0;
}
