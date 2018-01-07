/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:44 by rfulop            #+#    #+#             */
/*   Updated: 2017/11/04 22:31:10 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_labels(t_asm_env *env)
{
	t_tab_labs	*labels;
	t_tab_labs	*tmp;

	if (env)
	{
		labels = env->labs;
		while (labels)
		{
			tmp = labels;
			labels = labels->next;
			free(tmp->label);
			free(tmp);
		}
	}
}
