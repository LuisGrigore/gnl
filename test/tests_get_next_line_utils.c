#include "assertions.h"
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>


void test_create_list()
{
	t_list *list = create_list();

	start_unit_test()
	assert_not_null(list);
}

void test_append()
{
	t_list *list = create_list();
	char *buff = "Hola";

	append(list, buff);

	start_unit_test()
	assert_not_null(list->prev->buff);
	assert_equal_str(list->prev->buff, buff);
}

void test_get_next_buff_success_not_eof()
{
	int fd = open("./test/test_text_example.txt",O_RDONLY);
	char *expected_str = malloc(BUFFER_SIZE);

	read(fd, expected_str, BUFFER_SIZE);
	close(fd);
	fd = open("./test/test_text_example.txt",O_RDONLY);


	start_unit_test();
	assert_equal_str(expected_str, get_next_buff(fd));

	close(fd);
}

void test_get_next_buff_success_eof()
{
	int fd = open("./test/test_text_example_eof.txt",O_RDONLY);
	char *null_terminated_line = get_next_buff(fd);
	int line_len = strlen(null_terminated_line);

	start_unit_test();
	assert_equal_num('\0', null_terminated_line[line_len]);

	close(fd);
}

void test_get_next_buff_fail_bad_fd()
{
	start_unit_test();
	assert_null(get_next_buff(3));
}

int main(int argc, char const *argv[])
{
	test_create_list();

	test_append();

	test_get_next_buff_success_not_eof();
	test_get_next_buff_success_eof();
	test_get_next_buff_fail_bad_fd();

	return 0;
}
