/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_save.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/24 11:01:42 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 16:53:13 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	ft_saver(t_win *c3d)
{
	int fd;

	rayshoot(c3d);
	fd = open("output.bmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_write_header(c3d, fd);
	ft_mirror_img(c3d, fd);
	ft_free(c3d->file, c3d->file->maph);
	free(c3d->mlx);
	free(c3d);
}

void	ft_mirror_img(t_win *c3d, int fd)
{
	int		i;
	int		j;
	int		na;
	int		*test;
	void	*load;

	load = mlx_new_image(c3d->mlx, c3d->file->rx, c3d->file->ry);
	test = (int *)mlx_get_data_addr(load, &na, &na, &na);
	j = 0;
	while (j < c3d->file->rx)
	{
		i = 0;
		na = c3d->file->ry - 1;
		while (i < c3d->file->ry)
		{
			test[na * c3d->file->rx + j] = c3d->imgbuf[i * c3d->file->rx + j];
			i++;
			na--;
		}
		j++;
	}
	write(fd, test, c3d->file->rx * c3d->file->ry * 4);
}

void	ft_write_header(t_win *c3d, int fd)
{
	char header[54];

	ft_memset(header, 0, 54);
	ft_memcpy(header, "BM", 2);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(c3d->file->rx);
	header[19] = (unsigned char)(c3d->file->rx >> 8);
	header[20] = (unsigned char)(c3d->file->rx >> 16);
	header[21] = (unsigned char)(c3d->file->rx >> 24);
	header[22] = (unsigned char)(c3d->file->ry);
	header[23] = (unsigned char)(c3d->file->ry >> 8);
	header[24] = (unsigned char)(c3d->file->ry >> 16);
	header[25] = (unsigned char)(c3d->file->ry >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}
