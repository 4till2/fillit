/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 11:15:37 by yserkez           #+#    #+#             */
/*   Updated: 2018/10/30 11:41:11 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	i = 0;
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (s1[len])
	{
		ret[len] = (char)s1[len];
		len++;
	}
	while (s2[i])
		ret[len++] = (char)s2[i++];
	ret[len] = '\0';
	return (ret);
}
