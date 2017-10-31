#include <stdio.h>
#include <strings.h>
#include "memory.h"
#include "registers.h"
#include "opcodes.h"

t_registers	reg;
t_memory	mem;
t_vector	*rom;

int			main(int ac, char **av)
{
	int		fd;

	if (ac == 1) {
		return (1);
	}
	registers_reset();
	memory_reset();
	fd = open(av[1], O_RDONLY);
	if (fd <= 0) {
		dprintf(2, "open error\n");
		return (1);
	}
	rom = vector_new();
	while (1) {
		char	*str;
		int		ret;

		str = malloc(sizeof(char) * 0x4000);
		bzero(str, 0x4000);
		ret = read(fd, str, 0x4000);
		if (ret < 0) {
			dprintf(2, "read error\n");
			return (1);
		}
		if (ret == 0) {
			break ;
		}
		vector_push_back(rom, str);
	}
	if (vector_len(rom) < 2) {
		dprintf(2, "rom error\n");
		return (1);
	}
	memmove(mem.cart, vector_get_first(rom), 0x4000);
	memmove(mem.cart + 4000, vector_get(rom, 1), 0x4000);
	while (1) {
		next_opcode();
	}
	return (0);
}
