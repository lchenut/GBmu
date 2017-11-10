#ifndef MEMORY_H
# define MEMORY_H

# include "basics.h"

# define Div_Register		(mem.memory[0xff04])
# define Timer_Counter		(mem.memory[0xff05])
# define Timer_Modulo		(mem.memory[0xff06])
# define Timer_Control		(mem.memory[0xff07])
# define Interrupt_Flag		(mem.memory[0xff0f])
# define LCD_Control		(mem.memory[0xff40])
# define LCD_Status			(mem.memory[0xff41])
# define Scroll_Y			(mem.memory[0xff42])
# define Scroll_X			(mem.memory[0xff43])
# define LCD_Y_Coord		(mem.memory[0xff44])
# define LCD_Y_Compare		(mem.memory[0xff45])
# define DMA_Address		(mem.memory[0xff46])
# define BG_Palette			(mem.memory[0xff47])
# define Obj1_Palette		(mem.memory[0xff48])
# define Obj2_Palette		(mem.memory[0xff49])
# define Window_Y_Pos		(mem.memory[0xff4a])
# define Window_X_Pos		(mem.memory[0xff4b])
# define Interrupt_Enable	(mem.memory[0xffff])

typedef union			u_memory {
	struct {
		unsigned char		cart[0x8000]; // 0x0000 - 0x7FFF: ROM
		unsigned char		vram[0x2000]; // 0x8000 - 0x9FFF: Video RAM
		unsigned char		sram[0x2000]; // 0xA000 - 0xBFFF: Switchable RAM
		unsigned char		iram[0x2000]; // 0xC000 - 0xDFFF: Internal RAM
		unsigned char		echo_ram[0x1E00]; // 0xE000 - 0xFDFF: Echo of Internal RAM
		unsigned char		oam[0xA0];    // 0xFE00 - 0xFE9F: Sprite Attrib Memory
		unsigned char		io[0xE0];     // 0xFEA0 - 0xFF7F: I/O port (0xFF00 - 0xFF4B)
		unsigned char		hram[0x7F];   // 0xFF80 - 0xFFFE: Internal RAM(?)
		unsigned char		interrupt_register; // 0xFFFF: Interrupt enable register
	};
	unsigned char			memory[0x10000];
}							t_memory;

extern t_memory				mem;
extern t_vector				*rom;

void						memory_reset(void);

void						memory_write_byte(unsigned short address, unsigned char op);
void						memory_write_word(unsigned short address, unsigned short op);

unsigned char				memory_read_byte(unsigned short address);
unsigned short				memory_read_word(unsigned short address);

void						memory_push_byte_on_stack(unsigned char op);
void						memory_push_word_on_stack(unsigned short op);

unsigned char				memory_pop_byte_from_stack(void);
unsigned short				memory_pop_word_from_stack(void);

#endif // MEMORY_H
