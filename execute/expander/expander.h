/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:53:32 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/07 09:45:14 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// * standard libraries //
# include <dirent.h>

// * user defined modules //
# include "../executor.h"
# include "expander_utils/expander_utils.h"
# include "../../utils/ft_utils.h"

char	*expander(char *args);

#endif