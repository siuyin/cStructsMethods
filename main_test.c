#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

static MunitResult test_gerbau(const MunitParameter params[], void* user_data) {
	assert_true(1==1);	
	assert_double_equal(1.0123,1.0124,4);
	assert_string_equal("abc","abc");

	char* s = "123";
	char* t = s;
	assert_ptr_equal(s,t);
	
	return MUNIT_OK;
}
static MunitResult test_terpau(const MunitParameter params[], void* user_data) {
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
	assert_uint8(*(uint8_t*)user_data, ==, 42);
	*(uint8_t*)user_data = 123;
	return user_data;
}
static void my_teardown(void* fixture) {
	assert_uint8(*(uint8_t*)fixture, ==, 123);
}

static MunitResult test_my_setup(const MunitParameter params[], void* user_data) {
	assert_uint8(*(uint8_t*)user_data, ==, 123);

	return MUNIT_OK;
}
static MunitResult test_skipped(const MunitParameter params[], void* user_data) {
	return MUNIT_SKIP;

	return MUNIT_OK;
}
static char* foo_params[] = {"a","b","c",NULL};
static MunitParameterEnum my_params[] = {
	{"foo", foo_params},
	{NULL,NULL}
};
static MunitResult test_params(const MunitParameter params[], void* user_data) {
	if(!(*params[0].value == 'a' || *params[0].value == 'b' || *params[0].value == 'c')) return MUNIT_ERROR;
	return MUNIT_OK;
}
MunitTest test[] = {
	{"/params",test_params,NULL,NULL,MUNIT_TEST_OPTION_NONE,my_params},
	{"/gerbau",test_gerbau,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
	{"/terpau",test_terpau,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
	{"/my_setup",test_my_setup,my_setup,my_teardown,MUNIT_TEST_OPTION_NONE,NULL},
	{"/skipped",test_skipped,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
	{NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}
};

static const MunitSuite suite = {
	"/junk",test,NULL,1,MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc+1)]){
	uint8_t my_data = 42;
	return munit_suite_main(&suite,(void*) &my_data, argc,argv);
}

