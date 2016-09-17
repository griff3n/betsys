/*
 * myls.c
 *
 *  Created on: 08.06.2016
 *      Author: peter
 */
#define _BSD_SOURCE
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>

void printFile(char *name);
char *path;

int main(int argc, char **argv) {

	int aflag = 0;
	int lflag = 0;
	int index;
	int c;
	struct dirent *dirptr;

	opterr = 0;
	while ((c = getopt (argc, argv, "lal::")) != -1)
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		case '?':
			if (isprint (optopt)) {
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			} else {
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			}
			return 1;
		default:
			abort ();
		}
	index = optind;
	if( index < argc) {
		path = argv[index];
	} else {
		path = getenv("PWD");
	}
	printf ("aflag = %d, lflag = %d\n",aflag, lflag);
	printf ("Path %s\n", path);
	DIR *dir = opendir(path);
	if(dir == NULL) {
		fprintf(stderr,"Fehler beim oeffnen der Datei.");
		return EXIT_FAILURE;
	}
	dirptr = readdir(dir);
	while(dirptr != NULL) {
		char *filename = (*dirptr).d_name;
		if(aflag == 1 && lflag == 1) {
			printFile(filename);
		}
		else if(lflag == 1) {
			if(filename[0] != '.') {
				printFile(filename);
			}
		}
		else if(aflag == 1) {
			printf ("%s\n", filename);
		} else {
			if(filename[0] != '.') {
				printf ("%s\n", filename);
			}
		}
		dirptr = readdir(dir);
	}
	if (closedir(dir) == -1) {
		fprintf(stderr,"Fehler beim Schliessen von %s\n", path);
	}
	return 0;
}

void printFile(char *name) {
	char *dateiendung = strrchr(name, '.');
	struct stat sb;
	char l_rwx[10];
	char rwx[] = "rwxrwxrwx";
	int bits[] = {
			S_IRUSR,S_IWUSR,S_IXUSR,   /* Zugriffsrechte User    */
			S_IRGRP,S_IWGRP,S_IXGRP,   /* Zugriffsrechte Gruppe  */
			S_IROTH,S_IWOTH,S_IXOTH    /* Zugriffsrechte der Rest */
	};
	if (lstat(name, &sb) == -1) {
		perror("Fehler beim Dateiinformationen auslesen.");
	}
	if(sb.st_mode & S_IEXEC) {
		printf ("\033[0;0;31m %s \033[0m\t\t", name);
	} else if (dateiendung != 0 && !strcmp(dateiendung, ".c")) {
		printf ("\033[0;0;32m %s \033[0m\t\t", name);
	} else {
		printf ("%s\t\t", name);
	}
	if(S_ISBLK(sb.st_mode)) {
		printf("b");
	} else if(S_ISCHR(sb.st_mode)) {
		printf("c");
	} else if(S_ISDIR(sb.st_mode)) {
		printf("d");
	} else if(S_ISFIFO(sb.st_mode)) {
		printf("p");
	} else if(S_ISLNK(sb.st_mode)) {
		printf("l");
	} else if(S_ISREG(sb.st_mode)) {
		printf("-");
	} else if(S_ISSOCK(sb.st_mode)) {
		printf("s");
	} else {
		printf("-");
	}
	for(int i = 0; i < 9; i++) {
		/* wenn nicht 0, dann gesetzt */
		if(sb.st_mode & bits[i]) {
			l_rwx[i]=rwx[i];  /*r,w oder x*/
		}
		else {
			l_rwx[i] = '-';
		}
	}
	l_rwx[9]='\0';
	printf("%s ",l_rwx);
	printf("%ld ", (long) sb.st_nlink);
	printf("%lld bytes ",(long long) sb.st_size);
	printf("%s", ctime(&sb.st_mtime));
}
