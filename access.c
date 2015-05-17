/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 20:27:22 by mgrimald          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2015/05/16 23:39:01 by mgrimald         ###   ########.fr       */
=======
/*   Updated: 2015/05/14 13:05:07 by mgrimald         ###   ########.fr       */
>>>>>>> origin/master
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <sys/types.h>
#include <sys/stat.h>

static int	file_dir_link(struct stat s, char *path)
{
	int		ret;
	char	*tmp;
	int		len;

	ret = 0;
	if (S_ISDIR(s.st_mode) != 0)
		ret = 2;
	else if (S_ISREG(s.st_mode) != 0)
		ret = 1;
	else if (S_ISLNK(s.st_mode))
	{
		tmp = ft_strnew(1024);
		if ((len = readlink(path, tmp, 1023)) == -1)
			exit (-1);//error();
		tmp[len] = '\0';
		ft_putendl("gestion of the symlinks has not been implented yet");
		ft_putstr(path);
		ft_putstr(" redirect to ");
		ft_putendl(tmp);
		ft_strdel(&tmp);
		ret = 3;
	}
	return (ret);
}

static int	try_access(struct stat s, char *path)
{
	int		ret;

	ret = -1;
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			ret = file_dir_link(s, path);
		else
		{
			ft_putstr("permission denied: ");
			ft_putendl(path);
		}
	}
	else
	{
		ft_putstr("no such file or directory: ");
		ft_putendl(path);
	}
	return (ret);
}

int			check_file(char *path)
{
	struct stat	s;
	char		*f;
	char		*pwd;
	int			ret;

	if (*path != '/')
	{
		pwd = getcwd(NULL, 0);
		f = ft_strnew(ft_strlen(path) + ft_strlen(pwd) + 2);
<<<<<<< HEAD
		ft_strcpy(f, pwd);
		if (pwd[ft_strlen(pwd) - 1] != '/')
			ft_strcat(f, "/");
		f = ft_strcat(f, path);
=======
		f = ft_strcat(ft_strcat(ft_strcpy(f, pwd), "/"), path);
>>>>>>> origin/master
		ft_memdel((void**)&pwd);
	}
	else
		f = ft_strdup(path);
	ret = -1;
	stat(f, &s);
	ret = try_access(s, f);
	ft_memdel((void**)&f);
	return (ret);
}
