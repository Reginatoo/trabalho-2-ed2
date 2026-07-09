#include "unity.h"
#include "quadra.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_criar_e_validar_quadra(void) {
    Quadra q = criarQuadra("cep123", 100.0, 200.0, 50.0, 30.0);
    
    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_EQUAL_STRING("cep123", getQuadraCep(q));
    TEST_ASSERT_EQUAL_FLOAT(100.0, getQuadraX(q));
    TEST_ASSERT_EQUAL_FLOAT(200.0, getQuadraY(q));
    TEST_ASSERT_EQUAL_FLOAT(50.0, getQuadraW(q));
    TEST_ASSERT_EQUAL_FLOAT(30.0, getQuadraH(q));
    
    destruirQuadra(q);
}

void test_configurar_cores_quadra(void) {
    Quadra q = criarQuadra("cep999", 0.0, 0.0, 10.0, 10.0);
    
    setQuadraCores(q, "blue", "red", 1.5);
    TEST_ASSERT_EQUAL_STRING("blue", getQuadraCfill(q));
    TEST_ASSERT_EQUAL_STRING("red", getQuadraCstrk(q));
    TEST_ASSERT_EQUAL_FLOAT(1.5, getQuadraSw(q));
    
    destruirQuadra(q);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_criar_e_validar_quadra);
    RUN_TEST(test_configurar_cores_quadra);
    return UNITY_END();
}