/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:05:27 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 10:12:02 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_TYPES_H
# define EXECUTOR_TYPES_H

# include <sys/wait.h>

typedef struct e_branch
{
	pid_t	pid;
	int		exit_status;
}	t_branch;

#endif