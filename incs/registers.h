#ifndef REGISTERS_H
# define REGISTERS_H

# define FLAG_ZERO  ((reg.f >> 7) & 1)
# define FLAG_NEG   ((reg.f >> 6) & 1)
# define FLAG_HALF  ((reg.f >> 5) & 1)
# define FLAG_CARRY ((reg.f >> 4) & 1)
# define SET_FLAG_ZERO  (reg.f |= (1 << 7))
# define SET_FLAG_NEG   (reg.f |= (1 << 6))
# define SET_FLAG_HALF  (reg.f |= (1 << 5))
# define SET_FLAG_CARRY (reg.f |= (1 << 4))
# define UNSET_FLAG_ZERO  (reg.f &= ~(1 << 7))
# define UNSET_FLAG_NEG   (reg.f &= ~(1 << 6))
# define UNSET_FLAG_HALF  (reg.f &= ~(1 << 5))
# define UNSET_FLAG_CARRY (reg.f &= ~(1 << 4))
# define SET_ZERO_IF(x) ((x) ? SET_FLAG_ZERO : UNSET_FLAG_ZERO)
# define SET_NEG_IF(x) ((x) ? SET_FLAG_NEG : UNSET_FLAG_NEG)
# define SET_HALF_IF(x) ((x) ? SET_FLAG_HALF : UNSET_FLAG_HALF)
# define SET_CARRY_IF(x) ((x) ? SET_FLAG_CARRY : UNSET_FLAG_CARRY)


typedef struct				s_registers {
	union {
		struct {
			unsigned char	f;
			unsigned char	a;
		};
		unsigned short	af;
	};
	union {
		struct {
			unsigned char	c;
			unsigned char	b;
		};
		unsigned short		bc;
	};
	union {
		struct {
			unsigned char	e;
			unsigned char	d;
		};
		unsigned short		de;
	};
	union {
		struct {
			unsigned char	l;
			unsigned char	h;
		};
		unsigned short		hl;
	};
	unsigned short			sp;
	unsigned short			pc;
}							t_registers;

extern t_registers			reg;

void						registers_reset(void);

#endif // REGISTERS_H
