/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 09:37:35 by tmarcon           #+#    #+#             */
/*   Updated: 2020/08/03 11:25:35 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"

void		sp_swap(t_sp *tmp)
{
	float spx;
	float spy;
	float angle;
	float dist;

	spx = tmp->spx;
	tmp->spx = tmp->next->spx;
	tmp->next->spx = spx;
	spy = tmp->spy;
	tmp->spy = tmp->next->spy;
	tmp->next->spy = spy;
	dist = tmp->dist;
	tmp->dist = tmp->next->dist;
	tmp->next->dist = dist;
	angle = tmp->angle;
	tmp->angle = tmp->next->angle;
	tmp->next->angle = angle;
}

void		sp_sort(t_sp *sp)
{
	t_sp	*tmp;

	while (sp)
	{
		tmp = sp;
		while (tmp->next)
		{
			if (sp->dist < sp->next->dist)
				sp_swap(tmp);
			tmp = tmp->next;
		}
		sp = sp->next;
	}
}

int			sp_getheight(t_win *c3d, float len2)
{
	return (c3d->file->ry / c3d->player->view - len2 / c3d->player->crch);
}

void		sp_getdist(t_win *c3d, t_sp *spp)
{
	float	dx;
	float	dy;
	t_sp	*sp;

	sp = spp;
	while (sp->next)
	{
		dx = fabs(c3d->player->x - sp->spx);
		dy = fabs(c3d->player->y - sp->spy);
		if (c3d->player->x < sp->spx && c3d->player->y >= sp->spy)
			sp->angle = atan(dy / dx) * 180 / PI;
		else if (c3d->player->x >= sp->spx && c3d->player->y >= sp->spy)
			sp->angle = 180 - (atan(dy / dx) * 180 / PI);
		else if (c3d->player->x >= sp->spx && c3d->player->y < sp->spy)
			sp->angle = 270 - (atan(dx / dy) * 180 / PI);
		else if (c3d->player->x < sp->spx && c3d->player->y < sp->spy)
			sp->angle = 270 + (atan(dx / dy) * 180 / PI);
		sp->dist = pow(c3d->player->x - sp->spx, 2);
		sp->dist = sp->dist + pow(c3d->player->y - sp->spy, 2);
		sp->dist = sqrt(sp->dist);
		sp = sp->next;
	}
}

float		sp_getangle(float angle, float look)
{
	angle = (360 - angle) - (look - 60);
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle / 30);
}
