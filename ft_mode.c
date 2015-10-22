/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/21 19:14:52 by vroche            #+#    #+#             */
/*   Updated: 2015/10/21 19:16:33 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_acl(char *str, t_dirs *dirs)
{
	acl_t		acl;
	ssize_t		xattr;
	acl_entry_t	dummy;

	acl = NULL;
	xattr = 0;
	acl = acl_get_link_np(dirs->name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(dirs->name, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		str[0] = '@';
	else if (acl != NULL)
		str[0] = '+';
	else
		str[0] = ' ';
}

static void	ft_mode_s(char *new, short st_mode)
{
	if (S_ISREG(st_mode))
		*new = '-';
	else if (S_ISDIR(st_mode))
		*new = 'd';
	else if (S_ISBLK(st_mode))
		*new = 'b';
	else if (S_ISCHR(st_mode))
		*new = 'c';
	else if (S_ISFIFO(st_mode))
		*new = 'p';
	else if (S_ISLNK(st_mode))
		*new = 'l';
	else if (S_ISSOCK(st_mode))
		*new = 's';
	else
		*new = '?';
}

char		*ft_mode(short st_mode, t_dirs *dirs)
{
	char	*new;

	if (!(new = ft_strnew(11)))
		return (NULL);
	ft_mode_s(new++, st_mode);
	*new++ = ((st_mode & S_IRUSR) ? 'r' : '-');
	*new++ = ((st_mode & S_IWUSR) ? 'w' : '-');
	if (st_mode & S_ISUID)
		*new++ = (st_mode & 0100) ? 's' : 'S';
	else
		*new++ = ((st_mode & S_IXUSR) ? 'x' : '-');
	*new++ = ((st_mode & S_IRGRP) ? 'r' : '-');
	*new++ = ((st_mode & S_IWGRP) ? 'w' : '-');
	if (st_mode & S_ISGID)
		*new++ = (st_mode & 0010) ? 's' : 'S';
	else
		*new++ = ((st_mode & S_IXGRP) ? 'x' : '-');
	*new++ = ((st_mode & S_IROTH) ? 'r' : '-');
	*new++ = ((st_mode & S_IWOTH) ? 'w' : '-');
	if (st_mode & S_ISVTX)
		*new++ = (st_mode & 0100) ? 't' : 'T';
	else
		*new++ = ((st_mode & S_IXOTH) ? 'x' : '-');
	ft_acl(new, dirs);
	return (new - 10);
}
