/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:32:47 by tmarcon           #+#    #+#             */
/*   Updated: 2020/08/03 11:51:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"

void	ft_draw_ceil(t_win *c3d, float shift, int j)
{
	int		i;
	int		r;
	int		g;
	int		b;
	float	coef;

	i = 0;
	while (i < shift)
	{
		r = c3d->file->c[0];
		g = c3d->file->c[1];
		b = c3d->file->c[2];
		coef = (c3d->file->ry - i) / (c3d->file->ry * 0.7);
		if (c3d->shadow)
			rgb_shadow(&r, &g, &b, coef);
		ft_pcolor(c3d, i, j, rgbtohex(r, g, b));
		i++;
	}
}

void	ft_draw_floor(t_win *c3d, float shift, int j, int len)
{
	int		i;
	int		r;
	int		g;
	int		b;
	float	coef;

	i = c3d->file->ry;
	while (i > shift + len - 1)
	{
		r = c3d->file->f[0];
		g = c3d->file->f[1];
		b = c3d->file->f[2];
		coef = (i - c3d->file->ry / 4) / (c3d->file->ry * 0.7);
		if (c3d->shadow)
			rgb_shadow(&r, &g, &b, coef);
		if (j >= 0 && j < c3d->file->rx && i >= 0 && i < c3d->file->ry)
			ft_pcolor(c3d, i, j, rgbtohex(r, g, b));
		i--;
	}
}

void	ft_draw_wall(t_win *c3d, float len, int j, int horiz)
{
	int		i;
	int		o;
	int		uv;
	int		tex;
	int		color = 0;

	o = 0;
	tex = get_texnum(c3d, horiz);
	i = c3d->file->ry / c3d->player->view - len / c3d->player->crch;
	while (i < len + c3d->file->ry / c3d->player->view - len / c3d->player->crch
	&& i < c3d->file->ry)
	{
		if (i >= 0 && i < c3d->file->ry)
		{
			uv = o / (len / c3d->wall_h[tex]);
			if (tex == 0 || tex == 3)
				uv++;
			uv = uv * c3d->wall_w[tex] + get_tex_uvmap(c3d, tex);
			if (uv >= 0 && uv < c3d->wall_w[tex] * c3d->wall_h[tex])
				color = rgb_shadow_wall(c3d->wall[tex][uv], len, c3d);
			ft_pcolor(c3d, i, j, color);
		}
		i++;
		o++;
	}
}

void	ft_draw_sp(t_win *c3d, float len, int j, t_sp *sp)
{
	int		o;
	int		i;
	int		uv;
	float	len2;
	float	i2;

	len2 = WALLWD / sp->dist * (c3d->file->rx / 2) * c3d->cosi;
	if (len < len2)
	{
		o = -1;
		i = (c3d->file->ry / c3d->player->view - len2 / c3d->player->crch) - 1;
		len = (sp_getangle(sp->angle, c3d->player->look) - 1) * c3d->file->rx;
		i2 = len / 2 - len2 / 2;
		if (j > i2 && j < len - i2)
			while (++i < c3d->file->ry + sp_getheight(c3d, len2) + (++o)
			&& i < c3d->file->ry)
				if (i >= 0 && i < sp_getheight(c3d, len2) + len2 - 1)
				{
					uv = c3d->sp_w * (int)((o / (len2 / c3d->sp_h)));
					uv = c3d->sp[uv + (int)((j - i2) / len2 * c3d->sp_w)];
					uv = rgb_shadow_wall(uv, len2, c3d);
					if (uv)
						ft_pcolor(c3d, i, j, uv);
				}
	}
}

void	raycast(t_win *c3d, float len, int j, int horiz)
{
	t_sp	*sp;
	float	shift;

	len = WALLWD / len * ((c3d->file->rx / 2) * tan(PI * 60 / 180));
	shift = c3d->file->ry / c3d->player->view - len / c3d->player->crch;
	ft_draw_ceil(c3d, shift, j);
	ft_draw_wall(c3d, len, j, horiz);
	ft_draw_floor(c3d, shift, j, len);
	sp_sort(c3d->spp);
	sp = c3d->spp;
	if (sp)
		while (sp->next)
		{
			ft_draw_sp(c3d, len, j, sp);
			sp = sp->next;
		}
}
