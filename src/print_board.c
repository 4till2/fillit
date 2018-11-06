/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:21:12 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/06 10:49:56 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
/*
unsigned long long convert(unsigned long long dec)
{
printf("convert: %llu\n", dec);
    if (dec == 0)
    {
        return 0;
    }
    else
    {
        return (dec % 2 + 10 * convert(dec / 2));
    }
}
*/
unsigned long long convert(unsigned long long dec) 
{ 
	unsigned  long long binary;
	unsigned  long long remainder;
	unsigned  long long base;

	binary = 0;
	base = 1;
    while (dec > 0)
    {
        remainder = dec % 2;
        binary = binary + remainder * base;
        dec = dec / 2;
        base = base * 10;
    }
	return (binary);
} 

void		prntbin(t_piece *pieces)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		printf("%llu", convert(pieces[i].placed[0]));
		printf("\n");
		printf("%llu", convert(pieces[i].placed[1]));
		printf("\n");
		printf("%llu", convert(pieces[i].placed[2]));
		printf("\n");
		printf("%llu", convert(pieces[i].placed[3]));
		printf("\n");
		printf("\n");
	}
}
void		prntdec(t_piece *pieces)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		printf("%llu", pieces[i].placed[0]);
		printf("\n");
		printf("%llu", pieces[i].placed[1]);
		printf("\n");
		printf("%llu", pieces[i].placed[2]);
		printf("\n");
		printf("%llu", pieces[i].placed[3]);
		printf("\n");
		printf("\n");
	}
}

void	print_board(t_board *board, int boardsize)
{
	int	i;
	int j;
	int k;
	
	i = -1;
	j = -1;
	while (++j < boardsize)
	{
		k = -1;
		while (++k < boardsize)
			(board->result[j][k] == '\0') ? (board->result[j][k] = '.') : (0);
	}
	while (++i < boardsize)
		printf("%s\n", board->result[i]);
}


void	get_alph_board(t_piece *pieces, t_board *board, int boardsize)
{
	int	p;
	int	k;
	int h;
	unsigned long long control;

	p = -1;
	while (++p <= board->nbr_pieces)
	{
		k = -1;
		while (++k < 4)
		{
			h = -1;
			control = 1ULL << 63;
			while (++h < boardsize)
			{
				if ((pieces[p].placed[k] & control) == control)
					board->result[pieces[p].firstrow + k][h] = pieces[p].alph_piece;
				control = control >> 1;
			}
		}
	}
	print_board(board, boardsize);
}
