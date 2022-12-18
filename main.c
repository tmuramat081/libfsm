#include "libfsm.h"

enum event_type {
	EVENT_PARSE_CHAR,
};

bool	is_equal_character(void *ch, t_event *event);
bool	is_not_equal_character(void *ch, t_event *event);
t_state state_general, state_quote, state_dquote;

t_state state_general = {
    .parent_state = NULL,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'\'', is_equal_character, NULL, &state_quote},
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'\"', is_equal_character, NULL, &state_dquote},
	},
    .num_transitions = 2,
    .data = "general",
    .entry_action = NULL,
    .exit_action = NULL,
};

t_state state_quote = {
    .parent_state = NULL,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'\'', is_equal_character, NULL, &state_general},
	},
    .num_transitions = 1,
    .data = "quote",
    .entry_action = NULL,
    .exit_action = NULL,
};

t_state state_dquote = {
    .parent_state = NULL,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'\"', is_equal_character, NULL, &state_general},
	},
    .num_transitions = 1,
    .data = "dquote",
    .entry_action = NULL,
    .exit_action = NULL,
};

t_state state_error = {
	.entry_action = NULL,
};

bool	is_equal_character(void *ch, t_event *event)
{
	if (event->type != EVENT_PARSE_CHAR)
		return (false);
	return ((intptr_t)ch == (intptr_t)event->data);
};

bool	is_not_equal_character(void *ch, t_event *event)
{
	if (event->type != EVENT_PARSE_CHAR)
		return (false);
	return ((intptr_t)ch != (intptr_t)event->data);
}

int main (int argc, char  **argv)
{
	t_state_machine fsm;
	size_t			i;
	char			*line;

	if (argc != 2)
		return (0);
	line = argv[1];
	fsm_init(&fsm, &state_general, &state_error);
	i = 0;
	while (line[i])
	{
		fsm_handle_event(&fsm, &(t_event){EVENT_PARSE_CHAR, (void *)(intptr_t)line[i]});
		i++;
	}
	return (0);
}