#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

static MunitResult test_gerbau(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;
	assert_true(1==1);	
	assert_double_equal(1.0123,1.0124,4);
	assert_string_equal("abc","abc");
	return MUNIT_OK;
}

MunitTest test[] = {
	{"/test-gerbau",test_gerbau,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL},
	{NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}
};

static const MunitSuite suite = {
	"/my-tests",test,NULL,1,MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc+1)]){
	return munit_suite_main(&suite,(void*) "unit", argc,argv);
}
