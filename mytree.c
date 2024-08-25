#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>

typedef struct dirent d_dirent;

int listing_dir(DIR* , int, char*);
int is_dir(d_dirent* );
void display_levels(int );


int main(int argc, char* argv[]) {
	
	DIR *dir;
	
	int dir_res;
	
	if (argc < 2) {
		
		fprintf(stdout, "%s\n", ".");		
		dir = opendir(".");
		dir_res = listing_dir(dir, 0, ".");
		
	}
	
	else {
		
		fprintf(stdout, "%s\n", argv[1]);
		dir = opendir(argv[1]);
		dir_res = listing_dir(dir, 0, argv[1]);
		
	} 
	
	return 0;

}

int listing_dir(DIR* dir, int tabs, char* path) {

	d_dirent *de;
	char temp_path_var[200];
	
	int next_dir;
	

	if (dir == NULL) {
	
		fprintf(stderr, "ERROR: cannot open the directory - %s\n", path);
		return 0;
	
	}
	
	
	// de = readdir(dir);
	
	while ((de = readdir(dir)) != NULL) {
	
			// fprintf(stdout, "%s \n", de->d_name);
		
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
		
			continue;
		
		}
		
		display_levels(tabs);
		
		fprintf(stdout, "|---");
		fprintf(stdout, "%s\n", de->d_name);
		
		if (is_dir(de) == 1){
		
			strcpy(temp_path_var, path);
			strcat(temp_path_var, "/");
			strcat(temp_path_var, de->d_name);
			
			next_dir = listing_dir(opendir(temp_path_var), tabs + 1, temp_path_var);
	
		}
		

	}

}


int is_dir(d_dirent* de) {

	if (de->d_type == DT_DIR) 
		return 1;
	return -1;

}

void display_levels(int tabs) {

	int i;
	
	for (i = 0; i < tabs; i++)
		fprintf(stdout, "|   ");

}
