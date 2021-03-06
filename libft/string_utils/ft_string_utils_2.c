/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 09:45:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/16 16:46:48 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief this function checks wether the number of occurrences
 * of the first quote occurring in the input string is balanced
 * 
 * @param str 
 * @return t_bool 
 */
t_bool	ft_quote_occurrence_balanced(char *str)
{
	// char	quote;
	// int		occurrences;

	return (
			str_number_occurrences(str, '\'') % 2 == 0
		&&
			str_number_occurrences(str, '"') % 2 == 0
	);
	// if (!str)
	// 	return (e_true);
	// quote = take_starting_quote(str);
	// if (quote != '"' && quote != '\'')
	// 	return (e_true);
	// occurrences = 0;
	// while (*str)
	// {
	// 	if (*str == quote)
	// 		occurrences += 1;
	// 	str++;
	// }
	// return (occurrences % 2 == 0);
}

char	take_starting_quote(char *str)
{
	if (!str)
		return ('\0');
	while (*str)
	{
		if (*str == '"')
			return ('"');
		if (*str == '\'')
			return ('\'');
		str++;
	}
	return ('\0');
}

char	*ft_itoa(int nbr)
{
	char	digit[2];

	if (nbr == INT_MIN)
		return (ft_strjoin(
				ft_itoa(INT_MIN / 10),
				ft_itoa((INT_MAX % 10) + 1), e_true, e_true));
	if (nbr < 0)
		return (ft_strjoin("-", ft_itoa(-nbr), e_false, e_true));
	digit[0] = (nbr % 10) + 48;
	digit[1] = '\0';
	if (nbr > 9)
		return (ft_strjoin(ft_itoa(nbr / 10), digit, e_true, e_false));
	return (ft_strjoin("", digit, e_false, e_false));
}
