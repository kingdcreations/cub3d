/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_errorfile.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 14:46:23 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 14:42:24 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	ft_checkfc(t_file *file, char *line)
{
	int	i;
	int comma;

	i = 0;
	comma = 0;
	while (line[i])
		if (line[i++] == ',')
			comma++;
	if (comma != 2)
		ft_error(file, "Floor or ceiling not well formatted", -1);
	if (file->f[0] < -1 || file->f[1] < -1 || file->f[2] < -1
	|| file->c[0] < -1 || file->c[1] < -1 || file->c[2] < -1
	|| file->f[0] > 255 || file->f[1] > 255 || file->f[2] > 255
	|| file->c[0] > 255 || file->c[1] > 255 || file->c[2] > 255)
		ft_error(file, "Floor or ceiling not well formatted", -1);
}

void	ft_checkerror(t_file *file)
{
	if (file->rx < 0 || file->rx < 0 || !file->no || !file->so
	|| !file->we || !file->ea || !file->s || file->f[0] < 0
	|| file->c[0] < 0 || file->f[1] < 0 || file->c[1] < 0
	|| file->f[2] < 0 || file->c[2] < 0 || !file->mapmode)
	{
		ft_putstr_fd("Error\nMising element in .cub file.", 2);
		ft_free(file, file->maph);
		exit(EXIT_SUCCESS);
	}
}

void	ft_error(t_file *file, char *s, int i)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	if (i == -1)
	{
		free(file->line);
		ft_splitfree(file->param);
	}
	ft_free(file, i);
	exit(EXIT_SUCCESS);
}

void	ft_maperror(t_file *file, char c, int j, int k)
{
	if (!(c == '0' || c == '1' || c == '2'
	|| c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		ft_error(file, "Bad character into map parsing.", j + 1);
	if (file->map[j][k] == 0 &&
	(k == 0 || k == file->mapw - 1 || j == 0 || j == file->maph - 1))
		ft_error(file, "Map must be closed.", j + 1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!file->pl)
		{
			file->pl = c;
			file->plx = k + 1;
			file->ply = j + 1;
		}
		else
			ft_error(file, "Map must contain one single player.", j + 1);
	}
}

char	*ft_doubledef(t_file *file, char *var, char **param, char *line)
{
	if (var == NULL)
		return (ft_strdup(param[1]));
	else
	{
		free(line);
		ft_splitfree(param);
		ft_error(file, "Element setup twice.", 0);
	}
	return (NULL);
}
