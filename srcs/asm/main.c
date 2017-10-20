/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/10/19 04:59:42 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char *take_word(char *str)
{
  int a;
  int len;
  char  *word;

  a = 0;
  len = 0;
  while (str[len] && str[len] != ' ' && str[len] != '\t' && str[len] != SEPARATOR_CHAR)
    ++len;
  if (!(word = (char*)malloc(sizeof(char) * len + 1)))
    exit (0);
  word[len] = '\0';
  while (a != len)
  {
    word[a] = str[a];
    ++a;
  }
  word[a] = '\0';
  return (word);
}

char  *moove_on_line(char *line)
{
  int a;

  a = 0;
  while (ft_isalpha(line[a]) || ft_isdigit(line[a]))
    ++a;
  while(line[a] == ' ' || line[a] == '\t')
    ++a;
  return (line + a);
}

int   detect_arg(char *line)
{
  int a;

  a = 0;
  if (line[a] == 'r')
    return (REG_CODE);
  if (line[a] == LABEL_CHAR || ft_isdigit(line[a]))
    return (IND_CODE);
  if (line [a] == DIRECT_CHAR)
    return (DIR_CODE);
  return (0);
}

char *concat_opcode(char *ocp, int arg)
{
  if (!ocp)
  {
    if (!(ocp = ft_strnew(0)))
      asm_error(MALLOC_ERR, NULL);
  }
    if (arg == REG_CODE)
      ft_strcat(ocp, "01");
    else if (arg == DIR_CODE)
      ft_strcat(ocp, "10");
    else if (arg == IND_CODE)
      ft_strcat(ocp, "11");
  return (ocp);
}

void write_ocp(t_asm_env *env, char *ocp)
{
  char *str;
  char res;

  while (ft_strlen(ocp) != 8)
    ft_strcat(ocp, "00");
  str = ft_convert_base(ocp, "01", "0123456789");
  res = ft_atoi(str);
  ft_putchar_fd(res, env->fd);
}

int  goto_nextarg(char *line)
{
  int a;

  a  = 0;
  while (line[a] && line[a] != SEPARATOR_CHAR)
    ++a;
  if (line[a] == SEPARATOR_CHAR)
    ++a;
  while(line[a] && (line[a] == ' ' || line[a] == '\t'))
    ++a;
  return (a);
}

void  write_reg(t_asm_env *env, char *line)
{
  int a;
  char reg;
  char *str;

  a = 0;
  line++;
  while (line[a] && ft_isdigit(line[a]))
    ++a;
  str = ft_strndup(line, a);
  reg = ft_atoi(str);
  ft_putchar_fd(reg, env->fd);
}

int  reverse_int(int nb)
{
return (nb & 0x000000FFU) << 24 | (nb & 0x0000FF00U) << 8 |
       (nb & 0x00FF0000U) >> 8 | (nb & 0xFF000000U) >> 24;
}

short reverse_short(short nb)
{
    return ((nb & 0xFFU) << 8 | (nb & 0xFF00U) >> 8);
}

int  dist_label(t_asm_env *env, char *label)
{
  t_tab_labs *tmp;

  tmp = env->labs;
  while (ft_strcmp(label, tmp->label))
    tmp = tmp->next;
//  printf("label find = '%s' with pos = %d\n", tmp->label, tmp->nb_oct);
  return (tmp->nb_oct - env->bytes);
}

void  write_dir(t_asm_env *env, char *line, int i)
{
  int a;
  int dir4o;
  short dir2o;
  char  *str;
  char *label;
  int nb;

  a = 0;
  line++;
  nb = ft_atoi(line);
   if (line[a] != LABEL_CHAR)
   {
     while (line[a] && ft_isdigit(line[a]))
       ++a;
     str = ft_strndup(line, a);
   }

  if (i == 1 || i == 2 || i == 6 || i == 7 || i == 8 || i == 14)
  {
    if (line[a] == LABEL_CHAR)
    {
      label = take_word(line + 1);
      dir4o = dist_label(env, label);
    }
    else
      dir4o = nb;
    dir4o = reverse_int(dir4o);
    write(env->fd, &dir4o, 4);
  }
  else
  {
    if (line[a] == LABEL_CHAR)
    {
      label = take_word(line + 1);
      dir2o = dist_label(env, label);
    }
    else
      dir2o = nb;
    dir2o = reverse_short(dir2o);
    write(env->fd, &dir2o, 2);
  }
}

void  write_ind(t_asm_env *env, char *line)
{
  int a;
  short ind;
  char *str;

  a = 0;
  if (ft_isdigit(*line))
  {
    while (line[a] && ft_isdigit(line[a]))
      ++a;
    str = ft_strndup(line, a);
    ind = ft_atoi(str);
  }
  else
  {
    str = take_word(line + 1);
    ind = dist_label(env, str);
  }
  ind = reverse_short(ind);
  write(env->fd, &ind, 2);
//  print_labs_lst(env->labs);
}

void  write_args(t_asm_env *env, char *line, int i)
{
  int a;
  int res;

  res = 0;
  a = 0;
  while (line[a])
  {
    res = detect_arg(line + a);
    if (res == REG_CODE)
      write_reg(env, line + a);
    else if (res == DIR_CODE)
      write_dir(env, line + a, i);
    else if (res == IND_CODE)
      write_ind(env, line + a);
    a += goto_nextarg(line + a);
  }

}

void  op_ocp(t_asm_env *env, int i, char *line)
{
  int  a;
  int res;
  char *ocp;

  a = 0;
  res = 0;
  ocp = NULL;
  ft_putchar_fd(i + 1, env->fd);
  line = moove_on_line(line);
  while (line[a])
  {
    res = detect_arg(line + a);
    ocp = concat_opcode(ocp, res);
    a += goto_nextarg(line + a);
  }
  write_ocp(env, ocp);
  write_args(env, line, i + 1);
}

void  op_no_ocp(t_asm_env *env, int i, char *line)
{
  int  a;
  int res;

  a = 0;
  res = 0;
  ft_putchar_fd(i + 1, env->fd);
  line = moove_on_line(line);
  while (line[a])
  {
    res = detect_arg(line + a);
    a += goto_nextarg(line + a);
  }
  write_args(env, line, i + 1);
}

int analyse_args(int oct, char *line, int i)
{
  if (*line == 'r')
    oct += 1;
  else if (*line == '%')
  {
    if ((i == 0 || i == 1 || i == 5 || i == 6 || i == 7 || i == 13))
      oct += 4;
    else
      oct += 2;
  }
  else if (*line == ':' || ft_isdigit(*line))
    oct += 2;
  return (oct);
}

int  analyse(int oct, char *line, int i)
{
  int a;

  a = 0;
//  printf("'%s'\n", line);
  while (line[a] && line[a] != '\n')
  {
    while (line[a] == ':')
      ++a;
    while (line[a] && (line[a] == '-' || ft_isalpha(line[a]) || ft_isdigit(line[a])))
      ++a;
    while (line[a] && (line[a] == ' ' || line[a] == '\t'))
      ++a;
    if (line[a] == ',')
      ++a;
    oct = analyse_args(oct, line + a, i);
    if (line[a] == ',')
      a++; // pour la vrigule tmts
    if (line[a] == '%')
      a++;
    if (line[a] == '#')
      return (oct);
  }
    return (oct);
}

int find_op(t_asm_env *env, char *word, char *line, int printmode)
{
  int i;
  int tmp;
  int oct;

  oct = 1;
  i = 0;
  tmp = 0;
  while (op_tab[i].inst)
  {
    if (!ft_strcmp(word, op_tab[i].inst))
    {
      if (!op_tab[i].need_ocp)
      {
        tmp = i;
        if (printmode)
          op_no_ocp(env, i, line);
      }
      else
      {
        tmp = i;
        ++oct;
        if (printmode)
          op_ocp(env, i, line);
      }
      oct = analyse(oct, line, tmp);
    }
    ++i;
  }
  return (oct);
}

void parse(t_asm_env *env, char *line, int printmode)
{
  int   a;
  char  *word;

  if (line && line[0] != '#')
  {
    a = 0;
    while (line[a] == ' ' || line[a] == '\t')
      ++a;
    if (!line[a] || line[a] == '#')
      return ;
    word = take_word(line + a);
    if (!ft_strcmp(word, NAME_CMD_STRING) || !ft_strcmp(word, COMMENT_CMD_STRING))
      write_header(env, line, printmode);
      else if (word[ft_strlen(word) - 1] == LABEL_CHAR)
      {
//    bullshit pour tester si le compteur d'octets fonctionne
//    on recuperera les label et leur postition soon
        if (!printmode)
          create_label(&env->labs , env->bytes, line + a);
        //  env->labs = create_label(&env->labs , env->bytes, line + a);
        while(ft_isalpha(line[a]) || ft_isdigit(line[a]))
          ++a;
        while (line[a] == ' ' || line[a] == '\t' || line[a] == ':')
          ++a;
        free(word);
        word = take_word(line + a);
        if (*word)
          env->bytes += find_op(env, word, line + a, printmode);
        }
      else
      {
        env->bytes += find_op(env, word, line + a, printmode);
      }
      free(word);
    }
//    printf("bytes = %d\n", env->bytes);
}

void  create_file(t_asm_env *env, char *str)
{
  int fd;
  int len;
  char *tmp;
  char *name;

  len = ft_strlen(str) - 2;
  tmp = ft_strndup(str, len);
  name = ft_strnew(len + 2);
  name = ft_strcpy(name, tmp);
  name = ft_strcat(name, ".cor");
  fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  env->fd = fd;
}

int main (int argc, char **argv)
{
  int   fd;
  int   fd2;
  char  *line;
  t_asm_env env;

  if ((fd = open(argv[1], O_RDONLY)) == -1)
    asm_error(SOURCE_ERR, argv[1]);
  printf("fd = %d\n", fd);
  line = NULL;
  env.bytes = 1;
  while (get_next_line(fd, &line))
  {
   // printf("%s\n", line);
    parse(&env, line, 0);
    ft_memdel((void*)&line);
  }

//  printf("\n\nFinal bytes number = %d\n\n", env.bytes - 1);
  env.size = env.bytes - 1;
  create_file(&env, argv[1]);
  fd2 = open(argv[1], O_RDONLY);
  line = NULL;
  env.bytes = 1;
  while (get_next_line(fd2, &line))
  {
  //  printf("line = '%s'\n", line);
    parse(&env, line, 1);
    ft_memdel((void*)&line);
  }
  argv[1][ft_strlen(argv[1]) - 2] = '\0';
  ft_printf("Writting output program to %s.cor\n", argv[1]);
  return (0);
}
