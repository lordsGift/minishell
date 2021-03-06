/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:36:03 by earendil          #+#    #+#             */
/*   Updated: 2022/07/19 18:54:56 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

static void	take_next_star_segment_boundaries(char *str,
				size_t *start, size_t *end);
static void	take_next_dollar_segment_boundaries(char *str,
				size_t *start, size_t *end);
static char	*get_segment(char *str,
				size_t start, size_t end);
static char	*get_suffix(char *str, size_t cutting_index);

void	expansion_split(t_special_char special_char,
				char *args,
				char **next_segment_ref,
				char **post_ref)
{
	size_t	start_of_segment;
	size_t	end_of_segment;

	if (special_char == STAR)
		take_next_star_segment_boundaries(args,
			&start_of_segment, &end_of_segment);
	else if (special_char == DOLLAR)
		take_next_dollar_segment_boundaries(args,
			&start_of_segment, &end_of_segment);
	*next_segment_ref = get_segment(args, start_of_segment, end_of_segment);
	*post_ref = get_suffix(args, end_of_segment + 1);
}

/**
 * 
 * ```
 * this function sets the boundaries for the next segment in the string.
 * (i.e.: the next quoted sequence delimited by blanks or end/start of string)
 * N.B.: a quoted sequence is a word (string which does not contain spaces),
 * or a string surrounded by quotes)
 * ``` 
 */
static void	take_next_star_segment_boundaries(char *str,
				size_t *start, size_t *end)
{
	size_t	offset;

	if (!str || !(*str))
		return ;
	*start = 0;
	// if (str[0] == '"' || str[0] == '\'')
	// {
	// 		offset = skip_past_char(str, 0 + 1, str[0], +1);
	// 		printf("offset at end of \" is: %zu\n", offset);
	// }
	// else if (e_true == ft_isspace(str[0]))
	// 	offset = skip_consecutive_chars(str, 0, str[0], +1);
	if (e_true == ft_isspace(str[0]))
		offset = skip_consecutive_chars(str, 0, str[0], +1);
	else
	{
		offset = 0; //skip_past_char(str, 0, ' ', +1);//skip_consecutive_chars(str, 0, ' ', +1);
		while (str[offset] == '"' || str[offset] == '\'')
		{
				offset = skip_past_char(str, offset + 1, str[offset], +1);
				// printf("offset at end of \" is: %zu\n", offset);
		}
		while (e_true)
		{
			if (str[offset] == '\0'
				|| e_true == ft_isspace(str[offset]))//bash_control_character(str[offset]))
				break ;
			offset++;
		}
	}
	*end = offset - 1;
	return ;
}

static void	take_next_dollar_segment_boundaries(char *str,
				size_t *start, size_t *end)
{
	size_t	offset;
	char	additional_delimiter;

	if (!str || !str[0])
		return ;
	{
		*start = 0;
		if (str[0] == '"' || str[0] == '\'')
				*end = skip_past_char(str, 1, str[0], +1) - 1;
		else if (str[0] == '$' && str[1] == '*')
			*end = 1;
		else if (str[0] == '$' && str[1] == '$')
			*end = 1;
		else
		{
			// offset = skip_consecutive_chars(str, 0, ' ', +1);
			offset = 0;
			while (str[offset + 1]
					&& str[offset + 1] != '*'
					&& str[offset + 1] != '$'
					&& e_false == bash_control_character(str[offset + 1]))
			{
				offset++;
			}
			*end = offset;
		}
	}
}

static char	*get_segment(char *str,
				size_t start, size_t end)
{
	return (ft_strcpy(NULL, str + start, end - start + 1));
}

static char	*get_suffix(char *str, size_t cutting_index)
{
	size_t	len_str;
	size_t	first_non_space_char_index;

	len_str = ft_strlen(str);
	if (cutting_index > len_str - 1)
		return (NULL);
	first_non_space_char_index
		= skip_consecutive_chars(str, cutting_index, ' ', +1);
	if (first_non_space_char_index > len_str - 1
		|| cutting_index > len_str - 1)
		return (NULL);
	else
		return (ft_strcpy(NULL, str + cutting_index,
					len_str - cutting_index));
}
