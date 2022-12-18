/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:21:21 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/18 10:31:54 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfsm.h"

t_state	*fsm_current_state(t_state_machine *fsm)
{
	if (!fsm)
		return (NULL);
	return (fsm->current_state);
}

t_state	*fsm_previus_state(t_state_machine *fsm)
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
