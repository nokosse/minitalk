/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:16:34 by kvisouth          #+#    #+#             */
/*   Updated: 2023/03/10 15:33:43 by kvisouth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include "libft/inc/libft.h"
#include "libft/inc/ft_printf.h"

int     is_str_numeric(char *str);
char	*str_append_c(char *str, char c);

#endif