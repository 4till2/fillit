/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:24:07 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/06 23:24:47 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long ft_sqrt(long long n)
{
     long long low = 0;
     long long high = n+1;
     while (high - low > 1)
     {
           long long mid = (low+high)/2;
           if (mid*mid <= n)
                 low = mid;
           else
                 high = mid;
     }
     
     return low;
}
