/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/21 19:48:09 by vroche            #+#    #+#             */
/*   Updated: 2015/10/22 14:41:19 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls_dir_part(DIR *odir, t_opt *opt, char *dir)
{
	t_dirent	*dirent;
	t_dirs		*dirs;

	dirs = NULL;
	while (odir && (dirent = readdir(odir)) != NULL)
	{
		if (*(dirent->d_name) != 0)
			ft_list_dirs_add(&dirs, dirent, opt, dir);
	}
	ft_display(dirs, opt, 0);
	if (opt->rec)
	{
		while (dirs)
		{
			if (ft_strcmp(dirs->dirent.d_name, ".") == 0 \
				|| ft_strcmp(dirs->dirent.d_name, "..") == 0)
				;
			else if ((dirs->st.st_mode & S_IFMT) == S_IFDIR \
				&& dirs->st.st_mode == dirs->lst.st_mode \
				&& ((opt->a && *(dirs->dirent.d_name) == '.') \
					|| *(dirs->dirent.d_name) != '.'))
				ft_ls_dir(dir, opt, dirs->dirent.d_name);
			dirs = dirs->next;
		}
	}
}

void			ft_ls_dir(char *dir, t_opt *opt, char *rec)
{
	DIR	*odir;

	if (rec)
		dir = ft_cat_dir(dir, rec);
	odir = opendir(dir);
	if (rec)
		ft_printf("\n%s:\n", dir);
	if (!odir)
	{
		if (rec)
			ft_perror(rec);
		else
			ft_perror(dir);
	}
	ft_ls_dir_part(odir, opt, dir);
	if (rec)
		free(dir);
	if (odir)
		closedir(odir);
}
