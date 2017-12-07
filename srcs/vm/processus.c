/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:57:25 by lchety            #+#    #+#             */
/*   Updated: 2017/12/05 14:32:11 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_process(t_vm *vm, t_proc *proc)
{
	if (vm->proc)
		proc->next = vm->proc;
	vm->proc = proc;
}

void	kill_proc(t_vm *vm)
{
	t_proc *tmp;
	t_proc *t;

	tmp = vm->proc;
	while (tmp)
	{
		if ((vm->cycle - tmp->last_live) >= vm->ctd && tmp->active)
		{
			tmp->active = 0;
			if (0x8 & vm->verbosity)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				tmp->id + 1, vm->cycle - tmp->last_live, vm->ctd);
		}
		if (tmp->next && !tmp->next->active)
		{
			t = tmp->next;
			tmp->next = tmp->next->next;
			free(t);
		}
		tmp = tmp->next;
	}
}

int		set_proc_id(t_vm *vm)
{
	t_proc	*tmp;
	int		nb;

	nb = 0;
	tmp = vm->proc;
	if (!tmp)
		return (nb);
	while (tmp)
	{
		if (tmp->id > nb)
			nb = tmp->id;
		tmp = tmp->next;
	}
	return (nb + 1);
}

t_proc	*create_process(t_vm *vm, int num)
{
	t_proc	*tmp;

	if (!(tmp = (t_proc*)ft_memalloc(sizeof(t_proc))))
		error("Malloc\n");
	tmp->id = set_proc_id(vm);
	tmp->num = num;
	tmp->pc = (MEM_SIZE / vm->nb_player) * ((num * (-1) - 1));
	tmp->last_pc = 0;
	ft_bzero(tmp->reg, sizeof(int) * (REG_NUMBER + 1));
	tmp->reg[1] = num;
	tmp->carry = 0;
	tmp->last_live = 0;
	tmp->active = 1;
	tmp->op.active = 0;
	tmp->next = NULL;
	return (tmp);
}

int		process_living(t_vm *vm)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	tmp = vm->proc;
	if (vm->cycle < vm->next_ctd)
		return (1);
	kill_proc(vm);
	set_ctd(vm);
	vm->next_ctd = vm->cycle + vm->ctd;
	while (tmp)
	{
		if (tmp->active)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
