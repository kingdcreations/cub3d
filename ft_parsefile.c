/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsefile.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 14:28:46 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 10:51:47 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	parsemap(t_file *file)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	i = 0;
	s = file->strmap;
	file->map = malloc(sizeof(int *) * file->maph);
	j = 0;
	while (j < file->maph)
	{
		k = 0;
		file->map[j] = malloc(sizeof(int) * file->mapw);
		while (k < file->mapw)
		{
			while (s[i] == ' ')
				i++;
			file->map[j][k] = s[i] - '0';
			ft_maperror(file, s[i], j, k);
			k++;
			i++;
		}
		j++;
	}
}

int		get_file(t_file *file, char *name)
{
	int		fd;
	int		res;
	char	*line;

	res = 1;
	fd = open(name, O_RDONLY);
	while (res)
	{
		if ((res = get_next_line(fd, &line, file)) == -1)
			ft_error(file, "File not found.", 0);
		file->line = line;
		if (line[0] == 'R' || line[0] == 'S' || !line[0]
		|| !(ft_strncmp(line, "SO", 2)) || !(ft_strncmp(line, "WE", 2))
		|| !(ft_strncmp(line, "EA", 2)) || !(ft_strncmp(line, "NO", 2))
		|| line[0] == 'F' || line[0] == 'C' || line[0] == '1')
			ft_parse(file, line);
		else
		{
			free(line);
			ft_error(file, "Corrupted file", 0);
		}
		free(line);
	}
	close(fd);
	return (1);
}

void	ft_parsefile(t_file *file, char *filename)
{
	initfile(file);
	get_file(file, filename);
	parsemap(file);
	ft_checkerror(file);
	if (!file->pl)
		ft_error(file, "Player not found.", file->maph);
	if (file->rx > 2560)
		file->rx = 2560;
	if (file->ry > 1440)
		file->ry = 1440;
}
