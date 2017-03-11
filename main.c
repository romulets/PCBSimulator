/*
 * main.c
 *
 *  Created on: 2017-03-08
 *      Author: romulo-farias
 *
 *  @TODO [Bug fix] it isn't modifying the memory address in the elegible_processes array;
 */

#include <stdio.h>
#include <stdlib.h>

#include "process.h"

#define MAXIMUM_TIME_IN_SAME_PROCESS 2
#define FILE_PATH "/home/romulo-farias/Documents/development/c/20170308_so_alghorithms/data.txt"

Process* get_highest_priority(Process **processes, int items_count);

int main()
{
	int i;
	int times;
	int times_in_same_process;
	int elegible_processes_count;
	FILE *file;
	Process *process;
	Process *last_executed;
	Process *executing;
	Process **processes;
	Process **elegible_processes;
	file = fopen(FILE_PATH, "r");

	if (!file)
		return -1;

	int items_count = count_lines(file);
	processes = read_processes_from_file(file);

	fclose(file);

	printf("time");
	for (i = 0; i < items_count; i++)
	{
		printf("\tP%d", processes[i]->id);
	}

	times = 0;
	elegible_processes = malloc(items_count * sizeof(Process));
	times_in_same_process = MAXIMUM_TIME_IN_SAME_PROCESS;
	while (1 == 1)
	{
		printf("\n% d-", times);

		if (times_in_same_process >= MAXIMUM_TIME_IN_SAME_PROCESS)
		{

			elegible_processes_count = 0;
			for (i = 0; i < items_count; i++)
			{
				process = processes[i];
				if (process->start_time <= times && process->finished == 0
						&& process != executing)
				{
					elegible_processes[i] = process;
					elegible_processes_count++;
				}
			}

			executing = get_highest_priority(elegible_processes,
					elegible_processes_count);
			times_in_same_process = 1;
		}
		else
		{
			times_in_same_process++;
		}

		for (i = 0; i < items_count; i++)
		{
			process = processes[i];

			if (process->start_time <= times)
			{
				if (process == executing)
				{
					printf("\t##");
				}
				else
				{
					printf("\t--");
				}
			}
			else
			{
				printf("\t");
			}

		}

		if (times == 3)
			break;

		last_executed = executing;
		times++;
	}

	return 0;
}

Process* get_highest_priority(Process **processes, int items_count)
{
	Process *highest_priority, *process;

	highest_priority = processes[0];

	for (int i = 1; i < items_count; i++)
	{
		process = processes[i];
		if (process->priority < highest_priority->priority)
		{
			highest_priority = process;
		}
	}

	return highest_priority;
}
