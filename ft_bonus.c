/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bonus.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 13:02:39 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 13:17:19 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

int		life_getj(t_win *c3d, int j)
{
	return (c3d->file->ry - j - c3d->file->ry * .04);
}

void	drawlife(t_win *c3d)
{
	int i;
	int j;
	int pad;
	int max;
	int pix;

	j = 0;
	pad = (c3d->file->rx * 0.4);
	max = c3d->file->rx - pad * 2;
	pix = max * c3d->player->life / 100;
	if (c3d->player->life <= 0)
		fail_close(c3d, "YOU DED");
	while (j < c3d->file->ry * 0.02)
	{
		i = pad - 1;
		while (++i < max + pad)
			c3d->imgbuf[life_getj(c3d, j) * (int)c3d->file->rx + i] = 0xFF5555;
		i = pad - 1;
		while (++i < pix + pad)
			c3d->imgbuf[life_getj(c3d, j) * (int)c3d->file->rx + i] = 0x55FF55;
		j++;
	}
}
