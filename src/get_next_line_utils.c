#include "get_next_line.h"
#include "config.h"
#include <stdio.h>

t_list *create_list()
{
	t_list *list = malloc(sizeof(t_list));
	list->buff = NULL;
	list->next = NULL;
	return (list);
}

t_list *append(t_list *list, char *buff)
{
	t_list *new_node;
	
	if(!list || !buff)
		return (list);
	new_node = create_list();
	new_node->buff = buff;
	new_node->next = list;
	return (new_node);
}

static void destroy_node(t_list *list)
{
	if(!list)
		return;
	if(list->buff)
		free(list->buff);
	free(list);
}

static void destroy_list(t_list *list)
{
	if(!list)
		return;
	destroy_node(list);
	if(list->next)
		destroy_list(list->next);
}

/*
static t_list *find_last_node(t_list *list)
{
	if(!list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}
*/

char *get_next_buff(int fd)
{
	char *buff;
	int read_out;

	buff = malloc(BUFFER_SIZE);
	read_out = read(fd, buff, BUFFER_SIZE);
	if(read_out <= 0)
	{
		free(buff);
		return (NULL);
	}
	if(read_out < BUFFER_SIZE)
		buff[read_out] = '\0';
	return (buff);
}

int new_line_exists(char *str)
{
	int i;

	i = 0;
	while(i < BUFFER_SIZE && str[i])
	{
		if (str[i] == '\n')
			return(i);
		i++;
	}
	return (-1);
}

