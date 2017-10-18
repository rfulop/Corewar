/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 16:57:25 by lchety            #+#    #+#             */
/*   Updated: 2017/10/17 01:55:16 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	kill_proc(t_vm *vm)
{
	t_proc *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		if ((vm->cycle - tmp->last_live) > vm->ctd)
		{
			tmp->active = 0;
			if (0x8 & vm->verbosity)
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n", tmp->id + 1, vm->cycle - tmp->last_live, vm->ctd);
		}
		tmp = tmp->next;
	}
}

int		set_proc_id(t_vm *vm)
{
	t_proc *tmp;
	int nb;

	nb = 0;
	tmp = vm->proc;
	if (!tmp)
		return (nb);
	while (tmp)
	{
		tmp = tmp->next;
		nb++;
	}
	return (nb);
}

t_proc	*create_process(t_vm *vm, int num)
{
	t_proc	*tmp;

	if(!(tmp = (t_proc*)ft_memalloc(sizeof(t_proc))))
		error("error : malloc\n");
	tmp->id = set_proc_id(vm);
	// printf("NOMBRE => %d\n", num * (-1));
	// printf("NUM > %d\n", num);
	tmp->num = num;
	tmp->pc = (MEM_SIZE / vm->nb_player) * ((num * (-1) -1));
	tmp->last_pc = 0;
	// printf(">>>> %d   num %d\n", tmp->pc, num);
	tmp->op = NULL;
	// tmp->reg = init_registre(num);
	ft_bzero(tmp->reg, sizeof(int) * (REG_NUMBER + 1));
	// printf("INIT REG 1 >>> %x\n", num * -1);
	tmp->reg[1] = num;
	tmp->state = IDLE;
	tmp->carry = 0;
	tmp->last_live = 0;
	tmp->active = 1;
	return (tmp);
}

void	undertaker(t_vm *vm)
{
	int i;
	t_proc	*tmp;

	i = 1;
	tmp = vm->proc;
	while (i <= MAX_PLAYERS)
	{
		if (!vm->player[i].life_signal && vm->player[i].active)
		{
			vm->player[i].active = 0;
		}
		i++;
	}
	kill_proc(vm);
}

int		is_pc(t_vm *vm, int nb)
{
	t_proc *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		if (tmp->pc == nb && tmp->active)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
