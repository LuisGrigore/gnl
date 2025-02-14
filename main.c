#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int fd = open("puta.txt",O_RDONLY);
	int i = 0;
	char *line;

	while (i < 6)
	{
		line = get_next_line(fd);
		printf("%s",line);
		i++;
		free(line);
	}
	return 0;
}
