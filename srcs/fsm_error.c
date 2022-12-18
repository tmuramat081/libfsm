#include "libfsm.h"

static void	goto_error_state(t_state_machine *machine, t_event *const event)
{
	machine->previous_state = machine->current_state;
	machine->current_state = machine->error_state;
	if (machine->current_state && machine->current_state->entry_action)
		machine->current_state->entry_action(machine->current_state->data, event);
}