#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>




typedef struct t_list
{
    char *buff;
    struct t_list *next;
} t_list;

char *get_next_line(int fd);
int found_new_line(t_list *list);
void create_list(t_list **list, int fd);
void append(t_list **list, char *buff);
char *my_get_line(t_list *list);
void copy_str(t_list *list, char *str);
int len_new_line(t_list *list);
void	prepare_for_next_line(t_list **list);
void dealloc(t_list **list, t_list *clean_node, char *buff);
t_list *find_last_node(t_list *list);
#endif