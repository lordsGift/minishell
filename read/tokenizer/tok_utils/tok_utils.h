/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:04:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/21 09:51:04 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_UTILS_H
# define TOK_UTILS_H

#include "../tokenizer.h"

// * user defines TYPES

# ifndef TOK_TYPES
#  define TOK_TYPES
typedef enum e_op_code
{
	e_RETURN_TOK,
	e_STORE_NXT_TOK,
	e_STORE_STR,
	e_RETURN_CUR_STR,
	e_ADVANCE_STR,
	e_CLEAN
}	t_op_code;

typedef enum e_token_id
{
	e_IN_FILE,
	e_OUT_FILE,
	e_ARG,
	e_OPT,
	e_EXPORT,
	e_ENV_VAR_NAME,
	e_SHELL_VAR_NAME,
	e_FILENAME,
	e_USR_PROGRAM,
	e_DOUBLE_QUOTE,
	e_SINGLE_QUOTE,
	e_PARENTHESIS,
	e_OPERATOR,
	e_REDIRECT,
	e_LOGICAL,
	e_ASSIGN,
	e_PIPE,
	e_NONE
}	t_token_id;

typedef struct s_token
{
	t_token_id	token_id;
	void		*token_val;
}	t_token;

typedef struct s_var_content
{
	char	*name;
	char	*val;
}	t_var_content;

# endif

// * user defined functions

void	*lexer(void *arg, t_op_code op_code);
// void	*lexer_input_handling(void *arg, char **input_string_ref,
// 			int *offset, t_op_code op_code);
// void	*lexer_token_handling(void *arg, t_token **cur_token,
// 			t_op_code op_code);

int		scan_var(char *str, t_token_id var_type);
t_token	*scan_var_set_cursor(char *str, char **cursor, t_token_id var_type);
char	*scan_var_name(char *cursor, char **name);
char	*scan_var_value(char *cursor, char **value);

int	scan_spaces(char *str);
int	scan_invariant_quotes(char *str);
int	scan_alternate_invariant_spaces_quotes(char *str);

#endif