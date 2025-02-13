#include "get_next_line.h"

t_fd_list *get_fd_node(t_fd_list **list, int fd)
{
    t_fd_list *temp = *list;

    while (temp)
    {
        if (temp->fd == fd)
            return temp;
        temp = temp->next;
    }
    t_fd_list *new_node = (t_fd_list *)malloc(sizeof(t_fd_list));
    if (!new_node)
        return NULL;
    new_node->fd = fd;
    new_node->buffer = NULL;
    new_node->next = *list;
    *list = new_node;
    return new_node;
}

void free_fd_node(t_fd_list **list, int fd)
{
    t_fd_list *temp = *list, *prev = NULL;

    while (temp)
    {
        if (temp->fd == fd)
        {
            if (prev)
                prev->next = temp->next;
            else
                *list = temp->next;
            free(temp->buffer);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

char *str_join_free(char *s1, char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = strlen(s2);
    char *new_str = (char *)malloc(len1 + len2 + 1);
    if (!new_str)
        return NULL;
    if (s1)
        strcpy(new_str, s1);
    strcpy(new_str + len1, s2);
    free(s1);
    return new_str;
}

char *extract_line(char **buffer)
{
    char *newline_pos = strchr(*buffer, '\n');
    char *line, *rest;

    if (!newline_pos)
    {
        if (**buffer == '\0') 
        {
            free(*buffer);
            *buffer = NULL;
            return NULL;
        }
        line = strdup(*buffer);
        free(*buffer);
        *buffer = NULL;
        return line;
    }
    size_t line_len = newline_pos - *buffer + 1;
    line = strndup(*buffer, line_len);
    rest = strdup(newline_pos + 1);
    free(*buffer);
    *buffer = rest;
    return line;
}