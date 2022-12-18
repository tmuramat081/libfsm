#include "libfsm.h"

const t_state state_general = {
    .parent_state = NULL,
    .entry_state = NULL,
    .transitions = NULL,
    .num_transitions = NULL,
    .data = "general",
    .entry_action = NULL,
    .exit_action = NULL,
};

const t_state state_quote = {
    .parent_state = NULL,
    .entry_state = NULL,
    .transitions = NULL,
    .num_transitions = NULL,
    .data = "quote",
    .entry_action = NULL,
    .exit_action = NULL,
};


const t_state state_dquote = {
    .parent_state = NULL,
    .entry_state = NULL,
    .transitions = NULL,
    .num_transitions = NULL,
    .data = "dquote",
    .entry_action = NULL,
    .exit_action = NULL,
};

const t_transition goto_state_quote = {
    .type = 0,
    .condition = NULL,
    .guard = NULL,
    .action = NULL,
    .next_state = &state_quote,
};

const