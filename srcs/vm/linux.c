/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 22:26:34 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 22:27:04 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	display_linux(void)
{
	int i;
	int j;

	i = 0;
	attron(COLOR_PAIR(NC_P_BLACK_B));
	while (i < (MEM_SIZE / 64) + 5)
	{
		j = 0;
		while (j < 3 * (MEM_SIZE / 64) + 72)
		{
			mvprintw(i, j, " ");
			++j;
		}
		++i;
	}
}
