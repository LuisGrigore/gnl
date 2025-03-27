#include "assertions.h"
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>


void test_init_list()
{
	t_list *list = init_list();

	start_unit_test()
	assert_not_null(list);
	assert_null(list->first);
	assert_null(list->last);
	assert_equal_num(0,list->size);
	assert_equal_num(-1,list->end_pos);
}

void test_append_to_empty_list()
{
	t_list *list = init_list();
	char *expected_value = malloc(BUFFER_SIZE);

	append(list, expected_value);

	start_unit_test();
	assert_equal_num(list->size, 1);
	assert_not_null(list->first);
	assert_not_null(list->last);
	assert_equal(list->first,list->last);
	assert_equal_str(expected_value, list->first->value);
	assert_equal(list->first->next, NULL);
	assert_equal(list->first->prev, NULL);
}

void test_append_to_size_1_list()
{
	t_list *list = init_list();
	t_node *node = malloc(sizeof(t_node));

	list->first = node;
	list->last = node;
	list->size = 1;

	char *expected_value = malloc(BUFFER_SIZE);


	append(list, expected_value);

	start_unit_test();
	assert_equal_num(list->size, 2);
	assert_not_null(list->first);
	assert_not_null(list->last);
	assert_not_null(list->first->next);
	assert_not_null(list->last->prev);
	assert_equal(list->first, node);
	assert_equal_str(expected_value, list->last->value);
}

void test_append_to_size_n_list()
{
	t_list *list = init_list();
	t_node *first_node = malloc(sizeof(t_node));
	t_node *second_node = malloc(sizeof(t_node));
	int expected_size = 3;

	first_node->next = second_node;
	second_node->prev = first_node;

	list->first = first_node;
	list->last = second_node;
	list->size = 2;

	char *expected_value = malloc(BUFFER_SIZE);


	append(list, expected_value);

	start_unit_test();
	assert_equal_num(expected_size, list->size);
	assert_not_null(list->first->next->next);
	assert_not_null(list->last);
	assert_equal(list->last->prev, second_node);
	assert_equal_str(expected_value, list->last->value);
}

void test_clean_list()
{
	t_list *list = init_list();
	char *first_other_value = malloc(BUFFER_SIZE);
	char *second_other_value = malloc(BUFFER_SIZE);
	char *last_value = malloc(BUFFER_SIZE);

	strcpy(first_other_value, "firsttt");
	strcpy(second_other_value, "secondd");
	strcpy(last_value, "lastttt");

	first_other_value[BUFFER_SIZE-1] = 't';
	second_other_value[BUFFER_SIZE-1] = 'd';
	last_value[BUFFER_SIZE-1] = '\n';


	append(list, first_other_value);
	append(list, second_other_value);
	append(list, last_value);

	clean_list(list);

	start_unit_test();
	assert_equal_num(list->size, 1);
	assert_not_null(list->first)
	assert_not_null(list->last)
	assert_equal(list->first, list->last);
	assert_null(list->first->next);
	assert_null(list->first->prev);
	assert_equal(list->first->value, last_value);
}

void test_get_last_part()
{
	char *str = "hola\nque";
	char *result = get_last_part(str);

	start_unit_test();
	assert_equal_str("que", result);
}

int main(int argc, char const *argv[])
{
	test_init_list();

	test_append_to_empty_list();
	test_append_to_size_1_list();
	test_append_to_size_n_list();

	test_clean_list();

	test_get_last_part();
	return 0;
}
