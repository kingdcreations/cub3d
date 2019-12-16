/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_handlefile.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 10:13:39 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 15:26:03 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	parse_fc(t_file *file, char *line, char **param)
{
	file->param = param;
	if (ft_splitac(param) == 3)
	{
		if (line[0] == 'F')
		{
			if (file->f[0] != -1)
				ft_error(file, "Floor not well formatted.", -1);
			file->f[0] = ft_atoi(param[0]);
			file->f[1] = ft_atoi(param[1]);
			file->f[2] = ft_atoi(param[2]);
		}
		else
		{
			if (file->c[0] != -1)
				ft_error(file, "Ceiling not well formatted.", -1);
			file->c[0] = ft_atoi(param[0]);
			file->c[1] = ft_atoi(param[1]);
			file->c[2] = ft_atoi(param[2]);
		}
		ft_checkfc(file, line);
	}
	else
		ft_error(file, "Floor or ceiling not well formatted.", -1);
}

void	parse_tex(t_file *file, char *line, char **param)
{
	if (line[0] == 'R' && (file->rx != -1 || file->ry != -1
	|| ft_splitac(param) != 3 || (file->rx = ft_atoi(param[1])) <= 0
	|| (file->ry = ft_atoi(param[2])) <= 0))
	{
		free(line);
		ft_splitfree(param);
		ft_error(file, "Resolution not well formatted.", 0);
	}
	if (ft_splitac(param) == 2)
	{
		if (line[0] == 'N' && line[1] == 'O')
			file->no = ft_doubledef(file, file->no, param, line);
		else if (line[0] == 'S' && line[1] == 'O')
			file->so = ft_doubledef(file, file->so, param, line);
		else if (line[0] == 'W' && line[1] == 'E')
			file->we = ft_doubledef(file, file->we, param, line);
		else if (line[0] == 'E' && line[1] == 'A')
			file->ea = ft_doubledef(file, file->ea, param, line);
		else if (line[0] == 'S')
			file->s = ft_doubledef(file, file->s, param, line);
	}
}

void	parse_01(t_file *file, char *line, char **param)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (line[0] == '1' || file->mapmode == 1)
	{
		file->mapmode = 1;
		while (line[i++])
			if (line[i] != ' ')
				j++;
		if (file->mapw == 0)
			file->mapw = j;
		if (file->mapw != j)
		{
			free(line);
			ft_splitfree(param);
			ft_error(file, "Map must be a rectangle.", 0);
		}
		file->maph++;
		file->strmap = ft_strjoin(file->strmap, line);
	}
	else if (line[0] == '0' && file->mapmode == 1)
		ft_error(file, "Map must be closed.", 0);
}

int		ft_parse(t_file *file, char *line)
{
	char	**param;

	if (!(param = ft_split(line, ' ')))
		return (0);
	parse_tex(file, line, param);
	if (line[0] == '\0' && file->mapmode == 1)
		file->mapmode = 2;
	parse_01(file, line, param);
	if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
	{
		ft_splitfree(param);
		param = ft_split(line + 1, ',');
		parse_fc(file, line, param);
	}
	ft_splitfree(param);
	return (0);
}
