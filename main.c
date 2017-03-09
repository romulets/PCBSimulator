/*
 * main.c
 *
 *  Created on: 8 de mar de 2017
 *      Author: romulo-farias
 */

#include <stdio.h>
#include <stdlib.h>
#include "file_reader.h"

typedef struct {
	int start_time;
	int duration;
	int priority;
} Proccess;

int main ()
{
    char *file_to_read = "/home/romulo-farias/Documents/development/c/20170308_so_alghorithms/data.txt";
    read_file(file_to_read);
    return 0;
}
