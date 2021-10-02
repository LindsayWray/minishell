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
#include <signal.h>
#include <termios.h>

t_token		*lexer(char *str);
t_cmd_lst	*parser(t_token *token);
int			syntax_error(t_token *token_lst, t_cmd_lst *cmd_lst);
void		exec(t_cmd_lst *cmd_lst);
char		*get_path(char *command);
int		    set_redirection(int *input_fd, int *output_fd, t_subcmd subcmd);
void		dup_fd(int input_fd, int output_fd);
int			invalid_io_file_char(char c);
void		expand(t_cmd_lst *cmd_lst);
void	    skip_over_quotes(char * str, int *i);
char		*add_string(char *str1, char *str2);
char		*quote_handler(char *cmd);
char 		**complex_cmd(char **cmd);
char		**ft_envlst_to_array(t_env_lst *env_lst);
t_env_lst	*ft_getenv(char **env);
t_env_lst	*ft_get_env_var(char *key);
char		*get_env_value(char *key);
void		refresh(void);
void		free_cmdlst(t_cmd_lst *cmd_lst);
void		lst_clear(t_token **lst);
void		clean_all(void);
void		received_signal(int signal);
void		signal_from_child(int signal);
void		signal_from_heredoc(int signal);
void		received_signal(int signal);

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