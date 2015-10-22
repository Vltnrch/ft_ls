/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/18 15:21:29 by vroche            #+#    #+#             */
/*   Updated: 2015/10/21 20:11:35 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_ls_arg_part1(t_dirs *tmp, int *disp, t_opt *opt)
{
	while (tmp)
	{
		if ((tmp->st.st_mode & S_IFMT) != S_IFDIR \
			|| (S_ISLNK(tmp->lst.st_mode) && opt->l))
		{
			ft_display(tmp, opt, 1);
			*disp = 1;
		}
		tmp = tmp->next;
	}
}

static void	ft_ls_arg_part2(t_dirs *dirs, int *disp, t_opt *opt, int i)
{
	while (dirs)
	{
		if (i > 1 && (dirs->st.st_mode & S_IFMT) == S_IFDIR)
			ft_printf("%s%s:\n", *disp ? "\n" : "", dirs->name);
		if ((dirs->st.st_mode & S_IFMT) == S_IFDIR \
			&& !((dirs->st.st_mode & S_IFMT) != S_IFDIR \
				|| (S_ISLNK(dirs->lst.st_mode) && opt->l)))
		{
			ft_ls_dir(dirs->name, opt, NULL);
			*disp = 1;
		}
		dirs = dirs->next;
	}
}

static void	ft_ls_arg(char **av, t_opt *opt)
{
	struct stat st;
	t_dirs		*dirs;
	int			i;
	int			disp;

	dirs = NULL;
	i = 0;
	disp = 0;
	while (*av)
	{
		if (lstat(*av, &st) == -1)
			ft_perror(**av == 0 ? "fts_open" : *av);
		else
			ft_list_args_add(&dirs, opt, *av);
		av++;
		i++;
	}
	ft_ls_arg_part1(dirs, &disp, opt);
	ft_ls_arg_part2(dirs, &disp, opt, i);
}

static void	ft_tri_arg(char **av)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (av[i])
	{
		j = i + 1;
		while (av[j])
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	t_opt	*opt;

	if (ac >= 1)
		opt = ft_check_opt(&av);
	else
		opt = NULL;
	if (!*av)
		ft_ls_dir(".", opt, NULL);
	else
	{
		ft_tri_arg(av);
		ft_ls_arg(av, opt);
	}
}
