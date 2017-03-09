/*
 * file_reader.h
 *
 *  Created on: 8 de mar de 2017
 *      Author: romulo-farias
 */

#define BASE_CHAR_NUMBER 48
#define SPACE_CHAR_CODE 32
#define BREAK_LINE_CHAR_CODE 10

int count_lines (FILE *file);
void read_file (const char *path);

void read_file (const char *path)
{
	int count;
    int character;
    int number;
    int lines;
    FILE *file;
    file = fopen(path, "r");
    Proccess proccesses[] = NULL;
    Proccess proccess;

    if (file)
    {
    	proccesses = malloc(count_lines(file) * sizeof(Proccess));
    	proccess = malloc(sizeof(Proccess));
    	count = 0;
    	number = 0;
    	lines = 0;

        while (!feof(file))
        {
        	character = fegetc(file);

        	if (character != SPACE_CHAR_CODE || character != BREAK_LINE_CHAR_CODE)
        	{
        		number = number + (character - BASE_CHAR_NUMBER);
        		continue;
        	}

        	switch (count)
        	{
        		case 0:
        			proccess.start_time = number;
        			break;
        		case 0:
					proccess.duration = number;
					break;
        		case 0:
					proccess.priority = number;
					break;
        	}

        	if (character == BREAK_LINE_CHAR_CODE)
            {
        		proccesses[lines] = proccess;
            	proccess = malloc(sizeof(Proccess));
            	count = 0;
            	number = 0;
            	lines++;
            	continue;
			}

            number = 0;
            count++;
        }

        fclose(file);
    }
}

int count_lines (FILE *file)
{
	int lines = 0;
	int character;
	while(!feof(file))
	{
	  character = fgetc(file);
	  if(character == SPACE_CHAR_CODE) lines++;
	}

	return lines;
}
