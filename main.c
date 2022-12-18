#include "libfsm.h"

enum event_type {
	EVENT_PARSE_CHAR,
};

bool	is_equal_character(void *ch, t_event *event);
bool	is_not_equal_character(void *ch, t_event *event);
void	print_message(void *data, t_event *event);
void	split_token(void *data, t_event *event, void *new_data);

t_state state_general, state_quote, state_dquote;

t_state state_group = {
    .parent_state = NULL,
    .entry_state = &state_general,
    .transitions = (t_transition[]){
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'\0', is_equal_character, NULL, NULL},
	},
    .num_transitions = 1,
    .data = "group",
    .entry_action = &print_message,
    .exit_action = &print_message,
};

t_state state_general = {
    .parent_state = &state_group,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{EVENT_PARSE_CHAR, (void *)(intptr_t)' ', is_equal_character, &split_token, &state_general},
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'\'', is_equal_character, NULL, &state_quote},
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'"', is_equal_character, NULL, &state_dquote},
	},
    .num_transitions = 3,
    .data = "general",
    .entry_action = &print_message,
    .exit_action = &print_message,
};

t_state state_quote = {
    .parent_state = &state_group,
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
    .parent_state = &state_group,
    .entry_state = NULL,
    .transitions = (t_transition[]){
		{EVENT_PARSE_CHAR, (void *)(intptr_t)'"', is_equal_character, NULL, &state_general},
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

void print_message(void *state_data, t_event *event)
{
   printf( "state_data: %s\n", (char *)state_data);
}

void split_token(void *state_data, t_event *event, void *new_data)
{
	new_data = state_data;
	printf("split: %c\n", *(char *)state_data);
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
		int ret = fsm_handle_event(&fsm, &(t_event){EVENT_PARSE_CHAR, (void *)(intptr_t)line[i]});
		printf("%d\n", ret);
		i++;
	}
	return (0);
}