#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_fd_list *fd_list = NULL;
    t_fd_list *node = get_fd_node(&fd_list, fd);
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if (!node || fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (!strchr(node->buffer, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buffer[bytes_read] = '\0';
        node->buffer = str_join_free(node->buffer, buffer);
    }
    
    char *line = extract_line(&node->buffer);
    if (!line)
        free_fd_node(&fd_list, fd);
    return line;
}
