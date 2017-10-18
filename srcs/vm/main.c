/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 22:10:50 by lchety            #+#    #+#             */
/*   Updated: 2017/10/17 02:04:22 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_ocp(t_vm *vm, t_proc *proc)
{
	// printf("MEM BEFORE   %x\n", (unsigned char)vm->mem[proc->pc]);
	if (op_tab[proc->op->code - 1].need_ocp)
	{
		proc->pc++;
		proc->op->ocp = vm->ram[proc->pc].mem;
	}
}

void	get_dir(t_vm *vm, t_proc *proc, int num)
{
	// printf(">>>>>>>>>>GET_DIR<<<<<<<<<<<\n");
	unsigned int value;

	value = 0;

	proc->pc++;


	if (vm->debug)
	{
		printf("- start -\n");
		printf("%x\n", (unsigned char)vm->ram[proc->pc - 2].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc - 1].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 1].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 2].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 3].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 4].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 5].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 6].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 7].mem);
		printf("%x\n", (unsigned char)vm->ram[proc->pc + 8].mem);

		printf("- end -\n");
	}
	value = (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug)
		printf("Value => %x\n", value);
	if (vm->debug)
	printf("Pc => %d\n", proc->pc);
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	if (vm->debug)
	printf("Value => %x\n", value);
	if (vm->debug)
	printf("Pc => %d\n", proc->pc);

	// printf(" hexa dans mem %x\n", vm->mem[proc->pc]);
	if (op_tab[proc->op->code - 1].direct_size)
	{
		if ((value & 0x8000) == 0x8000)
			value = (value - USHRT_MAX) - 1;
		// printf("deux octets value %x\n", value);
		proc->op->ar[num] = value;
		return ;
	}

	if (proc->op->code == 1 && proc->id == 5 && vm->debug)
		printf("GET DIR 4\n");
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	// printf("get dir 2 -> %x\n", (unsigned char)vm->ram[proc->pc].mem);

	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;

	// printf("get dir value -> %d\n", value);
	proc->op->ar[num] = value;

	if (proc->op->code == 1 && proc->id == 5 && vm->debug)
		printf("live value => %d   arg_num => %d\n", value, num);
}

void	get_reg(t_vm *vm, t_proc *proc, int num)
{
	// printf(">>>>>>>>>>GET_REG<<<<<<<<<<<\n");
	unsigned char value;

	proc->pc++;
	value = (unsigned char)vm->ram[proc->pc].mem;

	// printf("reg value %d\n", value);

	proc->op->ar[num] = value;
}

void	get_ind(t_vm *vm, t_proc *proc, int num)
{
	// printf(">>>>>>>>>>GET_IND<<<<<<<<<<<\n");

	unsigned int value;

	value = 0;

	proc->pc++;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->pc++;
	value = value << 8;
	value = value | (unsigned char)vm->ram[proc->pc].mem;
	proc->op->ar[num] = value;
	if ((value & 0x8000) == 0x8000)
	 	proc->op->ar[num] = (value - USHRT_MAX) - 1;
}

void	find_args(t_vm *vm, t_proc *proc, int num)
{
	// printf("ENTER FUNC : FIND_ARGS\n");
	unsigned char	type;
	unsigned char	mask;

	type = proc->op->ocp;
	mask = 0xC0;
	mask = mask >> (2 * num);
	type = type & mask;
	type = type >> (6 - 2 * num);
	proc->op->ar_typ[num] = type;

	if (proc->op->code == 1)
		printf("LIVE OP CODE\n");

	if (type == REG_CODE)
		get_reg(vm, proc, num);
	if (type == DIR_CODE)
		get_dir(vm, proc, num);
	if (type == IND_CODE)
		get_ind(vm, proc, num);

}


int		is_opcode(char data)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if ((char)op_tab[i].code == data)
			return (data);
		i++;
	}
	return (0);
}



t_player	*get_survivor(t_vm *vm)
{
	int i;

	i  = 1;
	while (i <= MAX_PLAYERS)
	{
		if (vm->player[i].active)
			return (&vm->player[i]);
		i++;
	}
	return (vm->last_one);
}

// int		cycle_to_die(t_vm *vm)
// {
// 	if (vm->cycle % vm->ctd == 0 && vm->cycle / vm->ctd > 0)
// 		return (1);
// 	return (0);
// }

void	animate_proc(t_vm *vm, t_proc *proc)
{
	if (proc->state == IDLE)
		idle_state(vm, proc);
	// else if (proc->state == WAIT)
	// 	wait_state(vm, proc);
	// else if (proc->state == START)
	// 	proc->state = IDLE;
}

int		count_proc(t_vm *vm)
{
	int i;
	t_proc	*proc;

	i = 0;
	proc = vm->proc;
	while (proc)
	{
		if (proc->active)
			i++;
		proc = proc->next;
	}
	return (i);
}

void	dump(t_vm *vm)
{
	if (!(vm->cycle % vm->dump))
		show_mem(vm);
}

void	run(t_vm *vm)
{
	t_proc	*proc;

	while (!all_died(vm))
	{
		if (2 & vm->verbosity)
			printf("It is now cycle %d\n", vm->cycle + 1);
		//-------------------NCURSES
		if (vm->ncurses)
		{
			call_ncurses(vm);
			controller(vm);
			usleep(vm->delay);
		}
		//-------------------NCURSES
		// printf("RRRRRRRRRRRRRUUUUUUUUUUUNNNNNNNNNNNN   %d\n", vm->cycle);
		// printf("here\n");
		proc = vm->proc;
		while (proc != NULL)
		{
			if (proc->active)
			{
				animate_proc(vm, proc);
			}
			if (16 & vm->verbosity)
				show_pc_move(vm, proc);
			proc->last_pc = proc->pc;
			proc = proc->next;
		}
		vm->cycle++;
//-------------------------Debug


//-------------------------Debug
		// printf("%d\n", vm->dump);
		if (vm->dump != -1 && !vm->ncurses)
			dump(vm);
	}
	printf("END\n");
	if (vm->last_one)
		printf("Last_one => %s\n", vm->last_one->file_name);
}

int		modulo(int a, int b)
{
	if (a % b >= 0)
		return (a % b);
	else
		return ((a % b) + b);
	// return (a % b) >= 0 ? (a % b) : (a % b) + b;
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	WINDOW *w;//ncurses

	// show_mem(&vm);
	init_vm(&vm);
	if(check_arg(&vm, argc, argv))//check des parametres
		error("Error\n");

	if (vm.ncurses)
		init_ncurses(&w);

//-------------Debug
	// printf("Debug : active -> %d\n", vm.player[1].active);
//-------------Debug
	create_players(&vm);//initialisation de la machine virtuelle

	// printf("SEGV\n");
	run(&vm);//lancement du combat

	if (vm.ncurses)
		endwin();
	return (0);
}
