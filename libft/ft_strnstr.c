/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 10:19:21 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 16:14:20 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	lenf;

	if (*needle == '\0')
		return ((char*)haystack);
	i = 0;
	lenf = ft_strlen((char*)needle);
	while (haystack[i] && len-- >= lenf)
	{
		if (ft_memcmp(haystack + i, needle, lenf) == 0)
			return ((char*)haystack + i);
		i++;
	}
	return (NULL);
}
