/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_keyhandling.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 13:21:21 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 14:09:24 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

float	ft_swap(t_win *c3d, float lnx, float lny, int *horiz)
{
	if (lny < lnx)
	{
		lnx = lny;
		c3d->ax = c3d->bx;
		c3d->ay = c3d->by;
		*horiz = 0;
	}
	else
		*horiz = 1;
	return (lnx);
}

void	rayshoot(t_win *c3d)
{
	int		j;
	int		horiz;
	float	i;
	float	lnx;
	float	lny;

	i = -30;
	j = -1;
	while (i < 30)
	{
		lnx = linex(c3d, c3d->player->x, c3d->player->y, c3d->player->look + i);
		lny = liney(c3d, c3d->player->x, c3d->player->y, c3d->player->look + i);
		lnx = ft_swap(c3d, lnx, lny, &horiz);
		c3d->cosi = tan(PI * 60 / 180) / cos(PI * i / 180);
		if (++j < c3d->file->rx && j >= 0)
			raycast(c3d, lnx * cos(PI * i / 180), j, horiz);
		i += (60 / (float)c3d->file->rx);
	}
}

int		isfree(t_win *c3d, int x, int y)
{
	if (c3d->file->map[x][y] == 1 || c3d->file->map[x][y] == 2)
		return (0);
	if (c3d->file->map[x][y] == 3)
		return (3);
	return (1);
}

void	ft_collider(t_win *c3d)
{
	int		d;
	float	x;
	float	y;

	if ((d = c3d->up + c3d->down))
	{
		x = d * 5 * cos(PI * c3d->player->look / 180);
		y = d * 5 * sin(PI * c3d->player->look / 180);
		if (isfree(c3d, c3d->player->y / 64, (c3d->player->x + x * 3) / 64))
			c3d->player->x += x;
		if (isfree(c3d, (c3d->player->y + y * 3) / 64, c3d->player->x / 64))
			c3d->player->y += y;
	}
	if ((d = c3d->sleft + c3d->sright))
	{
		x = d * 3 * cos(PI * (c3d->player->look - 90) / 180);
		y = d * 3 * sin(PI * (c3d->player->look - 90) / 180);
		if (isfree(c3d, c3d->player->y / 64, (c3d->player->x + x * 3) / 64))
			c3d->player->x += x;
		if (isfree(c3d, (c3d->player->y + y * 3) / 64, c3d->player->x / 64))
			c3d->player->y += y;
	}
}

int		keyhandle(t_win *c3d)
{
	if (c3d->up || c3d->right || c3d->left || c3d->down
	|| c3d->sleft || c3d->sright || c3d->first)
	{
		c3d->first = 0;
		if (isfree(c3d, c3d->player->y / 64, c3d->player->x / 64) == 3)
			c3d->player->life--;
		c3d->player->look -= (c3d->left + c3d->right) * 3;
		ft_collider(c3d);
		sp_getdist(c3d, c3d->spp);
		rayshoot(c3d);
		drawlife(c3d);
		drawmap(c3d);
		mlx_put_image_to_window(c3d->mlx, c3d->win, c3d->img, 0, 0);
	}
	return (0);
}
