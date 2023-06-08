#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "linked_list.h"

void should_create_linked_list() {
  linked_list *list = create_linked_list();

  CU_ASSERT_TRUE(is_empty(list));
}

void should_push_front() {
  linked_list *list = create_linked_list();

  push_front(list, 84);
  push_front(list, 42);
  push_front(list, 100);

  CU_ASSERT_FALSE(is_empty(list));
  CU_ASSERT_EQUAL(size(list), 3);
  CU_ASSERT_EQUAL(value_at(list, 0), 100);
  CU_ASSERT_EQUAL(value_at(list, 1), 42);
  CU_ASSERT_EQUAL(value_at(list, 2), 84);
}

void should_push_back() {
  linked_list *list = create_linked_list();

  push_back(list, 84);
  push_back(list, 42);
  push_back(list, 100);

  CU_ASSERT_FALSE(is_empty(list));
  CU_ASSERT_EQUAL(size(list), 3);
  CU_ASSERT_EQUAL(value_at(list, 0), 84);
  CU_ASSERT_EQUAL(value_at(list, 1), 42);
  CU_ASSERT_EQUAL(value_at(list, 2), 100);
}

void should_get_front() {
  linked_list *list = create_linked_list();

  push_front(list, 84);
  push_front(list, 42);

  CU_ASSERT_EQUAL(front(list), 42);

  push_front(list, 100);

  CU_ASSERT_EQUAL(front(list), 100);
}

void should_get_back() {
  linked_list *list = create_linked_list();

  push_front(list, 84);
  push_front(list, 42);

  CU_ASSERT_EQUAL(back(list), 84);

  push_back(list, 100);

  CU_ASSERT_EQUAL(back(list), 100);
}

void should_pop_front() {
  linked_list *list = create_linked_list();

  push_back(list, 1);
  push_back(list, 2);
  push_back(list, 3);

  CU_ASSERT_EQUAL(pop_front(list), 1);
  CU_ASSERT_EQUAL(size(list), 2);
  CU_ASSERT_EQUAL(value_at(list, 0), 2);
  CU_ASSERT_EQUAL(value_at(list, 1), 3);
  CU_ASSERT_EQUAL(pop_front(list), 2);
  CU_ASSERT_EQUAL(size(list), 1);
  CU_ASSERT_EQUAL(pop_front(list), 3);
  CU_ASSERT_EQUAL(size(list), 0);
}

void should_pop_back() {
  linked_list *list = create_linked_list();

  push_back(list, 1);
  push_back(list, 2);
  push_back(list, 3);

  CU_ASSERT_EQUAL(pop_back(list), 3);
  CU_ASSERT_EQUAL(size(list), 2);
  CU_ASSERT_EQUAL(value_at(list, 0), 1);
  CU_ASSERT_EQUAL(value_at(list, 1), 2);
  CU_ASSERT_EQUAL(pop_back(list), 2);
  CU_ASSERT_EQUAL(size(list), 1);
  CU_ASSERT_EQUAL(pop_back(list), 1);
  CU_ASSERT_EQUAL(size(list), 0);
}

void should_insert() {
  linked_list *list = create_linked_list();

  push_back(list, 1);
  push_back(list, 2);
  push_back(list, 3);

  insert(list, 2, 42);
  insert(list, 0, 84);

  CU_ASSERT_EQUAL(value_at(list, 0), 84);
  CU_ASSERT_EQUAL(value_at(list, 3), 42);
  CU_ASSERT_EQUAL(size(list), 5);
}

void should_erase() {
  linked_list *list = create_linked_list();

  push_back(list, 1);
  push_back(list, 2);
  push_back(list, 3);

  erase(list, 2);
  erase(list, 0);

  CU_ASSERT_EQUAL(size(list), 1);
  CU_ASSERT_EQUAL(value_at(list, 0), 2);
}

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void add_test(CU_pSuite suite, const char* name, void (*test_func)(void)) {
  if (CU_add_test(suite, name, test_func) == NULL) {
    CU_cleanup_registry();
    exit(CU_get_error());
  }
}

int main() {
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  CU_pSuite suite = CU_add_suite("Tests suit", init_suite, clean_suite);

  if (NULL == suite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  add_test(suite, "Should create a linked list", should_create_linked_list);
  add_test(suite, "Should push on element in the begin", should_push_front);
  add_test(suite, "Should push on element in the end", should_push_back);
  add_test(suite, "Should get the first element", should_get_front);
  add_test(suite, "Should get the last element", should_get_back);
  add_test(suite, "Should pop the first element", should_pop_front);
  add_test(suite, "Should pop the last element", should_pop_back);
  add_test(suite, "Should insert in the middle", should_insert);
  add_test(suite, "Should remove in the middle", should_erase);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return CU_get_error();
}
