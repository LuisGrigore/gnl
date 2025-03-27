#include "get_next_line.h"
#include "assertions.h"

void _create_populate(const char *filename, char c, int n) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error al crear el archivo");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (write(fd, &c, 1) == -1) {
            perror("Error al escribir en el archivo");
            close(fd);
            return;
        }
    }

    close(fd);
}

void _delete(const char *filename) {
    if (unlink(filename) == -1) {
        perror("Error al eliminar el archivo");
        return;
    }
}




void test_get_next_buff_bad_fd()
{
	char *next_buff = get_next_buff(3);
	start_unit_test();
	assert_null(next_buff);
}

void test_get_next_buff_no_eof()
{
	const char *file_name = "test_get_next_buff_no_eof.txt";
	_create_populate(file_name, 'a', BUFFER_SIZE+1);
	int fd = -1;

	fd = open(file_name, O_RDONLY);
	char *actual_buff = get_next_buff(fd);
	close(fd);

	fd = open(file_name, O_RDONLY);
	char *expected_buff = malloc(BUFFER_SIZE);
	read(fd, expected_buff, BUFFER_SIZE);
	close(fd);

	_delete(file_name);

	start_unit_test();
	assert_not_null(actual_buff);
	assert_equal_str(expected_buff, actual_buff);
}

void test_get_next_buff_eof()
{
	const char *file_name = "test_get_next_buff_eof.txt";
	_create_populate(file_name, 'a', BUFFER_SIZE-1);
	int fd = -1;

	fd = open(file_name, O_RDONLY);
	char *actual_buff = get_next_buff(fd);
	close(fd);

	_delete(file_name);

	start_unit_test();
	assert_not_null(actual_buff);
	assert_equal_num('\0', actual_buff[BUFFER_SIZE]);
}


void test_has_next_line_false()
{
	char *buff = "no new line";
	int next_line_pos = has_new_line(buff);

	start_unit_test();
	assert_equal_num(-1, next_line_pos);
}

void test_has_next_line_true()
{
	char *buff = "\n";
	int next_line_pos = has_new_line(buff);

	start_unit_test();
	assert_equal_num(0, next_line_pos);
}

void test_has_null_false()
{
	char buff[BUFFER_SIZE];
	int i = 0;
	while(i < BUFFER_SIZE)
	{
		buff[i] = 'a';
		i++;
	}
	int null_pos = has_null(buff);

	start_unit_test();
	assert_equal_num(-1, null_pos);
}

void test_has_null_true()
{
	char *buff = "\0";
	int null_pos = has_null(buff);

	start_unit_test();
	assert_equal_num(0, null_pos);
}

void test_get_next_line()
{
	char *file_name = "get_next_line_test.txt";
	//_create_populate(file_name,'a', 25);

	int fd = open(file_name, O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
}

int main()
{
	test_get_next_buff_bad_fd();
	test_get_next_buff_no_eof();
	test_get_next_buff_eof();

	test_has_next_line_false();
	test_has_next_line_true();

	test_has_null_false();
	test_has_null_true();

	test_get_next_line();
	return 0;
}
