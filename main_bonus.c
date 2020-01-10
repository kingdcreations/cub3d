/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_bonus.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 12:13:52 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/10 13:27:24 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

void	ft_pcolor(t_win *c3d, int i, int j, int color)
{
	if (i < c3d->file->ry && j < c3d->file->rx
	&& i >= 0 && j >= 0)
		c3d->imgbuf[i * c3d->file->rx + j] = color;
}

void	c3d_init(t_win *c3d)
{
	c3d->mlx = NULL;
	c3d->win = NULL;
	c3d->player = NULL;
	if (!(c3d->player = malloc(sizeof(t_pl))))
		fail_close(c3d, "Player struct malloc failed");
	c3d->first = 1;
	c3d->shadow = 0;
	c3d->player->life = 100;
	c3d->player->x = (c3d->file->plx * WALLWD - WALLWD / 2);
	c3d->player->y = (c3d->file->ply * WALLWD - WALLWD / 2);
	c3d->player->view = 2;
	c3d->player->crch = 2;
	c3d->player->oldx = c3d->file->rx / 2;
	if (c3d->file->pl == 'N')
		c3d->player->look = 270;
	else if (c3d->file->pl == 'E')
		c3d->player->look = 0;
	else if (c3d->file->pl == 'W')
		c3d->player->look = 180;
	else if (c3d->file->pl == 'S')
		c3d->player->look = 90;
}

void	ft_hooker(t_win *c3d)
{
	mlx_hook(c3d->win, 17, 0, hook_close, c3d);
	mlx_hook(c3d->win, 6, 0, hook_motion, c3d);
	mlx_hook(c3d->win, 2, 0, hook_keypress, c3d);
	mlx_hook(c3d->win, 3, 0, hook_keyrelease, c3d);
	mlx_loop_hook(c3d->mlx, keyhandle, c3d);
	mlx_loop(c3d->mlx);
}

void	ft_loader(t_win *c3d)
{
	ft_img_loader(c3d);
	ft_sprite_handler(c3d);
	sp_getdist(c3d, c3d->spp);
	sp_sort(c3d->spp, c3d);
}

int		main(int ac, char **av)
{
	t_win	*c3d;
	t_file	*file;

	if (ac == 2 || (ac == 3 && ft_strcmp(av[2], "-save") == 0))
	{
		if (!(file = malloc(sizeof(t_file))))
			exit(EXIT_FAILURE);
		ft_parsefile(file, av[1]);
		if (!(c3d = malloc(sizeof(t_win))))
			exit(EXIT_FAILURE);
		c3d->file = file;
		c3d_init(c3d);
		if (!(c3d->mlx = mlx_init()))
			fail_close(c3d, "Mlx init failed");
		if (ac == 2)
			if (!(c3d->win = mlx_new_window(c3d->mlx, file->rx, file->ry,
			"Cub3D")))
				fail_close(c3d, "Mlx init failed");
		ft_loader(c3d);
	}
	if (ac == 2)
		ft_hooker(c3d);
	else if (ac == 3 && ft_strcmp(av[2], "-save") == 0)
		ft_saver(c3d);
	return (0);
}
