/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 12:08:41 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status);
static t_tree_node	*parse_cmd_list(t_tree_node *current,
						t_parser_status *parser_status);
static t_tree_node	*parse_statement(t_token *token);

// * end of declarations //

t_tree_node	*parse(void)
{
	t_tree_node				*tree;
	t_parser_status			parser_status;

	parser_initialize(&parser_status);
	tree = parse_cmd_list(parse_atomic_exp(&parser_status), &parser_status);
	tree->is_parse_tree_root = e_true;
	if (parser_status.status == ERROR)
	{
		put_error(PARSE_ERROR, 258, &parser_status);
		free_tree(&tree);
		tokenizer_free(); // * meglio se la chiamo nello entry point di minishell insieme a parser_free
		parser_initialize(&parser_status);
	}
	tree_to_string(tree);
	return (tree);
}

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token			*token;
	t_tree_node		*parenthesised;

	token = atomic_exp_parsing_init(parser_status);
	if (!token)
		return (NULL);
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == '(')
	{
		parser_status->open.parenthesis += 1;
		parenthesised = parse_cmd_list(
			parse_atomic_exp(parser_status), parser_status);
		parenthesised->launch_subshell = e_true;
		return (parenthesised);
	}
	else
		return (parse_statement(token));
}

static t_tree_node	*parse_cmd_list(t_tree_node *current,
	t_parser_status *parser_status)
{
	t_token		*token;
	t_tree_node	*new_subtree;
	// t_bool		launch_subshell;

	token = cmd_list_parsing_init(parser_status);
	if (!token)
		return (current);
	else if (token->token_id == e_OPERATOR)
	{
		// launch_subshell = e_false;
		new_subtree = parse_cmd_list(
				new_tree_node(current, parse_operator(token), e_false,
					parse_atomic_exp(parser_status)),
				parser_status);
		new_subtree->launch_subshell = e_false; //launch_subshell;
		new_subtree->is_parse_tree_root = e_false;
		if (new_subtree->right == NULL)
			set_error(&(parser_status->status));
		return (new_subtree);
	}
	else
	{
		set_error(&(parser_status->status));
		return (current);
	}
}

		// if (*((char *)token->token_val) == '|' && *(((char *)token->token_val) + 1) != '|')
		// 	launch_subshell = e_true;
		// else
		// 	launch_subshell = e_false;

static t_tree_node	*parse_statement(t_token *token)
{
	t_node_content	*node_content;

	token = parse_statement_init(token, &node_content);
	if (!token)
		return (new_tree_node(NULL, node_content, e_false, NULL));
	else
	{
		if (token->token_id == e_CMD_NAME
			|| token->token_id == e_CMD_ARG)
			return (new_tree_node(NULL,
						parse_simple_command(token, node_content), e_false,
						NULL));
		else if (token->token_id == e_ENV_VAR_DECL
				|| token->token_id == e_ENV_VAR_UNSET)
			return (new_tree_node(NULL,
						parse_env_statement(token, node_content), e_false,
						NULL));
		ft_free(node_content->in_redir.file_name);
		ft_free(node_content->out_redir.file_name);
		free(node_content);
		return (NULL);
	}
}
