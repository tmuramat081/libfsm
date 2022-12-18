/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:22:26 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/18 10:31:05 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfsm.h"

static void	_goto_error_state(t_state_machine *fsm, t_event *const event)
{
	fsm->previous_state = fsm->current_state;
	fsm->current_state = fsm->error_state;
	if (fsm->current_state && fsm->current_state->entry_action)
		fsm->current_state->entry_action(fsm->current_state->data, event);
}

static t_transition	*_get_transition(t_state_machine *fsm, t_state *state,
	t_event *const event)
{
	t_transition	*t;
	size_t			i;

	(void)fsm;
	i = 0;
	while (i < state->num_transitions)
	{
		t = &state->transitions[i];
		if (t->type == event->type)
		{
			if (!t->guard)
				return (t);
			else if (t->guard(t->condition, event))
				return (t);
		}
		i++;
	}
	return (NULL);
}

int	fsm_handle_event(t_state_machine *fsm, t_event *event)
{
	t_state			*next_state;
	t_transition	*transition;

	if (!fsm|| !event)
		return (FSM_ERR_ARGS);
	if (!fsm->current_state)
	{
		_goto_error_state(fsm, event);
		return (FSM_ERR_STATE_REACHED);
	}
	if (fsm->current_state->num_transitions)
		return (FSM_STATE_NOT_CHANGED);
	next_state = fsm->current_state;
	while (true)
	{
		transition = _get_transition(fsm, next_state, event);
		if (!transition)
		{
			next_state = next_state->parent_state;
			continue ;
		}
		if (!transition->next_state)
		{
			_goto_error_state(fsm, event);
			return (FSM_ERR_STATE_REACHED);
		}
		next_state = transition->next_state;
		while (next_state->entry_state)
			next_state = next_state->entry_state;
		if (next_state != fsm->current_state && fsm->current_state->exit_action)
			fsm->current_state->exit_action(fsm->current_state->data, event);
		if (transition->action)
			transition->action(fsm->current_state->data, event,
				next_state->data);
		if (next_state != fsm->current_state && next_state->entry_action)
			next_state->entry_action(next_state->data, event);
		fsm->previous_state = fsm->current_state;
		fsm->current_state = next_state;
		if (fsm->current_state == fsm->previous_state)
			return (FSM_STATE_LOOP);
		if (fsm->current_state == fsm->error_state)
			return (FSM_ERR_STATE_REACHED);
		if (!fsm->current_state->num_transitions)
			return (FSM_STATE_END_REACHED);
		return (FSM_STATE_NOT_CHANGED);
	}
}
