/*
 * main.c
 *
 *  Created on: 2017-03-08
 *      Author: romulo-farias
 */

#include <stdio.h>
#include <stdlib.h>

#include "process.h"

int main ()
{
	Process *process;
    char *file_to_read = "/home/romulo-farias/Documents/development/c/20170308_so_alghorithms/data.txt";
    Process **processes = read_processes_from_file(file_to_read);

    int items_count = 4; //sizeof(Processes) / sizeof(Processes[0]);

    for (int i = 0; i < items_count; i++)
	{
		process = processes[i];
		printf("%d %d %d\n", process->start_time, process->duration, process->priority);
	}

    return 0;
}
