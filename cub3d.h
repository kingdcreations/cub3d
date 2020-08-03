/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 17:07:44 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 16:40:40 by tmarcon     ###    #+. /#+    ###.fr     */
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

# define UP 13
# define DOWN 1
# define WALLWD 64

# define KEY_X 7
# define KEY_C 8

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

	int		oldx;
	float	crch;
	float	view;
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

typedef struct	s_sp
{
	float		spx;
	float		spy;
	float		dist;
	float		angle;
	struct s_sp	*next;
}				t_sp;

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

	float	ax;
	float	ay;
	float	bx;
	float	by;
	float	cosi;

	int		*wall[4];
	int		wall_w[4];
	int		wall_h[4];

	int		*sp;
	int		sp_h;
	int		sp_w;
	int		sp_nb;
	t_sp	*spp;
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
void			raycast(t_win *c3d, float len, int j, int horiz);
void			ft_draw_ceil(t_win *c3d, float shift, int j);
void			ft_draw_floor(t_win *c3d, float shift, int j, int len);
void			ft_draw_wall(t_win *c3d, float len, int j, int horiz);
int				rgbtohex(int r, int g, int b);
void			rgb_shadow(int *r, int *g, int *b, float shade);
int				rgb_shadow_wall(int color, float len, t_win *c3d);
int				get_texnum(t_win *c3d, int horiz);
int				get_tex_uvmap(t_win *c3d, int tex);
void			ft_sprite_handler(t_win *c3d);
void			ft_draw_sp(t_win *c3d, float len, int j, t_sp *sp);
int				sp_getheight(t_win *c3d, float len2);
void			sp_getdist(t_win *c3d, t_sp *spp);
float			sp_getangle(float angle, float look);
void			sp_sort(t_sp *sp);

int				hook_close(t_win *c3d);
void			fail_close(t_win *c3d, char *s);
int				hook_keypress(int key, t_win *c3d);
int				hook_keyrelease(int key, t_win *c3d);
void			ft_img_loader(t_win *c3d);
void			ft_pcolor(t_win *c3d, int i, int j, int color);

void			drawlife(t_win *c3d);
void			drawlifecont(t_win *c3d, int pad);
int				hook_motion(int x, int y, t_win *c3d);

int				keyhandle(t_win *c3d);
void			rayshoot(t_win *c3d);
float			linex(t_win *c3d, float x0, float y0, float ang);
float			liney(t_win *c3d, float x0, float y0, float ang);
void			ft_saver(t_win *c3d);
void			ft_loader(t_win *c3d);

void			npix(t_win *c3d, int size, int x, int y);
void			drawmap(t_win *c3d);
void			ft_spfree(t_win *c3d);

#endif
