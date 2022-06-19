/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 12:30:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char		*get_decorated_cwd(char *cwd);

// * alert 1
// ! readline library function always takes terminating '\n' off,
// ! so a new line is actually EOF (\0)
// * alert 2
// ! non empty means NO CHAR present except '\0'
// ! (i.e.: a string full of spaces is not considered empty!)
/**
 * @brief This function tries to read a line until a non empty-quote balanced 
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
	char	*command;

	command = readline(prompt);
	if (asked_for_termination(command))
		exit_shell(EXIT_SUCCESS, e_true);
	else if (*command == '\0')
	{
		free(command);
		return (ft_readline(prompt, free_prompt));
	}
	else if (e_false == ft_quote_occurrence_balanced(command))
	{
		command = prompt_complete_line(command);
	}
	if (e_true == here_doc_line(command))
	{
		here_doc_read(here_doc_take_delimiter(command));
	}
	ft_add_history(command);
	if (free_prompt)
		free(prompt);
	return (command);
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
	return (
		ft_strjoin
		(
			"📁:-",
			ft_strjoin
			(
				ft_strjoin(MAGENTA, cwd, e_false, e_false),
				": " RESET,
				e_true,
				e_false
			),
			e_false,
			e_true
		)
	);
}