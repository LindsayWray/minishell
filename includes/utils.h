#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include <unistd.h>
#include "types.h"

// *** Linked List Handlers
t_token	    **lst_add_back(t_token **list, t_token *new);
void	    cmd_lst_add_back(t_cmd_lst **list, t_cmd_lst *new);
t_token	    *lst_new(char *content, t_type type);
t_cmd_lst	*cmd_lst_new(t_subcmd subcmd);
t_token	    *lst_last(t_token *last);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *last);
t_env_lst	*env_lst_last(t_env_lst *last);
t_env_lst	*env_lst_new(char *key, char *value);
void	    env_lst_add_back(t_env_lst **list, t_env_lst *new);
int     	lst_size(t_cmd_lst *cmd_lst);
void	    lst_clear(t_token **lst);
void	    cmd_lst_clear(t_cmd_lst **cmd_lst);
// ***
t_env_lst   *ft_getenv(char **env);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
int		    ft_strlen(char *str);
char	    **ft_split(char const *s, char c);
char	    *ft_strdup(char *src);
char	    *ft_strjoin(char const *s1, char const *s2);
int     	ft_streql(char *s1, char *s2);
void	    ft_putstr_fd(char *str, int fd);
int         ft_cinstr(const char *str, char c);
void	    ft_split_free(char **str);
int	        ft_isalpha(int c);
int         ft_isdigit(int c);
int	        ft_isalnum_str(char *str);
char		*ft_itoa(int n);
char		*ft_shiftstr_right(char *str);
char		*ft_shiftstr_left(char *str);
int			ft_dprintf(int fd, const char *format, ...);

#endif