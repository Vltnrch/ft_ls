/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_prepare.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/21 19:20:11 by vroche            #+#    #+#             */
/*   Updated: 2015/10/21 19:43:08 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_prepare_part1(t_maxlen *maxlen, struct stat *st)
{
	size_t		len;

	if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode))
		maxlen->dev = 1;
	if (maxlen->link < (len = ft_strlen(ft_lltoa((size_t)st->st_nlink))))
		maxlen->link = len;
	if (getpwuid(st->st_uid))
	{
		if (maxlen->uid < (len = ft_strlen(getpwuid(st->st_uid)->pw_name)))
			maxlen->uid = len;
	}
	else
	{
		if (maxlen->uid < (len = ft_strlen(ft_lltoa((size_t)st->st_uid))))
			maxlen->uid = len;
	}
}

static void	ft_prepare_part2(t_maxlen *maxlen, struct stat *st)
{
	size_t		len;

	if (getgrgid(st->st_gid))
	{
		if (maxlen->gid < (len = ft_strlen(getgrgid(st->st_gid)->gr_name)))
			maxlen->gid = len;
	}
	else
	{
		if (maxlen->gid < (len = ft_strlen(ft_lltoa((size_t)st->st_gid))))
			maxlen->gid = len;
	}
	if (getgrgid(st->st_gid) && maxlen->gid < \
					(len = ft_strlen(getgrgid(st->st_gid)->gr_name)))
		maxlen->gid = len;
	if (maxlen->size < (len = ft_strlen(ft_lltoa((size_t)st->st_size))))
		maxlen->size = len;
}

t_maxlen	*ft_display_prepare(t_dirs *dirs, t_opt *opt, int arg)
{
	t_maxlen	*maxlen;
	struct stat	*st;

	if (!(maxlen = (t_maxlen *)ft_memalloc(sizeof(t_maxlen))))
		ft_perror_exit("ft_memalloc t_maxlen");
	while (dirs)
	{
		if (arg || (opt->a && *(dirs->dirent.d_name) == '.') \
				|| *(dirs->dirent.d_name) != '.')
		{
			if (dirs->st.st_mode != dirs->lst.st_mode)
				st = &(dirs->lst);
			else
				st = &(dirs->st);
			ft_prepare_part1(maxlen, st);
			ft_prepare_part2(maxlen, st);
			maxlen->total += st->st_blocks;
			maxlen->cache = 1;
		}
		ft_dirs_next(&dirs, arg);
	}
	if (!arg && maxlen->cache)
		ft_printf("total %llu\n", maxlen->total);
	return (maxlen);
}
