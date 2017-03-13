/*
 * process.h
 *
 *  Created on: 2017-03-08
 *      Author: romulo-farias
 */

#define BASE_CHAR_NUMBER 48
#define SPACE_CHAR_CODE 32
#define BREAK_LINE_CHAR_CODE 10

typedef struct
{
	int id;
	int start_time;
	int duration;
	int priority;
	int life_time;
	int total_time;
	int alternations;
	int finished;
} Process;

int count_lines(FILE *file);
Process create_process();
Process * read_processes_from_file(FILE *file);

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
	process.finished = 0;
	return process;
}

Process * read_processes_from_file(FILE *file)
{
	int count;
	int character;
	int number;
	int lines;
	Process *processes;

	processes = malloc(count_lines(file) * sizeof(Process));
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

	rewind(file);

	return processes;
}

int count_lines(FILE *file)
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
