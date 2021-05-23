//
//  cpu.hpp
//
//  Created 12/27/20.
//

#ifndef cpu_hpp
#define cpu_hpp

#include <cstdint>
#include <bitset>
#include <iostream>
#include <fstream>

#include "cartridge.hpp"
#include "iobus.hpp"

// need to rewrite logging as it's taking too much time to output each line, only enable for debug
#define fprintf //

struct CPUinstruction {
    uint8_t opcode;
    uint16_t location;
    uint16_t target;
};


class CPU {
    
public:
    
    const float CPU_FREQ = 1790000;
    
    CPU(std::shared_ptr<IOBus> iob): _sp{0xFD}, _a{0}, _x{0}, _y{0}, _cycle_cnt{0}, _iob{iob}
    {
   //     _iob = std::make_unique<IOBus>(c);
        _setFlag(CPUFlags::U);
        _pc = _iob->readMemory(0xFFFD) * 256 + _iob->readMemory(0xFFFC);
        _CPULOG = fopen ("cpu_log2.txt", "w");
    }
    
    uint32_t CPU_cycle();
    void ProcessDMAcycles();
    
private:
    
    FILE * _CPULOG;
    
    uint8_t _a;
    uint8_t _x;
    uint8_t _y;
    uint8_t _sp;
    uint16_t _pc;

    std::bitset<8> _flags;

    enum class CPUFlags {
        C=0,    // Carry
        Z,      // Zero
        I,      // Interrupt Disable
        D,      // Decimal mode (not used in NES)
        B,      // Break Command
        U,      // Unused
        V,      // Overflow
        N       // Negative
    } ;
    
    uint32_t _cycle_cnt;
    
    std::shared_ptr<IOBus> _iob;
    
    uint8_t _fetchOpcode();
    void _decodeInstruction(uint8_t);
    void _executeInstruction(uint8_t);
    
    inline void _push(uint8_t value)
    {
        _iob->writeMemory(0x100 | _sp, value);
        _sp--;
    }
    
    inline uint8_t _pop(void)
    {
        uint8_t value;
        _sp++;
        value = _iob->readMemory(0x100 | _sp);
        return value;
    }
    
    
    inline uint8_t _getFlag(CPUFlags f)
    {
        return _flags.test(static_cast<uint8_t>(f));
    }
    
    inline void _setFlag(CPUFlags f)
    {
        _flags.set(static_cast<uint8_t>(f));
    }
    
    inline void _resetFlag(CPUFlags f)
    {
        _flags.reset(static_cast<uint8_t>(f));
    }
    
    inline uint8_t _getFlags(void)
    {
        return static_cast<uint8_t>(_flags.to_ulong());
    }
    
    inline void _setFlags(uint8_t f)
    {
        _flags = f;
    }
    
    inline void _printCPUStatus(void)
    {
        fprintf(_CPULOG, "\t A: %#04x X: %#04x Y: %#04x SP: %#04x ", (uint8_t)(_a), (uint8_t)(_x), (uint8_t)(_y), (uint8_t)(_sp)); // easier to handle printing char with printf
        
        fprintf(_CPULOG,"Flags %lu CYC: %d\n", _flags.to_ulong(),_cycle_cnt);
    }
    
    inline void _checkPageCrossing(uint16_t a, uint16_t b)
    {
        if((a & 0xFF00) != (b & 0xFF00))
            _cycle_cnt++;
    }
    
    // **** Basic opcodes functions
    void _generic_ADC(int16_t, bool load);
    void _generic_AND(int16_t, bool load);
    void _generic_ASL(int16_t, bool load);
    void _generic_BCC(int16_t, bool load);
    void _generic_BCS(int16_t, bool load);
    void _generic_BEQ(int16_t, bool load);
    void _generic_BIT(int16_t, bool load);
    void _generic_BMI(int16_t, bool load);
    void _generic_BNE(int16_t, bool load);
    void _generic_BPL(int16_t, bool load);
    void _generic_BRK();
    void _generic_BVC(int16_t, bool load);
    void _generic_BVS(int16_t, bool load);
    void _generic_CLC();
    void _generic_CLD();
    void _generic_CLI();
    void _generic_CLV();
    void _generic_CMP(int16_t, bool load);
    void _generic_CPX(int16_t, bool load);
    void _generic_CPY(int16_t, bool load);
    void _generic_DEC(int16_t, bool load);
    void _generic_DEX();
    void _generic_DEY();
    void _generic_EOR(int16_t, bool load);
    void _generic_INC(int16_t, bool load);
    void _generic_INX();
    void _generic_INY();
    void _generic_JMP(int16_t, bool load);
    void _generic_JSR(int16_t, bool load);
    void _generic_LDA(int16_t, bool load);
    void _generic_LDX(int16_t, bool load);
    void _generic_LDY(int16_t, bool load);
    void _generic_LSR(int16_t, bool load);
    void _generic_NOP() {}
    void _generic_ORA(int16_t, bool load);
    void _generic_PHA();
    void _generic_PHP();
    void _generic_PLA();
    void _generic_PLP();
    void _generic_ROL(int16_t, bool load);
    void _generic_ROR(int16_t, bool load);
    void _generic_RTI();
    void _generic_RTS();
    void _generic_SBC(int16_t, bool load);
    void _generic_SEC();
    void _generic_SED();
    void _generic_SEI();
    void _generic_STA(int16_t, bool load);
    void _generic_STX(int16_t, bool load);
    void _generic_STY(int16_t, bool load);
    void _generic_TAX();
    void _generic_TAY();
    void _generic_TSX();
    void _generic_TXA();
    void _generic_TXS();
    void _generic_TYA();
   
    uint16_t AddrINDY(bool checkCrossing);
    uint16_t AddrINDX();
    uint16_t AddrABS();
    
    void ProcessNMI();
    

#include "opcodes.inl"

};


#endif /* cpu_hpp */
