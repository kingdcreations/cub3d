/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_color.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 12:45:15 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 13:21:56 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

int		rgbtohex(int r, int g, int b)
{
	return (r * 65536 + g * 256 + b);
}

void	rgb_shadow(int *r, int *g, int *b, float shade)
{
	*r *= shade;
	*g *= shade;
	*b *= shade;
	if (*r > 255)
		*r = 255;
	if (*g > 255)
		*g = 255;
	if (*b > 255)
		*b = 255;
}

int		rgb_shadow_wall(int color, float len, t_win *c3d)
{
	int		r;
	int		g;
	int		b;
	float	dark;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	dark = len / 100 * 0.95;
	if (c3d->shadow)
	{
		if (r * dark < r)
			r = r * dark;
		if (g * dark < g)
			g = g * dark;
		if (b * dark < b)
			b = b * dark;
	}
	return (rgbtohex(r, g, b));
}

int		get_texnum(t_win *c3d, int horiz)
{
	int sideh;
	int sidev;

	if (c3d->player->y < c3d->ay)
		sideh = 'N';
	else
		sideh = 'S';
	if (c3d->player->x < c3d->ax)
		sidev = 'E';
	else
		sidev = 'W';
	if (horiz && sideh == 'N')
		return (1);
	else if (horiz && sideh == 'S')
		return (0);
	else if (!horiz && sidev == 'E')
		return (3);
	else if (!horiz && sidev == 'W')
		return (2);
	return (-1);
}

int		get_tex_uvmap(t_win *c3d, int tex)
{
	int texy;

	texy = 0;
	if (tex == 0)
		texy = c3d->wall_w[0] - c3d->ax / 64 * c3d->wall_w[0];
	else if (tex == 1)
		texy = c3d->ax / 64 * c3d->wall_w[1];
	else if (tex == 2)
		texy = c3d->ay / 64 * c3d->wall_w[2];
	else if (tex == 3)
		texy = c3d->wall_w[3] - (c3d->ay / 64 * c3d->wall_w[3]);
	texy = texy % c3d->wall_w[tex];
	if (tex == 0 || tex == 3)
		texy--;
	return (texy);
}
