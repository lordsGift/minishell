/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:36:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/24 15:16:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tok_utils.h"

size_t	scan_simple_command(char *command_line, size_t offset,
			t_token **token_list)
{
	offset = scan_cmd_name(command_line, offset, token_list);
	offset = scan_inout_file(command_line, offset, token_list); // * forse non necessario !
	offset = scan_cmd_arg(command_line, offset, token_list);
	offset = scan_inout_file(command_line, offset, token_list); // * forse non necessario !
	return (offset);
}

size_t	scan_prologue(char *command_line, size_t offset,
			t_token **token_list)
{
	offset = scan_parenthesis(command_line, offset, token_list);
	offset = scan_inout_file(command_line, offset, token_list);
	offset = scan_invariants(command_line, offset);
	return (offset);
}

size_t	scan_epilogue(char *command_line, size_t offset,
			t_token **token_list)
{
	offset = scan_inout_file(command_line, offset, token_list);
	offset = scan_parenthesis(command_line, offset, token_list);
	offset = scan_operator(command_line, offset, token_list);
	return (offset);
}
