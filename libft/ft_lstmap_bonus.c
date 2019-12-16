/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap_bonus.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 10:43:07 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 14:11:41 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*newlist;

	ptr = NULL;
	if (lst && f)
	{
		while (lst)
		{
			if (!(newlist = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&ptr, del);
				return (NULL);
			}
			ft_lstadd_back(&ptr, newlist);
			lst = lst->next;
		}
		return (ptr);
	}
	return (NULL);
}
