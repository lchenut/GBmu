#include "debugger.h"
#include "memory.h"
#include "opcodes.h"

static t_command	*memory_to_commands_new(void)
{
	t_command		*commands;
	const t_opcode	*op;
	char			com[35];

	commands = malloc(sizeof(t_command) * 0x10000);
	for (size_t i = 0; i < 0x10000; i += 1) {
		op = opcodes + mem.memory[i];
		bzero(com, 35);
		if (op->argument == 0) {
			commands[i].incr = 1;
			sprintf(com, "%02hhx        %-10s", mem.memory[i], op->name);
		} else if (op->argument == 1) {
			commands[i].incr = 2;
			if (mem.memory[i] == 0xcb) {
				op = cb_opcodes + mem.memory[i + 1];
				sprintf(com, "%02hhx %02hhx     %-10s",
						mem.memory[i], mem.memory[i + 1], op->name);
			} else if (mem.memory[i] == 0xe0 || mem.memory[i] == 0xf0) {
				sprintf(com, "%02hhx %02hhx     %-10s  0xff00+0x%02hhx",
						mem.memory[i], mem.memory[i + 1], op->name, mem.memory[i + 1]);
			} else {
				sprintf(com, "%02hhx %02hhx     %-10s  0x%02hhx",
						mem.memory[i], mem.memory[i + 1], op->name, mem.memory[i + 1]);
			}
		} else {
			commands[i].incr = 3;
			sprintf(com, "%02hhx %02hhx %02hhx  %-10s  0x%04hx",
					mem.memory[i], mem.memory[i + 1], mem.memory[i + 2], op->name,
					*((unsigned short *)(mem.memory + i + 1)));
		}
		commands[i].command = strdup(com);
		printf("0x%04zx: %s\n", i, commands[i].command);
	}
	return (NULL);
}

t_vector		*memory_to_commands(void)
{
	static t_command	*commands = NULL;

	if (commands == NULL) {
		commands = memory_to_commands_new();
	}
	return (NULL);
}
