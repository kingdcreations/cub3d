/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 09:54:31 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:48:57 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dsttmp;
	unsigned char	*srctmp;

	i = 0;
	dsttmp = (unsigned char *)dst;
	srctmp = (unsigned char *)src;
	while (n-- && srctmp[i] != (unsigned char)c)
	{
		dsttmp[i] = srctmp[i];
		i++;
	}
	if (srctmp[i] == (unsigned char)c)
	{
		dsttmp[i] = srctmp[i];
		return (dsttmp + i + 1);
	}
	else
		return (0);
}
