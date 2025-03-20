#include "get_next_line.h"
#include <stdio.h>

t_list *create_list()
{
	t_list *list = malloc(sizeof(t_list));
	list->buff = NULL;
	list->next = NULL;
	list->prev = NULL;
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
	list->prev = new_node;
	return (new_node);
}

char *list_to_str(t_list *list)
{
	t_list *current;
	int i;
	int j;
	char *resul;

	current = list;
	j = -1;
	while(1)
	{
		j++;
		if(!current->next)
			break;
		current = current->next;
	}
	resul = malloc(i + (BUFFER_SIZE * j));
	i = 0;
	j = 0;
	while(current)
	{
		while(i < BUFFER_SIZE)
		{
			resul[j] = current->buff[i];
			i++;
			j++;
			if(current->buff[i] == '\n' || current->buff[i] == '\0')
				break;
		}
		i = 0;
		current = current->prev;
	}
	return (resul);
}

void clean_list(t_list *list)
{
	destroy_list(list->next);
}

void destroy_list(t_list *list)
{
	if(!list)
		return;
	if(list->next)
		destroy_list(list->next);
	if(list->buff)
		free(list->buff);
	free(list);
}


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

int is_end_node(char *str)
{
	int i;

	i = 0;
	while(i < BUFFER_SIZE && str[i])
	{
		if (str[i] == '\n' || !str[i])
			return(i);
		i++;
	}
	return (-1);
}

