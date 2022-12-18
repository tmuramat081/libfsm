#include "libfsm.h"

t_state_machine *fsm_current_state(t_state_machine *fsm)
{
	if (!fsm)
		return (NULL);
	return (fsm->current_state);
}

t_state_machine *fsm_previus_state(t_state_machine *fsm)
{
	if (!fsm)
		return (NULL);
	return (fsm->previous_state);
}

bool	fsm_stopped(t_state_machine *fsm)
{
	if (!fsm)
		return (true);
	return (fsm->current_state->num_transitions == 0);
}