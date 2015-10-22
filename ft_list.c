/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/18 16:39:00 by vroche            #+#    #+#             */
/*   Updated: 2015/10/21 19:07:25 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_sort_list(t_dirs **dirs, t_dirs *new, \
							int (*f)(t_dirs *, t_dirs *))
{
	t_dirs	*prev;
	t_dirs	*tmp;

	tmp = *dirs;
	prev = tmp;
	while (tmp && f(tmp, new) < 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == *dirs)
	{
		*dirs = new;
		new->next = tmp;
	}
	else if (!tmp)
		prev->next = new;
	else
	{
		prev->next = new;
		new->next = tmp;
	}
}

static void	ft_list_add_part(t_dirs **dirs, t_dirs *new, t_opt *opt)
{
	if (opt->t)
	{
		if (!opt->rev)
			ft_sort_list(dirs, new, ft_sortmtime);
		else
			ft_sort_list(dirs, new, ft_sortmtime_rev);
	}
	else if (!opt->rev)
		ft_sort_list(dirs, new, ft_sortname);
	else
		ft_sort_list(dirs, new, ft_sortname_rev);
}

void		ft_list_dirs_add(t_dirs **dirs, struct dirent *dirent, \
								t_opt *opt, char *rec)
{
	t_dirs	*new;

	if (!(new = (t_dirs *)ft_memalloc(sizeof(t_dirs))))
		ft_perror_exit("ft_memalloc");
	ft_memcpy(&(new->dirent), dirent, sizeof(struct dirent));
	if (rec)
		new->name = ft_cat_dir(rec, new->dirent.d_name);
	else
		new->name = new->dirent.d_name;
	if (lstat(new->name, &(new->lst)) == -1)
	{
		ft_perror(new->dirent.d_name);
		free(new);
		return ;
	}
	if (stat(new->name, &(new->st)) == -1)
		ft_memcpy(&(new->st), &(new->lst), sizeof(struct stat));
	ft_list_add_part(dirs, new, opt);
}

void		ft_list_args_add(t_dirs **dirs, t_opt *opt, char *name)
{
	t_dirs	*new;

	if (!(new = (t_dirs *)ft_memalloc(sizeof(t_dirs))))
		ft_perror_exit("ft_memalloc");
	new->name = name;
	ft_memcpy(new->dirent.d_name, name, ft_strlen(name));
	if (lstat(new->name, &(new->lst)) == -1)
	{
		ft_perror(new->dirent.d_name);
		free(new);
		return ;
	}
	if (stat(new->name, &(new->st)) == -1)
		ft_memcpy(&(new->st), &(new->lst), sizeof(struct stat));
	ft_list_add_part(dirs, new, opt);
}
