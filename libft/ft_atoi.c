/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 17:43:38 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 14:57:47 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					found;

	i = 0;
	res = 0;
	found = 0;
	while (str[i])
		if (str[i++] != ' ')
			found = 1;
	if (!found)
		return (-2);
	i = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (unsigned long long)(str[i++] - '0');
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			return (-2);
	}
	return (res);
}
