/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sprite_list.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/07 09:37:35 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 12:51:43 by tmarcon     ###    #+. /#+    ###.fr     */
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
	sp->dist = 0;
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

void	ft_spfree(t_win *c3d)
{
	t_sp *lst;
	t_sp *tmp;

	lst = c3d->spp;
	if (lst)
		while (lst)
		{
			if (lst->next)
				tmp = lst->next;
			else
				tmp = NULL;
			free(lst);
			lst = tmp;
		}
}

void	ft_sprite_handler(t_win *c3d)
{
	int		i;
	int		j;
	int		n;
	t_sp	*sp;
	t_sp	*new;

	j = -1;
	n = 0;
	if (!(sp = sp_new()))
		fail_close(c3d, "Linked list allocation failed.");
	c3d->spp = sp;
	while (++j < c3d->file->maph)
	{
		i = -1;
		while (++i < c3d->file->mapw)
			if (c3d->file->map[j][i] == 2 || c3d->file->map[j][i] == 3)
			{
				n++;
				if (!(new = sp_new()))
					fail_close(c3d, "Linked list allocation failed.");
				sp_lstadd_back(&c3d->spp, new, i, j);
			}
	}
	c3d->sp_nb = n;
}
