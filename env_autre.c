/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_autre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 18:42:09 by mgrimald          #+#    #+#             */
/*   Updated: 2015/05/18 14:28:10 by mgrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

char	**prefabriced_env(void)
{
	char	**env;
	char	*str;

	env = (char**)ft_tabnew(5);
	env[0] = ft_strdup("PATH=/bin:/usr/bin");
	env[1] = ft_strdup("SHLVL=0");
	env[2] = ft_strdup("USER=John Doe");
	env[3] = ft_strdup("PROMPT_MESS=that's not nice");
	str = getcwd(NULL, 0);
	env[4] = ft_strjoin("PWD=", str);
	ft_strdel(&str);
	env[5] = NULL;
	return (env);
}

char	**get_addr_str_env(char *head)
{
	int		i;
	char	**env;
	int		len;

	len = ft_strlen(head);
	env = get_env(NULL, 0);
	i = 0;
	while (env != NULL && env[i] != NULL)
	{
		if (ft_strncmp(env[i], head, len) == 0 && env[i][len] == '=')
			return (env + i);
		i++;
	}
	return (NULL);
}

char	*get_str_env(char *head)
{
	char	**str;
	char	*tmp;

	if ((str = get_addr_str_env(head)) == NULL || *str == NULL)
		return ("");
	if ((tmp = ft_strchr(*str, '=')) == NULL)
		return ("");
	return (tmp + 1);
}

void	sh_increase_shlvl(void)
{
	char	**astr;
	char	*str;
	int		i;

	str = get_str_env("SHLVL");
	astr = (char**)ft_tabnew(4);
	astr[0] = ft_strdup("setenv");
	astr[1] = ft_strdup("SHLVL");
	if (str == NULL || str[0] == '\0')
		astr[2] = ft_strdup("1");
	else
	{
		i = ft_atoi(str);
		if (i <= 0)
			i = 0;
		astr[2] = ft_itoa(i + 1);
	}
	sh_setenv(astr);
	free_tab(astr);
}

char	**get_env(char **env, char action)
{
	static char	**ret = NULL;

	if ((action == 'f' || action == 'r') && ret != NULL)
	{
		free_tab(ret);
		ret = NULL;
	}
	if (ret == NULL && (action == 'r' || action == 's'))
	{
		if ((env == NULL || *env == NULL) && action == 's')
			ret = prefabriced_env();
		else if (env != NULL && *env != NULL)
			ret = ft_tabdup(env);
	}
	return (ret);
}
