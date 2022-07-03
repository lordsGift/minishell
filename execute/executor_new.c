/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 09:39:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:15:53 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute(t_tree_node *parse_tree)
{
	execute_rec(parse_tree, STDIN_FILENO, STDOUT_FILENO);
}

void	execute_rec(t_tree_node *root, int in, int out)
{
	if (root->launch_subshell == e_true)
		execute_subshell(root, in, out);
	else
		execute_in_shell(root, in, out);
}

void	execute_subshell(t_tree_node *root, int in, int out)
{
	int	subshell_pid;
	int	subshell_exit_status;

	root->launch_subshell = e_false;
	subshell_pid = fork();
	if (!subshell_pid)
	{
		execute_rec(root, in, out);
		if (!WIFEXITED(g_env.last_executed_cmd_exit_status)
			|| WEXITSTATUS(g_env.last_executed_cmd_exit_status))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	waitpid(subshell_pid, &subshell_exit_status, 0);
	if (!WIFEXITED(subshell_exit_status) || WEXITSTATUS(subshell_exit_status))
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	else
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

void	execute_in_shell(t_tree_node *root, int in, int out)
{
	if (root->content->content_type == SIMPL_CMD
		|| root->content->content_type == ENV_STATEMENT
		|| root->content->content_type == REDIR)
		execute_simple_statement(root, in, out);
	else if (root->content->content_type == OPERATOR
			&& root->content->operator_node.operator == e_PIPE)
		execute_pipe_statement(root, in, out);
	else if (root->content->content_type == e_AND
			&& root->content->operator_node.operator == e_AND)
		execute_and_statement(root, in, out);
	else if (root->content->content_type == e_OR
			&& root->content->operator_node.operator == e_OR)
		execute_or_statement(root, in, out);
	else
		exit(EXIT_FAILURE);
}

	// // * in
	// if (root->content->in_redir.file_name)
	// {
	// 	if (in != STDIN_FILENO)
	// 		close(in);
	// 	in = open(root->content->in_redir.file_name, O_RDONLY);
	// }
	// if (in != STDIN_FILENO)
	// {
	// 	dup2(in, STDIN_FILENO);
	// 	close(in);
	// }
	// // * out
	// if (root->content->out_redir.file_name)
	// {
	// 	if (out != STDOUT_FILENO)
	// 		close(out);
	// 	if (root->content->out_redir.append_mode == e_true)
	// 		out = open(root->content->out_redir.file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	// 	else
	// 		out = open(root->content->out_redir.file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	// }
	// if (out != STDOUT_FILENO)
	// {
	// 	dup2(out, STDOUT_FILENO);
	// 	close(out);
	// }
	// // * redir END












