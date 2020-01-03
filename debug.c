/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 15:03:48 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/03 15:03:50 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	npix(t_win *c3d, int size, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		mlx_pixel_put(c3d->mlx, c3d->win, i+x*size, j+y*size, 0xFFFFFF);
		i++;
	}
	while (j < size)
	{
		mlx_pixel_put(c3d->mlx, c3d->win, i+x*size, j+y*size, 0xFFFFFF);
		j++;
	}
	i = 0;
	j = 0;
	while (j < size)
	{
		mlx_pixel_put(c3d->mlx, c3d->win, i+x*size, j+y*size, 0xFFFFFF);
		j++;
	}
	while (i < size)
	{
		mlx_pixel_put(c3d->mlx, c3d->win, i+x*size, j+y*size, 0xFFFFFF);
		i++;
	}
}

void line(t_win *c3d, int x0, int y0, int x1, int y1, int color) {

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;

	if (color == 1)
		color = 0xFC4747;
	else
		color = 0x47FC47;
  for(;;){
		if (y0 >= 0 && y0 < c3d->file->ry && x0 >= 0 && x0 < c3d->file->rx)
			c3d->imgbuf[y0 * c3d->file->rx + x0] = color;
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
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
				npix(c3d, 30, j, i);
			j++;
		}
		i++;
	}
}
