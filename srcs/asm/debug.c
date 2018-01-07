/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:44 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/05 18:04:24 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_labs_lst(t_tab_labs *lst)
{
	int			count;
	t_tab_labs	*tmp;

	count = 0;
	tmp = lst;
	ft_printf("Labels list :\n");
	while (tmp && tmp->label)
	{
		ft_printf("%d - '%s' at + %d bytes\n", count, tmp->label, tmp->nb_oct);
		tmp = tmp->next;
		++count;
	}
	ft_printf("\n");
}
