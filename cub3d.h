/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 17:07:44 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 15:29:23 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125

# define PI 3.141592654

typedef struct	s_pl
{
	float	x;
	float	y;
	float	look;
}				t_pl;

typedef struct	s_file
{
	char	*nextl;
	char	*line;
	char	**param;

	int		rx;
	int		ry;
	int		pl;

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
	t_pl	*player;

	int		up;
	int		down;
	int		left;
	int		right;

	int		side;

	char	*wall[4];
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

#endif
