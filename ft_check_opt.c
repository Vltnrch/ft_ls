/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/18 16:30:29 by vroche            #+#    #+#             */
/*   Updated: 2015/10/20 21:45:21 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_usage(char c)
{
	ft_dprintf(2, "ls: illegal option -- %c\n", c);
	ft_dprintf(2, "usage: ft_ls [-Ralrt1] [file ...]\n");
	exit(EXIT_FAILURE);
}

static void	ft_check_opt_part(char *str, t_opt *opt)
{
	while (*str)
	{
		if (*str == 'R')
			opt->rec = 1;
		else if (*str == 'a')
			opt->a = 1;
		else if (*str == 'l')
			opt->l = 1;
		else if (*str == 'r')
			opt->rev = 1;
		else if (*str == 't')
			opt->t = 1;
		else if (*str == '1')
			;
		else
			ft_usage(*str);
		str++;
	}
}

t_opt		*ft_check_opt(char ***argv)
{
	t_opt	*opt;
	char	**av;

	av = *argv;
	av++;
	if (!(opt = (t_opt *)ft_memalloc(sizeof(t_opt))))
		ft_perror_exit("ft_memalloc");
	while (*av && **av == '-' && *(*av + 1) != 0)
	{
		(*av)++;
		if (**av != '-' || (**av == '-' && *(*av + 1) != 0))
			ft_check_opt_part(*av, opt);
		else
		{
			av++;
			*argv = av;
			return (opt);
		}
		av++;
	}
	*argv = av;
	return (opt);
}
