/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sprite.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 09:37:35 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 18:06:28 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	sp_sort(t_sp *sp, t_win *c3d)
{
	float mdist;
	float spx;
	float spy;
	float angle;
	float dist;
	t_sp *tmp;

	mdist = WALLWD * ((c3d->file->rx / 2) * tan(PI * 60 / 180));
	while (sp)
	{
		tmp = sp;
		while (tmp->next)
		{
			if (mdist / sp->dist > mdist / sp->next->dist)
			{
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
			tmp = tmp->next;
		}
		sp = sp->next;
	}
}

void	sp_getdist(t_win *c3d, t_sp *spp)
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

float	sp_getangle(float angle, float look)
{
	angle = (360 - angle) - (look - 30);
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}