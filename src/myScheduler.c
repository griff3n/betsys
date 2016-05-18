/*
 * myScheduler.c
 *
 *  Created on: 18.05.2016
 *      Author: peter
 */

#include "lists.h"
//#include "lists.c"
//#include "global.h"
//#include "global.c"

typedef struct Job {
	LIST_NODE_HEADER(struct Job);
	char *name;
	int id;
	int laufzeit;
	int prio;
} JobNode;

typedef struct {
	LIST_HEADER(JobNode);
} JobList;

int compareJobNodes_id(JobNode *n1, JobNode *n2, void *userData) {
	if(n1->id > n2->id) {
		return 1;
	}
	else if(n1->id < n2->id) {
			return -1;
	}
	else {
			return 0;
	}
}

int compareJobNodes_lz(JobNode *n1, JobNode *n2, void *userData) {
	if(n1->laufzeit > n2->laufzeit) {
		return 1;
	}
	else if(n1->laufzeit < n2->laufzeit) {
			return -1;
	}
	else {
			return 0;
	}
}

int compareJobNodes_pr(JobNode *n1, JobNode *n2, void *userData) {
	if(n1->prio > n2->prio) {
		return -1;
	}
	else if(n1->prio < n2->prio) {
			return 1;
	}
	else {
			return 0;
	}
}

static JobList jobs;

void initJobs(void) {
	List_init(&jobs);
	JobNode *a, *b, *c, *d, *e;
	a = LIST_NEW_NODE(JobNode);
	a->name = "A";
	a->id = 0;
	a->laufzeit = 30;
	a->prio = 2;

	b = LIST_NEW_NODE(JobNode);
	b->name = "B";
	b->id = 1;
	b->laufzeit = 20;
	b->prio = 1;

	c = LIST_NEW_NODE(JobNode);
	c->name = "C";
	c->id = 2;
	c->laufzeit = 25;
	c->prio = 5;

	d = LIST_NEW_NODE(JobNode);
	d->name = "D";
	d->id = 3;
	d->laufzeit = 28;
	d->prio = 4;

	e = LIST_NEW_NODE(JobNode);
	e->name = "E";
	e->id = 4;
	e->laufzeit = 18;
	e->prio = 3;

	List_append(&jobs, a);
	List_append(&jobs, b);
	List_append(&jobs, c);
	List_append(&jobs, d);
	List_append(&jobs, e);
}

int main(int argc, char **argv) {

	initJobs();
	JobNode *temp = jobs.head;
	int time = 0;
	float vtime = 0;
	printf("First Come First Served\n");
	while(temp != NULL) {
		time += temp->laufzeit;
		vtime += time;
		printf("%s wurde abgearbeitet (Aktuelle Zeit: %d)\n", temp->name, time);
		temp = temp->next;
	}
	vtime =  vtime / jobs.count;
	printf("Mittlere Verweilzeit: %f Zeiteinheiten\n\n", vtime);

	List_sort(&jobs, (ListNodeCompareFunction) compareJobNodes_lz, NULL);
	temp = jobs.head;
	time = 0;
	vtime = 0;
	printf("Shortest Job First\n");
	while(temp != NULL) {
		time += temp->laufzeit;
		vtime += time;
		printf("%s wurde abgearbeitet (Aktuelle Zeit: %d)\n", temp->name, time);
		temp = temp->next;
	}
	vtime =  vtime / jobs.count;
	printf("Mittlere Verweilzeit: %f Zeiteinheiten\n\n", vtime);

	List_sort(&jobs, (ListNodeCompareFunction) compareJobNodes_pr, NULL);
	temp = jobs.head;
	time = 0;
	vtime = 0;
	printf("prioritötsgesteuertes Scheduling\n");
	while(temp != NULL) {
		time += temp->laufzeit;
		vtime += time;
		printf("%s wurde abgearbeitet (Aktuelle Zeit: %d)\n", temp->name, time);
		temp = temp->next;
	}
	vtime =  vtime / jobs.count;
	printf("Mittlere Verweilzeit: %f Zeiteinheiten\n\n", vtime);
	List_sort(&jobs, (ListNodeCompareFunction) compareJobNodes_id, NULL);
	time = 0;
	vtime = 0;
	int zeitscheibe = 10;
	int count = 0;
	while(jobs.count != count) {
		temp = jobs.head;
		printf("Es wird an den Jobs zu folgenden Anteilen gearbeitet:\n");
		count = 0;
		while(temp != NULL) {
			if(temp->laufzeit<1) {
				temp = temp->next;
				count++;
			} else if(temp->laufzeit <= zeitscheibe) {
				printf("Es wurde %d Zeiteinheiten an %s gearbeitet.\n", temp->laufzeit, temp->name);
				time += temp->laufzeit;
				vtime += time;
				temp->laufzeit -= zeitscheibe;
				temp = temp->next;
			} else {
				printf("Es wurde %d Zeiteinheiten an %s gearbeitet.\n", zeitscheibe, temp->name);
				time += zeitscheibe;
				temp->laufzeit -= zeitscheibe;
				temp = temp->next;
			}
		}
	}
	vtime =  vtime / jobs.count;
	printf("Mittlere Verweilzeit: %f Zeiteinheiten\n\n", vtime);

	initJobs();
	time = 0;
	vtime = 0;
	count = 0;
	while(jobs.count != count) {
		temp = jobs.head;
		printf("Es wird an den Jobs zu folgenden Anteilen gearbeitet:\n");
		count = 0;
		while(temp != NULL) {
			if(temp->laufzeit<1) {
				temp = temp->next;
				count++;
			} else if(temp->laufzeit <= temp->prio) {
				printf("Es wurde %d Zeiteinheiten an %s gearbeitet.\n", temp->laufzeit, temp->name);
				time += temp->prio;
				vtime += time;
				temp->laufzeit -= temp->prio;
				temp = temp->next;
			} else {
				printf("Es wurde %d Zeiteinheiten an %s gearbeitet.\n", temp->prio, temp->name);
				time += temp->prio;
				temp->laufzeit -= temp->prio;
				temp = temp->next;
			}
		}
	}
	vtime =  vtime / jobs.count;
	printf("Mittlere Verweilzeit: %f Zeiteinheiten\n\n", vtime);
}

