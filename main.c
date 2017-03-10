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
	Process *proccess;
    char *file_to_read = "/home/romulo-farias/Documents/development/c/20170308_so_alghorithms/data.txt";
    Process **proccesses = read_processes_from_file(file_to_read);

    int items_count = 4; //sizeof(Processes) / sizeof(Processes[0]);

    for (int i = 0; i < items_count; i++)
	{
		proccess = proccesses[i];
		printf("%d %d %d\n", proccess->start_time, proccess->duration, proccess->priority);
	}

    return 0;
}
