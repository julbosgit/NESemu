//
//  cpu.cpp
//
//  Created 12/27/20.
//

#include "cpu.hpp"

// \JB hack for now to test
extern bool NMIDONE;



uint32_t CPU::CPU_cycle()
{
    uint8_t op;
        
    fprintf(_CPULOG, "%#06x\t",_pc);
    
    if(_iob->m_NMICallback())
        ProcessNMI();
        
    op = _fetchOpcode();
    _executeInstruction(op);
    _printCPUStatus();
    fflush(_CPULOG);

    return _cycle_cnt;
}

void CPU::ProcessNMI()
{
    uint8_t target[2];
    
    fprintf(_CPULOG,"\n **** NMI ****** \n");
    
    _push(static_cast<int8_t>((_pc >> 8)));
    _push(static_cast<int8_t>(_pc));
    
    _push(static_cast<int8_t>(_flags.to_ulong()));
    
    target[0] = _iob->readMemory(0xFFFA);
    target[1] = _iob->readMemory(0xFFFB);
    _pc = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8);
    
}

void CPU::ProcessDMAcycles()
{
    if (_cycle_cnt % 2)
        _cycle_cnt++;
    
    _cycle_cnt += 513;
}

uint8_t CPU::_fetchOpcode()
{
    return(_iob->readMemory(_pc++));
}


void CPU::_decodeInstruction(uint8_t opcode)
{
    
}



void CPU::_executeInstruction(uint8_t opcode)
{
//    std::cout << " CYC_before: " << std::dec << _cycle_cnt << "\t\t";
    switch(opcode)
    {
        case 0: _cycle_cnt += BRK_IMP() ; break;
        case 1: _cycle_cnt += ORA_INDX() ; break;
        case 4: _cycle_cnt += NOP_ZP() ; break;
        case 5: _cycle_cnt += ORA_ZP() ; break;
        case 6: _cycle_cnt += ASL_ZP() ; break;
        case 8: _cycle_cnt += PHP_IMP() ; break;
        case 9: _cycle_cnt += ORA_IMM() ; break;
        case 10: _cycle_cnt += ASL_ACC() ; break;
        case 12: _cycle_cnt += NOP_ABS() ; break;
        case 13: _cycle_cnt += ORA_ABS() ; break;
        case 14: _cycle_cnt += ASL_ABS() ; break;
        case 16: _cycle_cnt += BPL_REL() ; break;
        case 17: _cycle_cnt += ORA_INDY() ; break;
        case 21: _cycle_cnt += ORA_ZPX() ; break;
        case 22: _cycle_cnt += ASL_ZPX() ; break;
        case 24: _cycle_cnt += CLC_IMP() ; break;
        case 25: _cycle_cnt += ORA_ABSY() ; break;
        case 29: _cycle_cnt += ORA_ABSX() ; break;
        case 30: _cycle_cnt += ASL_ABSX() ; break;
        case 32: _cycle_cnt += JSR_ABS() ; break;
        case 33: _cycle_cnt += AND_INDX() ; break;
        case 36: _cycle_cnt += BIT_ZP() ; break;
        case 37: _cycle_cnt += AND_ZP() ; break;
        case 38: _cycle_cnt += ROL_ZP() ; break;
        case 40: _cycle_cnt += PLP_IMP() ; break;
        case 41: _cycle_cnt += AND_IMM() ; break;
        case 42: _cycle_cnt += ROL_ACC() ; break;
        case 44: _cycle_cnt += BIT_ABS() ; break;
        case 45: _cycle_cnt += AND_ABS() ; break;
        case 46: _cycle_cnt += ROL_ABS() ; break;
        case 48: _cycle_cnt += BMI_REL() ; break;
        case 49: _cycle_cnt += AND_INDY() ; break;
        case 53: _cycle_cnt += AND_ZPX() ; break;
        case 54: _cycle_cnt += ROL_ZPX() ; break;
        case 56: _cycle_cnt += SEC_IMP() ; break;
        case 57: _cycle_cnt += AND_ABSY() ; break;
        case 61: _cycle_cnt += AND_ABSX() ; break;
        case 62: _cycle_cnt += ROL_ABSX() ; break;
        case 64: _cycle_cnt += RTI_IMP() ; break;
        case 65: _cycle_cnt += EOR_INDX() ; break;
        case 69: _cycle_cnt += EOR_ZP() ; break;
        case 70: _cycle_cnt += LSR_ZP() ; break;
        case 72: _cycle_cnt += PHA_IMP() ; break;
        case 73: _cycle_cnt += EOR_IMM() ; break;
        case 74: _cycle_cnt += LSR_ACC() ; break;
        case 76: _cycle_cnt += JMP_ABS() ; break;
        case 77: _cycle_cnt += EOR_ABS() ; break;
        case 78: _cycle_cnt += LSR_ABS() ; break;
        case 80: _cycle_cnt += BVC_REL() ; break;
        case 81: _cycle_cnt += EOR_INDY() ; break;
        case 85: _cycle_cnt += EOR_ZPX() ; break;
        case 86: _cycle_cnt += LSR_ZPX() ; break;
        case 88: _cycle_cnt += CLI_IMP() ; break;
        case 89: _cycle_cnt += EOR_ABSY() ; break;
        case 93: _cycle_cnt += EOR_ABSX() ; break;
        case 94: _cycle_cnt += LSR_ABSX() ; break;
        case 96: _cycle_cnt += RTS_IMP() ; break;
        case 97: _cycle_cnt += ADC_INDX() ; break;
        case 101: _cycle_cnt += ADC_ZP() ; break;
        case 102: _cycle_cnt += ROR_ZP() ; break;
        case 104: _cycle_cnt += PLA_IMP() ; break;
        case 105: _cycle_cnt += ADC_IMM() ; break;
        case 106: _cycle_cnt += ROR_ACC() ; break;
        case 108: _cycle_cnt += JMP_IND() ; break;
        case 109: _cycle_cnt += ADC_ABS() ; break;
        case 110: _cycle_cnt += ROR_ABS() ; break;
        case 112: _cycle_cnt += BVS_REL() ; break;
        case 113: _cycle_cnt += ADC_INDY() ; break;
        case 117: _cycle_cnt += ADC_ZPX() ; break;
        case 118: _cycle_cnt += ROR_ZPX() ; break;
        case 120: _cycle_cnt += SEI_IMP() ; break;
        case 121: _cycle_cnt += ADC_ABSY() ; break;
        case 125: _cycle_cnt += ADC_ABSX() ; break;
        case 126: _cycle_cnt += ROR_ABSX() ; break;
        case 129: _cycle_cnt += STA_INDX() ; break;
        case 132: _cycle_cnt += STY_ZP() ; break;
        case 133: _cycle_cnt += STA_ZP() ; break;
        case 134: _cycle_cnt += STX_ZP() ; break;
        case 136: _cycle_cnt += DEY_IMP() ; break;
        case 138: _cycle_cnt += TXA_IMP() ; break;
        case 140: _cycle_cnt += STY_ABS() ; break;
        case 141: _cycle_cnt += STA_ABS() ; break;
        case 142: _cycle_cnt += STX_ABS() ; break;
        case 144: _cycle_cnt += BCC_REL() ; break;
        case 145: _cycle_cnt += STA_INDY() ; break;
        case 148: _cycle_cnt += STY_ZPX() ; break;
        case 149: _cycle_cnt += STA_ZPX() ; break;
        case 150: _cycle_cnt += STX_ZPY() ; break;
        case 152: _cycle_cnt += TYA_IMP() ; break;
        case 153: _cycle_cnt += STA_ABSY() ; break;
        case 154: _cycle_cnt += TXS_IMP() ; break;
        case 157: _cycle_cnt += STA_ABSX() ; break;
        case 160: _cycle_cnt += LDY_IMM() ; break;
        case 161: _cycle_cnt += LDA_INDX() ; break;
        case 162: _cycle_cnt += LDX_IMM() ; break;
        case 164: _cycle_cnt += LDY_ZP() ; break;
        case 165: _cycle_cnt += LDA_ZP() ; break;
        case 166: _cycle_cnt += LDX_ZP() ; break;
        case 168: _cycle_cnt += TAY_IMP() ; break;
        case 169: _cycle_cnt += LDA_IMM() ; break;
        case 170: _cycle_cnt += TAX_IMP() ; break;
        case 172: _cycle_cnt += LDY_ABS() ; break;
        case 173: _cycle_cnt += LDA_ABS() ; break;
        case 174: _cycle_cnt += LDX_ABS() ; break;
        case 176: _cycle_cnt += BCS_REL() ; break;
        case 177: _cycle_cnt += LDA_INDY() ; break;
        case 180: _cycle_cnt += LDY_ZPX() ; break;
        case 181: _cycle_cnt += LDA_ZPX() ; break;
        case 182: _cycle_cnt += LDX_ZPY() ; break;
        case 184: _cycle_cnt += CLV_IMP() ; break;
        case 185: _cycle_cnt += LDA_ABSY() ; break;
        case 186: _cycle_cnt += TSX_IMP() ; break;
        case 188: _cycle_cnt += LDY_ABSX() ; break;
        case 189: _cycle_cnt += LDA_ABSX() ; break;
        case 190: _cycle_cnt += LDX_ABSY() ; break;
        case 192: _cycle_cnt += CPY_IMM() ; break;
        case 193: _cycle_cnt += CMP_INDX() ; break;
        case 196: _cycle_cnt += CPY_ZP() ; break;
        case 197: _cycle_cnt += CMP_ZP() ; break;
        case 198: _cycle_cnt += DEC_ZP() ; break;
        case 200: _cycle_cnt += INY_IMP() ; break;
        case 201: _cycle_cnt += CMP_IMM() ; break;
        case 202: _cycle_cnt += DEX_IMP() ; break;
        case 204: _cycle_cnt += CPY_ABS() ; break;
        case 205: _cycle_cnt += CMP_ABS() ; break;
        case 206: _cycle_cnt += DEC_ABS() ; break;
        case 208: _cycle_cnt += BNE_REL() ; break;
        case 209: _cycle_cnt += CMP_INDY() ; break;
        case 213: _cycle_cnt += CMP_ZPX() ; break;
        case 214: _cycle_cnt += DEC_ZPX() ; break;
        case 216: _cycle_cnt += CLD_IMP() ; break;
        case 217: _cycle_cnt += CMP_ABSY() ; break;
        case 221: _cycle_cnt += CMP_ABSX() ; break;
        case 222: _cycle_cnt += DEC_ABSX() ; break;
        case 224: _cycle_cnt += CPX_IMM() ; break;
        case 225: _cycle_cnt += SBC_INDX() ; break;
        case 228: _cycle_cnt += CPX_ZP() ; break;
        case 229: _cycle_cnt += SBC_ZP() ; break;
        case 230: _cycle_cnt += INC_ZP() ; break;
        case 232: _cycle_cnt += INX_IMP() ; break;
        case 233: _cycle_cnt += SBC_IMM() ; break;
        case 234: _cycle_cnt += NOP_IMP() ; break;
        case 236: _cycle_cnt += CPX_ABS() ; break;
        case 237: _cycle_cnt += SBC_ABS() ; break;
        case 238: _cycle_cnt += INC_ABS() ; break;
        case 240: _cycle_cnt += BEQ_REL() ; break;
        case 241: _cycle_cnt += SBC_INDY() ; break;
        case 245: _cycle_cnt += SBC_ZPX() ; break;
        case 246: _cycle_cnt += INC_ZPX() ; break;
        case 248: _cycle_cnt += SED_IMP() ; break;
        case 249: _cycle_cnt += SBC_ABSY() ; break;
        case 253: _cycle_cnt += SBC_ABSX() ; break;
        case 254: _cycle_cnt += INC_ABSX() ; break;
        default:
            if((opcode & 0x0C) == 0x0C) _pc+=2;
            else if((opcode & 0x0A) != 0x0A)_pc+=1;
            fprintf(_CPULOG, "%#04x \t\t\t*** UNKNOWN \t\t\t", opcode);NOT_SUPPORTED();
    }
}


void CPU::_generic_ADC(int16_t t, bool load)
{
    uint8_t b = _a;
    uint8_t oldCarry = _getFlag(CPUFlags::C);
    
    _resetFlag(CPUFlags::N);
    _resetFlag(CPUFlags::Z);
    _resetFlag(CPUFlags::V);
    
    if(load)
        t = _iob->readMemory(t);
    
    _a = _a + static_cast<uint8_t>(t);
    
    if (_getFlag(CPUFlags::C))
        _a++;

    _resetFlag(CPUFlags::C);
    
    if(((b & 0x80)==0) && ((t & 0x0080)==0) && (_a & 0x80)) {
        _setFlag(CPUFlags::V);
    }
    else if ((b & 0x80) && (t & 0x0080) && (_a & 0x80)==0){
        _setFlag(CPUFlags::V);
    }
    if((static_cast<uint16_t>(t) + b + oldCarry) >= 0x100)
        _setFlag(CPUFlags::C);
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    
    
}


void CPU::_generic_AND(int16_t t, bool load)
{
    _resetFlag(CPUFlags::N);
    _resetFlag(CPUFlags::Z);
    
    if(load)
        t = _iob->readMemory(t);
    
    _a = _a & static_cast<int8_t>(t);
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    
    
}

void CPU::_generic_ASL(int16_t t, bool load)
{
    uint8_t m, res;
    _resetFlag(CPUFlags::C);
    _resetFlag(CPUFlags::Z);
    _resetFlag(CPUFlags::N);
    if(load)
    {
        m = _iob->readMemory(t);
        if(m & 0x80)
            _setFlag(CPUFlags::C);
        
        m = m << 1;
        _iob->writeMemory(t,m);
        res = m;
    }
    else
    {
        if(_a & 0x80)
            _setFlag(CPUFlags::C);
        
        _a = _a << 1;
        res = _a;
    }
    
    if(res & 0x80)
        _setFlag(CPUFlags::N);
    if(res == 0)
        _setFlag(CPUFlags::Z);
    
    
}


void CPU::_generic_BCC(int16_t t, bool load)
{
    if(!_getFlag(CPUFlags::C)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
       _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}

void CPU::_generic_BCS(int16_t t, bool load)
{
    if(_getFlag(CPUFlags::C)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}


void CPU::_generic_BEQ(int16_t t, bool load)
{
    if(_getFlag(CPUFlags::Z)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}


void CPU::_generic_BIT(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);
    
    int8_t b = _a & static_cast<int8_t>(t);
    
 //   printf("BIT %#06x %#06x  %#06x \n", _a,t,b);
    
    if(b == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
    
    if(static_cast<int8_t>(t) & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    if(static_cast<int8_t>(t) & 0x40)
        _setFlag(CPUFlags::V);
    else
        _resetFlag(CPUFlags::V);

    
}


void CPU::_generic_BMI(int16_t t, bool load)
{
    if(_getFlag(CPUFlags::N)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}

void CPU::_generic_BNE(int16_t t, bool load)
{
    if(!_getFlag(CPUFlags::Z)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}

void CPU::_generic_BPL(int16_t t, bool load)
{
    if(!_getFlag(CPUFlags::N)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}

void CPU::_generic_BRK()
{
    _setFlag(CPUFlags::B);
    
    // Need to add 1 to PC, bug 6502
    _pc++;
    
    _push(static_cast<int8_t>((_pc >> 8)));
    _push(static_cast<int8_t>(_pc));
    
    _push(static_cast<int8_t>(_flags.to_ulong()));
    
    int8_t target[2];
    
    target[0] = _iob->readMemory(0xFFFE);
    target[1] = _iob->readMemory(0xFFFF);
    
    _pc = static_cast<int16_t>(target[0]) + (static_cast<int16_t>(target[1]) << 8 );
    
    
}


void CPU::_generic_BVC(int16_t t, bool load)
{
    if(!_getFlag(CPUFlags::V)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}

void CPU::_generic_BVS(int16_t t, bool load)
{
    if(_getFlag(CPUFlags::V)) {
        _cycle_cnt++;
        _checkPageCrossing(_pc, static_cast<int16_t>(_pc) + t);
        _pc = static_cast<int16_t>(_pc) + t;
    }
    
    
}

void CPU::_generic_CLC()
{
    _resetFlag(CPUFlags::C);
    
    
}

void CPU::_generic_CLD()
{
    _resetFlag(CPUFlags::D);
    
    
}

void CPU::_generic_CLI()
{
    _resetFlag(CPUFlags::I);
    
    
}

void CPU::_generic_CLV()
{
    _resetFlag(CPUFlags::V);
    
    
}

void CPU::_generic_CMP(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);
        
    uint8_t b = _a - static_cast<uint8_t>(t);
    
    if(_a >= static_cast<uint8_t>(t))
        _setFlag(CPUFlags::C);
    else
        _resetFlag(CPUFlags::C);
    
    if(_a == static_cast<uint8_t>(t))
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(b & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_CPX(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);
    
    uint8_t b = _x - static_cast<uint8_t>(t);
    
    if(_x >= static_cast<uint8_t>(t))
        _setFlag(CPUFlags::C);
    else
        _resetFlag(CPUFlags::C);
    
    if(_x == static_cast<uint8_t>(t))
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(b & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_CPY(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);
    
    uint8_t b = _y - static_cast<uint8_t>(t);
    
    if(_y >= static_cast<uint8_t>(t))
        _setFlag(CPUFlags::C);
    else
        _resetFlag(CPUFlags::C);
    
    if(_y == static_cast<uint8_t>(t))
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(b & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_DEC(int16_t t, bool load)
{
    uint8_t m = _iob->readMemory(t);

    m--;
    _iob->writeMemory(t,m);
    
    if(m == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(m & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_DEX()
{
    _x--;

    if(_x == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_x & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_DEY()
{
    _y--;

    if(_y == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_y & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_EOR(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);
    
    _a = _a ^ static_cast<int8_t>(t);
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_INC(int16_t t, bool load)
{
    uint8_t m = _iob->readMemory(t);

    m++;
    _iob->writeMemory(t,m);
    
    if(m == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(m & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_INX()
{
    _x++;

    if(_x == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_x & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_INY()
{
    _y++;

    if(_y == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_y & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_JMP(int16_t t, bool load)
{
    _pc = t;
    
    
}

void CPU::_generic_JSR(int16_t t, bool load)
{
    
//    if(load)
//        t = _iob->readMemory(t);
    
    // Next instruction -1, which is current pc-1 (pc is already pointing to the next)
    _push(static_cast<int8_t>(((_pc-1) >> 8)));
    _push(static_cast<int8_t>(_pc-1));
    
    
    _pc = t;
    
}


void CPU::_generic_LDA(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);

    _a = t;
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_LDX(int16_t t, bool load)
{

    if(load)
        t = _iob->readMemory(t);
    
    _x = t;

    if(_x == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_x & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_LDY(int16_t t, bool load)
{
    
    if(load)
        t = _iob->readMemory(t);
    
    _y = t;

    if(_y == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_y & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_LSR(int16_t t, bool load)
{
    uint8_t m, res;
    _resetFlag(CPUFlags::C);
    _resetFlag(CPUFlags::Z);
    _resetFlag(CPUFlags::N);
    if(load)
    {
        m = _iob->readMemory(t);
        if(m & 0x01)
            _setFlag(CPUFlags::C);
        
        m = m >> 1;
        _iob->writeMemory(t,m);
        res = m;
    }
    else
    {
        if(_a & 0x01)
            _setFlag(CPUFlags::C);
        
        _a = _a >> 1;
        res = _a;
    }
    
    if(res & 0x80)
        _setFlag(CPUFlags::N);
    if(res == 0)
        _setFlag(CPUFlags::Z);
    
    
}

void CPU::_generic_ORA(int16_t t, bool load)
{
    if(load)
        t = _iob->readMemory(t);
    _a = _a | static_cast<uint8_t>(t);
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_PHA()
{
    _push(_a);
    
}

void CPU::_generic_PHP()
{
//    printf("PUSHING %#04x \n", static_cast<int8_t>(_flags.to_ulong()));
    _push(static_cast<int8_t>(_flags.to_ulong()));
    
}

void CPU::_generic_PLA()
{
    _a = _pop();
    
//    printf("POPING %#04x \n", _a);
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_PLP()
{
    _setFlags(_pop());
    
    
}


void CPU::_generic_RTI()
{
    uint16_t v;

    _setFlags(_pop());
    
    v = _pop();
    v |= (static_cast<uint16_t>(_pop())<<8);
    
    
    
    _pc = v;
    
    NMIDONE = true;
    
}

void CPU::_generic_ROL(int16_t t, bool load)
{
    uint8_t m, res, carry;
    
    carry = _getFlag(CPUFlags::C);
    _resetFlag(CPUFlags::C);
    _resetFlag(CPUFlags::Z);
    _resetFlag(CPUFlags::N);
    if(load)
    {
        m = _iob->readMemory(t);
        if(m & 0x80)
            _setFlag(CPUFlags::C);
        
        m = m << 1 | carry;
        _iob->writeMemory(t,m);
        res = m;
    }
    else
    {
        if(_a & 0x80)
            _setFlag(CPUFlags::C);
        
        _a = _a << 1 | carry;
        res = _a;
    }
    
    if(res & 0x80)
        _setFlag(CPUFlags::N);
    if(res == 0)
        _setFlag(CPUFlags::Z);
    
    
}

void CPU::_generic_ROR(int16_t t, bool load)
{
    uint8_t m, res, carry;
    
    carry = _getFlag(CPUFlags::C) << 7;
    _resetFlag(CPUFlags::C);
    _resetFlag(CPUFlags::Z);
    _resetFlag(CPUFlags::N);
    if(load)
    {
        m = _iob->readMemory(t);
        if(m & 0x01)
            _setFlag(CPUFlags::C);
        
        m = m >> 1 | carry;
        _iob->writeMemory(t,m);
        res = m;
    }
    else
    {
        if(_a & 0x01)
            _setFlag(CPUFlags::C);
        
        _a = _a >> 1 | carry;
        res = _a;
    }
    
    if(res & 0x80)
        _setFlag(CPUFlags::N);
    if(res == 0)
        _setFlag(CPUFlags::Z);
    
    
}


void CPU::_generic_RTS()
{
    uint16_t v;
  
    v = _pop();
    v |= (static_cast<uint16_t>(_pop())<<8);
    
    _pc = v+1;
    
    
}

void CPU::_generic_SBC(int16_t t, bool load)
{
    uint8_t b = _a;
    uint8_t oldCarry = _getFlag(CPUFlags::C);
    
    _resetFlag(CPUFlags::N);
    _resetFlag(CPUFlags::Z);
    _resetFlag(CPUFlags::V);

    if(load)
        t = _iob->readMemory(t);
    
    _a = _a - static_cast<uint8_t>(t) - !_getFlag(CPUFlags::C);

    _setFlag(CPUFlags::C);

     if(((b & 0x80)==0) && (t & 0x0080) && (_a & 0x80)) {
         _setFlag(CPUFlags::V);
     }
     else if ((b & 0x80) && (t & 0x0080)==0 && (_a & 0x80)==0){
         _setFlag(CPUFlags::V);
     }
    
    if(static_cast<uint16_t>(static_cast<uint16_t>(b) - static_cast<uint16_t>(t) -!(oldCarry)) >= 0x100)
        _resetFlag(CPUFlags::C);
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    
    
}

void CPU::_generic_SEC()
{
    _setFlag(CPUFlags::C);
    
    
}

void CPU::_generic_SED()
{
    _setFlag(CPUFlags::D);
    
    
}

void CPU::_generic_SEI()
{
    _setFlag(CPUFlags::I);
    
    
}

void CPU::_generic_STA(int16_t t, bool load)
{
 //   if(load)
 //       t = _iob->readMemory(t);
    
    _iob->writeMemory(t, _a);
 //   printf("STA WRite TO %#06x value  %#06x \n", t, _a);
    
}
void CPU::_generic_STX(int16_t t, bool load)
{
 //   if(load)
 //       t = _iob->readMemory(t);
    
    _iob->writeMemory(t, _x);
    
}
void CPU::_generic_STY(int16_t t, bool load)
{
 //   if(load)
 //       t = _iob->readMemory(t);
    
    _iob->writeMemory(t, _y);
    
}

void CPU::_generic_TAX()
{
    _x = _a;
    
    if(_x == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_x & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_TAY()
{
    _y = _a;
    
    if(_y == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_y & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_TSX()
{
    _x = _sp;
    
    if(_x == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_x & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_TXA()
{
    _a = _x;
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}

void CPU::_generic_TXS()
{
    _sp = _x;
    
    
}

void CPU::_generic_TYA()
{
    _a = _y;
    
    if(_a == 0)
        _setFlag(CPUFlags::Z);
    else
        _resetFlag(CPUFlags::Z);
            
    if(_a & 0x80)
        _setFlag(CPUFlags::N);
    else
        _resetFlag(CPUFlags::N);
    
    
}


uint16_t CPU::AddrINDY(bool checkCrossing)
{
    uint8_t target[2];
    uint16_t srcdst;

    target[0] = _iob->readMemory(_pc++);
    fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
    fprintf(_CPULOG, "    ");
    srcdst = static_cast<int16_t>(target[0]);
    target[0] = _iob->readMemory(srcdst);
    target[1] = _iob->readMemory((srcdst + 1)%256);
    srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + static_cast<uint16_t>(_y);
    
    if(checkCrossing)
        _checkPageCrossing(srcdst, srcdst -_y);
    
    return srcdst;
}


uint16_t CPU::AddrINDX()
{
    uint8_t target[2];
    uint16_t srcdst;
    
    srcdst = _iob->readMemory(_pc++);
    fprintf(_CPULOG, "%#04x ", (uint8_t)srcdst);
    fprintf(_CPULOG, "    ");
    target[0] = _iob->readMemory((srcdst + _x)%256);
    target[1] = _iob->readMemory((srcdst + _x + 1)%256);
    srcdst = _iob->readMemory(static_cast<uint8_t>(target[0] + _x) & 0x00FF);
    // val = PEEK(PEEK((arg + X) % 256) + PEEK((arg + X + 1) % 256) * 256)
    srcdst = target[0] | (static_cast<uint16_t>(target[1]) << 8);
    
    return srcdst;
}


uint16_t CPU::AddrABS()
{
    uint8_t target[2];
    uint16_t srcdst;

    target[0] = _iob->readMemory(_pc++);
    fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
    target[1] = _iob->readMemory(_pc++);
    fprintf(_CPULOG, "%#04x     ", (uint8_t)target[1]);
    fprintf(_CPULOG, "    ");
    srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8);

    fprintf(_CPULOG, "CPY %#06x             ", (uint16_t)srcdst);

    return srcdst;
}
