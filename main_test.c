#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

static MunitResult test_gerbau(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

	assert_true(1==1);	
	assert_double_equal(1.0123,1.0124,4);
	assert_string_equal("abc","abc");

	char* s = "123";
	char* t = s;
	assert_ptr_equal(s,t);
	
	return MUNIT_OK;
}
static MunitResult test_terpau(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

	munit_rand_seed(122);
	int i = munit_rand_int_range(0, 9);
	assert_int(i ,==,2);
	i = munit_rand_int_range(0, 9);
	assert_int(i ,==,4);
	i = munit_rand_int_range(0, 9);
	assert_int(i ,==,2);

	return MUNIT_OK;
}
static void* my_setup(const MunitParameter params[], void* user_data) {
	user_data = malloc(sizeof(uint8_t));
	*(uint8_t*)user_data = 123;
	return user_data;
}
static void my_teardown(void* fixture) {
	assert_uint8(*(uint8_t*)fixture, ==, 123);
	free(fixture);
}

static MunitResult test_my_setup(const MunitParameter params[], void* user_data) {
	(void) params;

	assert_uint8(*(uint8_t*)user_data, ==, 123);

	return MUNIT_OK;
}
MunitTest test[] = {
	{"/gerbau",test_gerbau,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
	{"/terpau",test_terpau,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
	{"/my_setup",test_my_setup,my_setup,my_teardown,MUNIT_TEST_OPTION_NONE,NULL},
	{NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}
};

static const MunitSuite suite = {
	"/junk",test,NULL,1,MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc+1)]){
	return munit_suite_main(&suite,(void*) "unit", argc,argv);
}
