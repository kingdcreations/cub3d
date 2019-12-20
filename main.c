/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 12:13:52 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/20 13:21:55 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

unsigned	rgbtohex(int r, int g, int b)
{
	return(r * 65536 + g * 256 + b);
}

void raycast(t_win *c3d, float len, int j, int horiz)
{
	float shift;
	int i;
	char sideh;
	char sidev;
	int o = 0;
	float test;
	float rest;

	len = WALLWD/len*700;
	shift = c3d->file->ry/2 - len/2;

	if (c3d->player->y < c3d->player->impy)
		sideh = 'N';
	else
		sideh = 'S';
	if (c3d->player->x < c3d->player->impx)
		sidev = 'E';
	else
		sidev = 'W';

	/* SKY */
	i = 0;
	while(i < shift)
	{
		c3d->imgbuf[i * c3d->file->rx+ j] = rgbtohex(c3d->file->f[0], c3d->file->f[1], c3d->file->f[2]);
		i++;
	}
	/* WALLS */
	i = shift;
	while(i < len + shift && i < c3d->file->ry)
	{
		if (i > 0)
		{
			if (horiz && sideh == 'N')
			{
				test = ((int)((o/(len/c3d->wall_h[0]))+1) * c3d->wall_h[0]);
				rest = (c3d->wall_h[0] - (int)c3d->player->impx/(64/c3d->wall_h[0]))%c3d->wall_h[0] - 1;
				c3d->imgbuf[i * c3d->file->rx + j] = mlx_get_color_value(c3d->mlx , c3d->wall[0][(int)(test + rest) * 4] + c3d->wall[0][(int)(test + rest) * 4 + 1] * 256 + c3d->wall[0][(int)(test + rest) * 4 + 2] * 65536)%16777216;
			}
			else if (horiz && sideh == 'S')
			{
				test = ((int)((o/(len/c3d->wall_h[1]))) * c3d->wall_h[1]);
				rest = ((int)c3d->player->impx/(64/c3d->wall_h[1]))%c3d->wall_h[1];
				c3d->imgbuf[i * c3d->file->rx + j] = mlx_get_color_value(c3d->mlx ,c3d->wall[1][(int)(test + rest) * 4] + c3d->wall[1][(int)(test + rest) * 4 + 1] * 256 + c3d->wall[1][(int)(test + rest) * 4 + 2] * 65536)%16777216;
			}
			else if (!horiz && sidev == 'E')
			{
				test = ((int)((o/(len/c3d->wall_h[2]))) * c3d->wall_h[2]);
				rest = ((int)c3d->player->impy/(64/c3d->wall_h[2]))%c3d->wall_h[2];
				c3d->imgbuf[i * c3d->file->rx + j] = mlx_get_color_value(c3d->mlx ,c3d->wall[2][(int)(test + rest) * 4] + c3d->wall[2][(int)(test + rest) * 4 + 1] * 256 + c3d->wall[2][(int)(test + rest) * 4 + 2] * 65536)%16777216;
			}
			else if (!horiz && sidev == 'W')
			{
				test = ((int)((o/(len/c3d->wall_h[3])) + 1) * c3d->wall_h[3]);
				rest = (c3d->wall_h[3] - (int)c3d->player->impy/(64/c3d->wall_h[3]))%c3d->wall_h[3] - 1;
				c3d->imgbuf[i * c3d->file->rx + j] = mlx_get_color_value(c3d->mlx ,c3d->wall[3][(int)(test + rest) * 4] + c3d->wall[3][(int)(test + rest) * 4 + 1] * 256 + c3d->wall[3][(int)(test + rest) * 4 + 2] * 65536)%16777216;
			}
		}
		i++;
		o++;
	}


	/* FLOOR */
	i = c3d->file->ry;
	while(i > shift + len - 1)
	{
		c3d->imgbuf[i * c3d->file->rx+ j] = rgbtohex(c3d->file->c[0], c3d->file->c[1], c3d->file->c[2]);
		i--;
	}
}

float line2(t_win *c3d, float x0, float y0, float ang) {

	float angle = -ang;
	float Ay;
	float Ax;
	float Ya;
	float Xa;
	char sidev;

	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;

	if (angle > 0 && angle < 180)
	{
		Ay = floor(y0 / WALLWD) * WALLWD - 1;
		Ya = -WALLWD;
	}
	else
	{
		Ay = floor(y0 /WALLWD) * WALLWD + WALLWD;
		Ya = WALLWD;
	}
	if (angle != 0 && angle != 180)
	{
		Ax = x0 + (y0-Ay) / tan(PI * angle/180);
		Xa = -Ya/tan(PI * angle/180);
	}
	else
		return (c3d->file->mapw*WALLWD);
	if (c3d->player->x < Ax)
		sidev = 'E';
	else
		sidev = 'W';
	while ((sidev = 'E' && Ax/WALLWD < c3d->file->mapw && Ay/WALLWD < c3d->file->maph && Ax/WALLWD > 0 && Ay/WALLWD > 0 && c3d->file->map[(int)Ay/WALLWD][(int)(Ax)/WALLWD] != 1)
	|| (sidev = 'W' && Ax/WALLWD < c3d->file->mapw && Ay/WALLWD < c3d->file->maph && Ax/WALLWD > 0 && Ay/WALLWD > 0 && c3d->file->map[(int)Ay/WALLWD][((int)Ax+1)/WALLWD] != 1))
	{
		Ax+=Xa;
		Ay+=Ya;
	}
	c3d->player->impx = Ax;
	c3d->player->impy = Ay;
	return (sqrt(pow(x0 - Ax, 2) + pow(y0 - Ay, 2)));
}

float line3(t_win *c3d, float x0, float y0, float ang) {

	float angle = -ang;
	float Ya;
	float Xa;
	float By;
	float Bx;
	char sidev;

	while (0 > angle)
		angle += 360;
	while (angle >= 360)
		angle -= 360;

//GAUCHE
	if (angle > 90 && angle < 270)
	{
		Bx = floor(x0 /WALLWD) * WALLWD - 1;
		Xa = -WALLWD;
	}
	else
	{
		Bx = floor(x0 / WALLWD) * WALLWD + WALLWD;
		Xa = WALLWD;
	}
	if (angle != 270 && angle != 90)
	{
		By = y0 + (x0-Bx) * tan(PI * angle/180);
		Ya = -Xa * tan(PI * angle/180);
	}
	else
		return (c3d->file->maph*WALLWD);
	if (c3d->player->y < By)
		sidev = 'N';
	else
		sidev = 'S';
	while ((sidev == 'N' && Bx/WALLWD < c3d->file->mapw && By/WALLWD < c3d->file->maph && Bx/WALLWD > 0 && By/WALLWD > 0 && c3d->file->map[(int)By/WALLWD][(int)Bx/WALLWD] != 1)
	|| (sidev == 'S' && Bx/WALLWD < c3d->file->mapw && By/WALLWD < c3d->file->maph && Bx/WALLWD > 0 && By/WALLWD > 0 && c3d->file->map[((int)By + 1)/WALLWD][(int)Bx/WALLWD] != 1))
	{
		Bx+=Xa;
		By+=Ya;
	}
	c3d->player->impx2 = Bx;
	c3d->player->impy2 = By;
	return(sqrt(pow(x0 - Bx, 2) + pow(y0 - By, 2)));
}

int		keyhandle(t_win *c3d)
{
	float i;
	int j;
	float len;
	float len2;
	int horiz;

	i = -30;
	j = 0;
	horiz = 1;
	if (c3d->up || c3d->right || c3d->left || c3d->down || c3d->sleft || c3d->sright)
	{
		if (c3d->left)
			c3d->player->look -= 3;
		if (c3d->right)
			c3d->player->look += 3;
		if (c3d->up && c3d->file->map[(int)(c3d->player->y + 10 * sin(PI*c3d->player->look/180))/64][(int)(c3d->player->x + 10 * cos(PI*c3d->player->look/180))/64] != 1)
		{
			c3d->player->x += 5 * cos(PI*c3d->player->look/180);
			c3d->player->y += 5 * sin(PI*c3d->player->look/180);
		}
		if (c3d->down && c3d->file->map[(int)(c3d->player->y - 10 * sin(PI*c3d->player->look/180))/64][(int)(c3d->player->x - 10 * cos(PI*c3d->player->look/180))/64] != 1)
		{
			c3d->player->x -= 5 * cos(PI*c3d->player->look/180);
			c3d->player->y -= 5 * sin(PI*c3d->player->look/180);
		}
		if (c3d->sleft && c3d->file->map[(int)(c3d->player->y + 5 * sin(PI*(c3d->player->look-90)/180))/64][(int)(c3d->player->x + 5 * cos(PI*(c3d->player->look-90)/180))/64] != 1)
		{
			c3d->player->x += 2 * cos(PI*(c3d->player->look - 90)/180);
			c3d->player->y += 2 * sin(PI*(c3d->player->look - 90)/180);
		}
		if (c3d->sright && c3d->file->map[(int)(c3d->player->y - 5 * sin(PI*(c3d->player->look-90)/180))/64][(int)(c3d->player->x - 5 * cos(PI*(c3d->player->look-90)/180))/64] != 1)
		{
			c3d->player->x -= 2 * cos(PI*(c3d->player->look - 90)/180);
			c3d->player->y -= 2 * sin(PI*(c3d->player->look - 90)/180);
		}
		mlx_clear_window(c3d->mlx, c3d->win);
		while (i < 30)
		{
			len = line2(c3d, c3d->player->x, c3d->player->y, c3d->player->look + i);
			len2 = line3(c3d, c3d->player->x, c3d->player->y, c3d->player->look + i);
			if (len2 < len)
			{
				len = len2;
				c3d->player->impx = c3d->player->impx2;
				c3d->player->impy = c3d->player->impy2;
				horiz = 0;
			}
			else
				horiz = 1;
			if (j < c3d->file->rx && j >= 0)
				raycast(c3d, len * cos (PI * i /180), j, horiz);
			// line(c3d, c3d->player->x, c3d->player->y, c3d->player->x + len * cos(PI*(c3d->player->look + i)/180), c3d->player->y + len * sin(PI*(c3d->player->look + i)/180));
			i+=(60/(float)c3d->file->rx);
			j++;
		}
		mlx_put_image_to_window(c3d->mlx, c3d->win, c3d->img, 0, 0);
	}
	return (0);
}

int		hook_close(t_win *c3d)
{
	mlx_destroy_image(c3d->mlx, c3d->img);
	free(c3d->win);
	free(c3d->mlx);
	free(c3d);
	exit(EXIT_SUCCESS);
	return (0);
}

void	fail_close(t_win *c3d)
{
	mlx_destroy_image(c3d->mlx, c3d->img);
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
	if (key == SLEFT)
		c3d->sleft = 1;
	if (key == SRIGHT)
		c3d->sright = 1;
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
	if (key == SLEFT)
		c3d->sleft = 0;
	if (key == SRIGHT)
		c3d->sright = 0;
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
		c3d->file = file;

	 	if (!(c3d->mlx = mlx_init())
	 	|| !(c3d->win = mlx_new_window(c3d->mlx, file->rx, file->ry, "cub3d"))
	 	|| !(c3d->player = malloc(sizeof(t_pl))))
	 		fail_close(c3d);



	 	c3d->player->x = (c3d->file->plx * WALLWD - WALLWD/2);
	 	c3d->player->y = (c3d->file->ply * WALLWD - WALLWD/2);

		if (file->pl == 'N')
	 		c3d->player->look = 270;
		else if(file->pl == 'E')
	 		c3d->player->look = 0;
		else if(file->pl == 'W')
	 		c3d->player->look = 180;
		else if(file->pl == 'S')
	 		c3d->player->look = 90;

	 	c3d->up = 0;
	 	c3d->down = 0;
	 	c3d->left = 0;
		c3d->right = 0;
		c3d->sright = 0;
	 	c3d->sleft = 0;

		int bpp;
		int size;
		int endian;
		if (!(c3d->img = mlx_new_image(c3d->mlx, file->rx, file->ry)))
			fail_close(c3d);
		if (!(c3d->imgbuf = (int *)mlx_get_data_addr(c3d->img, &bpp, &size, &endian)))
			fail_close(c3d);

		void *imgloader = mlx_xpm_file_to_image(c3d->mlx, "tex/debug2.xpm", &c3d->wall_w[0], &c3d->wall_h[0]);
		c3d->wall[0] = mlx_get_data_addr (imgloader, &bpp, &size, &endian);

		imgloader = mlx_xpm_file_to_image(c3d->mlx, "tex/debug2.xpm", &c3d->wall_w[1], &c3d->wall_h[1]);
		c3d->wall[1] = mlx_get_data_addr (imgloader, &bpp, &size, &endian);

		imgloader = mlx_xpm_file_to_image(c3d->mlx, "tex/debug2.xpm", &c3d->wall_w[2], &c3d->wall_h[2]);
		c3d->wall[2] = mlx_get_data_addr (imgloader, &bpp, &size, &endian);

		imgloader = mlx_xpm_file_to_image(c3d->mlx, "tex/debug2.xpm", &c3d->wall_w[3], &c3d->wall_h[3]);
		c3d->wall[3] = mlx_get_data_addr (imgloader, &bpp, &size, &endian);

	 	mlx_hook(c3d->win, 17, 0, hook_close, c3d);
	 	mlx_hook(c3d->win, 2, 0, hook_keypress, c3d);
	 	mlx_hook(c3d->win, 3, 0, hook_keyrelease, c3d);
	 	mlx_loop_hook(c3d->mlx, keyhandle, c3d);

	 	mlx_loop(c3d->mlx);
		ft_free(file, file->maph);
		mlx_destroy_image(c3d->mlx, c3d->img);
		free(c3d->win);
		free(c3d->mlx);
		free(c3d);
	}
	return (0);
}
