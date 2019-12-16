/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:40:22 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 14:20:45 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
}

static int	ft_issep(char s, char c)
{
	if (s == c)
		return (1);
	if (s == '\0')
		return (1);
	return (0);
}

static void	ft_strtosplit(char *tab, const char *str, char c)
{
	int i;

	i = 0;
	while (ft_issep(str[i], c) == 0)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
}

static int	ft_splittotab(char **tab, const char *str, char charset)
{
	int i;
	int len;
	int word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (ft_issep(str[i], charset) == 1)
			i++;
		else
		{
			len = 0;
			while (ft_issep(str[i + len], charset) == 0)
				len++;
			if (!(tab[word] = (char *)malloc(sizeof(char) * (len + 1))))
			{
				ft_free(tab, word);
				return (0);
			}
			ft_strtosplit(tab[word++], str + i, charset);
			i += len;
		}
	}
	return (1);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		nb;

	if (!s)
		return (NULL);
	i = 0;
	nb = 0;
	while (s[i])
	{
		if (ft_issep(s[i + 1], c) == 1 && ft_issep(s[i], c) == 0)
			nb++;
		i++;
	}
	if (!(tab = (char **)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	tab[nb] = NULL;
	if (ft_splittotab(tab, s, c))
		return (tab);
	else
	{
		free(tab);
		return (NULL);
	}
}
