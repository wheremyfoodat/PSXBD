#pragma once

enum cop0_reg {
    /// Breakpoint on execute (R/W)
    BPC = 3,
    /// Breakpoing on data access (R/W)
    BDA = 5,
    /// Randomly memorized jump address (R/W)
    JUMPDEST = 6,
    /// Breakpoint control (R/W)
    DCIC = 7,
    /// Bad virtual address (R)
    BadVaddr = 8,
    /// Data access breakpoint mask (R/W)
    BDAM = 9,
    /// Execute breakpoint mask (R/W)
    BPCM = 11,
    /// System status register (R/W)
    STATUS = 12,
    /// Most recently recognised exception (R)
    CAUSE = 13,
    /// Return Address from Trap (R)
    EPC = 14,
    /// Processor ID (R)
    PRID = 15
};

void write_cop0_reg(enum cop0_reg reg, u32 value);