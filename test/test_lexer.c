#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test_lexer(void)
{
    CU_ASSERT(add(2, 3) == 5);
    CU_ASSERT(add(-1, 1) == 0);
    CU_ASSERT(add(-1, -1) == -2);
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("LexerTestSuite", 0, 0);
    CU_add_test(suite, "test of lexer", test_lexer);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

