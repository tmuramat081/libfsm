/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:22:20 by tmuramat          #+#    #+#             */
/*   Updated: 2022/12/18 10:24:15 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfsm.h"

void	fsm_init(t_state_machine *fsm, t_state *init_state, t_state *err_state)
{
	if (!fsm)
		return ;
	fsm->current_state = init_state;
	fsm->previous_state = NULL;
	fsm->error_state = err_state;
}
