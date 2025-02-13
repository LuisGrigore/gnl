#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


#define BUFFER_SIZE 42


typedef struct s_fd_list
{
    int fd;
    char *buffer;
    struct s_fd_list *next;
} t_fd_list;

char *get_next_line(int fd);
t_fd_list *get_fd_node(t_fd_list **list, int fd);
void free_fd_node(t_fd_list **list, int fd);
char *str_join_free(char *s1, char *s2);
char *extract_line(char **buffer);
#endif