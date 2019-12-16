/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 12:13:52 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 16:04:31 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

int		keyhandle(t_win *c3d)
{
	(void)c3d;
	return (0);
}

int		hook_close(t_win *c3d)
{
	free(c3d->win);
	free(c3d->mlx);
	free(c3d);
	exit(EXIT_SUCCESS);
	return (0);
}

void	fail_close(t_win *c3d)
{
	free(c3d->win);
	free(c3d->mlx);
	free(c3d);
	exit(EXIT_FAILURE);
}

int		hook_keypress(int key, t_win *c3d)
{
	if (key == UP)
		c3d->up = 1;
	if (key == DOWN)
		c3d->down = 1;
	if (key == LEFT)
		c3d->left = 1;
	if (key == RIGHT)
		c3d->right = 1;
	if (key == 53)
		hook_close(c3d);
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
	return (0);
}

int		main(int ac, char **av)
{
	t_win		*c3d;
	t_file	*file;

	if (ac == 2)
	{
		if (!(file = malloc(sizeof(t_file))))
			return (-1);
		ft_parsefile(file, av[1]);

	 	if (!(c3d = malloc(sizeof(t_win))))
	 		exit(EXIT_FAILURE);
	 	c3d->mlx = NULL;
	 	c3d->win = NULL;
	 	c3d->player = NULL;
	 	if (!(c3d->mlx = mlx_init())
	 	|| !(c3d->win = mlx_new_window(c3d->mlx, file->rx, file->ry, "cub3d"))
	 	|| !(c3d->player = malloc(sizeof(t_pl))))
	 		fail_close(c3d);

	 	c3d->player->x = 40;
	 	c3d->player->y = 40;
	 	c3d->player->look = 90;

	 	c3d->up = 0;
	 	c3d->down = 0;
	 	c3d->left = 0;
	 	c3d->right = 0;

	 	mlx_hook(c3d->win, 17, 0, hook_close, c3d);
	 	mlx_hook(c3d->win, 2, 0, hook_keypress, c3d);
	 	mlx_hook(c3d->win, 3, 0, hook_keyrelease, c3d);
	 	mlx_loop_hook(c3d->mlx, keyhandle, c3d);

	 	mlx_loop(c3d->mlx);
		ft_free(file, file->maph);
		free(c3d->win);
		free(c3d->mlx);
		free(c3d);
	}
	return (0);
}
