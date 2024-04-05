/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:07 by tmazitov          #+#    #+#             */
/*   Updated: 2024/04/05 12:54:58 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum bool
{
	false, 
	true 
}		t_bool;

size_t		ft_strlen(char *str);
int			ft_atoi(char *str);
int			ft_isdigit(int ch);
char		*ft_itoa(int n);
char		*ft_strchr(char *str, int ch);
int			ft_strcmp(char *str1, char *str2);
long long	now(void);
long long	diff(long long t1, long long t2);

#endif