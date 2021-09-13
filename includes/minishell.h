#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include "utils.h"
#include "types.h"

t_token		*lexer(char *str);
t_cmd_lst	*parser(t_token *token);
int	exec    (t_cmd_lst *cmd_lst, char **env);
char		*get_path(char *command);
void		set_redirection(int input_fd, int output_fd, t_subcmd subcmd);
void	    run_command(char **cmd, char **env);

#endif