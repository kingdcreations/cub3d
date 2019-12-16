/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstclear_bonus.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 13:37:19 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 13:51:14 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*tmp;

	if (lst && *lst)
	{
		list = *lst;
		while (list)
		{
			if (list->next)
				tmp = list->next;
			else
				tmp = NULL;
			del(list->content);
			free(list);
			list = tmp;
		}
		*lst = NULL;
	}
}
