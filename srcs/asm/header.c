/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:13:29 by rfulop            #+#    #+#             */
/*   Updated: 2017/10/18 23:29:45 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// ON ASM42 COMMENTS ALWAYS ENDS AFTER 2192 bytes
// BUT, 2048 + 128 = 2176 (+MAGIC_NB + SIZE) ( = 2184)
void  write_comment(t_asm_env *env, char *line)
{
  int a;
  int tmp;
  int c;
  int size;

  a = 0;
  c = 0;
  tmp = 0;

// ASSUMING SIZE ON 4 BYTES
  size = reverse_int(env->size);
  write(env->fd, &size, 4);
//  write(env->fd, &env->size, 2);
//  printf("line comment = '%s'\n", line);
  while (line[a] != '\"')
    ++a;
  a++;
//  printf("between quotes = '%s'\n", line + a);
  tmp = a;
  a = 0;
  while (line[tmp + a] != '\"')
  {
    ft_putchar_fd(line[tmp + a], env->fd);
    ++a;
  }
  int test = 0;
  // STILL DONT KNOW WHY 4
  while (a != COMMENT_LENGTH + 4)
  {
    ft_putchar_fd(c, env->fd);
    a++;
    ++test;
  }
  printf("test = %d a = %d\n", test, a);
}


// NEED TO UNDERSTAND WHY 42ASM STARTS COMMENTS AFTER 140 BYTES, WHEREAS .H SAID 128
// NEED TO WRITE BYTE SIZE BEFORE COMMENTS -> 2 ? 4 ? 8 ?
// MAGIC NUMBER ON 4 BYTES. 140 - 4 = 136
// NO EXPLAINATION FOR THE 8 OTHER BYTES
void  write_name(t_asm_env *env, char *line)
{
  int a;
  int tmp;
  int c;
  int magic;

  tmp = 0;
  c = 0;
  magic = reverse_int(COREWAR_EXEC_MAGIC);
  write(env->fd, &magic, 4);
  a = 4;
  while(line[a] != '\"')
    ++a;
  ++a;
  tmp = a;
  a = 0;
  while(line[tmp + a] != '\"')
  {
    ft_putchar_fd(line[tmp + a], env->fd);
    ++a;
  }
  printf("nb = %d\n", env->size);

  // DONT UNDERSTAND WHY 4 BYTES
  while(a != PROG_NAME_LENGTH + 4)
  {
    ft_putchar_fd(c, env->fd);
    a++;
  }
}

void  write_header(t_asm_env *env, char *line, int printmode)
{
  int a;
  int tmp;

  a = 0;
  tmp = 0;
  if (!printmode)
    ;
  else
  {
    if (line[1] == 'n' && line[2] == 'a' && line[3] == 'm' && line[4] == 'e')
      write_name(env, line);
    else
      write_comment(env, line);
  }
}
