#include "../include/hardware.h"
#include "../include/mem.h"
#include "../include/cop.h"
#include "../include/init.h"

void init_bios_and_ram() {
    write_word(rBIOS_MEM_CTRL, 0x13243F); // Init the BIOS ROM control register
    asm("nop"); // Wait for the changes to take effect?
    write_word(rRAM_SIZE, 0xB88); // init RAM
  
    #pragma GCC unroll 20
    for (int i = 0; i < 20; i++) { // 20 cycle delay for changes to take effect
        asm("nop");
    }

}

// Initializes some expansion memory ports, mainly the memory size/delay ones and the base addresses for Expansion 1/2
// A lot of these, like the expansion 1/2 base ones tend to not be changed by software
void init_expansion_mem() {
    write_word(rCOM_DELAY, 0x31125); // Initialize COM delay
    write_word(rEXPANSION1_BASE, 0x1F000000); // Initialize the Expansion 1 Base Address register (This is usually not changed by games).
    write_word(rEXPANSION2_BASE, 0x1F802000); // Initialize the Expansion 2 Base Address register (This is usually not changed by games).
    write_word(rEXPANSION1_CTRL, 0x13243F); // Initialize memory size and delay registers
    write_word(rSPU_MEM_CTRL, 0x200931E1);
    write_word(rCDROM_MEM_CTRL, 0x20843);
    write_word(rEXPANSION3_CTRL, 0x3022);
    write_word(rEXPANSION2_CTRL, 0x70777); // TODO: Double check
}


void init() {
    init_bios_and_ram();
    init_expansion_mem();
    write_cop0_reg(STATUS, 0x10000); // Turn "Isolate data cache in cop0 on"
                                     // Per nocash: When isolated, all load and store operations are targetted
                                     // to the Data cache, and never the main memory.
                                     // (Used by PSX Kernel, in combination with Port FFFE0130h)

    asm("nop"); // wait for that to take effect
    asm("nop");

    for (int i = 0; i != 0xF80; i += 0x80) { // loop to initialize some of BIOS RAM to 0. This is some very ugly programming huh
        write_word(i, 0);
        write_word(i + 0x10, 0);
        write_word(i + 0x20, 0);
        write_word(i + 0x30, 0);
        write_word(i + 0x40, 0);
        write_word(i + 0x50, 0);
        write_word(i + 0x60, 0);
        write_word(i + 0x70, 0);
    }

    write_cop0_reg(STATUS, 0); // Turn cache isolation off
    asm("nop"); // small delay
    write_word(rCACHE_CONTROL, 0x800); // Enable code cache
    write_cop0_reg(STATUS, 0x10000); // Re-enable cache isolation?
}