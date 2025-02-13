#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	static t_fd_list *fd_list = NULL;
    t_fd_list *node = get_fd_node(&fd_list, 1);

	free_fd_node(&fd_list, 1);

	printf("%d\n", get_fd_node(&fd_list, 1)->fd);


	return 0;
}
