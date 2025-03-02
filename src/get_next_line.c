#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list	*list = NULL;
	char *temp;
	int nl;
    char	*next_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	list = create_list();
	temp = get_next_buff(fd);
	nl = new_line_exists(temp);
	if(temp[BUFFER_SIZE-1] == '\n' || temp[BUFFER_SIZE-1] == '\0')
	return (next_line);
}
