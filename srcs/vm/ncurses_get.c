/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amacieje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 09:21:17 by amacieje          #+#    #+#             */
/*   Updated: 2017/12/05 09:22:26 by amacieje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_dv(int live)
{
	int dv;

	dv = 0;
	if (live)
	{
		dv = (BREAK_DIS / live);
		if (BREAK_DIS % live)
			++dv;
	}
	return (dv);
}

int		get_nb_live(t_vm *vm)
{
	int i;
	int live;

	i = 1;
	live = 0;
	while (i <= MAX_PLAYERS)
	{
		live += vm->player[i].life_signal;
		++i;
	}
	return (live);
}

float	get_p_lives(t_vm *vm, int p, int tot_live)
{
	float p_lives;
	float perdiv;

	if (tot_live)
	{
		perdiv = (vm->player[p].life_signal * 100.0) / tot_live;
		p_lives = ((BREAK_DIS / 100.0) * perdiv);
		if (p_lives)
			++p_lives;
	}
	else
		p_lives = 0;
	return (p_lives);
}
