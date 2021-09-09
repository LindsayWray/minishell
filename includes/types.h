#ifndef TYPES_H
#define TYPES_H

typedef enum s_type
{
	WORD,
	PIPE,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	HEREDOC,
	APPEND
}	t_type;

// typedef struct s_token
// {
// 	t_type type;
// 	char *content;
// }	t_token;

typedef struct s_token
{
	//t_token token;
	t_type type;
	char *content;
	struct s_token *next;
	struct s_token *previous;
}	t_node;

#endif