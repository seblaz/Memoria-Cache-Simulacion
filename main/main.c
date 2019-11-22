//
// Created by sebas on 21/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/cache.h"

void read_file(char *file_path) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen(file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char *rmg;
    while (getline(&line, &len, fp) != -1) {
        if (strncmp(line, "FLUSH", 5) == 0){
            printf("Se ejecuta init().\n");
            init();
        }else if (line[0] == 'R') {
            unsigned int address = atoi(line + 2);
            printf("Se ejecuta read_byte(%i) con resultado: %u.\n", address, read_byte(address));
        } else if (line[0] == 'W') {
            unsigned int address = strtol(line + 2, &rmg, 10);
            unsigned int value = strtol(rmg + 2, &rmg, 10);
            printf("Se ejecuta write_byte(%i, %i).\n", address, value);
            write_byte(address, value);
        } else if (line[0] == 'M' && line[1] == 'R'){
            printf("Se ejecuta get_miss_rate() con resultado: %f.\n", get_miss_rate());
        }
    }

    fclose(fp);
    if (line) free(line);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s", "Uso: nombre_de_archivo_con_comandos.\n");
        return 1;
    }

    init();
    read_file(argv[1]);
}

