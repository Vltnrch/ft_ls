/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/18 13:37:12 by vroche            #+#    #+#             */
/*   Updated: 2015/10/22 14:41:08 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/types.h>
# include <pwd.h>
# include <sys/acl.h>
# include <sys/xattr.h>

# define FT_MAJOR(dev) ((unsigned int) (((dev) >> 24) & 0xff))
# define FT_MINOR(dev) ((unsigned int) ((dev) & 0xffffff))

typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_opt
{
	int					l;
	int					rec;
	int					a;
	int					rev;
	int					t;
}						t_opt;

typedef struct			s_maxlen
{
	size_t				link;
	size_t				uid;
	size_t				gid;
	size_t				size;
	int					cache;
	blkcnt_t			total;
	int					dev;
}						t_maxlen;

typedef struct			s_dirs
{
	char				*name;
	char				*mode;
	t_passwd			*uid;
	t_group				*gid;
	t_dirent			dirent;
	t_stat				st;
	t_stat				lst;
	struct s_dirs		*next;
}						t_dirs;

t_opt					*ft_check_opt(char ***av);

void					ft_display(t_dirs *dirs, t_opt *opt, int arg);

t_maxlen				*ft_display_prepare(t_dirs *dirs, t_opt *opt, int arg);

void					ft_list_dirs_add(t_dirs **dirs, struct dirent *dirent, \
										t_opt *opt, char *rec);
void					ft_list_args_add(t_dirs **dirs, t_opt *opt, char *name);

void					ft_ls_dir(char *dir, t_opt *opt, char *rec);

void					ft_perror_exit(const char *str);
char					*ft_cat_dir(char *dir1, char *dir2);
void					ft_perror(const char *str);
void					ft_dirs_next(t_dirs **dirs, int arg);

char					*ft_mode(short st_mode, t_dirs *dirs);

int						ft_sortname(t_dirs *a, t_dirs *b);
int						ft_sortname_rev(t_dirs *a, t_dirs *b);
int						ft_sortmtime(t_dirs *a, t_dirs *b);
int						ft_sortmtime_rev(t_dirs *a, t_dirs *b);

#endif
