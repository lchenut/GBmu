#ifndef REGISTERS_H
# define REGISTERS_H

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
