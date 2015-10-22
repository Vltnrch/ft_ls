/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/18 16:33:07 by vroche            #+#    #+#             */
/*   Updated: 2015/10/20 20:39:46 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_sortname(t_dirs *a, t_dirs *b)
{
	return (ft_strcmp(a->name, b->name));
}

int	ft_sortname_rev(t_dirs *a, t_dirs *b)
{
	return (ft_strcmp(b->name, a->name));
}

int	ft_sortmtime(t_dirs *a, t_dirs *b)
{
	struct stat *st1;
	struct stat *st2;

	if (a->st.st_mode != a->lst.st_mode)
		st1 = &(a->lst);
	else
		st1 = &(a->st);
	if (b->st.st_mode != b->lst.st_mode)
		st2 = &(b->lst);
	else
		st2 = &(b->st);
	if (st2->st_mtime > st1->st_mtime)
		return (1);
	else if (st2->st_mtime < st1->st_mtime)
		return (-1);
	else if (st2->st_mtimespec.tv_nsec > st1->st_mtimespec.tv_nsec)
		return (1);
	else if (st2->st_mtimespec.tv_nsec < st1->st_mtimespec.tv_nsec)
		return (-1);
	else
		return (ft_sortname(a, b));
}

int	ft_sortmtime_rev(t_dirs *a, t_dirs *b)
{
	struct stat *st1;
	struct stat *st2;

	if (a->st.st_mode != a->lst.st_mode)
		st1 = &(a->lst);
	else
		st1 = &(a->st);
	if (b->st.st_mode != b->lst.st_mode)
		st2 = &(b->lst);
	else
		st2 = &(b->st);
	if (st2->st_mtime > st1->st_mtime)
		return (-1);
	else if (st2->st_mtime < st1->st_mtime)
		return (1);
	else if (st2->st_mtimespec.tv_nsec > st1->st_mtimespec.tv_nsec)
		return (-1);
	else if (st2->st_mtimespec.tv_nsec < st1->st_mtimespec.tv_nsec)
		return (1);
	else
		return (ft_sortname_rev(a, b));
}
