#include "basics.h"
#include "registers.h"
#include "memory.h"
typedef struct	s_opcode {
	char		*name;
	size_t		argument;
	void		*fn;
	size_t		clock;
}				t_opcode;

#define FLAG_ZERO  ((reg.f >> 7) & 1)
#define FLAG_NEG   ((reg.f >> 6) & 1)
#define FLAG_HALF  ((reg.f >> 5) & 1)
#define FLAG_CARRY ((reg.f >> 4) & 1)
#define SET_FLAG_ZERO  (reg.f |= (1 << 7))
#define SET_FLAG_NEG   (reg.f |= (1 << 6))
#define SET_FLAG_HALF  (reg.f |= (1 << 5))
#define SET_FLAG_CARRY (reg.f |= (1 << 4))
#define UNSET_FLAG_ZERO  (reg.f &= ~(1 << 7))
#define UNSET_FLAG_NEG   (reg.f &= ~(1 << 6))
#define UNSET_FLAG_HALF  (reg.f &= ~(1 << 5))
#define UNSET_FLAG_CARRY (reg.f &= ~(1 << 4))

void			xor(unsigned char c)
{
	reg.a ^= c;
	reg.a == 0 ? SET_FLAG_ZERO : UNSET_FLAG_ZERO;
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	UNSET_FLAG_CARRY;
}

unsigned char	inc(unsigned char value)
{
	(value & 0x0f) == 0x0f ? SET_FLAG_HALF : UNSET_FLAG_HALF;
	value += 1;
	value == 0 ? SET_FLAG_ZERO : UNSET_FLAG_ZERO;
	UNSET_FLAG_NEG;
	return (value);
}


unsigned char	dec(unsigned char value)
{
	value & 0x0f ? UNSET_FLAG_HALF : SET_FLAG_HALF;
	value -= 1;
	value == 0 ? SET_FLAG_ZERO : UNSET_FLAG_ZERO;
	SET_FLAG_NEG;
	return (value);
}

void			nop(void) { } // 0x00
void			ld_bc_nn(unsigned short op) { reg.bc = op; } // 0x01
void			ld_bc_a(void) { printf("0x%04hx\n", reg.bc); memory_write_byte(reg.bc, reg.a); } // 0x02
void			inc_b(void) { reg.b = inc(reg.b); } // 0x04
void			dec_b(void) { reg.b = dec(reg.b); } // 0x05
void			ld_b_n(unsigned char op) { reg.c = op; } // 0x06
void			inc_c(void) { reg.c = inc(reg.c); } // 0x0c
void			dec_c(void) { reg.c = dec(reg.c); } // 0x0d
void			ld_c_n(unsigned char op) { reg.c = op; } // 0x0e
void			inc_d(void) { reg.d = inc(reg.d); } // 0x14
void			dec_d(void) { reg.d = dec(reg.d); } // 0x15
void			ld_a_de(void) { reg.a = memory_read_byte(reg.de); } // 0x1a
void			inc_e(void) { reg.e = inc(reg.e); } // 0x1c
void			dec_e(void) { reg.e = dec(reg.e); } // 0x1d
void			jr_nz_n(unsigned char op) { if (FLAG_ZERO) { ; } else { reg.pc += (signed char)op; } } // 0x20 TODO if (0) 8 clock else 12 clock
void			ld_hl_nn(unsigned short op) { reg.hl = op; } // 0x21
void			inc_h(void) { reg.h = inc(reg.h); } // 0x24
void			dec_h(void) { reg.h = dec(reg.h); } // 0x25
void			inc_l(void) { reg.l = inc(reg.l); } // 0x2c
void			dec_l(void) { reg.l = dec(reg.l); } // 0x2d
void			ldd_hl_a(void) { memory_write_byte(reg.hl, reg.a); reg.hl -= 1; } // 0x32
void			inc_a(void) { reg.a = inc(reg.a); } // 0x3c
void			dec_a(void) { reg.a = dec(reg.a); } // 0x3d

// 0x40
void			ld_b_c(void) { reg.b = reg.c; } // 0x41
void			ld_b_d(void) { reg.b = reg.d; } // 0x42
void			ld_b_e(void) { reg.b = reg.e; } // 0x43
void			ld_b_h(void) { reg.b = reg.h; } // 0x44
void			ld_b_l(void) { reg.b = reg.l; } // 0x45
// 0x46
void			ld_b_a(void) { reg.b = reg.a; } // 0x47
void			ld_c_b(void) { reg.c = reg.b; } // 0x48
// 0x49
void			ld_c_d(void) { reg.c = reg.d; } // 0x4a
void			ld_c_e(void) { reg.c = reg.e; } // 0x4b
void			ld_c_h(void) { reg.c = reg.h; } // 0x4c
void			ld_c_l(void) { reg.c = reg.l; } // 0x4d
// 0x4e
void			ld_c_a(void) { reg.c = reg.a; } // 0x4f
void			ld_d_b(void) { reg.d = reg.b; } // 0x50
void			ld_d_c(void) { reg.d = reg.c; } // 0x51
// 0x52
void			ld_d_e(void) { reg.d = reg.e; } // 0x53
void			ld_d_h(void) { reg.d = reg.h; } // 0x54
void			ld_d_l(void) { reg.d = reg.l; } // 0x55
// 0x56
void			ld_d_a(void) { reg.d = reg.a; } // 0x57
void			ld_e_b(void) { reg.e = reg.b; } // 0x58
void			ld_e_c(void) { reg.e = reg.c; } // 0x59
void			ld_e_d(void) { reg.e = reg.d; } // 0x5a
// 0x5b
void			ld_e_h(void) { reg.e = reg.h; } // 0x5c
void			ld_e_l(void) { reg.e = reg.l; } // 0x5d
// 0x5e
void			ld_e_a(void) { reg.e = reg.a; } // 0x5f
void			ld_h_b(void) { reg.h = reg.b; } // 0x60
void			ld_h_c(void) { reg.h = reg.c; } // 0x61
void			ld_h_d(void) { reg.h = reg.d; } // 0x62
void			ld_h_e(void) { reg.h = reg.e; } // 0x63
// 0x64
void			ld_h_l(void) { reg.h = reg.l; } // 0x65
// 0x66
void			ld_h_a(void) { reg.h = reg.a; } // 0x67
void			ld_l_b(void) { reg.l = reg.b; } // 0x68
void			ld_l_c(void) { reg.l = reg.c; } // 0x69
void			ld_l_d(void) { reg.l = reg.d; } // 0x6a
void			ld_l_e(void) { reg.l = reg.e; } // 0x6b
void			ld_l_h(void) { reg.l = reg.h; } // 0x6c
// 0x6d
// 0x6e

void			ld_l_a(void) { reg.l = reg.a; } // 0x6f
void			ld_a_b(void) { reg.a = reg.b; } // 0x78
void			ld_a_c(void) { reg.a = reg.c; } // 0x79
void			ld_a_d(void) { reg.a = reg.d; } // 0x7a
void			ld_a_e(void) { reg.a = reg.e; } // 0x7b
void			ld_a_h(void) { reg.a = reg.h; } // 0x7c
void			ld_a_l(void) { reg.a = reg.l; } // 0x7d
// 0x7e
// 0x7f

void			xor_b(void) { xor(reg.b); } // 0xa8
void			xor_c(void) { xor(reg.c); } // 0xa9
void			xor_d(void) { xor(reg.d); } // 0xaa
void			xor_e(void) { xor(reg.e); } // 0xab
void			xor_h(void) { xor(reg.h); } // 0xac
void			xor_l(void) { xor(reg.l); } // 0xad
void			xor_a(void) { xor(reg.a); } // 0xaf
void			jp_nn(unsigned short op) { reg.pc = op; } // 0xc3
void			ldh_a_n(unsigned char op) { reg.a = memory_read_byte(0xff00 | op); } // f0

const t_opcode	opcodes[] = {
	{ "NOP", 0, nop, 4 },           // 0x00
	{ "LD BC,nn", 2, ld_bc_nn, 12 },      // 0x01
	{ "LD (BC),A", 0, ld_bc_a, 8 },     // 0x02
	{ "INC BC", 0, NULL, 0 },        // 0x03
	{ "INC B", 0, inc_b, 4 },         // 0x04
	{ "DEC B", 0, dec_b, 4 },         // 0x05
	{ "LD B,n", 1, ld_b_n, 4 },        // 0x06
	{ "RLC A", 0, NULL, 0 },         // 0x07
	{ "LD (nn),SP", 0, NULL, 0 },    // 0x08
	{ "ADD HL,BC", 0, NULL, 0 },     // 0x09
	{ "LD A,(BC)", 0, NULL, 0 },     // 0x0a
	{ "DEC BC", 0, NULL, 0 },        // 0x0b
	{ "INC C", 0, inc_c, 4 },         // 0x0c
	{ "DEC C", 0, NULL, 4 },         // 0x0d
	{ "LD C,n", 1, ld_c_n, 4 },        // 0x0e
	{ "RRC A", 0, NULL, 0 },         // 0x0f
	{ "STOP", 0, NULL, 0 },          // 0x10
	{ "LD DE,nn", 0, NULL, 0 },      // 0x11
	{ "LD (DE),A", 0, NULL, 0 },     // 0x12
	{ "INC DE", 0, NULL, 0 },        // 0x13
	{ "INC D", 0, inc_d, 4 },         // 0x14
	{ "DEC D", 0, dec_d, 4 },         // 0x15
	{ "LD D,n", 0, NULL, 0 },        // 0x16
	{ "RL A", 0, NULL, 0 },          // 0x17
	{ "JR n", 0, NULL, 0 },          // 0x18
	{ "ADD HL,DE", 0, NULL, 0 },     // 0x19
	{ "LD A,(DE)", 0, ld_a_de, 8 },     // 0x1a
	{ "DEC DE", 0, NULL, 0 },        // 0x1b
	{ "INC E", 0, inc_e, 4 },         // 0x1c
	{ "DEC E", 0, dec_e, 4 },         // 0x1d
	{ "LD E,n", 0, NULL, 0 },        // 0x1e
	{ "RR A", 0, NULL, 0 },          // 0x1f
	{ "JR NZ,n", 0, jr_nz_n, 0 },       // 0x20 TODO diff tick
	{ "LD HL,nn", 2, ld_hl_nn, 12 },      // 0x21
	{ "LDI (HL),A", 0, NULL, 0 },    // 0x22
	{ "INC HL", 0, NULL, 0 },        // 0x23
	{ "INC H", 0, inc_h, 4 },         // 0x24
	{ "DEC H", 0, dec_h, 4 },         // 0x25
	{ "LD H,n", 0, NULL, 0 },        // 0x26
	{ "DAA", 0, NULL, 0 },           // 0x27
	{ "JR Z,n", 0, NULL, 0 },        // 0x28
	{ "ADD HL,HL", 0, NULL, 0 },     // 0x29
	{ "LDI A,(HL)", 0, NULL, 0 },    // 0x2a
	{ "DEC HL", 0, NULL, 0 },        // 0x2b
	{ "INC L", 0, inc_l, 4 },         // 0x2c
	{ "DEC L", 0, dec_l, 4 },         // 0x2d
	{ "LD L,n", 0, NULL, 0 },        // 0x2e
	{ "CPL", 0, NULL, 0 },           // 0x2f
	{ "JR NC,n", 0, NULL, 0 },       // 0x30
	{ "LD SP,nn", 0, NULL, 0 },      // 0x31
	{ "LDD (HL),A", 0, ldd_hl_a, 8 },    // 0x32
	{ "INC SP", 0, NULL, 0 },        // 0x33
	{ "INC (HL)", 0, NULL, 0 },      // 0x34
	{ "DEC (HL)", 0, NULL, 0 },      // 0x35
	{ "LD (HL),n", 0, NULL, 0 },     // 0x36
	{ "SCF", 0, NULL, 0 },           // 0x37
	{ "JR C,n", 0, NULL, 0 },        // 0x38
	{ "ADD HL,SP", 0, NULL, 0 },     // 0x39
	{ "LDD A,(HL)", 0, NULL, 0 },    // 0x3a
	{ "DEC SP", 0, NULL, 0 },        // 0x3b
	{ "INC A", 0, inc_a, 4 },         // 0x3c
	{ "DEC A", 0, dec_a, 4 },         // 0x3d
	{ "LD A,n", 0, NULL, 0 },        // 0x3e
	{ "CCF", 0, NULL, 0 },           // 0x3f
	{ "LD B,B", 0, nop, 4 },        // 0x40
	{ "LD B,C", 0, ld_b_c, 4 },        // 0x41
	{ "LD B,D", 0, ld_b_d, 4 },        // 0x42
	{ "LD B,E", 0, ld_b_e, 4 },        // 0x43
	{ "LD B,H", 0, ld_b_h, 4 },        // 0x44
	{ "LD B,L", 0, ld_b_l, 4 },        // 0x45
	{ "LD B,(HL)", 0, NULL, 0 },     // 0x46
	{ "LD B,A", 0, ld_b_a, 4 },        // 0x47
	{ "LD C,B", 0, ld_c_b, 4 },        // 0x48
	{ "LD C,C", 0, nop, 4 },        // 0x49
	{ "LD C,D", 0, ld_c_d, 4 },        // 0x4a
	{ "LD C,E", 0, ld_c_e, 4 },        // 0x4b
	{ "LD C,H", 0, ld_c_h, 4 },        // 0x4c
	{ "LD C,L", 0, ld_c_l, 4 },        // 0x4d
	{ "LD C,(HL)", 0, NULL, 0 },     // 0x4e
	{ "LD C,A", 0, ld_c_a, 4 },        // 0x4f
	{ "LD D,B", 0, ld_d_b, 4 },        // 0x50
	{ "LD D,C", 0, ld_d_c, 4 },        // 0x51
	{ "LD D,D", 0, nop, 4 },        // 0x52
	{ "LD D,E", 0, ld_d_e, 4 },        // 0x53
	{ "LD D,H", 0, ld_d_h, 4 },        // 0x54
	{ "LD D,L", 0, ld_d_l, 4 },        // 0x55
	{ "LD D,(HL)", 0, NULL, 0 },     // 0x56
	{ "LD D,A", 0, ld_d_a, 4 },        // 0x57
	{ "LD E,B", 0, ld_e_b, 4 },        // 0x58
	{ "LD E,C", 0, ld_e_c, 4 },        // 0x59
	{ "LD E,D", 0, ld_e_d, 4 },        // 0x5a
	{ "LD E,E", 0, nop, 4 },        // 0x5b
	{ "LD E,H", 0, ld_e_h, 4 },        // 0x5c
	{ "LD E,L", 0, ld_e_l, 4 },        // 0x5d
	{ "LD E,(HL)", 0, NULL, 0 },     // 0x5e
	{ "LD E,A", 0, ld_e_a, 4 },        // 0x5f
	{ "LD H,B", 0, ld_h_b, 4 },        // 0x60
	{ "LD H,C", 0, ld_h_c, 4 },        // 0x61
	{ "LD H,D", 0, ld_h_d, 4 },        // 0x62
	{ "LD H,E", 0, ld_h_e, 4 },        // 0x63
	{ "LD H,H", 0, nop, 4 },        // 0x64
	{ "LD H,L", 0, ld_h_l, 4 },        // 0x65
	{ "LD H,(HL)", 0, NULL, 0 },     // 0x66
	{ "LD H,A", 0, ld_h_a, 4 },        // 0x67
	{ "LD L,B", 0, ld_l_b, 4 },        // 0x68
	{ "LD L,C", 0, ld_l_c, 4 },        // 0x69
	{ "LD L,D", 0, ld_l_d, 4 },        // 0x6a
	{ "LD L,E", 0, ld_l_e, 4 },        // 0x6b
	{ "LD L,H", 0, ld_l_h, 4 },        // 0x6c
	{ "LD L,L", 0, nop, 4 },        // 0x6d
	{ "LD L,(HL)", 0, NULL, 0 },     // 0x6e
	{ "LD L,A", 0, ld_l_a, 4 },        // 0x6f
	{ "LD (HL),B", 0, NULL, 0 },     // 0x70
	{ "LD (HL),C", 0, NULL, 0 },     // 0x71
	{ "LD (HL),D", 0, NULL, 0 },     // 0x72
	{ "LD (HL),E", 0, NULL, 0 },     // 0x73
	{ "LD (HL),H", 0, NULL, 0 },     // 0x74
	{ "LD (HL),L", 0, NULL, 0 },     // 0x75
	{ "HALT", 0, NULL, 0 },          // 0x76
	{ "LD (HL),A", 0, NULL, 0 },     // 0x77
	{ "LD A,B", 0, ld_a_b, 4 },        // 0x78
	{ "LD A,C", 0, ld_a_c, 4 },        // 0x79
	{ "LD A,D", 0, ld_a_d, 4 },        // 0x7a
	{ "LD A,E", 0, ld_a_e, 4 },        // 0x7b
	{ "LD A,H", 0, ld_a_h, 4 },        // 0x7c
	{ "LD A,L", 0, ld_a_l, 4 },        // 0x7d
	{ "LD A,(HL)", 0, NULL, 0 },     // 0x7e
	{ "LD A,A", 0, nop, 4 },        // 0x7f
	{ "ADD A,B", 0, NULL, 0 },       // 0x80
	{ "ADD A,C", 0, NULL, 0 },       // 0x81
	{ "ADD A,D", 0, NULL, 0 },       // 0x82
	{ "ADD A,E", 0, NULL, 0 },       // 0x83
	{ "ADD A,H", 0, NULL, 0 },       // 0x84
	{ "ADD A,L", 0, NULL, 0 },       // 0x85
	{ "ADD A,(HL)", 0, NULL, 0 },    // 0x86
	{ "ADD A,A", 0, NULL, 0 },       // 0x87
	{ "ADC A,B", 0, NULL, 0 },       // 0x88
	{ "ADC A,C", 0, NULL, 0 },       // 0x89
	{ "ADC A,D", 0, NULL, 0 },       // 0x8a
	{ "ADC A,E", 0, NULL, 0 },       // 0x8b
	{ "ADC A,H", 0, NULL, 0 },       // 0x8c
	{ "ADC A,L", 0, NULL, 0 },       // 0x8d
	{ "ADC A,(HL)", 0, NULL, 0 },    // 0x8e
	{ "ADC A,A", 0, NULL, 0 },       // 0x8f
	{ "SUB A,B", 0, NULL, 0 },       // 0x90
	{ "SUB A,C", 0, NULL, 0 },       // 0x91
	{ "SUB A,D", 0, NULL, 0 },       // 0x92
	{ "SUB A,E", 0, NULL, 0 },       // 0x93
	{ "SUB A,H", 0, NULL, 0 },       // 0x94
	{ "SUB A,L", 0, NULL, 0 },       // 0x95
	{ "SUB A,(HL)", 0, NULL, 0 },    // 0x96
	{ "SUB A,A", 0, NULL, 0 },       // 0x97
	{ "SBC A,B", 0, NULL, 0 },       // 0x98
	{ "SBC A,C", 0, NULL, 0 },       // 0x99
	{ "SBC A,D", 0, NULL, 0 },       // 0x9a
	{ "SBC A,E", 0, NULL, 0 },       // 0x9b
	{ "SBC A,H", 0, NULL, 0 },       // 0x9c
	{ "SBC A,L", 0, NULL, 0 },       // 0x9d
	{ "SBC A,(HL)", 0, NULL, 0 },    // 0x9e
	{ "SBC A,A", 0, NULL, 0 },       // 0x9f
	{ "AND B", 0, NULL, 0 },         // 0xa0
	{ "AND C", 0, NULL, 0 },         // 0xa1
	{ "AND D", 0, NULL, 0 },         // 0xa2
	{ "AND E", 0, NULL, 0 },         // 0xa3
	{ "AND H", 0, NULL, 0 },         // 0xa4
	{ "AND L", 0, NULL, 0 },         // 0xa5
	{ "AND (HL)", 0, NULL, 0 },      // 0xa6
	{ "AND A", 0, NULL, 0 },         // 0xa7
	{ "XOR B", 0, xor_b, 4 },         // 0xa8
	{ "XOR C", 0, xor_c, 4 },         // 0xa9
	{ "XOR D", 0, xor_d, 4 },         // 0xaa
	{ "XOR E", 0, xor_e, 4 },         // 0xab
	{ "XOR H", 0, xor_h, 4 },         // 0xac
	{ "XOR L", 0, xor_l, 4 },         // 0xad
	{ "XOR (HL)", 0, NULL, 0 },      // 0xae
	{ "XOR A", 0, xor_a, 4 },         // 0xaf
	{ "OR B", 0, NULL, 0 },          // 0xb0
	{ "OR C", 0, NULL, 0 },          // 0xb1
	{ "OR D", 0, NULL, 0 },          // 0xb2
	{ "OR E", 0, NULL, 0 },          // 0xb3
	{ "OR H", 0, NULL, 0 },          // 0xb4
	{ "OR L", 0, NULL, 0 },          // 0xb5
	{ "OR (HL)", 0, NULL, 0 },       // 0xb6
	{ "OR A", 0, NULL, 0 },          // 0xb7
	{ "CP B", 0, NULL, 0 },          // 0xb8
	{ "CP C", 0, NULL, 0 },          // 0xb9
	{ "CP D", 0, NULL, 0 },          // 0xba
	{ "CP E", 0, NULL, 0 },          // 0xbb
	{ "CP H", 0, NULL, 0 },          // 0xbc
	{ "CP L", 0, NULL, 0 },          // 0xbd
	{ "CP (HL)", 0, NULL, 0 },       // 0xbe
	{ "CP A", 0, NULL, 0 },          // 0xbf
	{ "RET NZ", 0, NULL, 0 },        // 0xc0
	{ "POP BC", 0, NULL, 0 },        // 0xc1
	{ "JP NZ,nn", 0, NULL, 0 },      // 0xc2
	{ "JP nn", 2, jp_nn, 16 },         // 0xc3
	{ "CALL NZ,nn", 0, NULL, 0 },    // 0xc4
	{ "PUSH BC", 0, NULL, 0 },       // 0xc5
	{ "ADD A,n", 0, NULL, 0 },       // 0xc6
	{ "RST 0", 0, NULL, 0 },         // 0xc7
	{ "RET Z", 0, NULL, 0 },         // 0xc8
	{ "RET", 0, NULL, 0 },           // 0xc9
	{ "JP Z,nn", 0, NULL, 0 },       // 0xca
	{ "Ext ops", 0, NULL, 0 },       // 0xcb
	{ "CALL Z,nn", 0, NULL, 0 },     // 0xcc
	{ "CALL nn", 0, NULL, 0 },       // 0xcd
	{ "ADC A,n", 0, NULL, 0 },       // 0xce
	{ "RST 8", 0, NULL, 0 },         // 0xcf
	{ "RET NC", 0, NULL, 0 },        // 0xd0
	{ "POP DE", 0, NULL, 0 },        // 0xd1
	{ "JP NC,nn", 0, NULL, 0 },      // 0xd2
	{ "XX", 0, NULL, 0 },            // 0xd3
	{ "CALL NC,nn", 0, NULL, 0 },    // 0xd4
	{ "PUSH DE", 0, NULL, 0 },       // 0xd5
	{ "SUB A,n", 0, NULL, 0 },       // 0xd6
	{ "RST 10", 0, NULL, 0 },        // 0xd7
	{ "RET C", 0, NULL, 0 },         // 0xd8
	{ "RETI", 0, NULL, 0 },          // 0xd9
	{ "JP C,nn", 0, NULL, 0 },       // 0xda
	{ "XX", 0, NULL, 0 },            // 0xdb
	{ "CALL C,nn", 0, NULL, 0 },     // 0xdc
	{ "XX", 0, NULL, 0 },            // 0xdd
	{ "SBC A,n", 0, NULL, 0 },       // 0xde
	{ "RST 18", 0, NULL, 0 },        // 0xdf
	{ "LDH (n),A", 0, NULL, 0 },     // 0xe0
	{ "POP HL", 0, NULL, 0 },        // 0xe1
	{ "LDH (C),A", 0, NULL, 0 },     // 0xe2
	{ "XX", 0, NULL, 0 },            // 0xe3
	{ "XX", 0, NULL, 0 },            // 0xe4
	{ "PUSH HL", 0, NULL, 0 },       // 0xe5
	{ "AND n", 0, NULL, 0 },         // 0xe6
	{ "RST 20", 0, NULL, 0 },        // 0xe7
	{ "ADD SP,d", 0, NULL, 0 },      // 0xe8
	{ "JP (HL)", 0, NULL, 0 },       // 0xe9
	{ "LD (nn),A", 0, NULL, 0 },     // 0xea
	{ "XX", 0, NULL, 0 },            // 0xeb
	{ "XX", 0, NULL, 0 },            // 0xec
	{ "XX", 0, NULL, 0 },            // 0xed
	{ "XOR n", 0, NULL, 0 },         // 0xee
	{ "RST 28", 0, NULL, 0 },        // 0xef
	{ "LDH A,(n)", 1, ldh_a_n, 12 },     // 0xf0
	{ "POP AF", 0, NULL, 0 },        // 0xf1
	{ "XX", 0, NULL, 0 },            // 0xf2
	{ "DI", 0, NULL, 0 },            // 0xf3
	{ "XX", 0, NULL, 0 },            // 0xf4
	{ "PUSH AF", 0, NULL, 0 },       // 0xf5
	{ "OR n", 0, NULL, 0 },          // 0xf6
	{ "RST 30", 0, NULL, 0 },        // 0xf7
	{ "LDHL SP,d", 0, NULL, 0 },     // 0xf8
	{ "LD SP,HL", 0, NULL, 0 },      // 0xf9
	{ "LD A,(nn)", 0, NULL, 0 },     // 0xfa
	{ "EI", 0, NULL, 0 },            // 0xfb
	{ "XX", 0, NULL, 0 },            // 0xfc
	{ "XX", 0, NULL, 0 },            // 0xfd
	{ "CP n", 0, NULL, 0 },          // 0xfe
	{ "RST 38", 0, NULL, 0 }         // 0xff
};

const t_opcode	cb_opcode[] = {
	{ "RLC B", 0, NULL, 0 },         // 0x00
	{ "RLC C", 0, NULL, 0 },         // 0x01
	{ "RLC D", 0, NULL, 0 },         // 0x02
	{ "RLC E", 0, NULL, 0 },         // 0x03
	{ "RLC H", 0, NULL, 0 },         // 0x04
	{ "RLC L", 0, NULL, 0 },         // 0x05
	{ "RLC (HL)", 0, NULL, 0 },      // 0x06
	{ "RLC A", 0, NULL, 0 },         // 0x07
	{ "RRC B", 0, NULL, 0 },         // 0x08
	{ "RRC C", 0, NULL, 0 },         // 0x09
	{ "RRC D", 0, NULL, 0 },         // 0x0a
	{ "RRC E", 0, NULL, 0 },         // 0x0b
	{ "RRC H", 0, NULL, 0 },         // 0x0c
	{ "RRC L", 0, NULL, 0 },         // 0x0d
	{ "RRC (HL)", 0, NULL, 0 },      // 0x0e
	{ "RRC A", 0, NULL, 0 },         // 0x0f
	{ "RL B", 0, NULL, 0 },          // 0x10
	{ "RL C", 0, NULL, 0 },          // 0x11
	{ "RL D", 0, NULL, 0 },          // 0x12
	{ "RL E", 0, NULL, 0 },          // 0x13
	{ "RL H", 0, NULL, 0 },          // 0x14
	{ "RL L", 0, NULL, 0 },          // 0x15
	{ "RL (HL)", 0, NULL, 0 },       // 0x16
	{ "RL A", 0, NULL, 0 },          // 0x17
	{ "RR B", 0, NULL, 0 },          // 0x18
	{ "RR C", 0, NULL, 0 },          // 0x19
	{ "RR D", 0, NULL, 0 },          // 0x1a
	{ "RR E", 0, NULL, 0 },          // 0x1b
	{ "RR H", 0, NULL, 0 },          // 0x1c
	{ "RR L", 0, NULL, 0 },          // 0x1d
	{ "RR (HL)", 0, NULL, 0 },       // 0x1e
	{ "RR A", 0, NULL, 0 },          // 0x1f
	{ "SLA B", 0, NULL, 0 },         // 0x20
	{ "SLA C", 0, NULL, 0 },         // 0x21
	{ "SLA D", 0, NULL, 0 },         // 0x22
	{ "SLA E", 0, NULL, 0 },         // 0x23
	{ "SLA H", 0, NULL, 0 },         // 0x24
	{ "SLA L", 0, NULL, 0 },         // 0x25
	{ "SLA (HL)", 0, NULL, 0 },      // 0x26
	{ "SLA A", 0, NULL, 0 },         // 0x27
	{ "SRA B", 0, NULL, 0 },         // 0x28
	{ "SRA C", 0, NULL, 0 },         // 0x29
	{ "SRA D", 0, NULL, 0 },         // 0x2a
	{ "SRA E", 0, NULL, 0 },         // 0x2b
	{ "SRA H", 0, NULL, 0 },         // 0x2c
	{ "SRA L", 0, NULL, 0 },         // 0x2d
	{ "SRA (HL)", 0, NULL, 0 },      // 0x2e
	{ "SRA A", 0, NULL, 0 },         // 0x2f
	{ "SWAP B", 0, NULL, 0 },        // 0x30
	{ "SWAP C", 0, NULL, 0 },        // 0x31
	{ "SWAP D", 0, NULL, 0 },        // 0x32
	{ "SWAP E", 0, NULL, 0 },        // 0x33
	{ "SWAP H", 0, NULL, 0 },        // 0x34
	{ "SWAP L", 0, NULL, 0 },        // 0x35
	{ "SWAP (HL)", 0, NULL, 0 },     // 0x36
	{ "SWAP A", 0, NULL, 0 },        // 0x37
	{ "SRL B", 0, NULL, 0 },         // 0x38
	{ "SRL C", 0, NULL, 0 },         // 0x39
	{ "SRL D", 0, NULL, 0 },         // 0x3a
	{ "SRL E", 0, NULL, 0 },         // 0x3b
	{ "SRL H", 0, NULL, 0 },         // 0x3c
	{ "SRL L", 0, NULL, 0 },         // 0x3d
	{ "SRL (HL)", 0, NULL, 0 },      // 0x3e
	{ "SRL A", 0, NULL, 0 },         // 0x3f
	{ "BIT 0,B", 0, NULL, 0 },       // 0x40
	{ "BIT 0,C", 0, NULL, 0 },       // 0x41
	{ "BIT 0,D", 0, NULL, 0 },       // 0x42
	{ "BIT 0,E", 0, NULL, 0 },       // 0x43
	{ "BIT 0,H", 0, NULL, 0 },       // 0x44
	{ "BIT 0,L", 0, NULL, 0 },       // 0x45
	{ "BIT 0,(HL)", 0, NULL, 0 },    // 0x46
	{ "BIT 0,A", 0, NULL, 0 },       // 0x47
	{ "BIT 1,B", 0, NULL, 0 },       // 0x48
	{ "BIT 1,C", 0, NULL, 0 },       // 0x49
	{ "BIT 1,D", 0, NULL, 0 },       // 0x4a
	{ "BIT 1,E", 0, NULL, 0 },       // 0x4b
	{ "BIT 1,H", 0, NULL, 0 },       // 0x4c
	{ "BIT 1,L", 0, NULL, 0 },       // 0x4d
	{ "BIT 1,(HL)", 0, NULL, 0 },    // 0x4e
	{ "BIT 1,A", 0, NULL, 0 },       // 0x4f
	{ "BIT 2,B", 0, NULL, 0 },       // 0x50
	{ "BIT 2,C", 0, NULL, 0 },       // 0x51
	{ "BIT 2,D", 0, NULL, 0 },       // 0x52
	{ "BIT 2,E", 0, NULL, 0 },       // 0x53
	{ "BIT 2,H", 0, NULL, 0 },       // 0x54
	{ "BIT 2,L", 0, NULL, 0 },       // 0x55
	{ "BIT 2,(HL)", 0, NULL, 0 },    // 0x56
	{ "BIT 2,A", 0, NULL, 0 },       // 0x57
	{ "BIT 3,B", 0, NULL, 0 },       // 0x58
	{ "BIT 3,C", 0, NULL, 0 },       // 0x59
	{ "BIT 3,D", 0, NULL, 0 },       // 0x5a
	{ "BIT 3,E", 0, NULL, 0 },       // 0x5b
	{ "BIT 3,H", 0, NULL, 0 },       // 0x5c
	{ "BIT 3,L", 0, NULL, 0 },       // 0x5d
	{ "BIT 3,(HL)", 0, NULL, 0 },    // 0x5e
	{ "BIT 3,A", 0, NULL, 0 },       // 0x5f
	{ "BIT 4,B", 0, NULL, 0 },       // 0x60
	{ "BIT 4,C", 0, NULL, 0 },       // 0x61
	{ "BIT 4,D", 0, NULL, 0 },       // 0x62
	{ "BIT 4,E", 0, NULL, 0 },       // 0x63
	{ "BIT 4,H", 0, NULL, 0 },       // 0x64
	{ "BIT 4,L", 0, NULL, 0 },       // 0x65
	{ "BIT 4,(HL)", 0, NULL, 0 },    // 0x66
	{ "BIT 4,A", 0, NULL, 0 },       // 0x67
	{ "BIT 5,B", 0, NULL, 0 },       // 0x68
	{ "BIT 5,C", 0, NULL, 0 },       // 0x69
	{ "BIT 5,D", 0, NULL, 0 },       // 0x6a
	{ "BIT 5,E", 0, NULL, 0 },       // 0x6b
	{ "BIT 5,H", 0, NULL, 0 },       // 0x6c
	{ "BIT 5,L", 0, NULL, 0 },       // 0x6d
	{ "BIT 5,(HL)", 0, NULL, 0 },    // 0x6e
	{ "BIT 5,A", 0, NULL, 0 },       // 0x6f
	{ "BIT 6,B", 0, NULL, 0 },       // 0x70
	{ "BIT 6,C", 0, NULL, 0 },       // 0x71
	{ "BIT 6,D", 0, NULL, 0 },       // 0x72
	{ "BIT 6,E", 0, NULL, 0 },       // 0x73
	{ "BIT 6,H", 0, NULL, 0 },       // 0x74
	{ "BIT 6,L", 0, NULL, 0 },       // 0x75
	{ "BIT 6,(HL)", 0, NULL, 0 },    // 0x76
	{ "BIT 6,A", 0, NULL, 0 },       // 0x77
	{ "BIT 7,B", 0, NULL, 0 },       // 0x78
	{ "BIT 7,C", 0, NULL, 0 },       // 0x79
	{ "BIT 7,D", 0, NULL, 0 },       // 0x7a
	{ "BIT 7,E", 0, NULL, 0 },       // 0x7b
	{ "BIT 7,H", 0, NULL, 0 },       // 0x7c
	{ "BIT 7,L", 0, NULL, 0 },       // 0x7d
	{ "BIT 7,(HL)", 0, NULL, 0 },    // 0x7e
	{ "BIT 7,A", 0, NULL, 0 },       // 0x7f
	{ "RES 0,B", 0, NULL, 0 },       // 0x80
	{ "RES 0,C", 0, NULL, 0 },       // 0x81
	{ "RES 0,D", 0, NULL, 0 },       // 0x82
	{ "RES 0,E", 0, NULL, 0 },       // 0x83
	{ "RES 0,H", 0, NULL, 0 },       // 0x84
	{ "RES 0,L", 0, NULL, 0 },       // 0x85
	{ "RES 0,(HL)", 0, NULL, 0 },    // 0x86
	{ "RES 0,A", 0, NULL, 0 },       // 0x87
	{ "RES 1,B", 0, NULL, 0 },       // 0x88
	{ "RES 1,C", 0, NULL, 0 },       // 0x89
	{ "RES 1,D", 0, NULL, 0 },       // 0x8a
	{ "RES 1,E", 0, NULL, 0 },       // 0x8b
	{ "RES 1,H", 0, NULL, 0 },       // 0x8c
	{ "RES 1,L", 0, NULL, 0 },       // 0x8d
	{ "RES 1,(HL)", 0, NULL, 0 },    // 0x8e
	{ "RES 1,A", 0, NULL, 0 },       // 0x8f
	{ "RES 2,B", 0, NULL, 0 },       // 0x90
	{ "RES 2,C", 0, NULL, 0 },       // 0x91
	{ "RES 2,D", 0, NULL, 0 },       // 0x92
	{ "RES 2,E", 0, NULL, 0 },       // 0x93
	{ "RES 2,H", 0, NULL, 0 },       // 0x94
	{ "RES 2,L", 0, NULL, 0 },       // 0x95
	{ "RES 2,(HL)", 0, NULL, 0 },    // 0x96
	{ "RES 2,A", 0, NULL, 0 },       // 0x97
	{ "RES 3,B", 0, NULL, 0 },       // 0x98
	{ "RES 3,C", 0, NULL, 0 },       // 0x99
	{ "RES 3,D", 0, NULL, 0 },       // 0x9a
	{ "RES 3,E", 0, NULL, 0 },       // 0x9b
	{ "RES 3,H", 0, NULL, 0 },       // 0x9c
	{ "RES 3,L", 0, NULL, 0 },       // 0x9d
	{ "RES 3,(HL)", 0, NULL, 0 },    // 0x9e
	{ "RES 3,A", 0, NULL, 0 },       // 0x9f
	{ "RES 4,B", 0, NULL, 0 },       // 0xa0
	{ "RES 4,C", 0, NULL, 0 },       // 0xa1
	{ "RES 4,D", 0, NULL, 0 },       // 0xa2
	{ "RES 4,E", 0, NULL, 0 },       // 0xa3
	{ "RES 4,H", 0, NULL, 0 },       // 0xa4
	{ "RES 4,L", 0, NULL, 0 },       // 0xa5
	{ "RES 4,(HL)", 0, NULL, 0 },    // 0xa6
	{ "RES 4,A", 0, NULL, 0 },       // 0xa7
	{ "RES 5,B", 0, NULL, 0 },       // 0xa8
	{ "RES 5,C", 0, NULL, 0 },       // 0xa9
	{ "RES 5,D", 0, NULL, 0 },       // 0xaa
	{ "RES 5,E", 0, NULL, 0 },       // 0xab
	{ "RES 5,H", 0, NULL, 0 },       // 0xac
	{ "RES 5,L", 0, NULL, 0 },       // 0xad
	{ "RES 5,(HL)", 0, NULL, 0 },    // 0xae
	{ "RES 5,A", 0, NULL, 0 },       // 0xaf
	{ "RES 6,B", 0, NULL, 0 },       // 0xb0
	{ "RES 6,C", 0, NULL, 0 },       // 0xb1
	{ "RES 6,D", 0, NULL, 0 },       // 0xb2
	{ "RES 6,E", 0, NULL, 0 },       // 0xb3
	{ "RES 6,H", 0, NULL, 0 },       // 0xb4
	{ "RES 6,L", 0, NULL, 0 },       // 0xb5
	{ "RES 6,(HL)", 0, NULL, 0 },    // 0xb6
	{ "RES 6,A", 0, NULL, 0 },       // 0xb7
	{ "RES 7,B", 0, NULL, 0 },       // 0xb8
	{ "RES 7,C", 0, NULL, 0 },       // 0xb9
	{ "RES 7,D", 0, NULL, 0 },       // 0xba
	{ "RES 7,E", 0, NULL, 0 },       // 0xbb
	{ "RES 7,H", 0, NULL, 0 },       // 0xbc
	{ "RES 7,L", 0, NULL, 0 },       // 0xbd
	{ "RES 7,(HL)", 0, NULL, 0 },    // 0xbe
	{ "RES 7,A", 0, NULL, 0 },       // 0xbf
	{ "SET 0,B", 0, NULL, 0 },       // 0xc0
	{ "SET 0,C", 0, NULL, 0 },       // 0xc1
	{ "SET 0,D", 0, NULL, 0 },       // 0xc2
	{ "SET 0,E", 0, NULL, 0 },       // 0xc3
	{ "SET 0,H", 0, NULL, 0 },       // 0xc4
	{ "SET 0,L", 0, NULL, 0 },       // 0xc5
	{ "SET 0,(HL)", 0, NULL, 0 },    // 0xc6
	{ "SET 0,A", 0, NULL, 0 },       // 0xc7
	{ "SET 1,B", 0, NULL, 0 },       // 0xc8
	{ "SET 1,C", 0, NULL, 0 },       // 0xc9
	{ "SET 1,D", 0, NULL, 0 },       // 0xca
	{ "SET 1,E", 0, NULL, 0 },       // 0xcb
	{ "SET 1,H", 0, NULL, 0 },       // 0xcc
	{ "SET 1,L", 0, NULL, 0 },       // 0xcd
	{ "SET 1,(HL)", 0, NULL, 0 },    // 0xce
	{ "SET 1,A", 0, NULL, 0 },       // 0xcf
	{ "SET 2,B", 0, NULL, 0 },       // 0xd0
	{ "SET 2,C", 0, NULL, 0 },       // 0xd1
	{ "SET 2,D", 0, NULL, 0 },       // 0xd2
	{ "SET 2,E", 0, NULL, 0 },       // 0xd3
	{ "SET 2,H", 0, NULL, 0 },       // 0xd4
	{ "SET 2,L", 0, NULL, 0 },       // 0xd5
	{ "SET 2,(HL)", 0, NULL, 0 },    // 0xd6
	{ "SET 2,A", 0, NULL, 0 },       // 0xd7
	{ "SET 3,B", 0, NULL, 0 },       // 0xd8
	{ "SET 3,C", 0, NULL, 0 },       // 0xd9
	{ "SET 3,D", 0, NULL, 0 },       // 0xda
	{ "SET 3,E", 0, NULL, 0 },       // 0xdb
	{ "SET 3,H", 0, NULL, 0 },       // 0xdc
	{ "SET 3,L", 0, NULL, 0 },       // 0xdd
	{ "SET 3,(HL)", 0, NULL, 0 },    // 0xde
	{ "SET 3,A", 0, NULL, 0 },       // 0xdf
	{ "SET 4,B", 0, NULL, 0 },       // 0xe0
	{ "SET 4,C", 0, NULL, 0 },       // 0xe1
	{ "SET 4,D", 0, NULL, 0 },       // 0xe2
	{ "SET 4,E", 0, NULL, 0 },       // 0xe3
	{ "SET 4,H", 0, NULL, 0 },       // 0xe4
	{ "SET 4,L", 0, NULL, 0 },       // 0xe5
	{ "SET 4,(HL)", 0, NULL, 0 },    // 0xe6
	{ "SET 4,A", 0, NULL, 0 },       // 0xe7
	{ "SET 5,B", 0, NULL, 0 },       // 0xe8
	{ "SET 5,C", 0, NULL, 0 },       // 0xe9
	{ "SET 5,D", 0, NULL, 0 },       // 0xea
	{ "SET 5,E", 0, NULL, 0 },       // 0xeb
	{ "SET 5,H", 0, NULL, 0 },       // 0xec
	{ "SET 5,L", 0, NULL, 0 },       // 0xed
	{ "SET 5,(HL)", 0, NULL, 0 },    // 0xee
	{ "SET 5,A", 0, NULL, 0 },       // 0xef
	{ "SET 6,B", 0, NULL, 0 },       // 0xf0
	{ "SET 6,C", 0, NULL, 0 },       // 0xf1
	{ "SET 6,D", 0, NULL, 0 },       // 0xf2
	{ "SET 6,E", 0, NULL, 0 },       // 0xf3
	{ "SET 6,H", 0, NULL, 0 },       // 0xf4
	{ "SET 6,L", 0, NULL, 0 },       // 0xf5
	{ "SET 6,(HL)", 0, NULL, 0 },    // 0xf6
	{ "SET 6,A", 0, NULL, 0 },       // 0xf7
	{ "SET 7,B", 0, NULL, 0 },       // 0xf8
	{ "SET 7,C", 0, NULL, 0 },       // 0xf9
	{ "SET 7,D", 0, NULL, 0 },       // 0xfa
	{ "SET 7,E", 0, NULL, 0 },       // 0xfb
	{ "SET 7,H", 0, NULL, 0 },       // 0xfc
	{ "SET 7,L", 0, NULL, 0 },       // 0xfd
	{ "SET 7,(HL)", 0, NULL, 0 },    // 0xfe
	{ "SET 7,A", 0, NULL, 0 },       // 0xff
};

void			next_opcode(void)
{
	const t_opcode	*op;

	op = opcodes + mem.memory[reg.pc];
	if (op->fn == NULL) {
		printf("-> %s (0x%02hhx) TODO\n", op->name, mem.memory[reg.pc]);
		exit(0);
	} else if (op->argument == 0) {
		printf("-> %s (0x%02hhx) DONE\n", op->name, mem.memory[reg.pc]);
		reg.pc += 1;
		((void (*)(void))(op->fn))();
	} else if (op->argument == 1) {
		printf("-> %s (0x%02hhx) (op = 0x%02hhx) DONE\n", op->name, mem.memory[reg.pc], mem.memory[reg.pc + 1]);
		reg.pc += 2;
		((void (*)(unsigned char))(op->fn))(mem.memory[reg.pc - 1]);
	} else if (op->argument == 2) {
		printf("-> %s (0x%02hhx) (op = 0x%04hx) DONE\n", op->name, mem.memory[reg.pc], *((unsigned short *)(mem.memory + reg.pc + 1)));
		reg.pc += 3;
		((void (*)(unsigned short))(op->fn))(*((unsigned short *)(mem.memory + reg.pc - 2)));
	}
}
