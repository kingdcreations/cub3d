/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bonus_off.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 13:02:39 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 13:53:15 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	npix(t_win *c3d, int color, int x0, int y0)
{
	int x;
	int y;
	int i;
	int j;
	int size;

	i = 0;
	j = 0;
	size = c3d->file->rx / 100;
	if (size > c3d->file->ry / 100)
		size = c3d->file->ry / 100;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			x = i + y0 * size + size;
			y = j + x0 * size + size;
			ft_pcolor(c3d, x, y, color);
			j++;
		}
		i++;
	}
}

void	drawmap(t_win *c3d)
{
	int i;
	int j;

	i = 0;
	while (i < c3d->file->maph)
	{
		j = 0;
		while (j < c3d->file->mapw)
		{
			if (c3d->file->map[i][j] == 1)
				npix(c3d, 0xFFFFFF, j, i);
			j++;
		}
		i++;
	}
	npix(c3d, 0xFF0000, c3d->player->x / 64, c3d->player->y / 64);
}

int		life_getj(t_win *c3d, int j)
{
	return (c3d->file->ry - j - c3d->file->ry * .04);
}

void	drawlife(t_win *c3d)
{
	int i;
	int j;
	int pad;
	int max;
	int pix;

	j = 0;
	pad = (c3d->file->rx * 0.4);
	max = c3d->file->rx - pad * 2;
	pix = max * c3d->player->life / 100;
	if (c3d->player->life <= 0)
	{
		ft_putstr("YOU ARE DEAD AHAH.");
		hook_close(c3d);
	}
	while (j < c3d->file->ry * 0.02)
	{
		i = pad - 1;
		while (++i < max + pad)
			c3d->imgbuf[life_getj(c3d, j) * (int)c3d->file->rx + i] = 0xFF5555;
		i = pad - 1;
		while (++i < pix + pad)
			c3d->imgbuf[life_getj(c3d, j) * (int)c3d->file->rx + i] = 0x55FF55;
		j++;
	}
}
