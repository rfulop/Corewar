/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 20:22:06 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 22:22:37 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_everything(t_vm *vm)
{
	t_proc *tmp;
	t_proc *tmp2;

	tmp = vm->proc;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	vm->proc = NULL;
}
