/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_draw.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 10:32:47 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/03 15:31:31 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

int		get_texnum(t_win *c3d, int horiz)
{
	int sideh;
	int sidev;

	if (c3d->player->y < c3d->player->impy)
		sideh = 'N';
	else
		sideh = 'S';
	if (c3d->player->x < c3d->player->impx)
		sidev = 'E';
	else
		sidev = 'W';
	if (horiz && sideh == 'N')
		return (0);
	else if (horiz && sideh == 'S')
		return (1);
	else if (!horiz && sidev == 'E')
		return (2);
	else if (!horiz && sidev == 'W')
		return (3);
	return (-1);
}

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
		coef = (c3d->file->ry / 2 - i) / (c3d->file->ry * 0.9);
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
		coef = (i - c3d->file->ry / 2) / (c3d->file->ry * 0.9);
		if (c3d->shadow)
			rgb_shadow(&r, &g, &b, coef);
		if (j >= 0 && j < c3d->file->rx && i >= 0 && i < c3d->file->ry)
			c3d->imgbuf[i * c3d->file->rx + j] = rgbtohex(r, g, b);
		i--;
	}
}

int		get_tex_uvmap(t_win *c3d, int tex)
{
	int texy;

	texy = 0;
	if (tex == 0)
		texy = c3d->wall_h[0] - c3d->player->impx / (WALLWD / c3d->wall_h[0]);
	else if (tex == 1)
		texy = c3d->player->impx / (WALLWD / c3d->wall_h[1]);
	else if (tex == 2)
		texy = c3d->player->impy / (WALLWD / c3d->wall_h[2]);
	else if (tex == 3)
		texy = c3d->wall_h[3] - c3d->player->impy / (WALLWD / c3d->wall_h[3]);
	texy = texy % c3d->wall_h[tex];
	if (tex == 0 || tex == 3)
		texy--;
	return (texy);
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
	i = c3d->file->ry / 2 - len / 2;
	while (i < len + c3d->file->ry / 2 - len / 2 && i < c3d->file->ry)
	{
		if (i >= 0 && i < c3d->file->ry)
		{
			uv = o / (len / c3d->wall_h[tex]);
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
