#include "../include/types.h"
#include "../include/mem.h"

void write_word(u32 address, u32 value) {
    *(u32*) address = value;
}

u32 read_word(u32 address) {
    return *(u32*) address;
}