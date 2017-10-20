/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:05:43 by lchety            #+#    #+#             */
/*   Updated: 2017/10/19 22:08:33 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// VM = https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C

#ifndef COREWAR_H
#define COREWAR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "libft.h"
#include "ft_printf.h"
//-------------------------

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
 **
 */

// typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
 **
 */

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3


typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					header_t;


//-------------------------

// #define PC;

#define INST_IDLE 0
#define INST_NAME 1
#define INST_OCP 2
#define INST_ARG 2

#define	IDLE 1
#define	WAIT 2
#define	READY 3
#define START 4

#define	MAGIC_NB 4
#define PROG_NAME 128 + 4
#define PROG_COMS 2048 + 4
#define	PROG_SIZE 4;

#define D4 0
#define D2 1

#define SRC_BEGIN MAGIC_NB + PROG_NAME + PROG_COMS + PROG_SIZE

#define BLING_DELAY 65
#define BLING_LIVE 45
#define NCURSES_DELAY 100000

typedef struct s_vm t_vm;
typedef struct s_optab t_optab;

typedef struct s_op
{
	t_optab			*optab_ref;
	char			code;
	unsigned char	ocp;
	int				ar[3];
	int				ar_typ[3];
	int				loadtime;
	int				pos_opcode;
	int				countdown;
}	t_op;


typedef struct s_player
{
	int		active;
	// int		id;
	int		life_signal;
	char	*file_name;
}	t_player;

typedef struct s_proc
{
	int		id;
	int		active;
	int		num;//Num du programme/player a fournir dans r1 (registre 1)
	int		last_pc;
	int		pc;// L adresse dans la memoire de la machine virtuelle de la prochaine instruction du programme
	int		state;
	char	carry;// Mystere //edit : plus maintenant;
	// int		*reg;//la on garde les registres en void* car ca taille est defini par une macro
	int		reg[17];
	int		loadtime;
	int		last_live; // si le processus a fait appel a live durant CYCLE_TO_DIE
	t_op	*op;
	struct	s_proc	*next;
}	t_proc;

// typedef struct s_optab
// {
// 	void	(*func)(t_vm *vm, t_op *op, int player);
// 	int		nb_arg;
// 	int		direct;
// 	int		ocp;
// }	t_optab;

typedef struct s_mem
{
	char	mem;
	int		num;
	int		blingbling;
	int		live;
}	t_mem;

typedef struct s_optab
{
	char	*inst;
	void	(*func)(t_vm *vm, t_proc *proc);
	int		nb_arg;
	int		ocp;
	int		code;
	int		loadtime;
	char	*name;
	int		need_ocp;
	int		direct_size; 	// nombre d'octect d'encodage. 2 ou 4;
	//changez ce nom de variable de merde :)
}	t_optab;

extern t_optab op_tab[];


typedef struct s_vm
{
	int		nb_player;
	int		ctd;
	int		cycle;
	int		keycode;
	int		pause;
	int		ncurses;
	int		delay;
	int		next_ctd;
	int		ctd_check;
	int		dump;
	int		debug;
	int		verbosity;
	// char	*mem;
	char	mem[MEM_SIZE];
	t_mem	ram[MEM_SIZE];
	int		life_signal[4];			// tab pour les vies.
	char	*files_name[5];
	t_player	player[5];
	t_player	*last_one;

	//void	(*op_tab[20])(struct s_vm *vm, t_op *op, int player);

	t_optab	optab[17];
	t_proc	*proc;
}	t_vm;


void		init_vm(t_vm *vm);
void		create_players(t_vm *vm);
void		error(char *str);
// void	write_player(t_vm *vm);
void		write_player(t_vm *vm, int nb, int num);
int			check_arg(t_vm *vm, int argc, char **argv);
t_proc		*create_process(t_vm *vm, int num);
void		add_process(t_vm *vm, t_proc *proc);
void		wait_state(t_vm *vm, t_proc *proc);
void		idle_state(t_vm *vm, t_proc *proc);
t_op		*create_op(t_vm *vm, t_proc *proc, char data);
void		call_ncurses(t_vm *vm);
void		undertaker(t_vm *vm);
void		kill_proc(t_vm *vm);
void		fill_cur_op(t_vm *vm, t_proc *proc);
void		controller(t_vm *vm);
int			is_pc(t_vm *vm, int nb);
int			count_proc(t_vm *vm);
int			all_died(t_vm *vm);
int			is_opcode(char data);
int			cycle_to_die(t_vm *vm);
t_player	*get_survivor(t_vm *vm);
void		get_ocp(t_vm *vm, t_proc *proc);
void		find_args(t_vm *vm, t_proc *proc, int num);
void		get_dir(t_vm *vm, t_proc *proc, int num);
int			modulo(int a, int b);
void		show_operations(t_vm *vm, t_proc *proc);
void	show_pc_move(t_vm *vm, t_proc *proc);
// int			*init_registre(int id);



/*--------INSTRUCTIONS----------*/
void		and(t_vm *vm, t_proc *proc);
void		ld(t_vm *vm, t_proc *proc);
void		ldi(t_vm *vm, t_proc *proc);
void		sti(t_vm *vm, t_proc *proc);
void		live(t_vm *vm, t_proc *proc);
void		add(t_vm *vm, t_proc *proc);
void		or(t_vm *vm, t_proc *proc);
void		xor(t_vm *vm, t_proc *proc);
void		st(t_vm *vm, t_proc *proc);
void		sub(t_vm *vm, t_proc *proc);
void		ft_fork(t_vm *vm, t_proc *proc);
void		zjmp(t_vm *vm, t_proc *proc);

/*--------NCURSES---------*/
void		init_ncurses(WINDOW **w);


/*-------DEBUG-------*/
void		show_mem(t_vm *vm);
void		show_mem_2(t_vm *vm);
void		show_proc_nb(t_vm *vm);
void		debug_display_proc(t_vm *vm);

/*
 ** ------- ASM -----------
 */

#define SOURCE_ERR 1
#define MALLOC_ERR 2

typedef struct s_asm_env
{
	struct s_tab_labs *labs;
	int              bytes;
	int							 size;
	int              fd;
}                  t_asm_env;

typedef struct s_tab_labs
{
	char              *label;
	int               nb_oct;
	struct s_tab_labs  *next;
}                   t_tab_labs;

typedef struct s_dasm_env
{
	int								fd;
}										t_dasm_env;

void print_labs_lst(t_tab_labs *lst);
void create_label(t_tab_labs **labels, int bytes, char *line);

void write_header(t_asm_env *env, char *line, int printmode);

void	init_vm(t_vm *vm);
void	asm_error(int err, char *str);

/*-------DEBUG-------*/
void	show_mem(t_vm *vm);

#endif
