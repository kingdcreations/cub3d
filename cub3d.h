/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 17:07:44 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/03 15:03:20 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define WALLWD 64

# define KEY_X 7

# define SLEFT 0
# define SRIGHT 2

# define PI 3.141592654

typedef struct	s_pl
{
	int		life;
	float	x;
	float	y;
	float	look;

	float	spx;
	float	spy;
	float	splen;

	float	impx;
	float	impy;

	float	impx2;
	float	impy2;
}				t_pl;

typedef struct	s_file
{
	char	*nextl;
	char	*line;
	char	**param;

	int		rx;
	int		ry;
	int		pl;
	int		plx;
	int		ply;

	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	char	*s;
	int		f[3];
	int		c[3];

	int		mapmode;
	char	*strmap;
	int		**map;

	int		mapw;
	int		maph;
}				t_file;

typedef struct	s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*imgbuf;
	t_pl	*player;
	t_file	*file;
	int		first;

	int		shadow;

	int		up;
	int		down;
	int		left;
	int		right;

	int		sleft;
	int		sright;

	int		*wall[4];
	int		wall_w[4];
	int		wall_h[4];

	int		*sp;
	int		sp_h;
	int		sp_w;
}				t_win;

void			ft_parsefile(t_file *file, char *filename);
void			parsemap(t_file *file);
void			initfile(t_file *file);
int				get_file(t_file *file, char *name);
void			ft_error(t_file *file, char *s, int i);
void			ft_checkerror(t_file *file);
int				ft_parse(t_file *file, char *line);
void			ft_maperror(t_file *file, char c, int j, int k);
void			ft_free(t_file *file, int j);
void			ft_splitfree(char **str);
int				ft_splitac(char **av);
char			*ft_doubledef(t_file *file, char *var,
	char **param, char *line);
void			ft_checkfc(t_file *file, char *line);
void			c3d_init(t_win *c3d);
void			ft_write_header(t_win *c3d, int fd);
void			ft_mirror_img(t_win *c3d, int fd);
void			fail_close(t_win *c3d, char *s);
void			ft_draw_ceil(t_win *c3d, float shift, int j);
void			ft_draw_floor(t_win *c3d, float shift, int j, int len);
void			ft_draw_wall(t_win *c3d, float len, int j, int horiz);
int				rgbtohex(int r, int g, int b);
void			rgb_shadow(int *r, int *g, int *b, float shade);
int				rgb_shadow_wall(int color, float len);


void	npix(t_win *c3d, int size, int x, int y);
void line(t_win *c3d, int x0, int y0, int x1, int y1, int color);
void	drawmap(t_win *c3d);

#endif
