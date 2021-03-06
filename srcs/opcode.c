#include "opcodes.h"
#include "basics.h"
#include "registers.h"
#include "memory.h"

size_t			total_clock = 0;
size_t			last_clock = 0;
bool			should_enable_interrupt = false;
bool			should_disable_interrupt = false;
bool			master_interrupt = false;

void			daa(void)
{
	unsigned short	new_a;

	new_a = reg.a;
	if (FLAG_ZERO) {
		if (FLAG_HALF) {
			new_a = (new_a - 6) & 0xFF;
		}
		if (FLAG_CARRY) {
			new_a -= 0x60;
		}
	} else {
		if (FLAG_HALF || (new_a & 0x0f) > 0x09) {
			new_a += 0x06;
		}
		if (FLAG_CARRY || new_a > 0x9f) {
			new_a += 0x60;
		}
	}
	SET_ZERO_IF(new_a & 0xff);
	UNSET_FLAG_HALF;
	SET_CARRY_IF(new_a & 0xff00);
	reg.a = ((unsigned char)(new_a & 0xff));
}

unsigned char	add(unsigned char v1, unsigned char v2)
{
	unsigned short	ret;

	ret = (v1 & 0xf) + (v2 & 0xf);
	SET_HALF_IF((ret & 0xf0) != 0);
	ret = v1 + v2;
	SET_CARRY_IF((ret & 0xff00) != 0);
	SET_ZERO_IF((ret & 0xff) == 0);
	UNSET_FLAG_NEG;
	return ((unsigned char)(ret & 0xff));
}

void			add_reg_val(unsigned short *r, unsigned short val)
{
	unsigned int	res;

	res = *r + val;
	SET_CARRY_IF(res & 0xffff0000);
	UNSET_FLAG_NEG;
	SET_HALF_IF(((*r & 0x0fff) + (val & 0x0fff)) & 0xf000);
	*r = (unsigned short)(res & 0xffff);
}

void			add_carry(unsigned char op)
{
	unsigned short	res;

	res = reg.a + op + FLAG_CARRY;
	SET_HALF_IF(((reg.a & 0xf) + (op & 0xf) + FLAG_CARRY) & 0xf0);
	SET_CARRY_IF(res & 0xff00);
	SET_ZERO_IF((res & 0x00ff) == 0);
	UNSET_FLAG_NEG;
	reg.a = (unsigned char)(res & 0x00ff);
}

unsigned char	sub(unsigned char v1, unsigned char v2)
{
	unsigned short	ret;

	SET_FLAG_NEG;
	SET_CARRY_IF(v2 > v1);
	SET_HALF_IF((v2 & 0x0f) > (v1 & 0x0f));
	ret = v1 - v2;
	SET_ZERO_IF((ret & 0x00ff) == 0);
	return ((unsigned char)(ret & 0x00ff));
}

void			sub_carry(unsigned char op)
{
	unsigned short	ret;

	ret = reg.a + FLAG_CARRY;
	SET_FLAG_NEG;
	SET_CARRY_IF((unsigned short)op > ret);
	SET_HALF_IF((op & 0x0f) > (ret & 0x0f));
	ret -= op;
	SET_ZERO_IF((ret & 0x00ff) == 0);
	reg.a = (unsigned char)(ret & 0x00ff);
}

void			and(unsigned char op)
{
	reg.a &= op;
	SET_ZERO_IF(reg.a == 0);
	UNSET_FLAG_NEG;
	SET_FLAG_HALF;
	UNSET_FLAG_CARRY;
}

void			xor(unsigned char op)
{
	reg.a ^= op;
	SET_ZERO_IF(reg.a == 0);
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	UNSET_FLAG_CARRY;
}

void			or(unsigned char op)
{
	reg.a |= op;
	SET_ZERO_IF(reg.a == 0);
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	UNSET_FLAG_CARRY;
}

void			cp(unsigned char op)
{
	SET_ZERO_IF(reg.a == op);
	SET_CARRY_IF(reg.a <= op);
	SET_HALF_IF((reg.a & 0x0f) > (op & 0x0f));
	SET_FLAG_NEG;
}

unsigned char	inc(unsigned char op)
{
	SET_HALF_IF((op & 0x0f) == 0x0f);
	op += 1;
	SET_ZERO_IF(op == 0);
	UNSET_FLAG_NEG;
	return (op);
}

unsigned char	dec(unsigned char op)
{
	SET_HALF_IF(op & 0x0f);
	op -= 1;
	SET_ZERO_IF(op == 0);
	SET_FLAG_NEG;
	return (op);
}

unsigned char rlc(unsigned char op)
{
	unsigned char	new_carry;

	new_carry = (op >> 7) & 1;
	op = (op << 1) | new_carry;
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	SET_CARRY_IF(new_carry != 0);
	return (op);
}

unsigned char rrc(unsigned char op)
{
	unsigned char	new_carry;

	new_carry = op & 1;
	op = (op >> 1) | (new_carry << 7);
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	SET_CARRY_IF(new_carry != 0);
	return (op);
}

unsigned char rl(unsigned char op)
{
	unsigned char	new_carry;

	new_carry = (op >> 7) & 1;
	op = (op << 1) | FLAG_CARRY;
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	SET_CARRY_IF(new_carry != 0);
	return (op);
}

unsigned char rr(unsigned char op)
{
	unsigned char	new_carry;

	new_carry = op & 1;
	op = (op >> 1) | (FLAG_CARRY << 7);
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	SET_CARRY_IF(new_carry != 0);
	return (op);
}

unsigned char sla(unsigned char op)
{
	SET_CARRY_IF((op >> 7) & 1);
	op <<= 1;
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	return (op);
}

unsigned char sra(unsigned char op)
{
	SET_CARRY_IF(op & 1);
	op = (op & (1 << 7)) | op >> 1;
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	return (op);
}

unsigned char swap(unsigned char op)
{
	op = (op << 4) | (op >> 4);
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	UNSET_FLAG_CARRY;
	SET_ZERO_IF(op == 0);
	return (op);
}

unsigned char srl(unsigned char op)
{
	SET_CARRY_IF(op & 1);
	op >>= 1;
	UNSET_FLAG_NEG;
	UNSET_FLAG_HALF;
	SET_ZERO_IF(op == 0);
	return (op);
}

void		bit(unsigned char b, unsigned char op)
{
	UNSET_FLAG_NEG;
	SET_FLAG_HALF;
	SET_ZERO_IF(((op >> b) & 1) == 0);
}

unsigned char	res(unsigned char b, unsigned char op)
{
	return (op & ~(1 << b));
}

unsigned char	set(unsigned char b, unsigned char op)
{
	return (op | (1 << b));
}

/* 0x00 */ void rlc_b(void) { reg.b = rlc(reg.b); }
/* 0x01 */ void rlc_c(void) { reg.c = rlc(reg.c); }
/* 0x02 */ void rlc_d(void) { reg.d = rlc(reg.d); }
/* 0x03 */ void rlc_e(void) { reg.e = rlc(reg.e); }
/* 0x04 */ void rlc_h(void) { reg.h = rlc(reg.h); }
/* 0x05 */ void rlc_l(void) { reg.l = rlc(reg.l); }
/* 0x06 */ void rlc_hl(void) { memory_write_byte(reg.hl, rlc(memory_read_byte(reg.hl))); }
/* 0x07 */ void rlc_a_cb(void) { reg.a = rlc(reg.a); }
/* 0x08 */ void rrc_b(void) { reg.b = rrc(reg.b); }
/* 0x09 */ void rrc_c(void) { reg.b = rrc(reg.b); }
/* 0x0a */ void rrc_d(void) { reg.b = rrc(reg.b); }
/* 0x0b */ void rrc_e(void) { reg.b = rrc(reg.b); }
/* 0x0c */ void rrc_h(void) { reg.b = rrc(reg.b); }
/* 0x0d */ void rrc_l(void) { reg.b = rrc(reg.b); }
/* 0x0e */ void rrc_hl(void) { memory_write_byte(reg.hl, rrc(memory_read_byte(reg.hl))); }
/* 0x0f */ void rrc_a_cb(void) { reg.b = rrc(reg.b); }
/* 0x10 */ void rl_b(void) { reg.b = rl(reg.b); }
/* 0x11 */ void rl_c(void) { reg.c = rl(reg.c); }
/* 0x12 */ void rl_d(void) { reg.d = rl(reg.d); }
/* 0x13 */ void rl_e(void) { reg.e = rl(reg.e); }
/* 0x14 */ void rl_h(void) { reg.h = rl(reg.h); }
/* 0x15 */ void rl_l(void) { reg.l = rl(reg.l); }
/* 0x16 */ void rl_hl(void) { memory_write_byte(reg.hl, rl(memory_read_byte(reg.hl))); }
/* 0x17 */ void rl_a_cb(void) { reg.a = rl(reg.a); }
/* 0x18 */ void rr_b(void) { reg.b = rr(reg.b); }
/* 0x19 */ void rr_c(void) { reg.c = rr(reg.b); }
/* 0x1a */ void rr_d(void) { reg.d = rr(reg.d); }
/* 0x1b */ void rr_e(void) { reg.e = rr(reg.e); }
/* 0x1c */ void rr_h(void) { reg.h = rr(reg.h); }
/* 0x1d */ void rr_l(void) { reg.l = rr(reg.l); }
/* 0x1e */ void rr_hl(void) { memory_write_byte(reg.hl, rr(memory_read_byte(reg.hl))); }
/* 0x1f */ void rr_a_cb(void) { reg.a = rr(reg.a); }
/* 0x20 */ void sla_b(void) { reg.b = sla(reg.b); }
/* 0x21 */ void sla_c(void) { reg.c = sla(reg.c); }
/* 0x22 */ void sla_d(void) { reg.d = sla(reg.d); }
/* 0x23 */ void sla_e(void) { reg.e = sla(reg.e); }
/* 0x24 */ void sla_h(void) { reg.h = sla(reg.h); }
/* 0x25 */ void sla_l(void) { reg.l = sla(reg.l); }
/* 0x26 */ void sla_hl(void) { memory_write_byte(reg.hl, sla(memory_read_byte(reg.hl))); }
/* 0x27 */ void sla_a(void) { reg.a = sla(reg.a); }
/* 0x28 */ void sra_b(void) { reg.b = sra(reg.b); }
/* 0x29 */ void sra_c(void) { reg.c = sra(reg.c); }
/* 0x2a */ void sra_d(void) { reg.d = sra(reg.d); }
/* 0x2b */ void sra_e(void) { reg.e = sra(reg.e); }
/* 0x2c */ void sra_h(void) { reg.h = sra(reg.h); }
/* 0x2d */ void sra_l(void) { reg.l = sra(reg.l); }
/* 0x2e */ void sra_hl(void) { memory_write_byte(reg.hl, sra(memory_read_byte(reg.hl))); }
/* 0x2f */ void sra_a(void) { reg.a = sra(reg.a); }
/* 0x30 */ void swap_b(void) { reg.b = swap(reg.b); }
/* 0x31 */ void swap_c(void) { reg.c = swap(reg.c); }
/* 0x32 */ void swap_d(void) { reg.d = swap(reg.d); }
/* 0x33 */ void swap_e(void) { reg.e = swap(reg.e); }
/* 0x34 */ void swap_h(void) { reg.h = swap(reg.h); }
/* 0x35 */ void swap_l(void) { reg.l = swap(reg.l); }
/* 0x36 */ void swap_hl(void) { memory_write_byte(reg.hl, swap(memory_read_byte(reg.hl))); }
/* 0x37 */ void swap_a(void) { reg.a = swap(reg.a); }
/* 0x38 */ void srl_b(void) { reg.b = srl(reg.b); }
/* 0x39 */ void srl_c(void) { reg.c = srl(reg.c); }
/* 0x3a */ void srl_d(void) { reg.d = srl(reg.d); }
/* 0x3b */ void srl_e(void) { reg.e = srl(reg.e); }
/* 0x3c */ void srl_h(void) { reg.h = srl(reg.h); }
/* 0x3d */ void srl_l(void) { reg.l = srl(reg.l); }
/* 0x3e */ void srl_hl(void) { memory_write_byte(reg.hl, srl(memory_read_byte(reg.hl))); }
/* 0x3f */ void srl_a(void) { reg.a = srl(reg.a); }
/* 0x40 */ void bit_0_b(void) { bit(0, reg.b); }
/* 0x41 */ void bit_0_c(void) { bit(0, reg.c); }
/* 0x42 */ void bit_0_d(void) { bit(0, reg.d); }
/* 0x43 */ void bit_0_e(void) { bit(0, reg.e); }
/* 0x44 */ void bit_0_h(void) { bit(0, reg.h); }
/* 0x45 */ void bit_0_l(void) { bit(0, reg.l); }
/* 0x46 */ void bit_0_hl(void) { bit(0, memory_read_byte(reg.hl)); }
/* 0x47 */ void bit_0_a(void) { bit(0, reg.a); }
/* 0x48 */ void bit_1_b(void) { bit(1, reg.b); }
/* 0x49 */ void bit_1_c(void) { bit(1, reg.c); }
/* 0x4a */ void bit_1_d(void) { bit(1, reg.d); }
/* 0x4b */ void bit_1_e(void) { bit(1, reg.e); }
/* 0x4c */ void bit_1_h(void) { bit(1, reg.h); }
/* 0x4d */ void bit_1_l(void) { bit(1, reg.l); }
/* 0x4e */ void bit_1_hl(void) { bit(1, memory_read_byte(reg.hl)); }
/* 0x4f */ void bit_1_a(void) { bit(1, reg.a); }
/* 0x50 */ void bit_2_b(void) { bit(2, reg.b); }
/* 0x51 */ void bit_2_c(void) { bit(2, reg.c); }
/* 0x52 */ void bit_2_d(void) { bit(2, reg.d); }
/* 0x53 */ void bit_2_e(void) { bit(2, reg.e); }
/* 0x54 */ void bit_2_h(void) { bit(2, reg.h); }
/* 0x55 */ void bit_2_l(void) { bit(2, reg.l); }
/* 0x56 */ void bit_2_hl(void) { bit(2, memory_read_byte(reg.hl)); }
/* 0x57 */ void bit_2_a(void) { bit(2, reg.a); }
/* 0x58 */ void bit_3_b(void) { bit(3, reg.b); }
/* 0x59 */ void bit_3_c(void) { bit(3, reg.c); }
/* 0x5a */ void bit_3_d(void) { bit(3, reg.d); }
/* 0x5b */ void bit_3_e(void) { bit(3, reg.e); }
/* 0x5c */ void bit_3_h(void) { bit(3, reg.h); }
/* 0x5d */ void bit_3_l(void) { bit(3, reg.l); }
/* 0x5e */ void bit_3_hl(void) { bit(3, memory_read_byte(reg.hl)); }
/* 0x5f */ void bit_3_a(void) { bit(3, reg.a); }
/* 0x60 */ void bit_4_b(void) { bit(4, reg.b); }
/* 0x61 */ void bit_4_c(void) { bit(4, reg.c); }
/* 0x62 */ void bit_4_d(void) { bit(4, reg.d); }
/* 0x63 */ void bit_4_e(void) { bit(4, reg.e); }
/* 0x64 */ void bit_4_h(void) { bit(4, reg.h); }
/* 0x65 */ void bit_4_l(void) { bit(4, reg.l); }
/* 0x66 */ void bit_4_hl(void) { bit(4, memory_read_byte(reg.hl)); }
/* 0x67 */ void bit_4_a(void) { bit(4, reg.a); }
/* 0x68 */ void bit_5_b(void) { bit(5, reg.b); }
/* 0x69 */ void bit_5_c(void) { bit(5, reg.c); }
/* 0x6a */ void bit_5_d(void) { bit(5, reg.d); }
/* 0x6b */ void bit_5_e(void) { bit(5, reg.e); }
/* 0x6c */ void bit_5_h(void) { bit(5, reg.h); }
/* 0x6d */ void bit_5_l(void) { bit(5, reg.l); }
/* 0x6e */ void bit_5_hl(void) { bit(5, memory_read_byte(reg.hl)); }
/* 0x6f */ void bit_5_a(void) { bit(5, reg.a); }
/* 0x70 */ void bit_6_b(void) { bit(6, reg.b); }
/* 0x71 */ void bit_6_c(void) { bit(6, reg.c); }
/* 0x72 */ void bit_6_d(void) { bit(6, reg.d); }
/* 0x73 */ void bit_6_e(void) { bit(6, reg.e); }
/* 0x74 */ void bit_6_h(void) { bit(6, reg.h); }
/* 0x75 */ void bit_6_l(void) { bit(6, reg.l); }
/* 0x76 */ void bit_6_hl(void) { bit(6, memory_read_byte(reg.hl)); }
/* 0x77 */ void bit_6_a(void) { bit(6, reg.a); }
/* 0x78 */ void bit_7_b(void) { bit(7, reg.b); }
/* 0x79 */ void bit_7_c(void) { bit(7, reg.c); }
/* 0x7a */ void bit_7_d(void) { bit(7, reg.d); }
/* 0x7b */ void bit_7_e(void) { bit(7, reg.e); }
/* 0x7c */ void bit_7_h(void) { bit(7, reg.h); }
/* 0x7d */ void bit_7_l(void) { bit(7, reg.l); }
/* 0x7e */ void bit_7_hl(void) { bit(7, memory_read_byte(reg.hl)); }
/* 0x7f */ void bit_7_a(void) { bit(7, reg.a); }
/* 0x80 */ void res_0_b(void) { reg.b = res(0, reg.b); }
/* 0x81 */ void res_0_c(void) { reg.c = res(0, reg.c); }
/* 0x82 */ void res_0_d(void) { reg.d = res(0, reg.d); }
/* 0x83 */ void res_0_e(void) { reg.e = res(0, reg.e); }
/* 0x84 */ void res_0_h(void) { reg.h = res(0, reg.h); }
/* 0x85 */ void res_0_l(void) { reg.l = res(0, reg.l); }
/* 0x86 */ void res_0_hl(void) { memory_write_byte(reg.hl, res(0, memory_read_byte(reg.hl))); }
/* 0x87 */ void res_0_a(void) { reg.a = res(0, reg.a); }
/* 0x88 */ void res_1_b(void) { reg.b = res(1, reg.b); }
/* 0x89 */ void res_1_c(void) { reg.c = res(1, reg.c); }
/* 0x8a */ void res_1_d(void) { reg.d = res(1, reg.d); }
/* 0x8b */ void res_1_e(void) { reg.e = res(1, reg.e); }
/* 0x8c */ void res_1_h(void) { reg.h = res(1, reg.h); }
/* 0x8d */ void res_1_l(void) { reg.l = res(1, reg.l); }
/* 0x8e */ void res_1_hl(void) { memory_write_byte(reg.hl, res(1, memory_read_byte(reg.hl))); }
/* 0x8f */ void res_1_a(void) { reg.a = res(1, reg.a); }
/* 0x90 */ void res_2_b(void) { reg.b = res(2, reg.b); }
/* 0x91 */ void res_2_c(void) { reg.c = res(2, reg.c); }
/* 0x92 */ void res_2_d(void) { reg.d = res(2, reg.d); }
/* 0x93 */ void res_2_e(void) { reg.e = res(2, reg.e); }
/* 0x94 */ void res_2_h(void) { reg.h = res(2, reg.h); }
/* 0x95 */ void res_2_l(void) { reg.l = res(2, reg.l); }
/* 0x96 */ void res_2_hl(void) { memory_write_byte(reg.hl, res(2, memory_read_byte(reg.hl))); }
/* 0x97 */ void res_2_a(void) { reg.a = res(2, reg.a); }
/* 0x98 */ void res_3_b(void) { reg.b = res(3, reg.b); }
/* 0x99 */ void res_3_c(void) { reg.c = res(3, reg.c); }
/* 0x9a */ void res_3_d(void) { reg.d = res(3, reg.d); }
/* 0x9b */ void res_3_e(void) { reg.e = res(3, reg.e); }
/* 0x9c */ void res_3_h(void) { reg.h = res(3, reg.h); }
/* 0x9d */ void res_3_l(void) { reg.l = res(3, reg.l); }
/* 0x9e */ void res_3_hl(void) { memory_write_byte(reg.hl, res(3, memory_read_byte(reg.hl))); }
/* 0x9f */ void res_3_a(void) { reg.a = res(3, reg.a); }
/* 0xa0 */ void res_4_b(void) { reg.b = res(4, reg.b); }
/* 0xa1 */ void res_4_c(void) { reg.c = res(4, reg.c); }
/* 0xa2 */ void res_4_d(void) { reg.d = res(4, reg.d); }
/* 0xa3 */ void res_4_e(void) { reg.e = res(4, reg.e); }
/* 0xa4 */ void res_4_h(void) { reg.h = res(4, reg.h); }
/* 0xa5 */ void res_4_l(void) { reg.l = res(4, reg.l); }
/* 0xa6 */ void res_4_hl(void) { memory_write_byte(reg.hl, res(4, memory_read_byte(reg.hl))); }
/* 0xa7 */ void res_4_a(void) { reg.a = res(4, reg.a); }
/* 0xa8 */ void res_5_b(void) { reg.b = res(5, reg.b); }
/* 0xa9 */ void res_5_c(void) { reg.c = res(5, reg.c); }
/* 0xaa */ void res_5_d(void) { reg.d = res(5, reg.d); }
/* 0xab */ void res_5_e(void) { reg.e = res(5, reg.e); }
/* 0xac */ void res_5_h(void) { reg.h = res(5, reg.h); }
/* 0xad */ void res_5_l(void) { reg.l = res(5, reg.l); }
/* 0xae */ void res_5_hl(void) { memory_write_byte(reg.hl, res(5, memory_read_byte(reg.hl))); }
/* 0xaf */ void res_5_a(void) { reg.a = res(5, reg.a); }
/* 0xb0 */ void res_6_b(void) { reg.b = res(6, reg.b); }
/* 0xb1 */ void res_6_c(void) { reg.c = res(6, reg.c); }
/* 0xb2 */ void res_6_d(void) { reg.d = res(6, reg.d); }
/* 0xb3 */ void res_6_e(void) { reg.e = res(6, reg.e); }
/* 0xb4 */ void res_6_h(void) { reg.h = res(6, reg.h); }
/* 0xb5 */ void res_6_l(void) { reg.l = res(6, reg.l); }
/* 0xb6 */ void res_6_hl(void) { memory_write_byte(reg.hl, res(6, memory_read_byte(reg.hl))); }
/* 0xb7 */ void res_6_a(void) { reg.a = res(6, reg.a); }
/* 0xb8 */ void res_7_b(void) { reg.b = res(7, reg.b); }
/* 0xb9 */ void res_7_c(void) { reg.c = res(7, reg.c); }
/* 0xba */ void res_7_d(void) { reg.d = res(7, reg.d); }
/* 0xbb */ void res_7_e(void) { reg.e = res(7, reg.e); }
/* 0xbc */ void res_7_h(void) { reg.h = res(7, reg.h); }
/* 0xbd */ void res_7_l(void) { reg.l = res(7, reg.l); }
/* 0xbe */ void res_7_hl(void) { memory_write_byte(reg.hl, res(7, memory_read_byte(reg.hl))); }
/* 0xbf */ void res_7_a(void) { reg.a = res(7, reg.a); }
/* 0xc0 */ void set_0_b(void) { reg.b = set(0, reg.b); }
/* 0xc1 */ void set_0_c(void) { reg.c = set(0, reg.c); }
/* 0xc2 */ void set_0_d(void) { reg.d = set(0, reg.d); }
/* 0xc3 */ void set_0_e(void) { reg.e = set(0, reg.e); }
/* 0xc4 */ void set_0_h(void) { reg.h = set(0, reg.h); }
/* 0xc5 */ void set_0_l(void) { reg.l = set(0, reg.l); }
/* 0xc6 */ void set_0_hl(void) { memory_write_byte(reg.hl, set(0, memory_read_byte(reg.hl))); }
/* 0xc7 */ void set_0_a(void) { reg.a = set(0, reg.a); }
/* 0xc8 */ void set_1_b(void) { reg.b = set(1, reg.b); }
/* 0xc9 */ void set_1_c(void) { reg.c = set(1, reg.c); }
/* 0xca */ void set_1_d(void) { reg.d = set(1, reg.d); }
/* 0xcb */ void set_1_e(void) { reg.e = set(1, reg.e); }
/* 0xcc */ void set_1_h(void) { reg.h = set(1, reg.h); }
/* 0xcd */ void set_1_l(void) { reg.l = set(1, reg.l); }
/* 0xce */ void set_1_hl(void) { memory_write_byte(reg.hl, set(1, memory_read_byte(reg.hl))); }
/* 0xcf */ void set_1_a(void) { reg.a = set(1, reg.a); }
/* 0xd0 */ void set_2_b(void) { reg.b = set(2, reg.b); }
/* 0xd1 */ void set_2_c(void) { reg.c = set(2, reg.c); }
/* 0xd2 */ void set_2_d(void) { reg.d = set(2, reg.d); }
/* 0xd3 */ void set_2_e(void) { reg.e = set(2, reg.e); }
/* 0xd4 */ void set_2_h(void) { reg.h = set(2, reg.h); }
/* 0xd5 */ void set_2_l(void) { reg.l = set(2, reg.l); }
/* 0xd6 */ void set_2_hl(void) { memory_write_byte(reg.hl, set(2, memory_read_byte(reg.hl))); }
/* 0xd7 */ void set_2_a(void) { reg.a = set(2, reg.a); }
/* 0xd8 */ void set_3_b(void) { reg.b = set(3, reg.b); }
/* 0xd9 */ void set_3_c(void) { reg.c = set(3, reg.c); }
/* 0xda */ void set_3_d(void) { reg.d = set(3, reg.d); }
/* 0xdb */ void set_3_e(void) { reg.e = set(3, reg.e); }
/* 0xdc */ void set_3_h(void) { reg.h = set(3, reg.h); }
/* 0xdd */ void set_3_l(void) { reg.l = set(3, reg.l); }
/* 0xde */ void set_3_hl(void) { memory_write_byte(reg.hl, set(3, memory_read_byte(reg.hl))); }
/* 0xdf */ void set_3_a(void) { reg.a = set(3, reg.a); }
/* 0xe0 */ void set_4_b(void) { reg.b = set(4, reg.b); }
/* 0xe1 */ void set_4_c(void) { reg.c = set(4, reg.c); }
/* 0xe2 */ void set_4_d(void) { reg.d = set(4, reg.d); }
/* 0xe3 */ void set_4_e(void) { reg.e = set(4, reg.e); }
/* 0xe4 */ void set_4_h(void) { reg.h = set(4, reg.h); }
/* 0xe5 */ void set_4_l(void) { reg.l = set(4, reg.l); }
/* 0xe6 */ void set_4_hl(void) { memory_write_byte(reg.hl, set(4, memory_read_byte(reg.hl))); }
/* 0xe7 */ void set_4_a(void) { reg.a = set(4, reg.a); }
/* 0xe8 */ void set_5_b(void) { reg.b = set(5, reg.b); }
/* 0xe9 */ void set_5_c(void) { reg.c = set(5, reg.c); }
/* 0xea */ void set_5_d(void) { reg.d = set(5, reg.d); }
/* 0xeb */ void set_5_e(void) { reg.e = set(5, reg.e); }
/* 0xec */ void set_5_h(void) { reg.h = set(5, reg.h); }
/* 0xed */ void set_5_l(void) { reg.l = set(5, reg.l); }
/* 0xee */ void set_5_hl(void) { memory_write_byte(reg.hl, set(5, memory_read_byte(reg.hl))); }
/* 0xef */ void set_5_a(void) { reg.a = set(5, reg.a); }
/* 0xf0 */ void set_6_b(void) { reg.b = set(6, reg.b); }
/* 0xf1 */ void set_6_c(void) { reg.c = set(6, reg.c); }
/* 0xf2 */ void set_6_d(void) { reg.d = set(6, reg.d); }
/* 0xf3 */ void set_6_e(void) { reg.e = set(6, reg.e); }
/* 0xf4 */ void set_6_h(void) { reg.h = set(6, reg.h); }
/* 0xf5 */ void set_6_l(void) { reg.l = set(6, reg.l); }
/* 0xf6 */ void set_6_hl(void) { memory_write_byte(reg.hl, set(6, memory_read_byte(reg.hl))); }
/* 0xf7 */ void set_6_a(void) { reg.a = set(6, reg.a); }
/* 0xf8 */ void set_7_b(void) { reg.b = set(7, reg.b); }
/* 0xf9 */ void set_7_c(void) { reg.c = set(7, reg.c); }
/* 0xfa */ void set_7_d(void) { reg.d = set(7, reg.d); }
/* 0xfb */ void set_7_e(void) { reg.e = set(7, reg.e); }
/* 0xfc */ void set_7_h(void) { reg.h = set(7, reg.h); }
/* 0xfd */ void set_7_l(void) { reg.l = set(7, reg.l); }
/* 0xfe */ void set_7_hl(void) { memory_write_byte(reg.hl, set(7, memory_read_byte(reg.hl))); }
/* 0xff */ void set_7_a(void) { reg.a = set(7, reg.a); }

const t_opcode	cb_opcodes[] = {
	{ "RLC B", 0, rlc_b, 8 },         // 0x00
	{ "RLC C", 0, rlc_c, 8 },         // 0x01
	{ "RLC D", 0, rlc_d, 8 },         // 0x02
	{ "RLC E", 0, rlc_e, 8 },         // 0x03
	{ "RLC H", 0, rlc_h, 8 },         // 0x04
	{ "RLC L", 0, rlc_l, 8 },         // 0x05
	{ "RLC (HL)", 0, rlc_hl, 16 },      // 0x06
	{ "RLC A", 0, rlc_a_cb, 8 },         // 0x07
	{ "RRC B", 0, rrc_b, 8 },         // 0x08
	{ "RRC C", 0, rrc_c, 8 },         // 0x09
	{ "RRC D", 0, rrc_d, 8 },         // 0x0a
	{ "RRC E", 0, rrc_e, 8 },         // 0x0b
	{ "RRC H", 0, rrc_h, 8 },         // 0x0c
	{ "RRC L", 0, rrc_l, 8 },         // 0x0d
	{ "RRC (HL)", 0, rrc_hl, 16 },      // 0x0e
	{ "RRC A", 0, rrc_a_cb, 8 },         // 0x0f
	{ "RL B", 0, rl_b, 8 },          // 0x10
	{ "RL C", 0, rl_c, 8 },          // 0x11
	{ "RL D", 0, rl_d, 8 },          // 0x12
	{ "RL E", 0, rl_e, 8 },          // 0x13
	{ "RL H", 0, rl_h, 8 },          // 0x14
	{ "RL L", 0, rl_l, 8 },          // 0x15
	{ "RL (HL)", 0, rl_hl, 16 },       // 0x16
	{ "RL A", 0, rl_a_cb, 8 },          // 0x17
	{ "RR B", 0, rr_b, 8 },          // 0x18
	{ "RR C", 0, rr_c, 8 },          // 0x19
	{ "RR D", 0, rr_d, 8 },          // 0x1a
	{ "RR E", 0, rr_e, 8 },          // 0x1b
	{ "RR H", 0, rr_h, 8 },          // 0x1c
	{ "RR L", 0, rr_l, 8 },          // 0x1d
	{ "RR (HL)", 0, rr_hl, 16 },       // 0x1e
	{ "RR A", 0, rr_a_cb, 8 },          // 0x1f
	{ "SLA B", 0, sla_b, 8 },         // 0x20
	{ "SLA C", 0, sla_c, 8 },         // 0x21
	{ "SLA D", 0, sla_d, 8 },         // 0x22
	{ "SLA E", 0, sla_e, 8 },         // 0x23
	{ "SLA H", 0, sla_h, 8 },         // 0x24
	{ "SLA L", 0, sla_l, 8 },         // 0x25
	{ "SLA (HL)", 0, sla_hl, 8 },      // 0x26
	{ "SLA A", 0, sla_a, 8 },         // 0x27
	{ "SRA B", 0, sra_b, 8 },         // 0x28
	{ "SRA C", 0, sra_c, 8 },         // 0x29
	{ "SRA D", 0, sra_d, 8 },         // 0x2a
	{ "SRA E", 0, sra_e, 8 },         // 0x2b
	{ "SRA H", 0, sra_h, 8 },         // 0x2c
	{ "SRA L", 0, sra_l, 8 },         // 0x2d
	{ "SRA (HL)", 0, sra_hl, 8 },      // 0x2e
	{ "SRA A", 0, sra_a, 8 },         // 0x2f
	{ "SWAP B", 0, swap_b, 8 },        // 0x30
	{ "SWAP C", 0, swap_c, 8 },        // 0x31
	{ "SWAP D", 0, swap_d, 8 },        // 0x32
	{ "SWAP E", 0, swap_e, 8 },        // 0x33
	{ "SWAP H", 0, swap_h, 8 },        // 0x34
	{ "SWAP L", 0, swap_l, 8 },        // 0x35
	{ "SWAP (HL)", 0, swap_hl, 8 },     // 0x36
	{ "SWAP A", 0, swap_a, 8 },        // 0x37
	{ "SRL B", 0, srl_b, 8 },         // 0x38
	{ "SRL C", 0, srl_c, 8 },         // 0x39
	{ "SRL D", 0, srl_d, 8 },         // 0x3a
	{ "SRL E", 0, srl_e, 8 },         // 0x3b
	{ "SRL H", 0, srl_h, 8 },         // 0x3c
	{ "SRL L", 0, srl_l, 8 },         // 0x3d
	{ "SRL (HL)", 0, srl_hl, 8 },      // 0x3e
	{ "SRL A", 0, srl_a, 8 },         // 0x3f
	{ "BIT 0,B", 0, bit_0_b, 8 },       // 0x40
	{ "BIT 0,C", 0, bit_0_c, 8 },       // 0x41
	{ "BIT 0,D", 0, bit_0_d, 8 },       // 0x42
	{ "BIT 0,E", 0, bit_0_e, 8 },       // 0x43
	{ "BIT 0,H", 0, bit_0_h, 8 },       // 0x44
	{ "BIT 0,L", 0, bit_0_l, 8 },       // 0x45
	{ "BIT 0,(HL)", 0, bit_0_hl, 16 },    // 0x46
	{ "BIT 0,A", 0, bit_0_a, 8 },       // 0x47
	{ "BIT 1,B", 0, bit_1_b, 8 },       // 0x48
	{ "BIT 1,C", 0, bit_1_c, 8 },       // 0x49
	{ "BIT 1,D", 0, bit_1_d, 8 },       // 0x4a
	{ "BIT 1,E", 0, bit_1_e, 8 },       // 0x4b
	{ "BIT 1,H", 0, bit_1_h, 8 },       // 0x4c
	{ "BIT 1,L", 0, bit_1_l, 8 },       // 0x4d
	{ "BIT 1,(HL)", 0, bit_1_hl, 16 },    // 0x4e
	{ "BIT 1,A", 0, bit_1_a, 8 },       // 0x4f
	{ "BIT 2,B", 0, bit_2_b, 8 },       // 0x50
	{ "BIT 2,C", 0, bit_2_c, 8 },       // 0x51
	{ "BIT 2,D", 0, bit_2_d, 8 },       // 0x52
	{ "BIT 2,E", 0, bit_2_e, 8 },       // 0x53
	{ "BIT 2,H", 0, bit_2_h, 8 },       // 0x54
	{ "BIT 2,L", 0, bit_2_l, 8 },       // 0x55
	{ "BIT 2,(HL)", 0, bit_2_hl, 16 },    // 0x56
	{ "BIT 2,A", 0, bit_2_a, 8 },       // 0x57
	{ "BIT 3,B", 0, bit_3_b, 8 },       // 0x58
	{ "BIT 3,C", 0, bit_3_c, 8 },       // 0x59
	{ "BIT 3,D", 0, bit_3_d, 8 },       // 0x5a
	{ "BIT 3,E", 0, bit_3_e, 8 },       // 0x5b
	{ "BIT 3,H", 0, bit_3_h, 8 },       // 0x5c
	{ "BIT 3,L", 0, bit_3_l, 8 },       // 0x5d
	{ "BIT 3,(HL)", 0, bit_3_hl, 16 },    // 0x5e
	{ "BIT 3,A", 0, bit_3_a, 8 },       // 0x5f
	{ "BIT 4,B", 0, bit_4_b, 8 },       // 0x60
	{ "BIT 4,C", 0, bit_4_c, 8 },       // 0x61
	{ "BIT 4,D", 0, bit_4_d, 8 },       // 0x62
	{ "BIT 4,E", 0, bit_4_e, 8 },       // 0x63
	{ "BIT 4,H", 0, bit_4_h, 8 },       // 0x64
	{ "BIT 4,L", 0, bit_4_l, 8 },       // 0x65
	{ "BIT 4,(HL)", 0, bit_4_hl, 16 },    // 0x66
	{ "BIT 4,A", 0, bit_4_a, 8 },       // 0x67
	{ "BIT 5,B", 0, bit_5_b, 8 },       // 0x68
	{ "BIT 5,C", 0, bit_5_c, 8 },       // 0x69
	{ "BIT 5,D", 0, bit_5_d, 8 },       // 0x6a
	{ "BIT 5,E", 0, bit_5_e, 8 },       // 0x6b
	{ "BIT 5,H", 0, bit_5_h, 8 },       // 0x6c
	{ "BIT 5,L", 0, bit_5_l, 8 },       // 0x6d
	{ "BIT 5,(HL)", 0, bit_5_hl, 16 },    // 0x6e
	{ "BIT 5,A", 0, bit_5_a, 8 },       // 0x6f
	{ "BIT 6,B", 0, bit_6_b, 8 },       // 0x70
	{ "BIT 6,C", 0, bit_6_c, 8 },       // 0x71
	{ "BIT 6,D", 0, bit_6_d, 8 },       // 0x72
	{ "BIT 6,E", 0, bit_6_e, 8 },       // 0x73
	{ "BIT 6,H", 0, bit_6_h, 8 },       // 0x74
	{ "BIT 6,L", 0, bit_6_l, 8 },       // 0x75
	{ "BIT 6,(HL)", 0, bit_6_hl, 16 },    // 0x76
	{ "BIT 6,A", 0, bit_6_a, 8 },       // 0x77
	{ "BIT 7,B", 0, bit_7_b, 8 },       // 0x78
	{ "BIT 7,C", 0, bit_7_c, 8 },       // 0x79
	{ "BIT 7,D", 0, bit_7_d, 8 },       // 0x7a
	{ "BIT 7,E", 0, bit_7_e, 8 },       // 0x7b
	{ "BIT 7,H", 0, bit_7_h, 8 },       // 0x7c
	{ "BIT 7,L", 0, bit_7_l, 8 },       // 0x7d
	{ "BIT 7,(HL)", 0, bit_7_hl, 16 },    // 0x7e
	{ "BIT 7,A", 0, bit_7_a, 8 },       // 0x7f
	{ "RES 0,B", 0, res_0_b, 8 },       // 0x80
	{ "RES 0,C", 0, res_0_c, 8 },       // 0x81
	{ "RES 0,D", 0, res_0_d, 8 },       // 0x82
	{ "RES 0,E", 0, res_0_e, 8 },       // 0x83
	{ "RES 0,H", 0, res_0_h, 8 },       // 0x84
	{ "RES 0,L", 0, res_0_l, 8 },       // 0x85
	{ "RES 0,(HL)", 0, res_0_hl, 16 },    // 0x86
	{ "RES 0,A", 0, res_0_a, 8 },       // 0x87
	{ "RES 1,B", 0, res_1_b, 8 },       // 0x88
	{ "RES 1,C", 0, res_1_c, 8 },       // 0x89
	{ "RES 1,D", 0, res_1_d, 8 },       // 0x8a
	{ "RES 1,E", 0, res_1_e, 8 },       // 0x8b
	{ "RES 1,H", 0, res_1_h, 8 },       // 0x8c
	{ "RES 1,L", 0, res_1_l, 8 },       // 0x8d
	{ "RES 1,(HL)", 0, res_1_hl, 16 },    // 0x8e
	{ "RES 1,A", 0, res_1_a, 8 },       // 0x8f
	{ "RES 2,B", 0, res_2_b, 8 },       // 0x90
	{ "RES 2,C", 0, res_2_c, 8 },       // 0x91
	{ "RES 2,D", 0, res_2_d, 8 },       // 0x92
	{ "RES 2,E", 0, res_2_e, 8 },       // 0x93
	{ "RES 2,H", 0, res_2_h, 8 },       // 0x94
	{ "RES 2,L", 0, res_2_l, 8 },       // 0x95
	{ "RES 2,(HL)", 0, res_2_hl, 16 },    // 0x96
	{ "RES 2,A", 0, res_2_a, 8 },       // 0x97
	{ "RES 3,B", 0, res_3_b, 8 },       // 0x98
	{ "RES 3,C", 0, res_3_c, 8 },       // 0x99
	{ "RES 3,D", 0, res_3_d, 8 },       // 0x9a
	{ "RES 3,E", 0, res_3_e, 8 },       // 0x9b
	{ "RES 3,H", 0, res_3_h, 8 },       // 0x9c
	{ "RES 3,L", 0, res_3_l, 8 },       // 0x9d
	{ "RES 3,(HL)", 0, res_3_hl, 16 },    // 0x9e
	{ "RES 3,A", 0, res_3_a, 8 },       // 0x9f
	{ "RES 4,B", 0, res_4_b, 8 },       // 0xa0
	{ "RES 4,C", 0, res_4_c, 8 },       // 0xa1
	{ "RES 4,D", 0, res_4_d, 8 },       // 0xa2
	{ "RES 4,E", 0, res_4_e, 8 },       // 0xa3
	{ "RES 4,H", 0, res_4_h, 8 },       // 0xa4
	{ "RES 4,L", 0, res_4_l, 8 },       // 0xa5
	{ "RES 4,(HL)", 0, res_4_hl, 16 },    // 0xa6
	{ "RES 4,A", 0, res_4_a, 8 },       // 0xa7
	{ "RES 5,B", 0, res_5_b, 8 },       // 0xa8
	{ "RES 5,C", 0, res_5_c, 8 },       // 0xa9
	{ "RES 5,D", 0, res_5_d, 8 },       // 0xaa
	{ "RES 5,E", 0, res_5_e, 8 },       // 0xab
	{ "RES 5,H", 0, res_5_h, 8 },       // 0xac
	{ "RES 5,L", 0, res_5_l, 8 },       // 0xad
	{ "RES 5,(HL)", 0, res_5_hl, 16 },    // 0xae
	{ "RES 5,A", 0, res_5_a, 8 },       // 0xaf
	{ "RES 6,B", 0, res_6_b, 8 },       // 0xb0
	{ "RES 6,C", 0, res_6_c, 8 },       // 0xb1
	{ "RES 6,D", 0, res_6_d, 8 },       // 0xb2
	{ "RES 6,E", 0, res_6_e, 8 },       // 0xb3
	{ "RES 6,H", 0, res_6_h, 8 },       // 0xb4
	{ "RES 6,L", 0, res_6_l, 8 },       // 0xb5
	{ "RES 6,(HL)", 0, res_6_hl, 16 },    // 0xb6
	{ "RES 6,A", 0, res_6_a, 8 },       // 0xb7
	{ "RES 7,B", 0, res_7_b, 8 },       // 0xb8
	{ "RES 7,C", 0, res_7_c, 8 },       // 0xb9
	{ "RES 7,D", 0, res_7_d, 8 },       // 0xba
	{ "RES 7,E", 0, res_7_e, 8 },       // 0xbb
	{ "RES 7,H", 0, res_7_h, 8 },       // 0xbc
	{ "RES 7,L", 0, res_7_l, 8 },       // 0xbd
	{ "RES 7,(HL)", 0, res_7_hl, 16 },    // 0xbe
	{ "RES 7,A", 0, res_7_a, 8 },       // 0xbf
	{ "SET 0,B", 0, set_0_b, 8 },       // 0xc0
	{ "SET 0,C", 0, set_0_c, 8 },       // 0xc1
	{ "SET 0,D", 0, set_0_d, 8 },       // 0xc2
	{ "SET 0,E", 0, set_0_e, 8 },       // 0xc3
	{ "SET 0,H", 0, set_0_h, 8 },       // 0xc4
	{ "SET 0,L", 0, set_0_l, 8 },       // 0xc5
	{ "SET 0,(HL)", 0, set_0_hl, 16 },    // 0xc6
	{ "SET 0,A", 0, set_0_a, 8 },       // 0xc7
	{ "SET 1,B", 0, set_1_b, 8 },       // 0xc8
	{ "SET 1,C", 0, set_1_c, 8 },       // 0xc9
	{ "SET 1,D", 0, set_1_d, 8 },       // 0xca
	{ "SET 1,E", 0, set_1_e, 8 },       // 0xcb
	{ "SET 1,H", 0, set_1_h, 8 },       // 0xcc
	{ "SET 1,L", 0, set_1_l, 8 },       // 0xcd
	{ "SET 1,(HL)", 0, set_1_hl, 16 },    // 0xce
	{ "SET 1,A", 0, set_1_a, 8 },       // 0xcf
	{ "SET 2,B", 0, set_2_b, 8 },       // 0xd0
	{ "SET 2,C", 0, set_2_c, 8 },       // 0xd1
	{ "SET 2,D", 0, set_2_d, 8 },       // 0xd2
	{ "SET 2,E", 0, set_2_e, 8 },       // 0xd3
	{ "SET 2,H", 0, set_2_h, 8 },       // 0xd4
	{ "SET 2,L", 0, set_2_l, 8 },       // 0xd5
	{ "SET 2,(HL)", 0, set_2_hl, 16 },    // 0xd6
	{ "SET 2,A", 0, set_2_a, 8 },       // 0xd7
	{ "SET 3,B", 0, set_3_b, 8 },       // 0xd8
	{ "SET 3,C", 0, set_3_c, 8 },       // 0xd9
	{ "SET 3,D", 0, set_3_d, 8 },       // 0xda
	{ "SET 3,E", 0, set_3_e, 8 },       // 0xdb
	{ "SET 3,H", 0, set_3_h, 8 },       // 0xdc
	{ "SET 3,L", 0, set_3_l, 8 },       // 0xdd
	{ "SET 3,(HL)", 0, set_3_hl, 16 },    // 0xde
	{ "SET 3,A", 0, set_3_a, 8 },       // 0xdf
	{ "SET 4,B", 0, set_4_b, 8 },       // 0xe0
	{ "SET 4,C", 0, set_4_c, 8 },       // 0xe1
	{ "SET 4,D", 0, set_4_d, 8 },       // 0xe2
	{ "SET 4,E", 0, set_4_e, 8 },       // 0xe3
	{ "SET 4,H", 0, set_4_h, 8 },       // 0xe4
	{ "SET 4,L", 0, set_4_l, 8 },       // 0xe5
	{ "SET 4,(HL)", 0, set_4_hl, 16 },    // 0xe6
	{ "SET 4,A", 0, set_4_a, 8 },       // 0xe7
	{ "SET 5,B", 0, set_5_b, 8 },       // 0xe8
	{ "SET 5,C", 0, set_5_c, 8 },       // 0xe9
	{ "SET 5,D", 0, set_5_d, 8 },       // 0xea
	{ "SET 5,E", 0, set_5_e, 8 },       // 0xeb
	{ "SET 5,H", 0, set_5_h, 8 },       // 0xec
	{ "SET 5,L", 0, set_5_l, 8 },       // 0xed
	{ "SET 5,(HL)", 0, set_5_hl, 16 },    // 0xee
	{ "SET 5,A", 0, set_5_a, 8 },       // 0xef
	{ "SET 6,B", 0, set_6_b, 8 },       // 0xf0
	{ "SET 6,C", 0, set_6_c, 8 },       // 0xf1
	{ "SET 6,D", 0, set_6_d, 8 },       // 0xf2
	{ "SET 6,E", 0, set_6_e, 8 },       // 0xf3
	{ "SET 6,H", 0, set_6_h, 8 },       // 0xf4
	{ "SET 6,L", 0, set_6_l, 8 },       // 0xf5
	{ "SET 6,(HL)", 0, set_6_hl, 16 },    // 0xf6
	{ "SET 6,A", 0, set_6_a, 8 },       // 0xf7
	{ "SET 7,B", 0, set_7_b, 8 },       // 0xf8
	{ "SET 7,C", 0, set_7_c, 8 },       // 0xf9
	{ "SET 7,D", 0, set_7_d, 8 },       // 0xfa
	{ "SET 7,E", 0, set_7_e, 8 },       // 0xfb
	{ "SET 7,H", 0, set_7_h, 8 },       // 0xfc
	{ "SET 7,L", 0, set_7_l, 8 },       // 0xfd
	{ "SET 7,(HL)", 0, set_7_hl, 16 },    // 0xfe
	{ "SET 7,A", 0, set_7_a, 8 },       // 0xff
};

/* 0x00 */ void nop(void) { }
/* 0x01 */ void ld_bc_nn(unsigned short op) { reg.bc = op; }
/* 0x02 */ void ld_bc_a(void) { memory_write_byte(reg.bc, reg.a); }
/* 0x03 */ void inc_bc(void) { reg.bc += 1; }
/* 0x04 */ void inc_b(void) { reg.b = inc(reg.b); }
/* 0x05 */ void dec_b(void) { reg.b = dec(reg.b); }
/* 0x06 */ void ld_b_n(unsigned char op) { reg.b = op; }
/* 0x07 */ void rlc_a(void) { unsigned char c; SET_CARRY_IF(c = (reg.a >> 7) & 1); reg.a = (reg.a << 1) | c; SET_ZERO_IF(c == 0); UNSET_FLAG_NEG; UNSET_FLAG_HALF; }
/* 0x08 */ void ld_nn_sp(unsigned short op) { memory_write_word(op, reg.sp); }
/* 0x09 */ void add_hl_bc(void) { add_reg_val(&(reg.hl), reg.bc); }
/* 0x0a */ void ld_a_bc(void) { reg.a = memory_read_byte(reg.bc); }
/* 0x0b */ void dec_bc(void) { reg.bc -= 1; }
/* 0x0c */ void inc_c(void) { reg.c = inc(reg.c); }
/* 0x0d */ void dec_c(void) { reg.c = dec(reg.c); }
/* 0x0e */ void ld_c_n(unsigned char op) { reg.c = op; }
/* 0x0f */ void rrc_a(void) { unsigned char c; SET_CARRY_IF(c = (reg.a & 1) << 7); reg.a = (reg.a >> 1) | c; SET_ZERO_IF(c == 0); UNSET_FLAG_NEG; UNSET_FLAG_HALF; }
/* 0x10 */
/* 0x11 */ void ld_de_nn(unsigned short op) { reg.de = op; }
/* 0x12 */ void ld_de_a(void) { memory_write_byte(reg.de, reg.a); }
/* 0x13 */ void inc_de(void) { reg.de += 1; }
/* 0x14 */ void inc_d(void) { reg.d = inc(reg.d); }
/* 0x15 */ void dec_d(void) { reg.d = dec(reg.d); }
/* 0x16 */ void ld_d_n(unsigned char op) { reg.d = op; }
/* 0x17 */ void rl_a(void) { unsigned char c; c = FLAG_CARRY; SET_CARRY_IF((reg.a >> 7) & 1); reg.a = (reg.a << 1) | c; SET_ZERO_IF(c == 0); UNSET_FLAG_NEG; UNSET_FLAG_HALF; }
/* 0x18 */ void jr_n(unsigned char op) { reg.pc += (signed char) op; }
/* 0x19 */ void add_hl_de(void) { add_reg_val(&(reg.hl), reg.de); }
/* 0x1a */ void ld_a_de(void) { reg.a = memory_read_byte(reg.de); }
/* 0x1b */ void dec_de(void) { reg.de -= 1; }
/* 0x1c */ void inc_e(void) { reg.e = inc(reg.e); }
/* 0x1d */ void dec_e(void) { reg.e = dec(reg.e); }
/* 0x1e */ void ld_e_n(unsigned char op) { reg.e = op; }
/* 0x1f */ void rr_a(void) { unsigned char c; c = FLAG_CARRY << 7; SET_CARRY_IF(reg.a & 1); reg.a = (reg.a >> 1) | c; SET_ZERO_IF(c == 0); UNSET_FLAG_NEG; UNSET_FLAG_HALF; }
/* 0x20 */ void jr_nz_n(unsigned char op) { if (!FLAG_ZERO) { reg.pc += (signed char)op; total_clock += 4; last_clock += 4; } }
/* 0x21 */ void ld_hl_nn(unsigned short op) { reg.hl = op; }
/* 0x22 */ void ldi_hl_a(void) { memory_write_byte(reg.hl, reg.a); reg.hl += 1; }
/* 0x23 */ void inc_hl(void) { reg.hl += 1; }
/* 0x24 */ void inc_h(void) { reg.h = inc(reg.h); }
/* 0x25 */ void dec_h(void) { reg.h = dec(reg.h); }
/* 0x26 */ void ld_h_n(unsigned char op) { reg.h = op; }
/* 0x27 */ void daa_(void) { daa(); }
/* 0x28 */ void jr_z_n(unsigned char op) { if (FLAG_ZERO) { reg.pc += (signed char)op; total_clock += 4; last_clock += 4; } }
/* 0x29 */ void add_hl_hl(void) { add_reg_val(&(reg.hl), reg.hl); }
/* 0x2a */ void ldi_a_hl(void) { reg.a = memory_read_byte(reg.hl); reg.hl += 1; }
/* 0x2b */ void dec_hl(void) { reg.hl -= 1; }
/* 0x2c */ void inc_l(void) { reg.l = inc(reg.l); }
/* 0x2d */ void dec_l(void) { reg.l = dec(reg.l); }
/* 0x2e */ void ld_l_n(unsigned char op) { reg.l = op; }
/* 0x2f */ void cpl(void) { reg.a = ~reg.a; SET_FLAG_NEG; SET_FLAG_HALF; }
/* 0x30 */ void jr_nc_n(unsigned char op) { if (!FLAG_CARRY) { reg.pc += (signed char)op; total_clock += 4; last_clock += 4; } }
/* 0x31 */ void ld_sp_nn(unsigned short op) { reg.sp = op; }
/* 0x32 */ void ldd_hl_a(void) { memory_write_byte(reg.hl, reg.a); reg.hl -= 1; }
/* 0x33 */ void inc_sp(void) { reg.sp += 1; }
/* 0x34 */ void inc_hlp(void) { memory_write_byte(reg.hl, inc(memory_read_byte(reg.hl))); }
/* 0x35 */ void dec_hlp(void) { memory_write_byte(reg.hl, dec(memory_read_byte(reg.hl))); }
/* 0x36 */ void ld_hl_n(unsigned char op) { memory_write_byte(reg.hl, op); }
/* 0x37 */ void scf(void) { SET_FLAG_CARRY; UNSET_FLAG_NEG; UNSET_FLAG_HALF; }
/* 0x38 */ void jr_c_n(unsigned char op) { if (FLAG_CARRY) { reg.pc += (signed char)op; total_clock += 4; last_clock += 4; } }
/* 0x39 */ void add_hl_sp(void) { add_reg_val(&(reg.hl), reg.sp); }
/* 0x3a */ void ldd_a_hl(void) { reg.a = memory_read_byte(reg.hl); reg.hl -= 1; }
/* 0x3b */ void dec_sp(void) { reg.sp -= 1; }
/* 0x3c */ void inc_a(void) { reg.a = inc(reg.a); }
/* 0x3d */ void dec_a(void) { reg.a = dec(reg.a); }
/* 0x3e */ void ld_a_n(unsigned char op) { reg.a = op; }
/* 0x3f */ void ccf(void) { SET_CARRY_IF(!FLAG_CARRY); UNSET_FLAG_NEG; UNSET_FLAG_HALF; }
/* 0x40 */ void ld_b_b(void) { reg.b = reg.b; }
/* 0x41 */ void ld_b_c(void) { reg.b = reg.c; }
/* 0x42 */ void ld_b_d(void) { reg.b = reg.d; }
/* 0x43 */ void ld_b_e(void) { reg.b = reg.e; }
/* 0x44 */ void ld_b_h(void) { reg.b = reg.h; }
/* 0x45 */ void ld_b_l(void) { reg.b = reg.l; }
/* 0x46 */ void ld_b_hl(void) { reg.b = memory_read_byte(reg.hl); }
/* 0x47 */ void ld_b_a(void) { reg.b = reg.a; }
/* 0x48 */ void ld_c_b(void) { reg.c = reg.b; }
/* 0x49 */ void ld_c_c(void) { reg.c = reg.c; }
/* 0x4a */ void ld_c_d(void) { reg.c = reg.d; }
/* 0x4b */ void ld_c_e(void) { reg.c = reg.e; }
/* 0x4c */ void ld_c_h(void) { reg.c = reg.h; }
/* 0x4d */ void ld_c_l(void) { reg.c = reg.l; }
/* 0x4e */ void ld_c_hl(void) { reg.c = memory_read_byte(reg.hl); }
/* 0x4f */ void ld_c_a(void) { reg.c = reg.a; }
/* 0x50 */ void ld_d_b(void) { reg.d = reg.b; }
/* 0x51 */ void ld_d_c(void) { reg.d = reg.c; }
/* 0x52 */ void ld_d_d(void) { reg.d = reg.d; }
/* 0x53 */ void ld_d_e(void) { reg.d = reg.e; }
/* 0x54 */ void ld_d_h(void) { reg.d = reg.h; }
/* 0x55 */ void ld_d_l(void) { reg.d = reg.l; }
/* 0x56 */ void ld_d_hl(void) { reg.d = memory_read_byte(reg.hl); }
/* 0x57 */ void ld_d_a(void) { reg.d = reg.a; }
/* 0x58 */ void ld_e_b(void) { reg.e = reg.b; }
/* 0x59 */ void ld_e_c(void) { reg.e = reg.c; }
/* 0x5a */ void ld_e_d(void) { reg.e = reg.d; }
/* 0x5b */ void ld_e_e(void) { reg.e = reg.e; }
/* 0x5c */ void ld_e_h(void) { reg.e = reg.h; }
/* 0x5d */ void ld_e_l(void) { reg.e = reg.l; }
/* 0x5e */ void ld_e_hl(void) { reg.e = memory_read_byte(reg.hl); }
/* 0x5f */ void ld_e_a(void) { reg.e = reg.a; }
/* 0x60 */ void ld_h_b(void) { reg.h = reg.b; }
/* 0x61 */ void ld_h_c(void) { reg.h = reg.c; }
/* 0x62 */ void ld_h_d(void) { reg.h = reg.d; }
/* 0x63 */ void ld_h_e(void) { reg.h = reg.e; }
/* 0x64 */ void ld_h_h(void) { reg.h = reg.h; }
/* 0x65 */ void ld_h_l(void) { reg.h = reg.l; }
/* 0x66 */ void ld_h_hl(void) { reg.h = memory_read_byte(reg.hl); }
/* 0x67 */ void ld_h_a(void) { reg.h = reg.a; }
/* 0x68 */ void ld_l_b(void) { reg.l = reg.b; }
/* 0x69 */ void ld_l_c(void) { reg.l = reg.c; }
/* 0x6a */ void ld_l_d(void) { reg.l = reg.d; }
/* 0x6b */ void ld_l_e(void) { reg.l = reg.e; }
/* 0x6c */ void ld_l_h(void) { reg.l = reg.h; }
/* 0x6d */ void ld_l_l(void) { reg.l = reg.l; }
/* 0x6e */ void ld_l_hl(void) { reg.l = memory_read_byte(reg.hl); }
/* 0x6f */ void ld_l_a(void) { reg.l = reg.a; }
/* 0x70 */ void ld_hl_b(void) { memory_write_byte(reg.hl, reg.b); }
/* 0x71 */ void ld_hl_c(void) { memory_write_byte(reg.hl, reg.c); }
/* 0x72 */ void ld_hl_d(void) { memory_write_byte(reg.hl, reg.d); }
/* 0x73 */ void ld_hl_e(void) { memory_write_byte(reg.hl, reg.e); }
/* 0x74 */ void ld_hl_h(void) { memory_write_byte(reg.hl, reg.h); }
/* 0x75 */ void ld_hl_l(void) { memory_write_byte(reg.hl, reg.l); }
/* 0x76 */
/* 0x77 */ void ld_hl_a(void) { memory_write_byte(reg.hl, reg.a); }
/* 0x78 */ void ld_a_b(void) { reg.a = reg.b; }
/* 0x79 */ void ld_a_c(void) { reg.a = reg.c; }
/* 0x7a */ void ld_a_d(void) { reg.a = reg.d; }
/* 0x7b */ void ld_a_e(void) { reg.a = reg.e; }
/* 0x7c */ void ld_a_h(void) { reg.a = reg.h; }
/* 0x7d */ void ld_a_l(void) { reg.a = reg.l; }
/* 0x7e */ void ld_a_hl(void) { reg.a = memory_read_byte(reg.hl); }
/* 0x7f */ void ld_a_a(void) { reg.a = reg.a; }
/* 0x80 */ void add_a_b(void) { reg.a = add(reg.a, reg.b); }
/* 0x81 */ void add_a_c(void) { reg.a = add(reg.a, reg.c); }
/* 0x82 */ void add_a_d(void) { reg.a = add(reg.a, reg.d); }
/* 0x83 */ void add_a_e(void) { reg.a = add(reg.a, reg.e); }
/* 0x84 */ void add_a_h(void) { reg.a = add(reg.a, reg.h); }
/* 0x85 */ void add_a_l(void) { reg.a = add(reg.a, reg.l); }
/* 0x86 */ void add_a_hl(void) { reg.a = add(reg.a, memory_read_byte(reg.hl)); }
/* 0x87 */ void add_a_a(void) { reg.a = add(reg.a, reg.a); }
/* 0x88 */ void adc_a_b(void) { add_carry(reg.b); }
/* 0x89 */ void adc_a_c(void) { add_carry(reg.c); }
/* 0x8a */ void adc_a_d(void) { add_carry(reg.d); }
/* 0x8b */ void adc_a_e(void) { add_carry(reg.e); }
/* 0x8c */ void adc_a_h(void) { add_carry(reg.h); }
/* 0x8d */ void adc_a_l(void) { add_carry(reg.l); }
/* 0x8e */ void adc_a_hl(void) { add_carry(memory_read_byte(reg.hl)); }
/* 0x8f */ void adc_a_a(void) { add_carry(reg.a); }
/* 0x90 */ void sub_a_b(void) { reg.a = sub(reg.a, reg.b); }
/* 0x91 */ void sub_a_c(void) { reg.a = sub(reg.a, reg.c); }
/* 0x92 */ void sub_a_d(void) { reg.a = sub(reg.a, reg.d); }
/* 0x93 */ void sub_a_e(void) { reg.a = sub(reg.a, reg.e); }
/* 0x94 */ void sub_a_h(void) { reg.a = sub(reg.a, reg.h); }
/* 0x95 */ void sub_a_l(void) { reg.a = sub(reg.a, reg.l); }
/* 0x96 */ void sub_a_hl(void) { reg.a = sub(reg.a, memory_read_byte(reg.hl)); }
/* 0x97 */ void sub_a_a(void) { reg.a = sub(reg.a, reg.a); }
/* 0x98 */ void sbc_a_b(void) { sub_carry(reg.b); }
/* 0x99 */ void sbc_a_c(void) { sub_carry(reg.c); }
/* 0x9a */ void sbc_a_d(void) { sub_carry(reg.d); }
/* 0x9b */ void sbc_a_e(void) { sub_carry(reg.e); }
/* 0x9c */ void sbc_a_h(void) { sub_carry(reg.h); }
/* 0x9d */ void sbc_a_l(void) { sub_carry(reg.l); }
/* 0x9e */ void sbc_a_hl(void) { sub_carry(memory_read_byte(reg.hl)); }
/* 0x9f */ void sbc_a_a(void) { sub_carry(reg.a); }
/* 0xa0 */ void and_b(void) { and(reg.b); }
/* 0xa1 */ void and_c(void) { and(reg.c); }
/* 0xa2 */ void and_d(void) { and(reg.d); }
/* 0xa3 */ void and_e(void) { and(reg.e); }
/* 0xa4 */ void and_h(void) { and(reg.h); }
/* 0xa5 */ void and_l(void) { and(reg.l); }
/* 0xa6 */ void and_hl(void) { and(memory_read_byte(reg.hl)); }
/* 0xa7 */ void and_a(void) { and(reg.a); }
/* 0xa8 */ void xor_b(void) { xor(reg.b); }
/* 0xa9 */ void xor_c(void) { xor(reg.c); }
/* 0xaa */ void xor_d(void) { xor(reg.d); }
/* 0xab */ void xor_e(void) { xor(reg.e); }
/* 0xac */ void xor_h(void) { xor(reg.h); }
/* 0xad */ void xor_l(void) { xor(reg.l); }
/* 0xae */ void xor_hl(void) { xor(memory_read_byte(reg.hl)); }
/* 0xaf */ void xor_a(void) { xor(reg.a); }
/* 0xb0 */ void or_b(void) { or(reg.b); }
/* 0xb1 */ void or_c(void) { or(reg.c); }
/* 0xb2 */ void or_d(void) { or(reg.d); }
/* 0xb3 */ void or_e(void) { or(reg.e); }
/* 0xb4 */ void or_h(void) { or(reg.h); }
/* 0xb5 */ void or_l(void) { or(reg.l); }
/* 0xb6 */ void or_hl(void) { or(memory_read_byte(reg.hl)); }
/* 0xb7 */ void or_a(void) { or(reg.a); }
/* 0xb8 */ void cp_b(void) { cp(reg.b); }
/* 0xb9 */ void cp_c(void) { cp(reg.c); }
/* 0xba */ void cp_d(void) { cp(reg.d); }                     
/* 0xbb */ void cp_e(void) { cp(reg.e); }
/* 0xbc */ void cp_h(void) { cp(reg.h); }
/* 0xbd */ void cp_l(void) { cp(reg.l); }
/* 0xbe */ void cp_hl(void) { cp(memory_read_byte(reg.hl)); }
/* 0xbf */ void cp_a(void) { cp(reg.a); }
/* 0xc0 */ void ret_nz(void) { if (!FLAG_ZERO) { reg.pc = memory_pop_word_from_stack(); total_clock += 12; last_clock += 12; } }
/* 0xc1 */ void pop_bc(void) { reg.bc = memory_pop_word_from_stack(); }
/* 0xc2 */ void jp_nz_nn(unsigned short op) { if (!FLAG_ZERO) { reg.pc = op; } }
/* 0xc3 */ void jp_nn(unsigned short op) { reg.pc = op; }
/* 0xc4 */ void call_nz_nn(unsigned short op) { if (!FLAG_ZERO) { memory_push_word_on_stack(reg.pc); reg.pc = op; total_clock += 12; last_clock += 12; } }
/* 0xc5 */ void push_bc(void) { memory_push_word_on_stack(reg.bc); }
/* 0xc6 */ void add_a_n(unsigned char op) { reg.a = add(reg.a, op); }
/* 0xc7 */ void rst_00(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x00; }
/* 0xc8 */ void ret_z(void) { if (FLAG_ZERO) { reg.pc = memory_pop_word_from_stack(); total_clock += 12; last_clock += 12; } }
/* 0xc9 */ void ret(void) { reg.pc = memory_pop_word_from_stack(); }
/* 0xca */ void jp_z_nn(unsigned short op) { if (FLAG_ZERO) { reg.pc = op; } }
/* 0xcb */ void ext_ops(unsigned char op) { ((void (*)(void))(cb_opcodes[op].fn))(); }
/* 0xcc */ void call_z_nn(unsigned short op) { if (FLAG_ZERO) { memory_push_word_on_stack(reg.pc); reg.pc = op; total_clock += 12; last_clock += 12; } }
/* 0xcd */ void call_nn(unsigned short op) { memory_push_word_on_stack(reg.pc); reg.pc = op; }
/* 0xce */ void adc_a_n(unsigned char op) { add_carry(op); }
/* 0xcf */ void rst_08(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x08; }
/* 0xd0 */ void ret_nc(void) { if (!FLAG_CARRY) { reg.pc = memory_pop_word_from_stack(); total_clock += 12; last_clock += 12; } }
/* 0xd1 */ void pop_de(void) { reg.de = memory_pop_word_from_stack(); }
/* 0xd2 */ void jp_nc_nn(unsigned short op) { if (!FLAG_CARRY) { reg.pc = op; } }
/* 0xd3 */ void bad_instruction_d3(void) { printf("/!\\ BAD INSTRUCTION D3 /!\\\n"); }
/* 0xd4 */ void call_nc_nn(unsigned short op) { if (!FLAG_CARRY) { memory_push_word_on_stack(reg.pc); reg.pc = op; total_clock += 12; last_clock += 12; } }
/* 0xd5 */ void push_de(void) { memory_push_word_on_stack(reg.de); }
/* 0xd6 */ void sub_a_n(unsigned char op) { reg.a = sub(reg.a, op); }
/* 0xd7 */ void rst_10(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x10; }
/* 0xd8 */ void ret_c(void) { if (FLAG_CARRY) { reg.pc = memory_pop_word_from_stack(); total_clock += 12; last_clock += 12; } }
/* 0xd9 */ void reti(void) { reg.pc = memory_pop_word_from_stack(); should_enable_interrupt = true; } // TODO Verif
/* 0xda */ void jp_c_nn(unsigned short op) { if (FLAG_CARRY) { reg.pc = op; } }
/* 0xdb */ void bad_instruction_db(void) { printf("/!\\ BAD INSTRUCTION DB /!\\\n"); }
/* 0xdc */ void call_c_nn(unsigned short op) { if (FLAG_CARRY) { memory_push_word_on_stack(reg.pc); reg.pc = op; total_clock += 12; last_clock += 12; } }
/* 0xdd */ void bad_instruction_dd(void) { printf("/!\\ BAD INSTRUCTION DD /!\\\n"); }
/* 0xde */ void sbc_a_n(unsigned char op) { sub_carry(op); }
/* 0xdf */ void rst_18(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x18; }
/* 0xe0 */ void ldh_n_a(unsigned char op) { memory_write_byte(0xff00 | op, reg.a); }
/* 0xe1 */ void pop_hl(void) { reg.hl = memory_pop_word_from_stack(); }
/* 0xe2 */ void ldh_c_a(void) { memory_write_byte(0xff00 | reg.c, reg.a); }
/* 0xe3 */ void bad_instruction_e3(void) { printf("/!\\ BAD INSTRUCTION E3 /!\\\n"); }
/* 0xe4 */ void bad_instruction_e4(void) { printf("/!\\ BAD INSTRUCTION E4 /!\\\n"); }
/* 0xe5 */ void push_hl(void) { memory_push_word_on_stack(reg.hl); }
/* 0xe6 */ void and_n(unsigned char op) { and(op); }
/* 0xe7 */ void rst_20(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x20; }
/* 0xe8 */ void add_sp_n(unsigned char op) { reg.sp += (signed char)op; }
/* 0xe9 */ void jp_hl(void) { reg.pc = reg.hl; }
/* 0xea */ void ld_nn_a(unsigned short op) { memory_write_byte(op, reg.a); }
/* 0xeb */ void bad_instruction_eb(void) { printf("/!\\ BAD INSTRUCTION EB /!\\\n"); }
/* 0xec */ void bad_instruction_ec(void) { printf("/!\\ BAD INSTRUCTION EC /!\\\n"); }
/* 0xed */ void bad_instruction_ed(void) { printf("/!\\ BAD INSTRUCTION ED /!\\\n"); }
/* 0xee */ void xor_n(unsigned char op) { xor(op); }
/* 0xef */ void rst_28(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x28; }
/* 0xf0 */ void ldh_a_n(unsigned char op) { reg.a = memory_read_byte(0xff00 | op); }
/* 0xf1 */ void pop_af(void) { reg.af = memory_pop_word_from_stack(); }
/* 0xf2 */ void ldh_a_c(void) { reg.a = memory_read_byte(0xff00 | reg.c); }
/* 0xf3 */ void interrupt_disable(void) { should_disable_interrupt = true; }
/* 0xf4 */ void bad_instruction_f4(void) { printf("/!\\ BAD INSTRUCTION F4 /!\\\n"); }
/* 0xf5 */ void push_af(void) { memory_push_word_on_stack(reg.af); }
/* 0xf6 */ void or_n(unsigned char op) { or(op); }
/* 0xf7 */ void rst_30(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x30; }
/* 0xf8 */ void ldhl_sp_n(unsigned char op) { int ret; ret = reg.sp + (signed char)op; SET_CARRY_IF(ret & 0xffff0000); SET_HALF_IF((reg.sp & 0x0f) + (op & 0x0f) > 0x0f); UNSET_FLAG_NEG; UNSET_FLAG_ZERO; reg.hl = (unsigned short)(ret & 0xffff); }
/* 0xf9 */ void ld_sp_hl(void) { reg.sp = reg.hl; }
/* 0xfa */ void ld_a_nn(unsigned short op) { reg.a = memory_read_byte(op); }
/* 0xfb */ void interrupt_enable(void) { should_enable_interrupt = true; }
/* 0xfc */ void bad_instruction_fc(void) { printf("/!\\ BAD INSTRUCTION FC /!\\\n"); }
/* 0xfd */ void bad_instruction_fd(void) { printf("/!\\ BAD INSTRUCTION FD /!\\\n"); }
/* 0xfe */ void cp_n(unsigned char op) { cp(op); }
/* 0xff */ void rst_38(void) { memory_push_word_on_stack(reg.pc); reg.pc = 0x38; }

const t_opcode	opcodes[] = {
 	{ "NOP", 0, nop, 4 },           // 0x00
 	{ "LD BC,nn", 2, ld_bc_nn, 12 },      // 0x01
 	{ "LD (BC),A", 0, ld_bc_a, 8 },     // 0x02
 	{ "INC BC", 0, inc_bc, 8 },        // 0x03
 	{ "INC B", 0, inc_b, 4 },         // 0x04
 	{ "DEC B", 0, dec_b, 4 },         // 0x05
 	{ "LD B,n", 1, ld_b_n, 8 },        // 0x06
	{ "RLC A", 0, rlc_a, 4 },         // 0x07
	{ "LD (nn),SP", 2, ld_nn_sp, 20 },    // 0x08
	{ "ADD HL,BC", 0, add_hl_bc, 8 },     // 0x09
	{ "LD A,(BC)", 0, ld_a_bc, 8 },     // 0x0a
	{ "DEC BC", 0, dec_bc, 8 },        // 0x0b
	{ "INC C", 0, inc_c, 4 },         // 0x0c
	{ "DEC C", 0, dec_c, 4 },         // 0x0d
	{ "LD C,n", 1, ld_c_n, 8 },        // 0x0e
	{ "RRC A", 0, rrc_a, 4 },         // 0x0f
	{ "STOP", 0, NULL, 0 },          // 0x10
	{ "LD DE,nn", 2, ld_de_nn, 12 },      // 0x11
	{ "LD (DE),A", 0, ld_de_a, 8 },     // 0x12
	{ "INC DE", 0, inc_de, 8 },        // 0x13
	{ "INC D", 0, inc_d, 4 },         // 0x14
	{ "DEC D", 0, dec_d, 4 },         // 0x15
	{ "LD D,n", 1, ld_d_n, 8 },        // 0x16
	{ "RL A", 0, rl_a, 4 },          // 0x17
	{ "JR n", 1, jr_n, 8 },          // 0x18
	{ "ADD HL,DE", 0, add_hl_de, 8 },     // 0x19
	{ "LD A,(DE)", 0, ld_a_de, 8 },     // 0x1a
	{ "DEC DE", 0, dec_de, 8 },        // 0x1b
	{ "INC E", 0, inc_e, 4 },         // 0x1c
	{ "DEC E", 0, dec_e, 4 },         // 0x1d
	{ "LD E,n", 1, ld_e_n, 8 },        // 0x1e
	{ "RR A", 0, rr_a, 4 },          // 0x1f
	{ "JR NZ,n", 1, jr_nz_n, 8 },       // 0x20
	{ "LD HL,nn", 2, ld_hl_nn, 12 },      // 0x21
	{ "LDI (HL),A", 0, ldi_hl_a, 8 },    // 0x22
	{ "INC HL", 0, inc_hl, 8 },        // 0x23
	{ "INC H", 0, inc_h, 4 },         // 0x24
	{ "DEC H", 0, dec_h, 4 },         // 0x25
	{ "LD H,n", 1, ld_h_n, 8 },        // 0x26
	{ "DAA", 0, daa_, 4 },           // 0x27
	{ "JR Z,n", 1, jr_z_n, 8 },        // 0x28
	{ "ADD HL,HL", 0, add_hl_hl, 8 },     // 0x29
	{ "LDI A,(HL)", 0, ldi_a_hl, 8 },    // 0x2a
	{ "DEC HL", 0, dec_hl, 8 },        // 0x2b
	{ "INC L", 0, inc_l, 4 },         // 0x2c
	{ "DEC L", 0, dec_l, 4 },         // 0x2d
	{ "LD L,n", 1, ld_l_n, 8 },        // 0x2e
	{ "CPL", 0, cpl, 4 },           // 0x2f
	{ "JR NC,n", 1, jr_nc_n, 8 },       // 0x30
	{ "LD SP,nn", 2, ld_sp_nn, 12 },      // 0x31
	{ "LDD (HL),A", 0, ldd_hl_a, 8 },    // 0x32
	{ "INC SP", 0, inc_sp, 8 },        // 0x33
	{ "INC (HL)", 0, inc_hlp, 12 },      // 0x34
	{ "DEC (HL)", 0, dec_hlp, 12 },      // 0x35
	{ "LD (HL),n", 1, ld_hl_n, 12 },     // 0x36
	{ "SCF", 0, scf, 4 },           // 0x37
	{ "JR C,n", 1, jr_c_n, 8 },        // 0x38
	{ "ADD HL,SP", 0, add_hl_sp, 8 },     // 0x39
	{ "LDD A,(HL)", 0, ldd_a_hl, 0 },    // 0x3a
	{ "DEC SP", 0, dec_sp, 8 },        // 0x3b
	{ "INC A", 0, inc_a, 4 },         // 0x3c
	{ "DEC A", 0, dec_a, 4 },         // 0x3d
	{ "LD A,n", 1, ld_a_n, 8 },        // 0x3e
	{ "CCF", 0, ccf, 4 },           // 0x3f
	{ "LD B,B", 0, ld_b_b, 4 },        // 0x40
	{ "LD B,C", 0, ld_b_c, 4 },        // 0x41
	{ "LD B,D", 0, ld_b_d, 4 },        // 0x42
	{ "LD B,E", 0, ld_b_e, 4 },        // 0x43
	{ "LD B,H", 0, ld_b_h, 4 },        // 0x44
	{ "LD B,L", 0, ld_b_l, 4 },        // 0x45
	{ "LD B,(HL)", 0, ld_b_hl, 8 },     // 0x46
	{ "LD B,A", 0, ld_b_a, 4 },        // 0x47
	{ "LD C,B", 0, ld_c_b, 4 },        // 0x48
	{ "LD C,C", 0, ld_c_c, 4 },        // 0x49
	{ "LD C,D", 0, ld_c_d, 4 },        // 0x4a
	{ "LD C,E", 0, ld_c_e, 4 },        // 0x4b
	{ "LD C,H", 0, ld_c_h, 4 },        // 0x4c
	{ "LD C,L", 0, ld_c_l, 4 },        // 0x4d
	{ "LD C,(HL)", 0, ld_c_hl, 8 },     // 0x4e
	{ "LD C,A", 0, ld_c_a, 4 },        // 0x4f
	{ "LD D,B", 0, ld_d_b, 4 },        // 0x50
	{ "LD D,C", 0, ld_d_c, 4 },        // 0x51
	{ "LD D,D", 0, ld_d_d, 4 },        // 0x52
	{ "LD D,E", 0, ld_d_e, 4 },        // 0x53
	{ "LD D,H", 0, ld_d_h, 4 },        // 0x54
	{ "LD D,L", 0, ld_d_l, 4 },        // 0x55
	{ "LD D,(HL)", 0, ld_d_hl, 8 },     // 0x56
	{ "LD D,A", 0, ld_d_a, 4 },        // 0x57
	{ "LD E,B", 0, ld_e_b, 4 },        // 0x58
	{ "LD E,C", 0, ld_e_c, 4 },        // 0x59
	{ "LD E,D", 0, ld_e_d, 4 },        // 0x5a
	{ "LD E,E", 0, ld_e_e, 4 },        // 0x5b
	{ "LD E,H", 0, ld_e_h, 4 },        // 0x5c
	{ "LD E,L", 0, ld_e_l, 4 },        // 0x5d
	{ "LD E,(HL)", 0, ld_e_hl, 8 },     // 0x5e
	{ "LD E,A", 0, ld_e_a, 4 },        // 0x5f
	{ "LD H,B", 0, ld_h_b, 4 },        // 0x60
	{ "LD H,C", 0, ld_h_c, 4 },        // 0x61
	{ "LD H,D", 0, ld_h_d, 4 },        // 0x62
	{ "LD H,E", 0, ld_h_e, 4 },        // 0x63
	{ "LD H,H", 0, ld_h_h, 4 },        // 0x64
	{ "LD H,L", 0, ld_h_l, 4 },        // 0x65
	{ "LD H,(HL)", 0, ld_h_hl, 8 },     // 0x66
	{ "LD H,A", 0, ld_h_a, 4 },        // 0x67
	{ "LD L,B", 0, ld_l_b, 4 },        // 0x68
	{ "LD L,C", 0, ld_l_c, 4 },        // 0x69
	{ "LD L,D", 0, ld_l_d, 4 },        // 0x6a
	{ "LD L,E", 0, ld_l_e, 4 },        // 0x6b
	{ "LD L,H", 0, ld_l_h, 4 },        // 0x6c
	{ "LD L,L", 0, ld_l_l, 4 },        // 0x6d
	{ "LD L,(HL)", 0, ld_l_hl, 8 },     // 0x6e
	{ "LD L,A", 0, ld_l_a, 4 },        // 0x6f
	{ "LD (HL),B", 0, ld_hl_b, 8 },     // 0x70
	{ "LD (HL),C", 0, ld_hl_c, 8 },     // 0x71
	{ "LD (HL),D", 0, ld_hl_d, 8 },     // 0x72
	{ "LD (HL),E", 0, ld_hl_e, 8 },     // 0x73
	{ "LD (HL),H", 0, ld_hl_h, 8 },     // 0x74
	{ "LD (HL),L", 0, ld_hl_l, 8 },     // 0x75
	{ "HALT", 0, NULL, 0 },          // 0x76
	{ "LD (HL),A", 0, ld_hl_a, 8 },     // 0x77
	{ "LD A,B", 0, ld_a_b, 4 },        // 0x78
	{ "LD A,C", 0, ld_a_c, 4 },        // 0x79
	{ "LD A,D", 0, ld_a_d, 4 },        // 0x7a
	{ "LD A,E", 0, ld_a_e, 4 },        // 0x7b
	{ "LD A,H", 0, ld_a_h, 4 },        // 0x7c
	{ "LD A,L", 0, ld_a_l, 4 },        // 0x7d
	{ "LD A,(HL)", 0, ld_a_hl, 8 },     // 0x7e
	{ "LD A,A", 0, ld_a_a, 4 },        // 0x7f
	{ "ADD A,B", 0, add_a_b, 4 },       // 0x80
	{ "ADD A,C", 0, add_a_c, 4 },       // 0x81
	{ "ADD A,D", 0, add_a_d, 4 },       // 0x82
	{ "ADD A,E", 0, add_a_e, 4 },       // 0x83
	{ "ADD A,H", 0, add_a_h, 4 },       // 0x84
	{ "ADD A,L", 0, add_a_l, 4 },       // 0x85
	{ "ADD A,(HL)", 0, add_a_hl, 8 },    // 0x86
	{ "ADD A,A", 0, add_a_a, 4 },       // 0x87
	{ "ADC A,B", 0, adc_a_b, 4 },       // 0x88
	{ "ADC A,C", 0, adc_a_c, 4 },       // 0x89
	{ "ADC A,D", 0, adc_a_d, 4 },       // 0x8a
	{ "ADC A,E", 0, adc_a_e, 4 },       // 0x8b
	{ "ADC A,H", 0, adc_a_h, 4 },       // 0x8c
	{ "ADC A,L", 0, adc_a_l, 4 },       // 0x8d
	{ "ADC A,(HL)", 0, adc_a_hl, 8 },    // 0x8e
	{ "ADC A,A", 0, adc_a_a, 4 },       // 0x8f
	{ "SUB A,B", 0, sub_a_b, 4 },       // 0x90
	{ "SUB A,C", 0, sub_a_c, 4 },       // 0x91
	{ "SUB A,D", 0, sub_a_d, 4 },       // 0x92
	{ "SUB A,E", 0, sub_a_e, 4 },       // 0x93
	{ "SUB A,H", 0, sub_a_h, 4 },       // 0x94
	{ "SUB A,L", 0, sub_a_l, 4 },       // 0x95
	{ "SUB A,(HL)", 0, sub_a_hl, 8 },    // 0x96
	{ "SUB A,A", 0, sub_a_a, 4 },       // 0x97
	{ "SBC A,B", 0, sbc_a_b, 4 },       // 0x98
	{ "SBC A,C", 0, sbc_a_c, 4 },       // 0x99
	{ "SBC A,D", 0, sbc_a_d, 4 },       // 0x9a
	{ "SBC A,E", 0, sbc_a_e, 4 },       // 0x9b
	{ "SBC A,H", 0, sbc_a_h, 4 },       // 0x9c
	{ "SBC A,L", 0, sbc_a_l, 4 },       // 0x9d
	{ "SBC A,(HL)", 0, sbc_a_hl, 4 },    // 0x9e
	{ "SBC A,A", 0, sbc_a_a, 4 },       // 0x9f
	{ "AND B", 0, and_b, 4 },         // 0xa0
	{ "AND C", 0, and_c, 4 },         // 0xa1
	{ "AND D", 0, and_d, 4 },         // 0xa2
	{ "AND E", 0, and_e, 4 },         // 0xa3
	{ "AND H", 0, and_h, 4 },         // 0xa4
	{ "AND L", 0, and_l, 4 },         // 0xa5
	{ "AND (HL)", 0, and_hl, 8 },      // 0xa6
	{ "AND A", 0, and_a, 4 },         // 0xa7
	{ "XOR B", 0, xor_b, 4 },         // 0xa8
	{ "XOR C", 0, xor_c, 4 },         // 0xa9
	{ "XOR D", 0, xor_d, 4 },         // 0xaa
	{ "XOR E", 0, xor_e, 4 },         // 0xab
	{ "XOR H", 0, xor_h, 4 },         // 0xac
	{ "XOR L", 0, xor_l, 4 },         // 0xad
	{ "XOR (HL)", 0, xor_hl, 8 },      // 0xae
	{ "XOR A", 0, xor_a, 4 },         // 0xaf
	{ "OR B", 0, or_b, 4 },          // 0xb0
	{ "OR C", 0, or_c, 4 },          // 0xb1
	{ "OR D", 0, or_d, 4 },          // 0xb2
	{ "OR E", 0, or_e, 4 },          // 0xb3
	{ "OR H", 0, or_h, 4 },          // 0xb4
	{ "OR L", 0, or_l, 4 },          // 0xb5
	{ "OR (HL)", 0, or_hl, 8 },       // 0xb6
	{ "OR A", 0, or_a, 4 },          // 0xb7
	{ "CP B", 0, cp_b, 4 },          // 0xb8
	{ "CP C", 0, cp_c, 4 },          // 0xb9
	{ "CP D", 0, cp_d, 4 },          // 0xba
	{ "CP E", 0, cp_e, 4 },          // 0xbb
	{ "CP H", 0, cp_h, 4 },          // 0xbc
	{ "CP L", 0, cp_l, 4 },          // 0xbd
	{ "CP (HL)", 0, cp_hl, 8 },       // 0xbe
	{ "CP A", 0, cp_a, 4 },          // 0xbf
	{ "RET NZ", 0, ret_nz, 8 },        // 0xc0
	{ "POP BC", 0, pop_bc, 12 },        // 0xc1
	{ "JP NZ,nn", 2, jp_nz_nn, 12 },      // 0xc2
	{ "JP nn", 2, jp_nn, 16 },         // 0xc3
	{ "CALL NZ,nn", 2, call_nz_nn, 12 },    // 0xc4
	{ "PUSH BC", 0, push_bc, 16 },       // 0xc5
	{ "ADD A,n", 1, add_a_n, 8 },       // 0xc6
	{ "RST 0", 0, rst_00, 32 },         // 0xc7
	{ "RET Z", 0, ret_z, 8 },         // 0xc8
	{ "RET", 0, ret, 16 },           // 0xc9
	{ "JP Z,nn", 2, jp_z_nn, 12 },       // 0xca
	{ "Ext ops", 1, ext_ops, 0 },       // 0xcb
	{ "CALL Z,nn", 2, call_z_nn, 12 },     // 0xcc
	{ "CALL nn", 2, call_nn, 24 },       // 0xcd
	{ "ADC A,n", 1, adc_a_n, 8 },       // 0xce
	{ "RST 8", 0, rst_08, 32 },         // 0xcf
	{ "RET NC", 0, ret_nc, 8 },        // 0xd0
	{ "POP DE", 0, pop_de, 12 },        // 0xd1
	{ "JP NC,nn", 2, jp_nc_nn, 12 },      // 0xd2
	{ "XX", 0, bad_instruction_d3, 0 },            // 0xd3
	{ "CALL NC,nn", 2, call_nc_nn, 12 },    // 0xd4
	{ "PUSH DE", 0, push_de, 16 },       // 0xd5
	{ "SUB A,n", 1, sub_a_n, 8 },       // 0xd6
	{ "RST 10", 0, rst_10, 32 },        // 0xd7
	{ "RET C", 0, ret_c, 8 },         // 0xd8
	{ "RETI", 0, reti, 16 },          // 0xd9
	{ "JP C,nn", 2, jp_c_nn, 12 },       // 0xda
	{ "XX", 0, bad_instruction_db, 0 },            // 0xdb
	{ "CALL C,nn", 2, call_c_nn, 12 },     // 0xdc
	{ "XX", 0, bad_instruction_dd, 0 },            // 0xdd
	{ "SBC A,n", 1, sbc_a_n, 8 },       // 0xde
	{ "RST 18", 0, rst_18, 32 },        // 0xdf
	{ "LDH (n),A", 1, ldh_n_a, 12 },     // 0xe0
	{ "POP HL", 0, pop_hl, 12 },        // 0xe1
	{ "LDH (C),A", 0, ldh_c_a, 8 },     // 0xe2
	{ "XX", 0, bad_instruction_e3, 0 },            // 0xe3
	{ "XX", 0, bad_instruction_e4, 0 },            // 0xe4
	{ "PUSH HL", 0, push_hl, 16 },       // 0xe5
	{ "AND n", 1, and_n, 8 },         // 0xe6
	{ "RST 20", 0, rst_20, 32 },        // 0xe7
	{ "ADD SP,n", 1, add_sp_n, 16 },      // 0xe8
	{ "JP (HL)", 0, jp_hl, 4 },       // 0xe9
	{ "LD (nn),A", 2, ld_nn_a, 16 },     // 0xea
	{ "XX", 0, bad_instruction_eb, 0 },            // 0xeb
	{ "XX", 0, bad_instruction_ec, 0 },            // 0xec
	{ "XX", 0, bad_instruction_ed, 0 },            // 0xed
	{ "XOR n", 1, xor_n, 8 },         // 0xee
	{ "RST 28", 0, rst_28, 32 },        // 0xef
	{ "LDH A,(n)", 1, ldh_a_n, 12 },     // 0xf0
	{ "POP AF", 0, pop_af, 12 },        // 0xf1
	{ "LDH A,(C)", 0, ldh_a_c, 8 },            // 0xf2
	{ "DI", 0, interrupt_disable, 4 },            // 0xf3
	{ "XX", 0, bad_instruction_f4, 0 },            // 0xf4
	{ "PUSH AF", 0, push_af, 16 },       // 0xf5
	{ "OR n", 1, or_n, 8 },          // 0xf6
	{ "RST 30", 0, rst_30, 32 },        // 0xf7
	{ "LDHL SP,n", 1, ldhl_sp_n, 12 },     // 0xf8
	{ "LD SP,HL", 0, ld_sp_hl, 8 },      // 0xf9
	{ "LD A,(nn)", 2, ld_a_nn, 16 },     // 0xfa
	{ "EI", 0, interrupt_enable, 4 },            // 0xfb
	{ "XX", 0, bad_instruction_fc, 0 },            // 0xfc
	{ "XX", 0, bad_instruction_fd, 0 },            // 0xfd
	{ "CP n", 1, cp_n, 8 },          // 0xfe
	{ "RST 38", 0, rst_38, 32 }         // 0xff
};

void			next_opcode(void)
{
	const t_opcode	*op;

	op = opcodes + mem.memory[reg.pc];
	total_clock += op->clock;
	last_clock = op->clock;
	if (op->fn == NULL) {
		printf("-> %s (0x%02hhx) TODO\n", op->name, mem.memory[reg.pc]);
		exit(0);
	} else if (op->argument == 0) {
//		printf("-> %s (0x%02hhx) DONE\n", op->name, mem.memory[reg.pc]);
		reg.pc += 1;
		((void (*)(void))(op->fn))();
	} else if (op->argument == 1) {
		reg.pc += 2;
//		printf("-> %s (0x%02hhx) (op = 0x%02hhx) DONE\n", op->name, mem.memory[reg.pc - 2], mem.memory[reg.pc - 1]);
		((void (*)(unsigned char))(op->fn))(mem.memory[reg.pc - 1]);
	} else if (op->argument == 2) {
//		printf("-> %s (0x%02hhx) (op = 0x%04hx) DONE\n", op->name, mem.memory[reg.pc], *((unsigned short *)(mem.memory + reg.pc + 1)));
		reg.pc += 3;
		((void (*)(unsigned short))(op->fn))(*((unsigned short *)(mem.memory + reg.pc - 2)));
	}
	if (should_disable_interrupt && op != opcodes + 0xf3) {
		master_interrupt = false;
		should_disable_interrupt = false;
	}
	if (should_enable_interrupt && op != opcodes + 0xfb) {
		master_interrupt = true;
		should_enable_interrupt = false;
	}
}

const t_opcode	*get_opcode(unsigned short index)
{
	return (opcodes + mem.memory[index]);
}
