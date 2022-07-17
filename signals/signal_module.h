/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_module.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:00:29 by evento            #+#    #+#             */
/*   Updated: 2022/07/17 12:16:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MODULE_H
# define SIGNAL_MODULE_H

// * user defined types //
# include "signal_types.h"

/**
 * @brief handler for all
 * 
 * @param signum 
 */
void	sig_handler(int signum);
void	sig_handling_set(t_sig_handling_opcode opcode);
void	shell_executor_handler(int signum);
void	line_completion_prompt_sig_handler(int signum);
void	here_doc_prompt_sig_handler(int signum);

#endif