#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct t_list
{
    char *buff;
    struct t_list *next;
	struct t_list *prev;
} t_list;

t_list *create_list();
t_list *append(t_list *list, char *buff);
char *get_next_buff(int fd);
static void dealloc(t_list **list, t_list *clean_node, char *buff);
static t_list *find_last_node(t_list *list);
char *get_next_line(int fd);
int is_end_node(char *str);

#endif