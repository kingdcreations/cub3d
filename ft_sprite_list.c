/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sprite_list.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 09:37:35 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 17:14:11 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "minilibx_macos/mlx.h"
#include "gnl/get_next_line.h"

t_sp	*sp_new(void)
{
	t_sp *sp;

	if (!(sp = malloc(sizeof(t_sp))))
		return (NULL);
	sp->next = NULL;
	return (sp);
}

t_sp	*sp_lstlast(t_sp *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	sp_lstadd_back(t_sp **alst, t_sp *new, int i, int j)
{
	t_sp *last;

	if (new && alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			last = sp_lstlast(*alst);
			last->spx = i * 64 + 32;
			last->spy = j * 64 + 32;
			last->next = new;
		}
	}
}

void	ft_sprite_handler(t_win *c3d)
{
	int		i;
	int		j;
	int		n;
	t_sp	*sp;

	j = 0;
	n = 0;
	sp = sp_new();
	c3d->spp = sp;
	while (j < c3d->file->maph)
	{
		i = 0;
		while (i < c3d->file->mapw)
		{
			if (c3d->file->map[j][i] == 2)
			{
				n++;
				sp_lstadd_back(&c3d->spp, sp_new(), i, j);
			}
			i++;
		}
		j++;
	}
	c3d->sp_nb = n;
}
