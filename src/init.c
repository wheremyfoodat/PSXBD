#include "../include/hardware.h"
#include "../include/mem.h"
#include "../include/cop.h"
#include "../include/init.h"
#include "../include/types.h"

void init_bios_and_ram() {
    write_word(rBIOS_MEM_CTRL, 0x13243F); // Init the BIOS ROM control register
    asm("nop"); // Wait for the changes to take effect?
    write_word(rRAM_SIZE, 0xB88); // init RAM
  
    #pragma GCC unroll 20
    for (int i = 0; i < 20; i++) { // 20 cycle delay for changes to take effect
        asm("nop");
    }

}

/// Initializes some expansion memory ports, mainly the memory size/delay ones and the base addresses for Expansion 1/2
/// A lot of these, like the expansion 1/2 base ones tend to not be changed by software
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

/// Initializes the cache
void init_cache() {
    write_cop0_reg(STATUS, 0x10000); // Turn "Isolate data cache in cop0 on"
                                     // Per nocash: When isolated, all load and store operations are targetted
                                     // to the Data cache, and never the main memory.
                                     // (Used by PSX Kernel, in combination with Port FFFE0130h)

    asm("nop"); // wait for that change to take effect
    asm("nop");

    // LAB_0xBFC00248
    for (u32 i = 0; i != 0xF80; i += 0x80) { // loop to initialize some of the data cache to 0. This is some very ugly programming huh
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
    asm("nop"); // small delay for change to take effect
    write_word(rCACHE_CONTROL, 0x800); // Enable code cache
    write_cop0_reg(STATUS, 0x10000); // Re-enable cache isolation?
    asm("nop"); // small delay for change to take effect
    asm("nop");

    // LAB_0xBFC002A0
    for (u32 i = 0; i != 0xF80; i += 0x80) { // initialize data cache... again? 
        #pragma gcc unroll 32 // This inner loop is completely unrolled in the binary. Gotta get that epic 0.0003ns speed boost when booting
        for (u32 j = 0; j < 0x80; j += 4) {
            write_word (i + j, 0);
        }
    }

    write_cop0_reg(STATUS, 0); // Turn cache isolation off
    
    // After turning cache isolation off, the BIOS spends some time reading from uninitialized RAM
    // address 0xA0000000, then does nothing with the value it reads. Don't ask why.
    #pragma gcc unroll 8
    for (int i = 0; i < 8; i++) {
        volatile u32 temp = read_word(0xA0000000);
    }

    write_word(rCACHE_CONTROL, 0x0001E988); // finish off cache initialization by writing to cache control one last time
}

/// Sets some cop0 regs to 0
void init_cop0() { 
    write_cop0_reg(DCIC, 0);
    write_cop0_reg(BPC, 0);
    write_cop0_reg(BDA, 0);
    write_cop0_reg(JUMPDEST, 0);
    write_cop0_reg(BDAM, 0);
    write_cop0_reg(BPCM, 0);
    write_cop0_reg(STATUS, 0); // STATUS is already 0 by this time but cheers
    write_cop0_reg(CAUSE, 0);
}

void init() {
    init_bios_and_ram();
    init_expansion_mem();
    init_cache();
    init_cop0();

    // LAB_0xBFC003A8
    for (u32 i = 0xA0009000; i < 0xA000C160; i += 4) {  // Initialize some of Kernel RAM to 0
        write_word(i, 0);
    }
    write_word(rRAM_SIZE, 0xB88); // Write 0xB88 to RAM_SIZE... again!
}