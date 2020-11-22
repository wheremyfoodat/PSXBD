#pragma once
#include "types.h"
#define KILOBYTE 1024

/// Size of main RAM
/// First 64KB are reserved for the BIOS
static const u32 MAIN_RAM_SIZE = 2048 * KILOBYTE;

/// Size of BIOS RAM
/// Resides in the first 64KB of main RAM
static const u32 BIOS_RAM_SIZE = 64 * KILOBYTE; 

/// Size of Expansion 1 (ROM/RAM)
static const u32 EXPANSION1_SIZE = 8192 * KILOBYTE;
/// Size of Expansion 2 (I/O ports)
static const u32 EXPANSION2_SIZE = 8 * KILOBYTE;
/// Size of Expansion 3 (For ?)
static const u32 EXPANSION3_SIZE = 2048 * KILOBYTE;

/// Size of BIOS ROM
static const u32 BIOS_ROM_SIZE = 512 * KILOBYTE;

/// Start of KUSEG region
static const u32 KUSEG_START = 0;
/// Start of KSEG0 region
static const u32 KSEG0_START = 0x80000000;
/// Start of KSEG1 region
static const u32 KSEG1_START = 0xA0000000;

void write_word(u32 address, u32 val);
u32 read_word(u32 address);

#undef KILOBYTE