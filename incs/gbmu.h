#ifndef GBMU_H
# define GBMU_H

typedef struct		s_gbmu {
	t_memory		mem;
	t_registers		reg;
	t_vector		*rom;
}					t_gbmu;

#endif // GBMU_H
