//
// Created by sebas on 21/11/19.
//

#include "cache_tests.h"
#include "../src/cache.h"
#include "testing.h"

void pruebas_get_offset() {
    print_test("get offset con cero", get_offset(0) == 0);
    print_test("get offset con 31", get_offset(31) == 31);
    print_test("get offset con index, sin tag y offset cero", get_offset(64) == 0);
    print_test("get offset con index, sin tag y offset distinto de cero", get_offset(74) == 10);
    print_test("get offset con index, con tag y offset cero", get_offset(64 + 32768) == 0);
    print_test("get offset con index, con tag y offset distinto de cero", get_offset(64 + 32768 + 13) == 13);
}

void pruebas_find_set() {
    print_test("find set con cero", find_set(0) == 0);
    print_test("find set con 64", find_set(64) == 1);
    print_test("find set con tag", find_set(64 + 32768) == 1);
}

void pruebas_cache() {
    pruebas_get_offset();
    pruebas_find_set();
}