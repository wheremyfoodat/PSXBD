#pragma once
#include "types.h"

/// Base address for expansion 1 (bits 24-31 hardcoded on the PSX?)
static const u32 rEXPANSION1_BASE = 0x1F801000;
/// Base address for expansion 2 (bits 24-31 hardcoded on the PSX?)
static const u32 rEXPANSION2_BASE = 0x1F801004;

/// Expansion 1 Size and Delay register
static const u32 rEXPANSION1_CTRL = 0x1F801008;
/// Expansion 3 Size and Delay register
static const u32 rEXPANSION3_CTRL = 0x1F80100C;
/// BIOS ROM Size and Delay register
static const u32 rBIOS_MEM_CTRL = 0x1F801010;
/// SPU Memory Size and Delay
static const u32 rSPU_MEM_CTRL = 0x1F801014;
/// CDROM Memory Size and Delay
static const u32 rCDROM_MEM_CTRL = 0x1F801018;
/// Expansion 2 Size and Delay register
static const u32 rEXPANSION2_CTRL = 0x1F80101C;

///  Cycle offsets that can be added to the Access Time values in ports 0x1F801008 to 0x1F80101C
static const u32 rCOM_DELAY = 0x1F801020;
/// RAM size register (usually 0xB88 or 0x888)
static const u32 rRAM_SIZE = 0x1F801060;

/// Cache Control (R/W)
static const u32 rCACHE_CONTROL = 0xFFFE0130;