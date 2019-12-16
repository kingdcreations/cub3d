/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_intlen_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 10:36:04 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/13 10:37:42 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

long	ft_intlen_base(long nb, int base)
{
	int	i;

	i = 0;
	if (nb > base - 1)
		i += ft_intlen_base(nb / base, base) + ft_intlen_base(nb % base, base);
	else
		i++;
	return (i);
}
