/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 12:02:01 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 19:34:01 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

void	print_operator(t_tree_node *node)
{
	if (node->content->operator_node.operator == e_PIPE)
		printf(" | ");
	if (node->content->operator_node.operator == e_OR)
		printf(" || ");
	if (node->content->operator_node.operator == e_AND)
		printf(" && ");
}

void	print_simple_command(t_tree_node *node)
{
	printf(GREEN "[cmd_name: %s, cmd_arg: %s, infile: %s, outfile: %s]" RESET, node->content->simple_cmd.cmd_name, node->content->simple_cmd.cmd_args, node->content->in_redir.file_name, node->content->out_redir.file_name);
}

void	print_env_statement(t_tree_node *node)
{
	// t_bindings	*binding;

	if (node->content->env_decl.set)
		printf(GREEN "[EXPORT : infile: %s, outfile: %s " RESET, node->content->in_redir.file_name, node->content->out_redir.file_name);
	else
		printf(GREEN "[UNSET : infile: %s, outfile: %s " RESET, node->content->in_redir.file_name, node->content->out_redir.file_name);
	// binding = node->content->env_decl.bindings;
	// while (binding)
	// {
	// 	printf("\tconcat: %d, var_name: %s, var_val: %s\t", binding->concat_mode, binding->var_name, binding->var_val);
	// 	binding = binding->next;
	// }
	// printf("]");
}
	// printf("(");
	// tree_to_string(root->left);
	// if (root->content->content_type == OPERATOR)
	// 	printf("OPERATOR ");
	// if (root->content->content_type == SIMPL_CMD)
	// 	printf("SIMPLE_CMD ");
	// if (root->content->content_type == ENV_STATEMENT)
	// 	printf("ENV_STATEMENT ");
	// tree_to_string(root->right);
	// printf(")");

void	tree_to_string(t_tree_node *root)
{
	if (!root)
	{
		// printf("HERE\n");
		return ;
	}
	// if (root->launch_subshell == e_true)
	// 	printf("new subshell ");
	if (root->launch_subshell == e_true)
		printf(">nsb >");
	if (root->content->content_type == REDIR)
		printf("REDIR_ONLY ");
	else if (root->content->content_type == SIMPL_CMD)
		printf("SIMPLE_CMD "); //print_simple_command(root);
	else if (root->content->content_type == ENV_STATEMENT)
		printf("ENV_STATEMENT "); //print_env_statement(root);
	else
	{
		printf("(");
		tree_to_string(root->left);
		printf("OPERATOR "); //print_operator(root);
		tree_to_string(root->right);
		printf(")");
	}
	printf("\n");
}
