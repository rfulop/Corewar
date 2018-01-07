/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:09:37 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 16:37:27 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_winner(t_vm *vm)
{
	int i;
	int best;

	i = 1;
	best = 0;
	vm->player[best].last_live = 0;
	while (i <= MAX_PLAYERS)
	{
		if (vm->player[i].active)
		{
			if (vm->player[i].last_live > vm->player[best].last_live)
				best = i;
		}
		i++;
	}
	if (!best)
		++best;
	vm->winner = best;
}
