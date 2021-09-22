#ifndef TYPES_H
# define TYPES_H
# define COMMAND_NOT_FOUND 127

typedef enum s_type
{
	VOID,
	WORD,
	PIPE,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	HEREDOC,
	APPEND
}	t_type;

typedef struct s_token
{
	t_type type;
	char *content;
	struct s_token *next;
	struct s_token *previous;
}	t_token;

typedef struct s_subcmd
{
	t_type	in_type;
	char	*in_file;
	t_type	out_type;
	char	*out_file;
	char	**cmd;
}	t_subcmd;

typedef struct s_cmd_lst
{
	t_subcmd	subcmd;
	struct s_cmd_lst *next;
	struct s_cmd_lst *previous;
}	t_cmd_lst;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*previous;
	struct s_env	*next;
}	t_env_lst;

typedef struct s_data
{
	t_cmd_lst	*cmd_lst;
	t_env_lst	*env_lst;
	int			*pids;
}	t_data;

#endif