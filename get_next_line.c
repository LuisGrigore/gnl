#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list	*list = NULL;
    char	*next_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);

	create_list(&list, fd);
	if(list == NULL)
		return (NULL);
	next_line = my_get_line(list);
	prepare_for_next_line(&list);
	return (next_line);
}
