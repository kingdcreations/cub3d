/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_color.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/03 12:45:15 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/03 14:35:20 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		rgbtohex(int r, int g, int b)
{
	return (r * 65536 + g * 256 + b);
}

void	rgb_shadow(int *r, int *g, int *b, float shade)
{
	*r *= shade;
	*g *= shade;
	*b *= shade;
}

int		rgb_shadow_wall(int color, float len)
{
	int		r;
	int		g;
	int		b;
	float	dark;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	dark = len / 500 * 0.9;
	if (r * dark < r)
		r = r * dark;
	if (g * dark < g)
		g = g * dark;
	if (b * dark < b)
		b = b * dark;
	return (rgbtohex(r, g, b));
}
