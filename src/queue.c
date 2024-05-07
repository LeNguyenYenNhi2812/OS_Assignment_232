#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static int cur_prior = 272;
int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
	if(q[0].size == MAX_QUEUE_SIZE) return;
	for(int i = MAX_QUEUE_SIZE - 1; i >= 0; i--) {
		if(q[0].proc[i] == NULL) {
			q[0].proc[i] = proc;
			q[0].size++;
			//printf("\nPID: %d\nSize: %d\n",q[0].proc[i]->pid, q[0].size); 
			break;
		}
	} 
}


struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
       /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
	// Pre-process (Assign cur_prior) (272 is default value when it's initialized
	if (cur_prior == 272) {
		for(int i = 0; i < MAX_PRIO; i++) 
			if(q[i].size != 0) cur_prior = i;
	}
	cur_prior = 0;
	// In-process 
	// Case: cur priority-queue have 0 slot (1)
	int countPriorQ = 0;
	while(q[cur_prior].size == 0) {
		if(countPriorQ >= MAX_PRIO) {
			return NULL; // No more process
		}
		else {
			cur_prior = (cur_prior + 1) % 140;
			countPriorQ++;
		}
	} // Stop at prior-queue have process 
	
	// Take oldest process in cur prior-queue (2)
	struct pcb_t *run = q[cur_prior].proc[MAX_QUEUE_SIZE - 1];// Take oldest process
	q[cur_prior].proc[MAX_QUEUE_SIZE - 1] = q[cur_prior].proc[MAX_QUEUE_SIZE - 2];
	// Shift-right all process in array (Just shift size - 1 elements) (3)
	for(int i = MAX_QUEUE_SIZE - 2; i >= 1; i--) {
		if(q[cur_prior].proc[i] == NULL) break;	// have shifted all process 
		else {
			q[cur_prior].proc[i] = q[cur_prior].proc[i - 1]; 
		}
	}

	q[cur_prior].size--;
	run->prio = (run->prio + 1 < 139) ? (run->prio + 1) : 139;
	return run;
}

