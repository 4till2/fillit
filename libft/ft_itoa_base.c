/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:41:35 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/05 10:22:39 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long long n, unsigned long long base)
{
	int		size;
	char	*str;

	size =  ft_countdigits(n, base);
	if ((str = (char*)malloc(size + 1)) == NULL)
		return (NULL);
	str[size] = '\0';
	while (n / base > 0 || n % base > 0)
	{
		size--;
		str[size] = (n % base < 10) ? (n % base) + '0' : (n % base - 10) + 'a';
		n /= base;
	}
	return (str);
}
