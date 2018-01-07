/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:05:43 by lchety            #+#    #+#             */
/*   Updated: 2017/12/07 16:02:54 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <ncurses.h>
# include "libft.h"
# include "ft_printf.h"

# define T_WINDOW WINDOW
# define IND_SIZE				2
# define REG_SIZE				1
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define SCOLON_CHAR ';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','
# define REG_CHAR			'r'
# define SPACE ' '
# define TAB '\t'

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_DIR4					3
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define INST_IDLE 0
# define INST_NAME 1
# define INST_OCP 2
# define INST_ARG 2

# define IDLE 1
# define WAIT 2
# define READY 3
# define START 4

# define MAGIC_NB 4
# define PROG_NAME 128 + 4
# define PROG_COMS 2048 + 4
# define PROG_SIZE 4

# define D4 0
# define D2 1

# define SRC_BEGIN MAGIC_NB + PROG_NAME + PROG_COMS + PROG_SIZE

# define BLING_DELAY 65
# define BLING_LIVE 45
# define NCURSES_DELAY 90000
# define BREAK_DIS 60
# define BOOST_CYCLES 200

/*
** --------NCURSES_COLORS----------
*/

# define NC_C_WHITE 20
# define NC_C_BLACK 21
# define NC_C_GREY 22
# define NC_C_GREEN 23
# define NC_C_BLUE 24
# define NC_C_RED 25
# define NC_C_CYAN 26

# define NC_C_GREEN_BLING 32
# define NC_C_BLUE_BLING 33
# define NC_C_RED_BLING 34
# define NC_C_CYAN_BLING 35

# define NC_P_GREY 20
# define NC_P_WHITE 21
# define NC_P_BLACK 22
# define NC_P_GREEN 23
# define NC_P_BLUE 24
# define NC_P_RED 25
# define NC_P_CYAN 26

# define NC_P_GREEN_BLING 30
# define NC_P_BLUE_BLING 31
# define NC_P_RED_BLING 32
# define NC_P_CYAN_BLING 33

# define NC_P_GREEN_PC 40
# define NC_P_BLUE_PC 41
# define NC_P_RED_PC 42
# define NC_P_CYAN_PC 43

# define NC_P_GREEN_LIFE 50
# define NC_P_BLUE_LIFE 51
# define NC_P_RED_LIFE 52
# define NC_P_CYAN_LIFE 53
# define NC_P_WHITE_B 54
# define NC_P_BLACK_B 55

# define NC_C_BASIC 15
# define NC_C_YELLOW 60

typedef struct	s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}				t_header;

typedef struct	s_op
{
	int				active;
	char			code;
	unsigned char	ocp;
	int				ar[3];
	int				ar_typ[3];
	int				loadtime;
	int				pos_opcode;
}				t_op;

typedef struct	s_player
{
	int		active;
	int		life_signal;
	int		last_live;
	int		tot;
	int		last_period;
	int		read_ret;
	int		padding;
	char	*file_name;
	char	name[PROG_NAME];
	char	comments[PROG_COMS];
}				t_player;

typedef struct	s_proc
{
	int				id;
	int				active;
	int				num;
	int				last_pc;
	int				pc;
	char			carry;
	int				reg[17];
	int				last_live;
	t_op			op;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_mem
{
	char	mem;
	char	padding1;
	char	padding2;
	char	padding3;
	int		num;
	int		blingbling;
	int		live;
	int		pc;
}				t_mem;

typedef struct	s_vm
{
	int				nb_player;
	int				ctd;
	int				cycle;
	int				boost;
	int				pause;
	int				ncurses;
	int				delay;
	int				next_ctd;
	int				ctd_check;
	int				dump;
	int				debug;
	int				verbosity;
	int				winner;
	int				lives_in_cycle;
	t_mem			ram[MEM_SIZE];
	int				life_signal[4];
	char			*files_name[5];
	t_player		player[5];
	t_player		*last_one;
	t_proc			*proc;
}				t_vm;

typedef struct	s_optab
{
	char	*inst;
	void	(*func)(t_vm *vm, t_proc *proc);
	int		nb_arg;
	int		ocp[3];
	int		code;
	int		loadtime;
	char	*name;
	int		need_ocp;
	int		direct_size;
}				t_optab;

extern t_optab g_op_tab[];

/*
** --------VM_FUNCTIONS----------
*/

void			init_vm(t_vm *vm);
void			init_op(t_op *op);
void			create_players(t_vm *vm);
void			error(char *str);
void			write_player(t_vm *vm, int nb, int num);
int				check_arg(t_vm *vm, int argc, char **argv);
t_proc			*create_process(t_vm *vm, int num);
void			add_process(t_vm *vm, t_proc *proc);
void			wait_state(t_vm *vm, t_proc *proc);
void			create_op(t_proc *proc, char data);
void			call_ncurses(t_vm *vm);
void			kill_proc(t_vm *vm);
int				fill_cur_op(t_vm *vm, t_proc *proc);
void			controller(t_vm *vm);
int				count_proc(t_vm *vm);
int				all_died(t_vm *vm);
int				is_opcode(char data);
void			show_mem(t_vm *vm);
int				cycle_to_die(t_vm *vm);
void			get_ocp(t_vm *vm, t_proc *proc);
int				find_args(t_vm *vm, t_proc *proc, int num, int pos);
void			get_dir(t_vm *vm, t_proc *proc, int num, int pos);
void			get_reg(t_vm *vm, t_proc *proc, int num, int pos);
void			get_ind(t_vm *vm, t_proc *proc, int num, int pos);
int				modulo(int a, int b);
void			show_operations(t_proc *proc);
void			show_pc_move(t_vm *vm, t_proc *proc);
void			reduce_ctd(t_vm *vm);
int				process_living(t_vm *vm);
void			set_ctd(t_vm *vm);
int				check_reg(int nb);
int				check_params(t_op *op);
int				check_ocp(int ocp, int opcode);
void			free_everything(t_vm *vm);
int				get_indirect(t_vm *vm, t_op *op, int nb_arg);
void			get_winner(t_vm *vm);
void			new_player(t_vm *vm, int nb, char *str);
int				count_octet(int octet, t_optab *ref);
void			delete_op(t_proc *proc);
void			reset_live(t_vm *vm);
void			dump(t_vm *vm);
int				srch_nb_player(char **argv, int arg_num);
int				srch_players(t_vm *vm, int argc, char **argv);
void			new_player(t_vm *vm, int nb, char *str);
int				get_nb_player(t_vm *vm, char **argv, int arg_num);
int				move_pc(t_proc *proc);
void			init_process(t_vm *vm);
void			usage(void);

/*
** --------INSTRUCTIONS----------
*/
void			aff(t_vm *vm, t_proc *proc);
void			and(t_vm *vm, t_proc *proc);
void			ld(t_vm *vm, t_proc *proc);
void			ldi(t_vm *vm, t_proc *proc);
void			sti(t_vm *vm, t_proc *proc);
void			live(t_vm *vm, t_proc *proc);
void			add(t_vm *vm, t_proc *proc);
void			or(t_vm *vm, t_proc *proc);
void			xor(t_vm *vm, t_proc *proc);
void			st(t_vm *vm, t_proc *proc);
void			sub(t_vm *vm, t_proc *proc);
void			ft_fork(t_vm *vm, t_proc *proc);
void			ft_lfork(t_vm *vm, t_proc *proc);
void			zjmp(t_vm *vm, t_proc *proc);
void			lld(t_vm *vm, t_proc *proc);
void			lldi(t_vm *vm, t_proc *proc);

/*
**--------NCURSES---------
*/
void			init_ncurses(WINDOW **w);
void			display_mem(t_vm *vm);
void			display_menu(t_vm *vm);
int				display_players(t_vm *vm);
int				display_breakdown(t_vm *vm, int line);
int				get_dv(int live);
int				get_nb_live(t_vm *vm);
float			get_p_lives(t_vm *vm, int p, int tot_live);
void			name_color(int player);
void			name_color_off(int player);
void			display_linux(void);

/*
** ------- ASM -----------
*/
# define COLOR(param) ft_printf("\033[%sm",param)

# define C_RED "31"
# define C_GREEN "32"
# define C_YELLOW "33"
# define C_BLUE "34"
# define C_MAGENTA "35"
# define C_CYAN "36"
# define C_RESET "0"

# define CHECK_MODE 0
# define PRINT_MODE 1
# define ERROR_MIN 0
# define ERROR_MAX 30
# define NO_FILE_ERR 0
# define SOURCE_ERR 1
# define MALLOC_ERR 2
# define SIZE_ERROR 3
# define OPEN_ERROR 4
# define FILE_ERROR 5
# define INST_ERROR 6
# define LEX_ERROR 7
# define LABEL_ERROR 8
# define TOO_MUCH_ARG_ERR 9
# define BAD_ARG_REG 10
# define BAD_ARG_DIR 11
# define BAD_ARG_IND 12
# define BAD_ARG_REG_IND 13
# define BAD_ARG_REG_DIR 14
# define BAD_ARG_IND_DIR 15
# define BAD_ARG_REG_DIR_IND 16
# define NAME_SIZE_ERR 17
# define COM_SIZE_ERR 18
# define NAME_EXISTS 19
# define COM_EXISTS 20
# define COMMAND_ERR 21
# define NO_NAME 22
# define NO_COMMENT 23
# define NO_INSTRUCTIONS 24
# define NO_ARGUMENTS 25
# define WRONG_FORM_COM 26
# define SIZE_MAX_ERR 27
# define WRONG_FILE 28
# define NO_COMP 29
# define LAB_EXISTS 30
# define WRONG_MAG 50

typedef struct	s_asm_env
{
	struct s_tab_labs	*labs;
	int					bytes;
	int					size;
	int					fd;
	int					line;
	char				*current_line;
	char				*verbose_line;
	int					name;
	int					comment;
	int					debug;
	int					verbose;
	int					ko;
	int					print;
}				t_asm_env;

typedef struct	s_tab_labs
{
	char				*label;
	int					nb_oct;
	struct s_tab_labs	*next;
}				t_tab_labs;

typedef struct	s_check_ins
{
	int						args;
	int						inst;
	int						label;
	char					*word;
}				t_check_ins;

void			free_labels(t_asm_env *env);
void			print_labs_lst(t_tab_labs *lst);
int				char_is_com(char c);

/*
** -------- Create file ---------
*/
void			create_file(t_asm_env *env, char *str);
int				check_name(char *str);
int				parse_args(t_asm_env *env, char **argv);
void			check_args_letter(t_asm_env *env, char let);
void			debug_mode(t_asm_env *env, int fd);
void			print_mode(t_asm_env *env, char *file);
void			check_mode(t_asm_env *env, char *name, int fd);
void			print_mode_verbose(t_asm_env *env);
void			init_env(t_asm_env *env);
void			print_help(void);

/*
** -------- Analyse -------------
*/
int				analyse(int oct, char *line, int i);
int				analyse_args(int oct, char *line, int i);
void			op_no_ocp(t_asm_env *env, int i, char *line);
void			op_ocp(t_asm_env *env, int i, char *line);
char			*moove_on_line(char *line);
int				detect_arg(char *line);
char			*concat_opcode(char *ocp, int arg);

/*
** ---------- Read -------------
*/
void			parse(t_asm_env *env, char *line);
int				goto_nextarg(char *line);
char			*red_label_name(char *word, int len);

/*
** ---------- Parsing tools ---------
*/
int				until_is_not_space(char *str);
int				until_is_space(char *str);
int				until_next_arg(char *str, t_asm_env *env, int col);
int				len_is_label(char *line);

/*
** --------- Find op -----------
*/
int				find_op(t_asm_env *env, char *word, char *line);

/*
 ** --------- Check line --------------
*/
void			check_instr(char *line, t_asm_env *env);
int				check_op(char *instr, t_asm_env *env, int col);
void			check_header(t_asm_env *env, char *line);
void			check_parse_arg(char *str, int instr, t_asm_env *env, int col);
void			check_line(t_asm_env *env, char *line);

/*
**---------- Lex instructions ---------
*/
void			check_instr_endline(char *str, t_asm_env *env, int col);
void			check_instr_1_9_12_15(char *str, t_asm_env *env, int col);
void			check_instr_2_13(char *str, t_asm_env *env, int col);
void			check_instr_3(char *str, t_asm_env *env, int col);
void			check_instr_4_5(char *str, t_asm_env *env, int col);
void			check_instr_6_7_8(char *str, t_asm_env *env, int col);
void			check_instr_10(char *str, t_asm_env *env, int col);
void			check_instr_11(char *str, t_asm_env *env, int col);
void			check_instr_14(char *str, t_asm_env *env, int col);
void			check_instr_16(char *str, t_asm_env *env, int col);

/*
** ---------- Display ------------
*/
void			write_reg(t_asm_env *env, char *line);
void			write_dir(t_asm_env *env, char *line, int i);
void			write_dir_short(t_asm_env *env, char *line, int nb, int a);
void			write_dir_int(t_asm_env *env, char *line, int nb, int a);
void			write_ind(t_asm_env *env, char *line);
void			write_args(t_asm_env *env, char *line, int i);
void			write_ocp(t_asm_env *env, char *ocp);

/*
** ------------ Check args -----------
*/
int				is_ind(char *str);
int				is_dir(char *str);
int				is_reg(char *str);
int				is_reg_or_ind(char *str, t_asm_env *env, int col);
int				is_reg_or_dir(char *str, t_asm_env *env, int col);
int				is_ind_or_dir(char *str, t_asm_env *env, int col);
int				is_reg_or_ind_or_dir(char *str, t_asm_env *env, int col);

/*
** -------- Header -------------
*/

void			write_comment(t_asm_env *env, char *line);
void			write_name(t_asm_env *env, char *line);
void			write_header(t_asm_env *env, char *line, int printmode);

/*
** --------- Labels ------------
*/
t_tab_labs		*new_label(t_tab_labs **labels, char *line, int bytes);
void			create_label(t_tab_labs **labels, int bytes, char *line);
int				dist_label(t_asm_env *env, char *label);
int				is_label_str(char *str);
int				is_label_char(char c);
void			check_lab_exits(t_tab_labs **labels, char *name);

/*
** ---------- Toolkit ----------
*/
int				reverse_int(int nb);
short			reverse_short(short nb);
int				is_dir_int(int i);
int				is_space(char c);
char			*take_word(char *str);

/*
** ------- Error -------
*/
void			asm_error(int err, char *str, t_asm_env *env, int column);
void			asm_error1(int err, char *str, t_asm_env *env);
void			asm_error2(int err, char *str, t_asm_env *env, int column);
void			asm_error3(int err, char *str, t_asm_env *env, int column);
void			asm_error4(int err, char *str, t_asm_env *env);
void			asm_error5(int err, char *str, t_asm_env *env);
void			asm_error6(int err, t_asm_env *env);

void			verbose_inst(t_asm_env *env, char *ins, int hex);
void			verbose_arg(t_asm_env *env, char *line, int arg, int hex);
void			verbose_arg_bis(char *line, int arg);
void			verbose_lab(char *lab);
void			verbose_dist_lab(int dist);
void			verbose_ocp(t_asm_env *env, char ocp);
char			*swap_hex(char *str);
/*
**------------------- DECOMPILER ------------------
*/

typedef struct	s_dasm_env
{
	int				fd;
	int				size_file;
	unsigned char	*file;
}				t_dasm_env;

/*
** ------ Display instructions ---------
*/
int				print_dir4(int fd, unsigned char *str);
int				print_dir2(int fd, unsigned char *str);
int				print_reg(int fd, int reg);
int				print_ind(int fd, unsigned char *str);
int				print_args(int fd, int inst, unsigned char *str);

/*
** ------ Error -------
*/
void			dasm_error(int err, char *str);
int				len_is_label(char *str);
void			check_magic_nb(t_dasm_env *env);

/*
** ----- Create file -----
*/
int				ft_bin_len(unsigned char *str);
unsigned char	*open_bin(t_dasm_env *env, int fd);
void			create_file_cor(t_dasm_env *env, char *str);
void			parse_cor(t_dasm_env *env);

/*
** ----- Get types ---
*/
int				get_uint32(unsigned char *buff);
short			get_uint16(unsigned char *buff);

#endif
