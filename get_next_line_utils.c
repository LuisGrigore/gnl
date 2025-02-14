#include "get_next_line.h"
#include <stdio.h>

void create_list(t_list **list, int fd)
{
	int char_read;
	char *buff;
	while(found_new_line(*list) == 0)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if(!buff)
			return ;
		char_read = read(fd, buff, BUFFER_SIZE);
		if(!char_read)
		{
			free(buff);
			return ;
		}
		buff[char_read] = '\0';
		append(list, buff);
	}
}

int found_new_line(t_list *list)
{
	int i;

	if (list == NULL)
		return (0);
	i = 0;
	while(list)
	{
		i = 0;
		while (list -> buff[i] && i < BUFFER_SIZE)
		{
			if(list->buff[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void append(t_list **list, char *buff)
{
	t_list *new_node;
	t_list *last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->buff = buff;
	new_node->next = NULL;
}

char *my_get_line(t_list *list)
{
	int str_len;
	char *next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_new_line(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
	
}

void copy_str(t_list *list, char *str)
{
	int i;
	int k;

	if( list == NULL)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->buff[i])
		{
			if (list->buff[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->buff[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

int len_new_line(t_list *list)
{
	int i;
	int len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->buff[i])
		{
			if (list->buff[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	prepare_for_next_line(t_list **list)
{
	t_list *last_node;
	t_list *clean_node;
	int i;
	int k;
	char *buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buff == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->buff[i] && last_node->buff[i] != '\n')
		++i;
	while (last_node->buff[i] && last_node->buff[++i])
		buff[k++] = last_node->buff[i];
	buff[k] = '\0';
	clean_node->buff = buff;
	clean_node->next = NULL;
	dealloc(list, clean_node, buff);
}

void dealloc(t_list **list, t_list *clean_node, char *buff)
{
	t_list *tmp;

	if(*list == NULL)
		return ;
	while(*list)
	{
		tmp = (*list)->next;
		free((*list)->buff);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if(clean_node->buff[0])
		*list = clean_node;
	else 
	{
		free(buff);
		free(clean_node);
	}
}

t_list *find_last_node(t_list *list)
{
	if(!list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}