/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_draw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 10:32:47 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 17:44:07 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
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
		c3d->imgbuf[i * c3d->file->rx + j] = rgbtohex(r, g, b);
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
			c3d->imgbuf[i * c3d->file->rx + j] = rgbtohex(r, g, b);
		i--;
	}
}

void	ft_draw_wall(t_win *c3d, float len, int j, int horiz)
{
	int		i;
	int		o;
	int		uv;
	int		tex;
	int		color;

	o = 0;
	tex = get_texnum(c3d, horiz);
	i = c3d->file->ry / c3d->player->view - len / c3d->player->crch;
	while (i < len + c3d->file->ry / c3d->player->view - len / c3d->player->crch && i < c3d->file->ry)
	{
		if (i >= 0 && i < c3d->file->ry)
		{
			uv = o / (len / c3d->wall_w[tex]);
			if (tex == 0 || tex == 3)
				uv++;
			uv = uv * c3d->wall_h[tex] + get_tex_uvmap(c3d, tex);
			color = c3d->wall[tex][uv];
			if (c3d->shadow)
				color = rgb_shadow_wall(color, len);
			c3d->imgbuf[i * c3d->file->rx + j] = color;
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
	//
	// if (j == c3d->file->rx/60)
	// {
	// 	dprintf(1, "%f\n", j / 60.0);
	// }
	len2 = WALLWD / sp->dist * ((c3d->file->rx / 2) * tan(PI * 60 / 180));
	if (len < len2)
	{
		o = -1;
		i = (c3d->file->ry / c3d->player->view - len2 / c3d->player->crch) - 1;
		len = sp_getangle(sp->angle, c3d->player->look)/2 * (c3d->file->rx * 2) / 30 - c3d->file->rx;
		i2 = len / 2 - len2 / 2;
		if (j > i2 && j < len - i2)
			while (++i < c3d->file->ry + (c3d->file->ry / c3d->player->view - len2 / c3d->player->crch) + (++o)
			&& i < c3d->file->ry)
				if (i >= 0 && i < (c3d->file->ry / c3d->player->view - len2 / c3d->player->crch) + len2 - 1)
				{
					uv = c3d->sp_w * (int)((o / (len2 / c3d->sp_w)));
					uv = uv + (int)((j - i2) / (len2 / c3d->sp_h)) % 64;
					if (c3d->sp[uv])
						c3d->imgbuf[i * c3d->file->rx + j] = c3d->sp[uv];
				}
	}
}
