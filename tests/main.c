//
// Created by sebas on 21/11/19.
//

#include "testing.h"
#include "cache_tests.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ~~~\n");
    pruebas_cache();

    return failure_count() > 0;
}