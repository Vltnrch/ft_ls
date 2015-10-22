/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 17:37:00 by vroche            #+#    #+#             */
/*   Updated: 2015/10/21 19:43:59 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_display_l_part(t_dirs *dirs, struct stat *st, t_maxlen *maxlen)
{
	dirs->mode = ft_mode(st->st_mode, dirs);
	dirs->uid = getpwuid(st->st_uid);
	dirs->gid = getgrgid(st->st_gid);
	ft_printf("%s %*lld ", dirs->mode, maxlen->link, st->st_nlink);
	if (dirs->uid)
		ft_printf("%-*s  ", maxlen->uid, dirs->uid->pw_name);
	else
		ft_printf("%-*d  ", maxlen->uid, st->st_uid);
	if (dirs->gid)
		ft_printf("%-*s ", maxlen->gid, dirs->gid->gr_name);
	else
		ft_printf("%-*d ", maxlen->gid, st->st_gid);
}

static void	ft_display_l(t_dirs *dirs, t_maxlen *maxlen)
{
	char		*ct;
	time_t		tmp;
	struct stat	*st;

	if (dirs->st.st_mode != dirs->lst.st_mode)
		st = &(dirs->lst);
	else
		st = &(dirs->st);
	ft_display_l_part(dirs, st, maxlen);
	if (*(dirs->mode) == 'b' || *(dirs->mode) == 'c')
		ft_printf("%4d,%4d ", FT_MAJOR(st->st_rdev), FT_MINOR(st->st_rdev));
	else if (*(dirs->mode) == 's')
		ft_printf(" %*ld ", maxlen->dev ? 8 : maxlen->size, 0);
	else
		ft_printf(" %*ld ", maxlen->dev ? 8 : maxlen->size, st->st_size);
	tmp = st->st_mtime;
	ct = ctime(&(st->st_mtime));
	if (time(&(tmp)) - st->st_mtime > 15768000 || time(&(tmp)) < st->st_mtime)
		ft_printf("%-7.7s %-4.4s ", ct + 4, ct + 20);
	else
		ft_printf("%-12.12s ", ct + 4);
}

static void	ft_display_real(t_dirs *dirs, t_opt *opt, t_maxlen *maxlen, int arg)
{
	char	*buff;

	while (dirs)
	{
		if (arg || (opt->a && *(dirs->dirent.d_name) == '.') \
						|| *(dirs->dirent.d_name) != '.')
		{
			if (opt->l == 1)
				ft_display_l(dirs, maxlen);
			ft_putstr(dirs->dirent.d_name);
			if (opt->l == 1 && (S_ISLNK(dirs->st.st_mode) \
						|| S_ISLNK(dirs->lst.st_mode)))
			{
				if (!(buff = ft_strnew(1024)))
					ft_perror_exit("ft_strnew");
				if (readlink(dirs->name, buff, 1024) < 0)
					ft_perror("readlink");
				ft_printf(" -> %s", buff);
			}
			ft_printf("\n");
		}
		ft_dirs_next(&dirs, arg);
	}
}

void		ft_display(t_dirs *dirs, t_opt *opt, int arg)
{
	t_maxlen	*maxlen;

	maxlen = NULL;
	if (opt->l == 1)
		maxlen = ft_display_prepare(dirs, opt, arg);
	ft_display_real(dirs, opt, maxlen, arg);
}
