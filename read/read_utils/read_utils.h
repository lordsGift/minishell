/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:54:53 by earendil          #+#    #+#             */
/*   Updated: 2022/06/16 17:27:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_UTILS_H
# define READ_UTILS_H

# include "../read.h"

// * user defined functions

void	*lexer_input_handling(void *arg, char **input_string_ref,
			int *offset, t_op_code op_code);
void	*lexer_token_handling(void *arg, t_token **cur_token,
			t_op_code op_code);

#endif
