/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 18:59:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char		*get_decorated_cwd(char *cwd);

static t_status	complete_line(char **command);
static t_status	read_completed_line(char **command,
					pid_t line_completion_prompt_pid,
					int line_channel[], int line_size_channel[]);

// * end of static declarations //


//									perche gli altri non devono essere gestiti
// TODO :-> fare line completion anche con {`, &, pipe, (, \} --> {&, pipe, (}
// * alert 1
// ! readline library function always takes terminating '\n' off,
// ! so a new line is actually EOF (\0)
// * alert 2
// ! non empty means NO CHAR present except '\0'
// ! (i.e.: a string full of spaces is not considered empty!)
/**
 * @brief This function tries to read a line until a non-empty/non-pending 
 * one is entered or ctr + D is hit.
 * Here_Doc is managed too.
 * 
 * @param prompt the prompt to be displayed with the readline library function.
 * @param free_prompt true iff prompt needs to be freed after use
 * @return char* the next line read
 * (except here_doc content which is put in a hidden file for later use)
 */
char	*ft_readline(char *prompt, t_bool free_prompt)
{
	char		*command;
	t_status	prompt_status;

	prompt_status = OK;
	command = readline(prompt);
	if (!command)
	{
		free(prompt);
		exit_shell(g_env.last_executed_cmd_exit_status, e_true);
	}
	else if (*command == '\0')
	{
		free(command);
		return (ft_readline(prompt, free_prompt));
	}
	else if (e_true == ft_pending_pipe(command)
			|| e_true == ft_pending_logical_op(command))
	{
		prompt_status = complete_line(&command);
	}
	if (e_true == here_doc_line(command))
	{
		prompt_status = here_doc_read(command);
	}
	ft_add_history(command);
	if (free_prompt)
		free(prompt);
	if (prompt_status == ERROR)
	{
		free(command);
		command = NULL;
	}
	return (command);
}

static t_status	complete_line(char **command)
{
	t_status	outcome;
	pid_t		line_cont_prompt_pid;
	int			line_channel[2];
	int			line_size_channel[2];

	pipe(line_channel);
	pipe(line_size_channel);
	line_cont_prompt_pid = fork();
	if (!line_cont_prompt_pid)
	{
		line_continuation_prompt(COMPLETE_LINE, line_channel, line_size_channel);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		outcome = read_completed_line(command, line_cont_prompt_pid,
					line_channel, line_size_channel);
		signal(SIGINT, sig_handler);
	}
	close_pipe(line_channel);
	close_pipe(line_size_channel);
	return (outcome);
}

static t_status	read_completed_line(char **command,
					pid_t line_completion_prompt_pid,
					int line_channel[], int line_size_channel[])
{
	char		*continuation;
	size_t		continuation_len;
	int			line_completion_prompt_exit_status;
	t_status	outcome;

	close(line_channel[1]);
	close(line_size_channel[1]);
	waitpid(line_completion_prompt_pid, &line_completion_prompt_exit_status, 0);
	if (!WIFEXITED(line_completion_prompt_exit_status)
		|| WEXITSTATUS(line_completion_prompt_exit_status))
	{
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		outcome = ERROR;
	}
	else
		outcome = OK;
	read(line_size_channel[0], &continuation_len, sizeof(continuation_len));
	continuation = (char *) malloc((continuation_len + 1) * sizeof(char));
	read(line_channel[0], continuation, continuation_len * sizeof(char));
	continuation[continuation_len] = '\0';
	*command = ft_strjoin(*command, continuation, e_true, e_true);
	return (outcome);
}

/**
 * @brief Get the current working directory (not with full path)
 * 
 * @return char* 
 */
char	*get_current_working_directory(void)
{
	char	*abs_path;
	char	*cwd;
	size_t	last_slash_idx;
	size_t	idx;

	abs_path = getcwd(NULL, PATH_MAX);
	if (0 == ft_strcmp(abs_path, env_handler(BINDING_GET_VALUE, "HOME")))
		return (ft_strjoin(
			ft_itoa(g_env.last_executed_cmd_exit_status), 
			" in 📁:-" CYAN " ~ " RESET,
			e_true, e_false)
		);
	last_slash_idx = 0;
	idx = -1;
	while (abs_path[++idx])
		if (abs_path[idx] == '/')
			last_slash_idx = idx;
	cwd = get_decorated_cwd(abs_path + last_slash_idx);
	free(abs_path);
	return (cwd);
}

// ! cwd must not to be freed as it is a shifted pointer !! 
/**
 * @brief this function returns the current working directory from the shifted
 * absolute path pointer (char *) stored in cwd.
 * 
 * @param cwd char * -: the current working directory (cwd) full path
 * shifted to the last occurrence of a '/' character
 * @return char* -: the current working directory name,
 * colored and decorated with a funny emoji
 */
static char	*get_decorated_cwd(char *cwd)
{
	char	*color;

	if (g_env.last_executed_cmd_exit_status == EXIT_SUCCESS)
		color = GREEN;
	else
		color = RED;
	return (
		ft_strjoin(
			ft_itoa(g_env.last_executed_cmd_exit_status),
			ft_strjoin
			(
				" in 📁:-",
				ft_strjoin
				(
					ft_strjoin(color, cwd, e_false, e_false),
					": " RESET,
					e_true,
					e_false
				),
				e_false,
				e_true
			),
			e_true, e_true
		)
	);
}
