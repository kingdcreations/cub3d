/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 12:13:52 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 18:07:52 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

float	ft_repairangle(float angle)
{
	angle = -angle;
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	return (angle);
}

float	linex(t_win *c3d, float x0, float y0, float angle)
{
	double	ay;
	float	ax;
	float	ya;
	float	xa;

	angle = ft_repairangle(angle);
	if (angle > 0 && angle < 180)
	{
		ay = floor(y0 / WALLWD) * WALLWD - 0.00001;
		ya = -WALLWD;
	}
	else
	{
		ay = floor(y0 / WALLWD) * WALLWD + WALLWD;
		ya = WALLWD;
	}
	if (angle != 0 && angle != 180)
	{
		ax = x0 + (y0 - ay) / tan(PI * angle / 180);
		xa = -ya / tan(PI * angle / 180);
	}
	else
		return (c3d->file->mapw * WALLWD);
	while (ax / WALLWD < c3d->file->mapw && ay / WALLWD < c3d->file->maph && ax / WALLWD > 0 && ay / WALLWD > 0 && c3d->file->map[(int)ay / WALLWD][(int)ax / WALLWD] != 1)
	{
		ax += xa;
		ay += ya;
	}
	c3d->player->impx = ax;
	c3d->player->impy = ay;
	return (sqrt(pow(x0 - ax, 2) + pow(y0 - ay, 2)));
}

float	liney(t_win *c3d, float x0, float y0, float angle)
{
	float	ya;
	float	xa;
	float	by;
	double	bx;

	angle = ft_repairangle(angle);
	if (angle > 90 && angle < 270)
	{
		bx = floor(x0 / WALLWD) * WALLWD - 0.00001;
		xa = -WALLWD;
	}
	else
	{
		bx = floor(x0 / WALLWD) * WALLWD + WALLWD;
		xa = WALLWD;
	}
	if (angle != 270 && angle != 90)
	{
		by = y0 + (x0 - bx) * tan(PI * angle / 180);
		ya = -xa * tan(PI * angle / 180);
	}
	else
		return (c3d->file->maph * WALLWD);
	while (bx / WALLWD < c3d->file->mapw && by / WALLWD < c3d->file->maph && bx / WALLWD > 0 && by / WALLWD > 0 && c3d->file->map[(int)by / WALLWD][(int)bx / WALLWD] != 1)
	{
		bx += xa;
		by += ya;
	}
	c3d->player->impx2 = bx;
	c3d->player->impy2 = by;
	return (sqrt(pow(x0 - bx, 2) + pow(y0 - by, 2)));
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
	// mlx_hook(c3d->win, 6, 0, hook_motion, c3d);
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
