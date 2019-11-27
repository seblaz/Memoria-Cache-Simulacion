#ifndef TP2_CACHE_H
#define TP2_CACHE_H

#include <stdbool.h>

#define SIZE_BLOQUE 64
#define BLOQUES_POR_CONJUNTO 8
#define CANT_CONJUNTOS 32
#define TAG 5
#define INDEX 5
#define OFFSET 6
#define TAMANIO_DE_MEMORIA 65536

void init();

/**
 * Memoria principal.
 */
 struct memoria_principal {
    unsigned char data [65536];
} memoria_principal;

void iniciar_memoria_principal();

/**
 * Cache.
 * Tamaño: 16 KB.
 * Direcciones: 16 bits.
 * Conjuntos: 32.
 * Bloque: 64 bytes (32 conjuntos).
 * Vias: 8.
 * Tag: 5 bits.
 * Index: 5 bits.
 * Offset: 6 bits.
 */
struct bloque {
    unsigned int numero;
    bool valido;
    bool dirty;
    unsigned char tag;
    unsigned char data[SIZE_BLOQUE];
};

struct conjunto {
    struct bloque vias[BLOQUES_POR_CONJUNTO];
};

struct cache {
    unsigned int hits;
    unsigned int missses;
    unsigned int ultimoBloque;
    struct conjunto conjuntos[CANT_CONJUNTOS];
} cache;

void iniciar_cache();

unsigned int get_offset(unsigned int address);

unsigned int get_tag(unsigned int address);

unsigned int get_memblock(unsigned int address);

unsigned int find_set(unsigned int address);

/**
 * Devuelve el bloque más antiguo del conjunto setnum.
 * @param setnum
 * @return
 */
unsigned int select_oldest(unsigned int setnum);

/**
 * Devuelve el valor que se encuentra en address. En caso de que no se encuentre
 * en la cache trae el bloque completo de la memoria a la cache.
 * @param address
 * @return
 */
unsigned char read_byte(unsigned int address);

/**
 * Trae el bloque blocknum de memoria a cache en la via way y conjunto set. Si
 * el bit dirty está en true escribe al bloque en memoria antes de reeemplazarlo.
 * @param blocknum
 * @param way
 * @param set
 */
void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set);

/**
 * Escribe value en adress. Al ser write back solo se escribe en la cache, y si
 * no se encuentra en cache trae el bloque completo a cache.
 * @param address
 * @param value
 */
void write_byte(unsigned int address, unsigned char value);

/**
 * En un reemplazo se utiliza para escribir el bloque de cache reemplazado en memoria.
 * @param way: via que va a escribirse a memoria.
 * @param set: conjunto que se selecciona para escribirse a memoria.
 */
void write_tomem(unsigned int way, unsigned int set);

float get_miss_rate();

#endif //TP2_CACHE_H
