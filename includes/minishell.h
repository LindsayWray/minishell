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
#include <errno.h>
#include <limits.h>

t_token		*lexer(char *str);
t_cmd_lst	*parser(t_token *token);
void		exec(t_cmd_lst *cmd_lst);
char		*get_path(char *command);
int		    set_redirection(int *input_fd, int *output_fd, t_subcmd subcmd);
void		dup_fd(int input_fd, int output_fd);
void		expand(t_cmd_lst *cmd_lst);
void	    skip_over_quotes(char * str, int *i);
char		*add_string(char *str1, char *str2);
char		*quote_handler(char *cmd);
char		**ft_envlst_to_array(t_env_lst *env_lst);
t_env_lst	*ft_getenv(char **env);
t_env_lst	*ft_get_env_var(char *key);
char		*get_env_value(char *key);
void		free_cmdlst(void);

//builtins
int         ft_export(char **cmd, int fd_out);
int         export_exists(char *key, char *value);
int         export_exists_key(char *key);
int 		ft_export_add(char *key, char *value);
int         ft_unset(char **cmd, int fd_out);
int         ft_env(char **cmd, int fd_out);
int         ft_cd(char **cmd, int fd_out);
int         ft_pwd(char **cmd, int fd_out);
int         ft_echo(char **cmd, int fd_out);
int         ft_exit(char **cmd, int fd_out);
#endif