#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void test_io(void) {

}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("IOTestSuite", 0, 0);
    CU_add_test(suite, "test of read_file()", test_io);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

