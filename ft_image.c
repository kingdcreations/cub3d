/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:02:04 by tmarcon           #+#    #+#             */
/*   Updated: 2020/08/03 15:13:20 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"

void	ft_pcolor(t_win *c3d, int i, int j, int color)
{
	if (i < c3d->file->ry && j < c3d->file->rx
	&& i >= 0 && j >= 0)
		c3d->imgbuf[i * c3d->file->rx + j] = color;
}

void	ft_loader(t_win *c3d)
{
	ft_img_loader(c3d);
	ft_sprite_handler(c3d);
	sp_getdist(c3d, c3d->spp);
}

void	ft_img_loader(t_win *c)
{
	int i;
	int		na;
	int		bpp;
	int		endian;

	i = 0;
	while (i < 5)
		c->tex[i++] = NULL;
	c->img = mlx_new_image(c->mlx, c->file->rx, c->file->ry);
	c->imgbuf = (int *)mlx_get_data_addr(c->img, &bpp, &na, &endian);
	if (!(c->tex[0] = mlx_xpm_file_to_image(c->mlx, c->file->no, &c->wall_w[0], &c->wall_h[0])))
		fail_close(c, "North texture not found");
	c->wall[0] = (int *)mlx_get_data_addr(c->tex[0], &bpp, &na, &endian);
	if (!(c->tex[1] = mlx_xpm_file_to_image(c->mlx, c->file->so, &c->wall_w[1], &c->wall_h[1])))
		fail_close(c, "South texture not found");
	c->wall[1] = (int *)mlx_get_data_addr(c->tex[1], &bpp, &na, &endian);
	if (!(c->tex[2] = mlx_xpm_file_to_image(c->mlx, c->file->we, &c->wall_w[2], &c->wall_h[2])))
		fail_close(c, "West texture not found");
	c->wall[2] = (int *)mlx_get_data_addr(c->tex[2], &bpp, &na, &endian);
	if (!(c->tex[3] = mlx_xpm_file_to_image(c->mlx, c->file->ea, &c->wall_w[3], &c->wall_h[3])))
		fail_close(c, "East texture not found");
	c->wall[3] = (int *)mlx_get_data_addr(c->tex[3], &bpp, &na, &endian);
	if (!(c->tex[4] = mlx_xpm_file_to_image(c->mlx, c->file->s, &c->sp_w, &c->sp_h)))
		fail_close(c, "Sprite texture not found");
	c->sp = (int *)mlx_get_data_addr(c->tex[4], &bpp, &na, &endian);
}
