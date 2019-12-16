/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 14:02:40 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 14:13:19 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(long n)
{
	int				i;
	char			tmp;
	unsigned long	nb;

	i = 0;
	if (n < 0)
	{
		i++;
		nb = -n;
		write(1, "-", 1);
	}
	else
		nb = n;
	if (nb > 9)
	{
		i += ft_putnbr(nb / 10);
		i += ft_putnbr(nb % 10);
	}
	else
	{
		i++;
		tmp = nb + '0';
		write(1, &tmp, 1);
	}
	return (i);
}
