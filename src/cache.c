//
// Created by sebas on 21/11/19.
//

#include "cache.h"
#include <string.h>

void iniciar_cache() {
    cache.hits = 0;
    cache.missses = 0;
    cache.ultimoBloque = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 8; j++) {
            cache.conjuntos[i].vias[j].valido = false;
            cache.conjuntos[i].vias[j].dirty = false;
            cache.conjuntos[i].vias[j].numero = 0;
        }
}

void iniciar_memoria_principal() {
     memset(memoria_principal.data, 0, sizeof memoria_principal);
}

void init(){
    iniciar_cache();
    iniciar_memoria_principal();
}

unsigned int get_offset(unsigned int address) {
    return address & 0b00111111;
}

unsigned int find_set(unsigned int address) {
    return (address & 0b011111000000) >> OFFSET;
}

unsigned int get_tag(unsigned int address) {
    return address >> (OFFSET + INDEX);
}

unsigned int get_memblock(unsigned int address) {
    return address >> (OFFSET);
}

unsigned int select_oldest(unsigned int setnum) {
    unsigned int via = 0;
    unsigned int min = cache.conjuntos[setnum].vias[via].numero;
    for (int j = 1; j < BLOQUES_POR_CONJUNTO; j++)
        if (cache.conjuntos[setnum].vias[j].numero < min) {
            min = cache.conjuntos[setnum].vias[j].numero;
            via = j;
        }
    return via;
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    if (cache.conjuntos[set].vias[way].valido && cache.conjuntos[set].vias[way].dirty)
        write_tomem(way, set); // Escribo el bloque en memoria.

    for (int i = 0; i < SIZE_BLOQUE; i++)
        cache.conjuntos[set].vias[way].data[i] = memoria_principal.data[blocknum * SIZE_BLOQUE + i];

    cache.conjuntos[set].vias[way].numero = ++cache.ultimoBloque;
    cache.conjuntos[set].vias[way].dirty = false;
    cache.conjuntos[set].vias[way].valido = true;
    cache.conjuntos[set].vias[way].tag = get_tag(blocknum * SIZE_BLOQUE);
}

unsigned char read_byte(unsigned int address) {
    unsigned int conjunto = find_set(address);
    unsigned int tag = get_tag(address);
    unsigned int offset = get_offset(address);
    for (int i = 0; i < BLOQUES_POR_CONJUNTO; i++)
        if (cache.conjuntos[conjunto].vias[i].valido && cache.conjuntos[conjunto].vias[i].tag == tag) {
            cache.hits++;
            return cache.conjuntos[conjunto].vias[i].data[offset];
        }

    // El dato no se encuentra en cache => cargo el bloque y devuelvo el dato.
    cache.missses++;
    unsigned int way = select_oldest(conjunto);
    read_tocache(get_memblock(address), way, conjunto);
    return cache.conjuntos[conjunto].vias[way].data[offset];
}

void write_byte(unsigned int address, unsigned char value) {
    unsigned int conjunto = find_set(address);
    unsigned int tag = get_tag(address);
    unsigned int offset = get_offset(address);
    for (int i = 0; i < BLOQUES_POR_CONJUNTO; i++)
        if (cache.conjuntos[conjunto].vias[i].valido && cache.conjuntos[conjunto].vias[i].tag == tag) {
            cache.hits++;
            cache.conjuntos[conjunto].vias[i].data[offset] = value;
            return;
        }

    // El dato no se encuentra en cache => cargo el bloque y lo escribo.
    cache.missses++;
    unsigned int way = select_oldest(conjunto);
    read_tocache(get_memblock(address), way, conjunto);
    cache.conjuntos[conjunto].vias[way].dirty = true;
    cache.conjuntos[conjunto].vias[way].data[offset] = value;
}

void write_tomem(unsigned int way, unsigned int set) {
    unsigned int tag = cache.conjuntos[set].vias[way].tag;
    unsigned int address = (tag << (INDEX + OFFSET)) + (set << OFFSET);
    for (int i = 0; i < SIZE_BLOQUE; i++)
        memoria_principal.data[address + i] = cache.conjuntos[set].vias[way].data[i];
}

float get_miss_rate() {
    return (float) cache.missses / (float) (cache.hits + cache.missses);
}
