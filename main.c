/*
 * main.c
 *
 *  Created on: 2017-03-08
 *      Author: romulo-farias
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "process.h"

#define MAXIMUM_TIME_IN_SAME_PROCESS 2
#define FILE_PATH "/home/romulo-farias/Documents/development/c/20170308_so_alghorithms/data.txt"

Process * get_highest_priority(Process **processes, int items_count);

int main()
{
	int i;
	int times;
	int should_finish;
	int times_in_same_process;
	int elegible_processes_count;
	FILE *file;
	Process *process;
	Process *executing;
	Process *processes;
	Process *last_executed;
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
		printf("\tP%d", processes[i].id);
	}

	times = 0;
	elegible_processes = malloc(items_count * sizeof(Process));
	executing = malloc(sizeof(Process));
	last_executed = malloc(sizeof(Process));
	executing->id = 0;
	times_in_same_process = MAXIMUM_TIME_IN_SAME_PROCESS;
	while (1 == 1)
	{
		should_finish = 1;
		for (i = 0; i < items_count; i++)
		{
			if (processes[i].finished == 0)
			{
				should_finish = 0;
				break;
			}
		}

		if (should_finish == 1)
			break;

		printf("\n% d-", times);

		if (times_in_same_process >= MAXIMUM_TIME_IN_SAME_PROCESS
				|| executing->finished == 1)
		{

			elegible_processes_count = 0;
			free(elegible_processes);
			elegible_processes = malloc(items_count * sizeof(Process));
			for (i = 0; i < items_count; i++)
			{
				process = &processes[i];
				if (process->start_time <= times && process->finished == 0
						&& process->id != executing->id)
				{
					elegible_processes[elegible_processes_count] = process;
					elegible_processes_count++;
				}
			}

			if (elegible_processes_count == 0 && executing->finished == 0)
			{
				executing = process;
			}
			else
			{
				executing = get_highest_priority(elegible_processes,
						elegible_processes_count);
			}

			if (executing->id != last_executed->id)
			{
				last_executed->alternations++;
			}

			times_in_same_process = 1;
		}
		else
		{
			times_in_same_process++;
		}

		for (i = 0; i < items_count; i++)
		{
			process = &processes[i];

			if (process->start_time <= times && process->finished == 0)
			{
				if (process->id == executing->id)
				{
					printf("\t##");
					process->used_time++;
				}
				else
				{
					printf("\t--");
				}

				process->total_time++;
				if (process->used_time > 0 && process->finished == 0)
					process->life_time++;
			}
			else
			{
				printf("\t");
			}

		}

		if (executing->used_time == executing->duration)
			executing->finished = 1;

		last_executed = executing;

		times++;
	}

	printf(
			"\n\nProcess \t Priority \t Duration \t Life Time \t Total Time \t Alternations\n");
	for (i = 0; i < items_count; i++)
	{
		process = &processes[i];
		printf("P%d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d\n", process->id, process->priority,
				process->duration, process->life_time, process->total_time,
				process->alternations);
	}

	return 0;
}

Process * get_highest_priority(Process **processes, int items_count)
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
