/*
 * proccess.h
 *
 *  Created on: 2017-03-08
 *      Author: romulo-farias
 */

#define BASE_CHAR_NUMBER 48
#define SPACE_CHAR_CODE 32
#define BREAK_LINE_CHAR_CODE 10

typedef struct {
	int start_time;
	int duration;
	int priority;
} Proccess;

int count_lines (FILE *file);
Proccess** read_proccesses_from_file (const char *path);

Proccess** read_proccesses_from_file (const char *path)
{
	int count;
    int character;
    int number;
    int lines;
    FILE *file;
    file = fopen(path, "r");
    Proccess **proccesses;

    if (file)
    {
    	proccesses = malloc(count_lines(file) * sizeof(Proccess));
    	proccesses[0] = malloc(sizeof(Proccess));
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
        			proccesses[lines]->start_time = number;
        			break;
        		case 1:
        			proccesses[lines]->duration = number;
					break;
        		case 2:
        			proccesses[lines]->priority = number;
					break;
        	}

        	if (character == BREAK_LINE_CHAR_CODE)
            {
        		lines++;
            	count = 0;
            	number = 0;
            	proccesses[lines] = malloc(sizeof(Proccess));
            	continue;
			}

            number = 0;
            count++;
        }

        fclose(file);
    }

    return proccesses;
}

int count_lines (FILE *file)
{
	int lines = 0;
	int character;
	while(!feof(file))
	{
	  character = fgetc(file);
	  if(character == BREAK_LINE_CHAR_CODE) lines++;
	}

	rewind(file);
	return lines;
}
