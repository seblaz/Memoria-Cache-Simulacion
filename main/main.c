//
// Created by sebas on 21/11/19.
//

#include <stdio.h>
#include "../src/memoria_principal.h"
#include "../src/cache.h"

void init() {
    iniciar_memoria_principal();
    iniciar_cache();
}

void read_file(char *file_path) {

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s", "Uso: nombre_de_archivo_con_comandos.\n");
        return 1;
    }

    init();
    read_file(argv[1]);
}

