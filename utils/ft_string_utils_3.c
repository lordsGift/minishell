/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:01:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 15:03:50 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"


t_bool	ft_isspace(char c)
{
	return (c == 32 || (c >= '\t' && c <= '\r'));
}