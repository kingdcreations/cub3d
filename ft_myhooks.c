/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_myhooks.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 12:56:34 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 14:40:58 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

int		hook_close(t_win *c3d)
{
	mlx_destroy_image(c3d->mlx, c3d->img);
	ft_free(c3d->file, c3d->file->maph);
	ft_spfree(c3d);
	free(c3d->win);
	free(c3d->mlx);
	free(c3d);
	exit(EXIT_SUCCESS);
}

void	fail_close(t_win *c3d, char *s)
{
	mlx_destroy_image(c3d->mlx, c3d->img);
	ft_free(c3d->file, c3d->file->maph);
	ft_spfree(c3d);
	free(c3d->win);
	free(c3d->mlx);
	free(c3d);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	exit(EXIT_SUCCESS);
}

int		hook_keypress(int key, t_win *c3d)
{
	if (key == UP)
		c3d->up = 1;
	if (key == DOWN)
		c3d->down = -1;
	if (key == LEFT)
		c3d->left = 1;
	if (key == RIGHT)
		c3d->right = -1;
	if (key == SLEFT)
		c3d->sleft = 1;
	if (key == SRIGHT)
		c3d->sright = -1;
	if (key == KEY_C)
		c3d->player->crch = 1.4;
	if (key == 53)
		hook_close(c3d);
	if (key == KEY_X)
	{
		if (c3d->shadow)
			c3d->shadow = 0;
		else
			c3d->shadow = 1;
	}
	c3d->first = 1;
	return (0);
}

int		hook_keyrelease(int key, t_win *c3d)
{
	if (key == UP)
		c3d->up = 0;
	if (key == DOWN)
		c3d->down = 0;
	if (key == LEFT)
		c3d->left = 0;
	if (key == RIGHT)
		c3d->right = 0;
	if (key == SLEFT)
		c3d->sleft = 0;
	if (key == SRIGHT)
		c3d->sright = 0;
	if (key == KEY_C)
		c3d->player->crch = 2;
	c3d->first = 1;
	return (0);
}

int		hook_motion(int x, int y, t_win *c3d)
{
	x += c3d->file->rx / 2;
	c3d->player->look -= (c3d->player->oldx - x) / 2;
	c3d->player->oldx = x;
	c3d->player->view = 2;
	if (y > 2 * c3d->file->ry / 3)
		c3d->player->view = 3;
	else if (y < c3d->file->ry / 3)
		c3d->player->view = 1.5;
	c3d->first = 1;
	return (0);
}
