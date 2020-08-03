/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:18:42 by tmarcon           #+#    #+#             */
/*   Updated: 2020/08/03 11:25:41 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"

float	ft_repairangle(float angle)
{
	angle = -angle;
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

double	dda_init(int min, float x0, float angle)
{
	double bx;

	if (angle > min && angle < min + 180)
		bx = floor(x0 / WALLWD) * WALLWD - 0.00001;
	else
		bx = floor(x0 / WALLWD) * WALLWD + WALLWD;
	return (bx);
}

float	linex(t_win *c3d, float x0, float y0, float angle)
{
	double	ay;
	float	ax;
	float	ya;
	float	xa;

	angle = ft_repairangle(angle);
	ya = (angle > 0 && angle < 180) ? -WALLWD : WALLWD;
	ay = dda_init(0, y0, angle);
	if (angle != 0 && angle != 180)
	{
		ax = x0 + (y0 - ay) / tan(PI * angle / 180);
		xa = -ya / tan(PI * angle / 180);
	}
	else
		return (c3d->file->mapw * WALLWD);
	while (ax / WALLWD < c3d->file->mapw && ay / WALLWD < c3d->file->maph
	&& ax / WALLWD > 0 && ay / WALLWD > 0
	&& c3d->file->map[(int)ay / WALLWD][(int)ax / WALLWD] != 1)
	{
		ax += xa;
		ay += ya;
	}
	c3d->ax = ax;
	c3d->ay = ay;
	return (sqrt(pow(x0 - ax, 2) + pow(y0 - ay, 2)));
}

float	liney(t_win *c3d, float x0, float y0, float angle)
{
	float	ya;
	float	xa;
	float	by;
	double	bx;

	angle = ft_repairangle(angle);
	xa = (angle > 90 && angle < 270) ? -WALLWD : WALLWD;
	bx = dda_init(90, x0, angle);
	if (angle != 270 && angle != 90)
	{
		by = y0 + (x0 - bx) * tan(PI * angle / 180);
		ya = -xa * tan(PI * angle / 180);
	}
	else
		return (c3d->file->maph * WALLWD);
	while (bx / WALLWD < c3d->file->mapw && by / WALLWD < c3d->file->maph
	&& bx / WALLWD > 0 && by / WALLWD > 0
	&& c3d->file->map[(int)by / WALLWD][(int)bx / WALLWD] != 1)
	{
		bx += xa;
		by += ya;
	}
	c3d->bx = bx;
	c3d->by = by;
	return (sqrt(pow(x0 - bx, 2) + pow(y0 - by, 2)));
}
