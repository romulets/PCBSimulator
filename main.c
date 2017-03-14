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

#define BASE_CHAR_NUMBER 48
#define SPACE_CHAR_CODE 32
#define BREAK_LINE_CHAR_CODE 10
#define MAXIMUM_TIME_IN_SAME_PROCESS 2
#define FILE_PATH "./data.txt"

typedef struct
{
	int id;
	int start_time;
	int duration;
	int priority;
	int life_time;
	int total_time;
	int alternations;
	int used_time;
	int finished;
} Process;

void perform_processes_simulation(Process *processes, int items_count);
void print_header(Process *processes, int items_count);
int should_finish_simulation(Process *processes, int items_count);
Process *get_next_process(Process *processes, int items_count, Process *was_executing, int times_executed);
Process *get_highest_priority(Process **processes, int items_count);
void print_simulation_line(Process *processes, int items_count, Process *executing, int times);
void print_summary(Process *processes, int items_count);
Process *read_processes_from_file(FILE *file);
int count_lines_from_file(FILE *file);
Process create_process();

int main()
{
	FILE *file;
	int items_count;
	Process *processes;

	file = fopen(FILE_PATH, "r");

	if (!file)
		return -1;

	items_count = count_lines_from_file(file);
	processes = read_processes_from_file(file);

	fclose(file);

	perform_processes_simulation(processes, items_count);

	return 0;
}

void perform_processes_simulation(Process * processes, int items_count)
{
	int times;
	int times_in_same_process;
	Process *executing;
	Process *last_executed;

	print_header(processes, items_count);

	times = 0;
	executing = malloc(sizeof(Process));
	last_executed = malloc(sizeof(Process));
	executing->id = 0;
	times_in_same_process = MAXIMUM_TIME_IN_SAME_PROCESS;
	while (1)
	{
		if (should_finish_simulation(processes, items_count) == 1)
			break;

		if (times_in_same_process >= MAXIMUM_TIME_IN_SAME_PROCESS || executing->finished == 1)
		{
			executing = get_next_process(processes, items_count, executing, times);

			if (executing->id != last_executed->id)
				last_executed->alternations++;

			times_in_same_process = 1;
		}
		else
		{
			times_in_same_process++;
		}

		print_simulation_line(processes, items_count, executing, times);

		if (executing->used_time == executing->duration)
			executing->finished = 1;

		last_executed = executing;

		times++;
	}

	print_summary(processes, items_count);
}

void print_header(Process *processes, int items_count)
{
	int i;
	printf("time");
	for (i = 0; i < items_count; i++)
	{
		printf("\tP%d", processes[i].id);
	}
}

int should_finish_simulation(Process * processes, int items_count)
{
	int i;
	for (i = 0; i < items_count; i++)
	{
		if (processes[i].finished == 0)
		{
			return 0;
		}
	}

	return 1;
}

Process *get_next_process(Process *processes, int items_count, Process *was_executing, int times_executed)
{
	int i;
	int elegible_processes_count;
	Process *process;
	Process **elegible_processes;

	elegible_processes_count = 0;
	elegible_processes = malloc(items_count * sizeof(Process));
	for (i = 0; i < items_count; i++)
	{
		process = &processes[i];
		if (process->start_time <= times_executed && process->finished == 0 && process->id != was_executing->id)
		{
			elegible_processes[elegible_processes_count] = process;
			elegible_processes_count++;
		}
	}

	if (elegible_processes_count == 0 && was_executing->finished == 0)
	{
		return process;
	}
	else
	{
		return get_highest_priority(elegible_processes, elegible_processes_count);
	}
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

void print_simulation_line(Process *processes, int items_count, Process *executing, int times)
{
	int i;
	Process * process;
	printf("\n% d-", times);

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
}

void print_summary(Process *processes, int items_count)
{
	int i;
	Process *process;

	printf("\n\nProcess \t Priority \t Duration \t Life Time \t Total Time \t Alternations\n");
	for (i = 0; i < items_count; i++)
	{
		process = &processes[i];
		printf("P%d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d\n", process->id, process->priority, process->duration,
				process->life_time, process->total_time, process->alternations);
	}
}

Process *read_processes_from_file(FILE *file)
{
	int count;
	int character;
	int number;
	int lines;
	Process *processes;

	processes = malloc(count_lines_from_file(file) * sizeof(Process));
	processes[0] = create_process();
	processes[0].id = 1;
	count = 0;
	number = 0;
	lines = 0;

	character = getc(file);
	while ((character = getc(file)) != EOF)
	{
		if (character != SPACE_CHAR_CODE && character != BREAK_LINE_CHAR_CODE)
		{
			number = number + (character - BASE_CHAR_NUMBER);
			continue;
		}

		switch (count)
		{
		case 0:
			processes[lines].start_time = number;
			break;
		case 1:
			processes[lines].duration = number;
			break;
		case 2:
			processes[lines].priority = number;
			break;
		}

		if (character == BREAK_LINE_CHAR_CODE)
		{
			lines++;
			count = 0;
			number = 0;
			processes[lines] = create_process();
			processes[lines].id = lines + 1;
			continue;
		}

		number = 0;
		count++;
	}

	processes[lines].priority = number;
	rewind(file);

	return processes;
}

int count_lines_from_file(FILE *file)
{
	int lines = 0;
	int character;
	while (!feof(file))
	{
		character = fgetc(file);
		if (character == BREAK_LINE_CHAR_CODE)
			lines++;
	}

	lines += 1;

	rewind(file);
	return lines;
}

Process create_process()
{
	Process process;
	process.id = -1;
	process.start_time = 0;
	process.duration = 0;
	process.priority = 0;
	process.life_time = 0;
	process.total_time = 0;
	process.alternations = 0;
	process.used_time = 0;
	process.finished = 0;
	return process;
}
