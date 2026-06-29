#include "unity.h"
#include "geo.h"
#include "quadra.h"

void setUp(void) {e
}

void tearDown(void) {
}

void test_criar_e_destruir_geo_vazio(void) {
    Geo g = criarGeo();
    TEST_ASSERT_NOT_NULL(g);
    destruirGeo(g);
}

void test_adicionar_e_buscar_quadra_no_geo(void) {
    Geo g = criarGeo();
    Quadra q = criarQuadra("cep123", 10.0, 20.0, 30.0, 40.0);
    
    geoAdicionarQuadra(g, q);
    
    Quadra encontrada = geoBuscarQuadra(g, "cep123"); 
    TEST_ASSERT_NOT_NULL(encontrada);
    TEST_ASSERT_EQUAL_STRING("cep123", getQuadraCep(encontrada));
    
    Quadra nao_existente = geoBuscarQuadra(g, "cep999");
    TEST_ASSERT_NULL(nao_existente);
    
    destruirGeo(g);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_criar_e_destruir_geo_vazio);
    RUN_TEST(test_adicionar_e_buscar_quadra_no_geo);
    return UNITY_END();
}