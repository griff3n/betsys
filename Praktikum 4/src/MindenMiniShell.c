/*
 * MindenMiniShell.c
 *
 *  Created on: 11.05.2016
 *      Author: peter
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFERSIZE_TOKEN 64
#define SEPARATOREN " \t\r\n\a"

char *readline(void);
char **parseline(char *line);
int execute(char **args);

int main(int argc, char **argv) {

	char *user, *path,*line, **args;

	int ende;
		do {
			user = getenv("USER");
			path = getenv("PWD");
			if(user == NULL || path == NULL) {
				printf("Fehler beim erstellen des Prompts\n");
				exit(EXIT_FAILURE);
			}
			chdir(path);
			printf("%s:%s$ ", user, path);
			line = readline();
			args = parseline(line);
			ende = execute(args);
			free(line);
			free(args);
		} while (ende);
	return 0;
}

char *readline() {
	char *line = NULL;
	size_t buffersize = 0;
	getline(&line, &buffersize, stdin);
	return line;
}

char **parseline(char *line) {
	int buffersize = BUFFERSIZE_TOKEN, pos = 0;
	char **tokens = malloc(buffersize * sizeof(char*));
	char *token;
	if (!tokens) {
		fprintf(stderr, "Fehler beim Speicher reservieren\n");
	    exit(EXIT_FAILURE);
	}
	token = strtok(line, SEPARATOREN);
	while (token != NULL) {
	    tokens[pos] = token;
	    pos++;
	    if (pos >= buffersize) {
	    	buffersize += BUFFERSIZE_TOKEN;
	    	tokens = realloc(tokens, buffersize * sizeof(char*));
	    	if (!tokens) {
	    		fprintf(stderr, "Fehler beim Speicher reservieren\n");
	    		exit(EXIT_FAILURE);
	      	}
	    }
	    token = strtok(NULL, SEPARATOREN);
	}
	tokens[pos] = NULL;
	return tokens;
}

int execute(char **args) {
	pid_t pid, wpid;
	int status;
	if (args[0] == NULL) {
		return 1;
	} else if (!strcmp(args[0],"exit")) {
		return 0;
	}
	else if (!strcmp(args[0],"cd")) {

		if(chdir(args[0]) != 0) {
			perror("Vereichnes wechseln fehlgeschlagen");
		}
		return 1;
	}
	else if (!strcmp(args[0],"set")) {
		putenv(args[1]);
		return 1;
	}
	pid = fork();
	if (pid == 0) {
		// Child process
		if (execvp(args[0], args) == -1) {
			perror("Speicherabild überschreiben fehlgeschlagen");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("Forken fehlgeschlagen");
	} else {
		// Parent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}
