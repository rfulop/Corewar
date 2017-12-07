/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:33:15 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 12:38:25 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			display_winner(t_vm *vm)
{
	int			win;

	win = vm->winner;
	attron(A_BOLD);
	mvprintw(45, 3 * (MEM_SIZE / 64) + 20, "The winner is : ");
	name_color(win);
	mvprintw(45, 3 * (MEM_SIZE / 64) + 20 + 16, "%s", vm->player[win].name);
	attron(COLOR_PAIR(NC_P_WHITE));
	mvprintw(46, 3 * (MEM_SIZE / 64) + 20, "Press Space to finish");
}

static void		keys_press(t_vm *vm, char key)
{
	if ((key == ' ' && vm->pause != 1) || vm->winner)
	{
		vm->pause = 1;
		attron(COLOR_PAIR(NC_P_WHITE));
		mvprintw(3, 3 * (MEM_SIZE / 64) + 7, "** PAUSED **");
		if (vm->winner)
			display_winner(vm);
		attron(COLOR_PAIR(NC_P_WHITE_B));
		mvprintw(68, 2, "");
	}
	if (key == 'r')
		vm->boost = (vm->boost) ? 0 : 1;
	if (key == 'w')
	{
		if (vm->delay + 24000 < 1000000)
			vm->delay += 24000;
	}
	else if (key == 'e')
	{
		if (vm->delay - 12000 > 0)
			vm->delay -= 12000;
		else
			vm->delay = 0;
	}
}

void			controller(t_vm *vm)
{
	char		key;

	key = -1;
	key = getch();
	if (key != -1 || vm->winner)
	{
		if (vm->winner)
			key = -2;
		keys_press(vm, key);
	}
	while (vm->pause)
	{
		key = getch();
		if (key != -1)
		{
			keys_press(vm, key);
			if (key == ' ')
			{
				vm->pause = 0;
				break ;
			}
		}
		usleep(180000);
	}
}
