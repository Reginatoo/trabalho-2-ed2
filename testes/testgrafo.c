#include "unity.h"
#include "grafo.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_criar_e_liberar_grafo_vazio(void) {
    Grafo g = criarGrafo(10);
    
    TEST_ASSERT_NOT_NULL(g);
    
    liberarGrafo(g);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_criar_e_liberar_grafo_vazio);
    return UNITY_END();
}