#ifndef LIBFSM_H
# define LIBFSM_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_event {
	int		type;
	void	*data;
}	t_event;

typedef struct s_transition {
	int		type;
	void	*condition;
	bool	(*guard)(void *condition, t_event *event);
	void	(*action)(void *current_data, t_event *event, void *new_data);
	t_state	*next_state;
}	t_transition;

typedef struct s_state {
	t_state			*parent_state;
	t_state			*entry_state;
	t_transition	*transitions;
	size_t			num_transitions;
	void			*data;
	void			(*entry_action)(void *state_data, t_event *event);
	void			(*exit_action)(void *state_data, t_event *event);
}	t_state;

typedef struct s_state_machine{
	t_state	*current_state;
	t_state	*previous_state;
	t_state	*error_state;
}	t_state_machine;

typedef enum {
	FSM_ERR_ARGS = -2,
	FSM_ERR_STATE_REACHED,
	FSM_STATE_CHANGED,
	FSM_STATE_LOOP,
	FSM_STATE_NOT_CHANGED,
	FSM_STATE_END_REACHED,
} t_status;

void	fsm_init(t_state_machine *fsm, t_state *initial_state, t_state *error_state);
int		fsm_handle_event(t_state_machine *fsm, t_event *event);
t_state	*fsm_current_state(t_state_machine *fsm);
t_state	*fsm_previus_state(t_state_machine *fsm);
bool	fsm_stopped(t_state_machine *fsm);

#endif


