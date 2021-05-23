uint8_t BRK_IMP()
{
	 fprintf(_CPULOG, "0x00 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		BRK 				");
	 _generic_BRK();
	 return 7;
}
uint8_t ORA_INDX()
{
	 fprintf(_CPULOG, "0x01 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	ORA %#06x 			", addr);
	 _generic_ORA(addr, true);
		 return 6;
}
uint8_t NOP_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x04 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	NOP %#04x 			", (uint8_t)srcdst);
	 _generic_NOP();
	 return 3;
}
uint8_t ORA_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x05 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	ORA %#04x 			", (uint8_t)srcdst);
	 _generic_ORA(srcdst, needLoad);
	 return 3;
}
uint8_t ASL_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x06 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	ASL %#04x 			", (uint8_t)srcdst);
	 _generic_ASL(srcdst, needLoad);
	 return 5;
}
uint8_t PHP_IMP()
{
	 fprintf(_CPULOG, "0x08 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		PHP 				");
	 _generic_PHP();
	 return 3;
}
uint8_t ORA_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x09 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	ORA %#04x 			", (uint8_t)srcdst);
	 _generic_ORA(srcdst, needLoad);
	 return 2;
}
uint8_t ASL_ACC()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x0a ");
	 fprintf(_CPULOG, "	");	 srcdst = _a;
	 fprintf(_CPULOG, "		ASL 				");
	 _generic_ASL(srcdst, needLoad);
	 return 2;
}
uint8_t NOP_ABS()
{
	 fprintf(_CPULOG, "0x0c ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	NOP %#06x 			", addr);
	 _generic_NOP();
		 return 3;
}
uint8_t ORA_ABS()
{
	 fprintf(_CPULOG, "0x0d ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	ORA %#06x 			", addr);
	 _generic_ORA(addr, true);
		 return 4;
}
uint8_t ASL_ABS()
{
	 fprintf(_CPULOG, "0x0e ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	ASL %#06x 			", addr);
	 _generic_ASL(addr, true);
		 return 6;
}
uint8_t BPL_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x10 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BPL %#04x 			", (uint8_t)srcdst);
	 _generic_BPL(srcdst, needLoad);
	 return 2;
}
uint8_t ORA_INDY()
{
	 fprintf(_CPULOG, "0x11 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	ORA %#06x 			", addr);
	 _generic_ORA(addr, true);
		 return 5;
}
uint8_t ORA_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x15 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	ORA %#04x 			", (uint8_t)srcdst);
	 _generic_ORA(srcdst, needLoad);
	 return 4;
}
uint8_t ASL_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x16 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	ASL %#04x 			", (uint8_t)srcdst);
	 _generic_ASL(srcdst, needLoad);
	 return 6;
}
uint8_t CLC_IMP()
{
	 fprintf(_CPULOG, "0x18 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		CLC 				");
	 _generic_CLC();
	 return 2;
}
uint8_t ORA_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x19 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "ORA %#06x 			", (uint16_t)srcdst);
	 _generic_ORA(srcdst, needLoad);
	 return 4;
}
uint8_t ORA_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x1d ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "ORA %#06x 			", (uint16_t)srcdst);
	 _generic_ORA(srcdst, needLoad);
	 return 4;
}
uint8_t ASL_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x1e ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "ASL %#06x 			", (uint16_t)srcdst);
	 _generic_ASL(srcdst, needLoad);
	 return 7;
}
uint8_t JSR_ABS()
{
	 fprintf(_CPULOG, "0x20 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	JSR %#06x 			", addr);
	 _generic_JSR(addr, true);
		 return 6;
}
uint8_t AND_INDX()
{
	 fprintf(_CPULOG, "0x21 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	AND %#06x 			", addr);
	 _generic_AND(addr, true);
		 return 6;
}
uint8_t BIT_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x24 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	BIT %#04x 			", (uint8_t)srcdst);
	 _generic_BIT(srcdst, needLoad);
	 return 3;
}
uint8_t AND_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x25 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	AND %#04x 			", (uint8_t)srcdst);
	 _generic_AND(srcdst, needLoad);
	 return 3;
}
uint8_t ROL_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x26 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	ROL %#04x 			", (uint8_t)srcdst);
	 _generic_ROL(srcdst, needLoad);
	 return 5;
}
uint8_t PLP_IMP()
{
	 fprintf(_CPULOG, "0x28 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		PLP 				");
	 _generic_PLP();
	 return 4;
}
uint8_t AND_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x29 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	AND %#04x 			", (uint8_t)srcdst);
	 _generic_AND(srcdst, needLoad);
	 return 2;
}
uint8_t ROL_ACC()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x2a ");
	 fprintf(_CPULOG, "	");	 srcdst = _a;
	 fprintf(_CPULOG, "		ROL 				");
	 _generic_ROL(srcdst, needLoad);
	 return 2;
}
uint8_t BIT_ABS()
{
	 fprintf(_CPULOG, "0x2c ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	BIT %#06x 			", addr);
	 _generic_BIT(addr, true);
		 return 4;
}
uint8_t AND_ABS()
{
	 fprintf(_CPULOG, "0x2d ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	AND %#06x 			", addr);
	 _generic_AND(addr, true);
		 return 4;
}
uint8_t ROL_ABS()
{
	 fprintf(_CPULOG, "0x2e ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	ROL %#06x 			", addr);
	 _generic_ROL(addr, true);
		 return 6;
}
uint8_t BMI_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x30 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BMI %#04x 			", (uint8_t)srcdst);
	 _generic_BMI(srcdst, needLoad);
	 return 2;
}
uint8_t AND_INDY()
{
	 fprintf(_CPULOG, "0x31 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	AND %#06x 			", addr);
	 _generic_AND(addr, true);
		 return 5;
}
uint8_t AND_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x35 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	AND %#04x 			", (uint8_t)srcdst);
	 _generic_AND(srcdst, needLoad);
	 return 4;
}
uint8_t ROL_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x36 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	ROL %#04x 			", (uint8_t)srcdst);
	 _generic_ROL(srcdst, needLoad);
	 return 6;
}
uint8_t SEC_IMP()
{
	 fprintf(_CPULOG, "0x38 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		SEC 				");
	 _generic_SEC();
	 return 2;
}
uint8_t AND_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x39 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "AND %#06x 			", (uint16_t)srcdst);
	 _generic_AND(srcdst, needLoad);
	 return 4;
}
uint8_t AND_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x3d ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "AND %#06x 			", (uint16_t)srcdst);
	 _generic_AND(srcdst, needLoad);
	 return 4;
}
uint8_t ROL_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x3e ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "ROL %#06x 			", (uint16_t)srcdst);
	 _generic_ROL(srcdst, needLoad);
	 return 7;
}
uint8_t RTI_IMP()
{
	 fprintf(_CPULOG, "0x40 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		RTI 				");
	 _generic_RTI();
	 return 6;
}
uint8_t EOR_INDX()
{
	 fprintf(_CPULOG, "0x41 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	EOR %#06x 			", addr);
	 _generic_EOR(addr, true);
		 return 6;
}
uint8_t EOR_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x45 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	EOR %#04x 			", (uint8_t)srcdst);
	 _generic_EOR(srcdst, needLoad);
	 return 3;
}
uint8_t LSR_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x46 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	LSR %#04x 			", (uint8_t)srcdst);
	 _generic_LSR(srcdst, needLoad);
	 return 5;
}
uint8_t PHA_IMP()
{
	 fprintf(_CPULOG, "0x48 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		PHA 				");
	 _generic_PHA();
	 return 3;
}
uint8_t EOR_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x49 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	EOR %#04x 			", (uint8_t)srcdst);
	 _generic_EOR(srcdst, needLoad);
	 return 2;
}
uint8_t LSR_ACC()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x4a ");
	 fprintf(_CPULOG, "	");	 srcdst = _a;
	 fprintf(_CPULOG, "		LSR 				");
	 _generic_LSR(srcdst, needLoad);
	 return 2;
}
uint8_t JMP_ABS()
{
	 fprintf(_CPULOG, "0x4c ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	JMP %#06x 			", addr);
	 _generic_JMP(addr, true);
		 return 3;
}
uint8_t EOR_ABS()
{
	 fprintf(_CPULOG, "0x4d ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	EOR %#06x 			", addr);
	 _generic_EOR(addr, true);
		 return 4;
}
uint8_t LSR_ABS()
{
	 fprintf(_CPULOG, "0x4e ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	LSR %#06x 			", addr);
	 _generic_LSR(addr, true);
		 return 6;
}
uint8_t BVC_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x50 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BVC %#04x 			", (uint8_t)srcdst);
	 _generic_BVC(srcdst, needLoad);
	 return 2;
}
uint8_t EOR_INDY()
{
	 fprintf(_CPULOG, "0x51 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	EOR %#06x 			", addr);
	 _generic_EOR(addr, true);
		 return 5;
}
uint8_t EOR_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x55 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	EOR %#04x 			", (uint8_t)srcdst);
	 _generic_EOR(srcdst, needLoad);
	 return 4;
}
uint8_t LSR_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x56 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	LSR %#04x 			", (uint8_t)srcdst);
	 _generic_LSR(srcdst, needLoad);
	 return 6;
}
uint8_t CLI_IMP()
{
	 fprintf(_CPULOG, "0x58 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		CLI 				");
	 _generic_CLI();
	 return 2;
}
uint8_t EOR_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x59 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "EOR %#06x 			", (uint16_t)srcdst);
	 _generic_EOR(srcdst, needLoad);
	 return 4;
}
uint8_t EOR_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x5d ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "EOR %#06x 			", (uint16_t)srcdst);
	 _generic_EOR(srcdst, needLoad);
	 return 4;
}
uint8_t LSR_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x5e ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "LSR %#06x 			", (uint16_t)srcdst);
	 _generic_LSR(srcdst, needLoad);
	 return 7;
}
uint8_t RTS_IMP()
{
	 fprintf(_CPULOG, "0x60 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		RTS 				");
	 _generic_RTS();
	 return 6;
}
uint8_t ADC_INDX()
{
	 fprintf(_CPULOG, "0x61 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	ADC %#06x 			", addr);
	 _generic_ADC(addr, true);
		 return 6;
}
uint8_t ADC_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x65 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	ADC %#04x 			", (uint8_t)srcdst);
	 _generic_ADC(srcdst, needLoad);
	 return 3;
}
uint8_t ROR_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x66 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	ROR %#04x 			", (uint8_t)srcdst);
	 _generic_ROR(srcdst, needLoad);
	 return 5;
}
uint8_t PLA_IMP()
{
	 fprintf(_CPULOG, "0x68 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		PLA 				");
	 _generic_PLA();
	 return 4;
}
uint8_t ADC_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x69 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	ADC %#04x 			", (uint8_t)srcdst);
	 _generic_ADC(srcdst, needLoad);
	 return 2;
}
uint8_t ROR_ACC()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x6a ");
	 fprintf(_CPULOG, "	");	 srcdst = _a;
	 fprintf(_CPULOG, "		ROR 				");
	 _generic_ROR(srcdst, needLoad);
	 return 2;
}
uint8_t JMP_IND()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x6c ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8);
	 // this is for JMP, which is bugged on the 6502, need to take it into account
	 target[0] = _iob->readMemory(srcdst);
	 target[1] = _iob->readMemory((srcdst&0xFF00) | ((srcdst + 1)&0x00FF));
	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8);
	 needLoad = true;
	 fprintf(_CPULOG, "JMP %#06x 			", (uint16_t)srcdst);
	 _generic_JMP(srcdst, needLoad);
	 return 5;
}
uint8_t ADC_ABS()
{
	 fprintf(_CPULOG, "0x6d ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	ADC %#06x 			", addr);
	 _generic_ADC(addr, true);
		 return 4;
}
uint8_t ROR_ABS()
{
	 fprintf(_CPULOG, "0x6e ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	ROR %#06x 			", addr);
	 _generic_ROR(addr, true);
		 return 6;
}
uint8_t BVS_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x70 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BVS %#04x 			", (uint8_t)srcdst);
	 _generic_BVS(srcdst, needLoad);
	 return 2;
}
uint8_t ADC_INDY()
{
	 fprintf(_CPULOG, "0x71 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	ADC %#06x 			", addr);
	 _generic_ADC(addr, true);
		 return 5;
}
uint8_t ADC_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x75 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	ADC %#04x 			", (uint8_t)srcdst);
	 _generic_ADC(srcdst, needLoad);
	 return 4;
}
uint8_t ROR_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x76 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	ROR %#04x 			", (uint8_t)srcdst);
	 _generic_ROR(srcdst, needLoad);
	 return 6;
}
uint8_t SEI_IMP()
{
	 fprintf(_CPULOG, "0x78 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		SEI 				");
	 _generic_SEI();
	 return 2;
}
uint8_t ADC_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x79 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "ADC %#06x 			", (uint16_t)srcdst);
	 _generic_ADC(srcdst, needLoad);
	 return 4;
}
uint8_t ADC_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x7d ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "ADC %#06x 			", (uint16_t)srcdst);
	 _generic_ADC(srcdst, needLoad);
	 return 4;
}
uint8_t ROR_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x7e ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "ROR %#06x 			", (uint16_t)srcdst);
	 _generic_ROR(srcdst, needLoad);
	 return 7;
}
uint8_t STA_INDX()
{
	 fprintf(_CPULOG, "0x81 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	STA %#06x 			", addr);
	 _generic_STA(addr, true);
		 return 6;
}
uint8_t STY_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x84 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	STY %#04x 			", (uint8_t)srcdst);
	 _generic_STY(srcdst, needLoad);
	 return 3;
}
uint8_t STA_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x85 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	STA %#04x 			", (uint8_t)srcdst);
	 _generic_STA(srcdst, needLoad);
	 return 3;
}
uint8_t STX_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x86 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	STX %#04x 			", (uint8_t)srcdst);
	 _generic_STX(srcdst, needLoad);
	 return 3;
}
uint8_t DEY_IMP()
{
	 fprintf(_CPULOG, "0x88 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		DEY 				");
	 _generic_DEY();
	 return 2;
}
uint8_t TXA_IMP()
{
	 fprintf(_CPULOG, "0x8a ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		TXA 				");
	 _generic_TXA();
	 return 2;
}
uint8_t STY_ABS()
{
	 fprintf(_CPULOG, "0x8c ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	STY %#06x 			", addr);
	 _generic_STY(addr, true);
		 return 4;
}
uint8_t STA_ABS()
{
	 fprintf(_CPULOG, "0x8d ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	STA %#06x 			", addr);
	 _generic_STA(addr, true);
		 return 4;
}
uint8_t STX_ABS()
{
	 fprintf(_CPULOG, "0x8e ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	STX %#06x 			", addr);
	 _generic_STX(addr, true);
		 return 4;
}
uint8_t BCC_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x90 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BCC %#04x 			", (uint8_t)srcdst);
	 _generic_BCC(srcdst, needLoad);
	 return 2;
}
uint8_t STA_INDY()
{
	 fprintf(_CPULOG, "0x91 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(false); 
	 fprintf(_CPULOG, "	STA %#06x 			", addr);
	 _generic_STA(addr, true);
		 return 6;
}
uint8_t STY_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x94 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	STY %#04x 			", (uint8_t)srcdst);
	 _generic_STY(srcdst, needLoad);
	 return 4;
}
uint8_t STA_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x95 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	STA %#04x 			", (uint8_t)srcdst);
	 _generic_STA(srcdst, needLoad);
	 return 4;
}
uint8_t STX_ZPY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x96 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = (static_cast<uint8_t>(target[0] + _y) & 0x00FF);
	 needLoad = true;
	 fprintf(_CPULOG, "	STX %#04x 			", (uint8_t)srcdst);
	 _generic_STX(srcdst, needLoad);
	 return 4;
}
uint8_t TYA_IMP()
{
	 fprintf(_CPULOG, "0x98 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		TYA 				");
	 _generic_TYA();
	 return 2;
}
uint8_t STA_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x99 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 needLoad = true;
	 fprintf(_CPULOG, "STA %#06x 			", (uint16_t)srcdst);
	 _generic_STA(srcdst, needLoad);
	 return 5;
}
uint8_t TXS_IMP()
{
	 fprintf(_CPULOG, "0x9a ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		TXS 				");
	 _generic_TXS();
	 return 2;
}
uint8_t STA_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0x9d ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "STA %#06x 			", (uint16_t)srcdst);
	 _generic_STA(srcdst, needLoad);
	 return 5;
}
uint8_t LDY_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xa0 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	LDY %#04x 			", (uint8_t)srcdst);
	 _generic_LDY(srcdst, needLoad);
	 return 2;
}
uint8_t LDA_INDX()
{
	 fprintf(_CPULOG, "0xa1 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	LDA %#06x 			", addr);
	 _generic_LDA(addr, true);
		 return 6;
}
uint8_t LDX_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xa2 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	LDX %#04x 			", (uint8_t)srcdst);
	 _generic_LDX(srcdst, needLoad);
	 return 2;
}
uint8_t LDY_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xa4 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	LDY %#04x 			", (uint8_t)srcdst);
	 _generic_LDY(srcdst, needLoad);
	 return 3;
}
uint8_t LDA_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xa5 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	LDA %#04x 			", (uint8_t)srcdst);
	 _generic_LDA(srcdst, needLoad);
	 return 3;
}
uint8_t LDX_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xa6 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	LDX %#04x 			", (uint8_t)srcdst);
	 _generic_LDX(srcdst, needLoad);
	 return 3;
}
uint8_t TAY_IMP()
{
	 fprintf(_CPULOG, "0xa8 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		TAY 				");
	 _generic_TAY();
	 return 2;
}
uint8_t LDA_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xa9 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	LDA %#04x 			", (uint8_t)srcdst);
	 _generic_LDA(srcdst, needLoad);
	 return 2;
}
uint8_t TAX_IMP()
{
	 fprintf(_CPULOG, "0xaa ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		TAX 				");
	 _generic_TAX();
	 return 2;
}
uint8_t LDY_ABS()
{
	 fprintf(_CPULOG, "0xac ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	LDY %#06x 			", addr);
	 _generic_LDY(addr, true);
		 return 4;
}
uint8_t LDA_ABS()
{
	 fprintf(_CPULOG, "0xad ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	LDA %#06x 			", addr);
	 _generic_LDA(addr, true);
		 return 4;
}
uint8_t LDX_ABS()
{
	 fprintf(_CPULOG, "0xae ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	LDX %#06x 			", addr);
	 _generic_LDX(addr, true);
		 return 4;
}
uint8_t BCS_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xb0 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BCS %#04x 			", (uint8_t)srcdst);
	 _generic_BCS(srcdst, needLoad);
	 return 2;
}
uint8_t LDA_INDY()
{
	 fprintf(_CPULOG, "0xb1 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	LDA %#06x 			", addr);
	 _generic_LDA(addr, true);
		 return 5;
}
uint8_t LDY_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xb4 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	LDY %#04x 			", (uint8_t)srcdst);
	 _generic_LDY(srcdst, needLoad);
	 return 4;
}
uint8_t LDA_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xb5 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	LDA %#04x 			", (uint8_t)srcdst);
	 _generic_LDA(srcdst, needLoad);
	 return 4;
}
uint8_t LDX_ZPY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xb6 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = (static_cast<uint8_t>(target[0] + _y) & 0x00FF);
	 needLoad = true;
	 fprintf(_CPULOG, "	LDX %#04x 			", (uint8_t)srcdst);
	 _generic_LDX(srcdst, needLoad);
	 return 4;
}
uint8_t CLV_IMP()
{
	 fprintf(_CPULOG, "0xb8 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		CLV 				");
	 _generic_CLV();
	 return 2;
}
uint8_t LDA_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xb9 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "LDA %#06x 			", (uint16_t)srcdst);
	 _generic_LDA(srcdst, needLoad);
	 return 4;
}
uint8_t TSX_IMP()
{
	 fprintf(_CPULOG, "0xba ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		TSX 				");
	 _generic_TSX();
	 return 2;
}
uint8_t LDY_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xbc ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "LDY %#06x 			", (uint16_t)srcdst);
	 _generic_LDY(srcdst, needLoad);
	 return 4;
}
uint8_t LDA_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xbd ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "LDA %#06x 			", (uint16_t)srcdst);
	 _generic_LDA(srcdst, needLoad);
	 return 4;
}
uint8_t LDX_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xbe ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "LDX %#06x 			", (uint16_t)srcdst);
	 _generic_LDX(srcdst, needLoad);
	 return 4;
}
uint8_t CPY_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xc0 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	CPY %#04x 			", (uint8_t)srcdst);
	 _generic_CPY(srcdst, needLoad);
	 return 2;
}
uint8_t CMP_INDX()
{
	 fprintf(_CPULOG, "0xc1 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	CMP %#06x 			", addr);
	 _generic_CMP(addr, true);
		 return 6;
}
uint8_t CPY_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xc4 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	CPY %#04x 			", (uint8_t)srcdst);
	 _generic_CPY(srcdst, needLoad);
	 return 3;
}
uint8_t CMP_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xc5 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	CMP %#04x 			", (uint8_t)srcdst);
	 _generic_CMP(srcdst, needLoad);
	 return 3;
}
uint8_t DEC_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xc6 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	DEC %#04x 			", (uint8_t)srcdst);
	 _generic_DEC(srcdst, needLoad);
	 return 5;
}
uint8_t INY_IMP()
{
	 fprintf(_CPULOG, "0xc8 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		INY 				");
	 _generic_INY();
	 return 2;
}
uint8_t CMP_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xc9 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	CMP %#04x 			", (uint8_t)srcdst);
	 _generic_CMP(srcdst, needLoad);
	 return 2;
}
uint8_t DEX_IMP()
{
	 fprintf(_CPULOG, "0xca ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		DEX 				");
	 _generic_DEX();
	 return 2;
}
uint8_t CPY_ABS()
{
	 fprintf(_CPULOG, "0xcc ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	CPY %#06x 			", addr);
	 _generic_CPY(addr, true);
		 return 4;
}
uint8_t CMP_ABS()
{
	 fprintf(_CPULOG, "0xcd ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	CMP %#06x 			", addr);
	 _generic_CMP(addr, true);
		 return 4;
}
uint8_t DEC_ABS()
{
	 fprintf(_CPULOG, "0xce ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	DEC %#06x 			", addr);
	 _generic_DEC(addr, true);
		 return 6;
}
uint8_t BNE_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xd0 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BNE %#04x 			", (uint8_t)srcdst);
	 _generic_BNE(srcdst, needLoad);
	 return 2;
}
uint8_t CMP_INDY()
{
	 fprintf(_CPULOG, "0xd1 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	CMP %#06x 			", addr);
	 _generic_CMP(addr, true);
		 return 5;
}
uint8_t CMP_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xd5 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	CMP %#04x 			", (uint8_t)srcdst);
	 _generic_CMP(srcdst, needLoad);
	 return 4;
}
uint8_t DEC_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xd6 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	DEC %#04x 			", (uint8_t)srcdst);
	 _generic_DEC(srcdst, needLoad);
	 return 6;
}
uint8_t CLD_IMP()
{
	 fprintf(_CPULOG, "0xd8 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		CLD 				");
	 _generic_CLD();
	 return 2;
}
uint8_t CMP_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xd9 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "CMP %#06x 			", (uint16_t)srcdst);
	 _generic_CMP(srcdst, needLoad);
	 return 4;
}
uint8_t CMP_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xdd ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "CMP %#06x 			", (uint16_t)srcdst);
	 _generic_CMP(srcdst, needLoad);
	 return 4;
}
uint8_t DEC_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xde ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "DEC %#06x 			", (uint16_t)srcdst);
	 _generic_DEC(srcdst, needLoad);
	 return 7;
}
uint8_t CPX_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xe0 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	CPX %#04x 			", (uint8_t)srcdst);
	 _generic_CPX(srcdst, needLoad);
	 return 2;
}
uint8_t SBC_INDX()
{
	 fprintf(_CPULOG, "0xe1 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrINDX();
	 fprintf(_CPULOG, "	SBC %#06x 			", addr);
	 _generic_SBC(addr, true);
		 return 6;
}
uint8_t CPX_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xe4 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	CPX %#04x 			", (uint8_t)srcdst);
	 _generic_CPX(srcdst, needLoad);
	 return 3;
}
uint8_t SBC_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xe5 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	SBC %#04x 			", (uint8_t)srcdst);
	 _generic_SBC(srcdst, needLoad);
	 return 3;
}
uint8_t INC_ZP()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xe6 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 needLoad = true;
	 fprintf(_CPULOG, "	INC %#04x 			", (uint8_t)srcdst);
	 _generic_INC(srcdst, needLoad);
	 return 5;
}
uint8_t INX_IMP()
{
	 fprintf(_CPULOG, "0xe8 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		INX 				");
	 _generic_INX();
	 return 2;
}
uint8_t SBC_IMM()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xe9 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = target[0];
	 fprintf(_CPULOG, "	SBC %#04x 			", (uint8_t)srcdst);
	 _generic_SBC(srcdst, needLoad);
	 return 2;
}
uint8_t NOP_IMP()
{
	 fprintf(_CPULOG, "0xea ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		NOP 				");
	 _generic_NOP();
	 return 2;
}
uint8_t CPX_ABS()
{
	 fprintf(_CPULOG, "0xec ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	CPX %#06x 			", addr);
	 _generic_CPX(addr, true);
		 return 4;
}
uint8_t SBC_ABS()
{
	 fprintf(_CPULOG, "0xed ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	SBC %#06x 			", addr);
	 _generic_SBC(addr, true);
		 return 4;
}
uint8_t INC_ABS()
{
	 fprintf(_CPULOG, "0xee ");
	 fprintf(_CPULOG, "	");	 uint16_t addr  = AddrABS();
	 fprintf(_CPULOG, "	INC %#06x 			", addr);
	 _generic_INC(addr, true);
		 return 6;
}
uint8_t BEQ_REL()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xf0 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<int16_t>(static_cast<int8_t>(target[0]));
	 fprintf(_CPULOG, "	BEQ %#04x 			", (uint8_t)srcdst);
	 _generic_BEQ(srcdst, needLoad);
	 return 2;
}
uint8_t SBC_INDY()
{
	 fprintf(_CPULOG, "0xf1 ");
	 fprintf(_CPULOG, "	");	 uint16_t addr;
	 addr = AddrINDY(true); 
	 fprintf(_CPULOG, "	SBC %#06x 			", addr);
	 _generic_SBC(addr, true);
		 return 5;
}
uint8_t SBC_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xf5 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	SBC %#04x 			", (uint8_t)srcdst);
	 _generic_SBC(srcdst, needLoad);
	 return 4;
}
uint8_t INC_ZPX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xf6 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint8_t>(target[0] + _x) & 0x00FF;
	 needLoad = true;
	 fprintf(_CPULOG, "	INC %#04x 			", (uint8_t)srcdst);
	 _generic_INC(srcdst, needLoad);
	 return 6;
}
uint8_t SED_IMP()
{
	 fprintf(_CPULOG, "0xf8 ");
	 fprintf(_CPULOG, "	");	 fprintf(_CPULOG, "		SED 				");
	 _generic_SED();
	 return 2;
}
uint8_t SBC_ABSY()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xf9 ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _y;
	 _checkPageCrossing(srcdst, srcdst -_y);	 needLoad = true;
	 fprintf(_CPULOG, "SBC %#06x 			", (uint16_t)srcdst);
	 _generic_SBC(srcdst, needLoad);
	 return 4;
}
uint8_t SBC_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xfd ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 _checkPageCrossing(srcdst, srcdst -_x);	 fprintf(_CPULOG, "SBC %#06x 			", (uint16_t)srcdst);
	 _generic_SBC(srcdst, needLoad);
	 return 4;
}
uint8_t INC_ABSX()
{
	 uint8_t target[2];
	 uint16_t srcdst;
	 bool needLoad = false;
	 fprintf(_CPULOG, "0xfe ");
	 target[0] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x ", (uint8_t)target[0]);
	 target[1] = _iob->readMemory(_pc++);
	 fprintf(_CPULOG, "%#04x 	", (uint8_t)target[1]);
	 fprintf(_CPULOG, "	");	 srcdst = static_cast<uint16_t>(target[0]) + (static_cast<uint16_t>(target[1]) << 8) + _x;
	 needLoad = true;
	 fprintf(_CPULOG, "INC %#06x 			", (uint16_t)srcdst);
	 _generic_INC(srcdst, needLoad);
	 return 7;
}
uint8_t NOT_SUPPORTED() {return 0;}
