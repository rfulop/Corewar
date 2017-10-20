/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:53:48 by rfulop            #+#    #+#             */
/*   Updated: 2017/10/19 22:23:40 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void parse_cor(t_dasm_env *env, char *line)
{
  char test;

  int i = 0;
  while (line[i])
  {
    test = line[i];
    printf("%d %c %x\n", test, test, test);
    ++i;
  }
/*
**   for (int i = 0; line[i]; ++i)
**     printf("%d", line[i]);
**   printf("\n");
*/
}

void create_file_cor(t_dasm_env *env, char *str)
{
  int fd;
  int len;
  char *tmp;
  char *name;

  len = ft_strlen(str) - 4;
  tmp = ft_strndup(str, len);
  name = ft_strnew(len + 2);
  name = ft_strcpy(name, tmp);
  name = ft_strcat(name, ".s");
  fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  env->fd = fd;
}

int main(int argc, char **argv)
{
  int fd;
  char *line;
  t_dasm_env env;

  if ((fd = open(argv[1], O_RDONLY)) == -1)
//    dasm_error(SOURCE_ERR, argv[1]);
  line = NULL;
  create_file_cor(&env, argv[1]);
  while (get_next_line(fd, &line))
  {
    parse_cor(&env, line);
    ft_memdel((void*)&line);
  }
  argv[1][ft_strlen(argv[1]) - 4] = '\0';
  ft_printf("Writting output file to %s.s\n", argv[1]);
  return (0);
}
