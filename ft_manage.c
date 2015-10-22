/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/18 15:42:37 by vroche            #+#    #+#             */
/*   Updated: 2015/10/21 19:31:13 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_perror_exit(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*ft_cat_dir(char *dir1, char *dir2)
{
	char	*tmp;
	char	*tmp2;

	if (!ft_strcmp(dir1, "/"))
		tmp = ft_strdup(dir1);
	else
		tmp = ft_strjoin(dir1, "/");
	tmp2 = ft_strjoin(tmp, dir2);
	free(tmp);
	return (tmp2);
}

void	ft_perror(const char *str)
{
	char	*tmp;

	tmp = ft_strjoin("ls: ", str);
	perror(tmp);
	if (!ft_strcmp("fts_open", str))
		exit(EXIT_FAILURE);
}

void	ft_dirs_next(t_dirs **dirs, int arg)
{
	if (arg)
		*dirs = NULL;
	else
		*dirs = (*dirs)->next;
}
