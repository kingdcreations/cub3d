/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_managefile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:43:40 by tmarcon           #+#    #+#             */
/*   Updated: 2020/08/03 11:50:16 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"

void	initfile(t_file *file)
{
	file->mapmode = 0;
	file->rx = -1;
	file->ry = -1;
	file->pl = 0;
	file->no = NULL;
	file->nextl = NULL;
	file->so = NULL;
	file->we = NULL;
	file->ea = NULL;
	file->s = NULL;
	file->f[0] = -1;
	file->f[1] = -1;
	file->f[2] = -1;
	file->c[0] = -1;
	file->c[1] = -1;
	file->c[2] = -1;
	file->mapw = 0;
	file->maph = 0;
	file->strmap = ft_strdup("");
	file->map = NULL;
}

void	ft_free(t_file *file, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(file->map[i++]);
	free(file->nextl);
	free(file->map);
	free(file->no);
	free(file->so);
	free(file->we);
	free(file->ea);
	free(file->s);
	free(file->strmap);
	free(file);
}

void	ft_splitfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str[i]);
	str[i] = NULL;
	free(str);
}

int		ft_splitac(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}
