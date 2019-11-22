//
// Created by sebas on 21/11/19.
//

#include "cache_tests.h"
#include "../src/cache.h"
#include "testing.h"
#include <math.h>

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

void pruebas1() {
    init();
    write_byte(0, 255);
    write_byte(2048, 48);
    write_byte(4096, 96);
    write_byte(8192, 192);
    write_byte(16384, 84);
    write_byte(32768, 68);
    write_byte(12288, 88);
    write_byte(20480, 80);
    print_test("prueba1", read_byte(0) == 255);
    print_test("prueba1", read_byte(2048) == 48);
    print_test("prueba1", read_byte(4096) == 96);
    print_test("prueba1", read_byte(8192) == 192);
    print_test("prueba1", read_byte(16384) == 84);

    print_test("prueba1", read_byte(32768) == 68);
    print_test("prueba1", read_byte(12288) == 88);
    print_test("prueba1", read_byte(20480) == 80);
    write_byte(10240, 240);
    print_test("prueba1", read_byte(0) == 255);
    print_test("prueba1", fabs(get_miss_rate() - 0.555556) < 0.000001);
}

void pruebas2() {
    init();
    print_test("prueba2", read_byte(0) == 0);
    print_test("prueba2", read_byte(31) == 0);
    write_byte(64, 10);
    print_test("prueba2", read_byte(64) == 10);
    write_byte(64, 20);
    print_test("prueba2", read_byte(64) == 20);
    print_test("prueba2", fabs(get_miss_rate() - 0.333333) < 0.000001);
}

void pruebas3() {
    init();
    write_byte(0, 255);
    write_byte(1, 2);
    write_byte(2, 3);
    write_byte(3, 4);
    write_byte(4, 5);
    print_test("prueba3", read_byte(0) == 255);
    print_test("prueba3", read_byte(1) == 2);
    print_test("prueba3", read_byte(2) == 3);
    print_test("prueba3", read_byte(3) == 4);
    print_test("prueba3", read_byte(4) == 5);
    print_test("prueba3", read_byte(4096) == 0);
    print_test("prueba3", read_byte(8192) == 0);
    print_test("prueba3", read_byte(0) == 255);
    print_test("prueba3", read_byte(1) == 2);
    print_test("prueba3", read_byte(2) == 3);
    print_test("prueba3", read_byte(3) == 4);
    print_test("prueba3", read_byte(4) == 5);
    print_test("prueba3", fabs(get_miss_rate() - 0.176471) < 0.000001);
}

void pruebas4() {
    init();
    write_byte(128, 1);
    write_byte(129, 2);
    write_byte(130, 3);
    write_byte(131, 4);
    print_test("prueba4", read_byte(2176) == 0);
    print_test("prueba4", read_byte(4224) == 0);
    print_test("prueba4", read_byte(6272) == 0);
    print_test("prueba4", read_byte(8320) == 0);
    print_test("prueba4", read_byte(10368) == 0);
    print_test("prueba4", read_byte(12416) == 0);
    print_test("prueba4", read_byte(14464) == 0);
    print_test("prueba4", read_byte(16512) == 0);
    print_test("prueba4", read_byte(128) == 1);
    print_test("prueba4", read_byte(129) == 2);
    print_test("prueba4", read_byte(130) == 3);
    print_test("prueba4", read_byte(131) == 4);
    print_test("prueba4", fabs(get_miss_rate() - 0.625000) < 0.000001);
}

void pruebas_cache() {
    pruebas_get_offset();
    pruebas_find_set();
    pruebas1();
    pruebas2();
    pruebas3();
    pruebas4();
}