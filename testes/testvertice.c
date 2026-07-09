#include "unity.h"
#include "vertice.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_criar_e_validar_vertice(void) {
    Vertice v = criarVertice("v1", 10.5, 20.5);
    
    TEST_ASSERT_NOT_NULL(v);
    TEST_ASSERT_EQUAL_STRING("v1", getVerticeId(v));
    TEST_ASSERT_EQUAL_FLOAT(10.5, getVerticeX(v));
    TEST_ASSERT_EQUAL_FLOAT(20.5, getVerticeY(v));
    
    destruirVertice(v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_criar_e_validar_vertice);
    return UNITY_END();
}