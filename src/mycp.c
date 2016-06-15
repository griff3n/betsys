/*
 * mycp.c
 *
 *  Created on: 14.06.2016
 *      Author: peter
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define MAXBYTES 1024

int isStdout(const char * arg);
int mycp(const int isstdout, const char *quelldatei, const char *zieldatei);

int main(int argc, char **argv) {
	char *quelldatei;
	char *zieldatei;
	int isstdout = 0;
	if(argc < 3) {
		char output[] = "Zu wenig Komandozeilenargumente.\n";
		write(2, &output, sizeof(output));
		return 1;
	} else if (argc == 3) {
		if(isStdout(argv[1])) {
			isstdout = 1;
			quelldatei = argv[2];
			zieldatei = NULL;
		} else {
			quelldatei = argv[1];
			zieldatei = argv[2];
		}
	} else if (argc == 4) {
		if(isStdout(argv[1])) {
			isstdout = 1;
		}
		quelldatei = argv[2];
		zieldatei = argv[3];
	}
	mycp(isstdout, quelldatei, zieldatei);
}

int isStdout(const char * arg) {
	int isstdout = 0;
	int j = 1;
	for(int i = 0; i < 3; i++) {
		char c = *(arg + i);
		if(c == '-') {
			isstdout += 2 * j;
		} else if(c == 'o') {
			isstdout += 3 * j;
		} else if(c == '\0') {

		} else {
			isstdout += j;
		}
		j *= 10;
	}
	if (isstdout == 32) {
		return 1;
	}
	return 0;
}

int mycp(const int isstdout, const char *quelldatei, const char *zieldatei) {
	off_t pos = 0;
	off_t dateiMitte = 0;
	off_t dateiEnde = 0;
	char buffer[MAXBYTES] = {0};
	ssize_t count = 0;
	int datei = open(quelldatei, O_RDONLY);
	if(datei == -1) {
		char output[] = "Fehler beim oeffnen der Datei.\n";
		write(2, &output, sizeof(output));
		return 1;
	}
	dateiEnde = lseek(datei, -1L, SEEK_END);
	dateiMitte = dateiEnde / 2;
	lseek(datei, dateiMitte, SEEK_SET);
	count = read(datei, buffer, MAXBYTES);
	while(count) {
		write(1, buffer, count);
		count = read(datei, buffer, MAXBYTES);
	}
	lseek(datei, 0L, SEEK_SET);
	count = read(datei, buffer, MAXBYTES);
	pos += count;
	while(pos <= dateiMitte) {
		write(1, buffer, count);
		count = read(datei, buffer, MAXBYTES);
		pos += count;
	}
	count = dateiMitte % MAXBYTES;
	if(count) {
		write(1, buffer, count);
	}
	//printf("Mitte: %ld\npos: %ld\n", dateiMitte, t);

	return 0;
}
