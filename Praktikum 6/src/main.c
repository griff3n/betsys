/*
 * main.c
 *
 *  Created on: 25.05.2016
 *      Author: peter
 */
#define _GNU_SOURCE
#include <stdio.h>
//#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <dirent.h>

#include "miniz.h"
#include "queue.h"


void* readThread(void *arg);
void* kompThread(void *arg);

typedef struct job {
	char * inhalt;
	char * dateipfad;
} Job;

typedef struct joblist {
	pthread_mutex_t *mutex;
	Queue jobs;
} Joblist;

static Joblist joblist;
static int statuslt = 1;

int main(int argc, char *argv[]) {
	int theads, cauntthreads = 0, statuskt[cauntthreads];
	if(argc < 2) {
		fprintf(stderr, "Zu wenig Komandozeilenargumente.");
		return EXIT_FAILURE;
	} else if (argc == 2) {
		theads = 3;
	}
	theads = atoi(argv[2]);
	pthread_t lthread, kthread[theads];
	joblist.jobs = queue_create();
	char *dirname = argv[1];
	printf("Ordner: %s\n", dirname);
	joblist.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if(!joblist.mutex) {
		fprintf(stderr,"Fehler beim Speicher reseviren.");
		return EXIT_FAILURE;
	}
	int status = pthread_mutex_init(joblist.mutex, NULL);
	pthread_create( &lthread, NULL, &readThread, (void*)dirname );
	pthread_join( lthread, (void*)statuslt );
	for(int i = 0; i < theads; i++) {
		pthread_create( &kthread[i], NULL, &kompThread, (void*)dirname );
		pthread_join( kthread[i], NULL );
	}
	status = pthread_mutex_destroy(joblist.mutex);
	free(joblist.mutex);
}

void* readThread(void *arg) {
	FILE *file;
	char* dirname = (char*)arg;
	DIR *dir = opendir(dirname);
	struct dirent *dirptr;
	Job *job  = (Job*) malloc(sizeof(Job));
	if(!job) {
		fprintf(stderr,"Fehler beim Speicher reseviren.");
		return (void*) EXIT_FAILURE;
	}
	if(dir == NULL) {
		fprintf(stderr,"Fehler beim oeffnen der Datei.");
		return (void*) EXIT_FAILURE;
	}
	dirptr = readdir(dir);
	while(dirptr != NULL) {
		char *filename = (*dirptr).d_name;
		char *dateiendung = strrchr(filename, '.');
		if(strcmp(filename, ".") && strcmp(filename, "..") && strcmp(dateiendung, ".compr")) {
			file = fopen(filename, "r");
			if(file == NULL) {
				fprintf(stderr, "Datei konnte nicht geoeffnet werden\n.");
			} else {
				job->dateipfad = filename;
				//int i = fscanf(file,"%s", job->inhalt);
				//int *temp = "";
				char *line = NULL;
				size_t *buffersize = 0;
				int i = getline(&line,buffersize,file);
				while(i != -1) {
					getline(&line,buffersize,file);
					strcat(job->inhalt, line);
				}
				int status=pthread_mutex_lock(joblist.mutex);
				queue_insert(joblist.jobs, job);
				status=pthread_mutex_unlock(joblist.mutex);
				printf("%s\n" , filename);
				fclose(file);
			}
		}
		dirptr = readdir(dir);
		job->dateipfad = "";
		job->inhalt = "";
	}
	free(job);
	if (closedir(dir) == -1) {
		fprintf(stderr,"Fehler beim Schliessen von %s\n", dirname);
	}
	return (void*) EXIT_SUCCESS;
}

void* kompThread(void *arg) {
	char* dirname = (char*)arg;
	DIR *dir = opendir(dirname);
	Result *result;
	if(dir == NULL) {
		fprintf(stderr,"Fehler beim oeffnen der Datei.");
		return (void*) EXIT_FAILURE;
	}
	Job *job  = (Job*) malloc(sizeof(Job));
		if(!job) {
			fprintf(stderr,"Fehler beim Speicher reseviren.");
			return (void*) EXIT_FAILURE;
		}
	while(joblist.jobs->head != 0 || statuslt != 0) {
		int status=pthread_mutex_lock(joblist.mutex);
		job = queue_head(joblist.jobs);
		status=pthread_mutex_unlock(joblist.mutex);
		queue_delete(joblist.jobs);
		result = compress_string(job->inhalt);
		char *newName = "";
		strcpy(newName, job->dateipfad);
		strcat(newName, ".compr");
		if( (rename(job->dateipfad,newName)) < 0) {
			fprintf(stderr, "Fehler beim Umbenennen von %s", job->dateipfad);
			return (void*)EXIT_FAILURE;
		}
		FILE* fp;
		fp = fopen(job->dateipfad,"w");
		fprintf(fp, result->data);
		fclose(fp);
	}
	free(job);
	free(result->data);
	free(result);
	if (closedir(dir) == -1) {
		fprintf(stderr,"Fehler beim Schliessen von %s\n", dirname);
	}
	return (void*) EXIT_SUCCESS;
}

