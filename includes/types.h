#ifndef TYPES_H
#define TYPES_H

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

#endif