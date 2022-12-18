#include "libfsm.h"

void	fsm_init(t_state_machine *machine, t_state *initial_state, t_state *error_state)
{
	if (!machine)
		return ;
	machine->current_state = initial_state;
	machine->previous_state = NULL;
	machine->error_state = error_state;
}
