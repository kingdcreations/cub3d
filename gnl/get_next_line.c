/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tmarcon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 16:21:11 by tmarcon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/16 11:44:51 by tmarcon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_output(int ret, char **nextl, char **line, char **buff)
{
	free(*nextl);
	if (ret != 0)
	{
		if (!(*nextl = ft_strdup_gnl(ft_strchr_gnl(*line, '\n'))) ||
		!(*line = ft_substr_gnl(*line, 0, ft_strlen_gnl(*line) - ft_strlen_gnl(*nextl))))
			return (0);
	}
	else
		*nextl = NULL;
	free(*buff);
	*buff = NULL;
	return (1);
}

int	get_next_line(int fd, char **line, t_file *file)
{
	int			sz;
	int			ret;
	char		*buff;
	static char	*nextl;

	ret = 1;
	if (!line || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0 ||
	!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!(*line = (nextl) ? ft_strdup_gnl(nextl + 1) : ft_strdup_gnl("")))
		return (-1);
	while (!(ft_strchr_gnl(*line, '\n')) && ret != 0)
		if ((sz = read(fd, buff, BUFFER_SIZE)) != 0)
		{
			buff[sz] = '\0';
			if (!(*line = ft_strjoin_gnl(*line, buff)))
				return (-1);
		}
		else
			ret = 0;
	if (!(ft_output(ret, &nextl, line, &buff)))
		return (-1);
	file->nextl = nextl;
	return (ret);
}
