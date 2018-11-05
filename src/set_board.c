/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:07:56 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/05 14:29:56 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fillit.h"

unsigned long long		on_bit(unsigned long long p, int n)
{
	return((p >> (63 - n)) & 1);
}

int		piece_reset(t_piece *piece, int full)
{
	piece->placed[3] = piece->origin[3];
	piece->placed[2] = piece->origin[2];
	piece->placed[1] = piece->origin[1];
	piece->placed[0] = piece->origin[0];
	if (full == 1)
		piece->firstrow = 0;
	return (1);
}

int		unset_piece(t_board *board,t_piece *piece)
{
	int i;

	i = 0;
	while (i < 4)
	{
printf("board before unset: %llu\n", board->bin_board[piece->firstrow + i]);
		board->bin_board[piece->firstrow + i] = board->bin_board[piece->firstrow + i] ^ piece->placed[i];
printf("piece %llu\n", piece->placed[i]);
printf("board after unset: %llu\n", board->bin_board[piece->firstrow + i]);
		++i;
	}
	return (1); 
}

int		down_shift(t_piece *piece,int boardsize)
{
	if (piece->lastrow - 1  >= boardsize) //piece reached last row
		return (-1);
	piece->firstrow += 1;
	piece->lastrow += 1;
	return (1);
}

int		right_shift(t_piece *piece,int boardsize)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		piece->placed[i] =	piece->placed[i] >> 1;
		if (on_bit(piece->placed[i], boardsize) == 1) //piece cross width boundry
		{
			piece_reset(piece, 0); //reset column but not rows
			return (-1);
		}
		++i;
	}
	return (1);
}



int		piece_shift(t_piece *piece, int boardsize)
{
	if ((right_shift(piece, boardsize) == -1) && (down_shift(piece, boardsize) == -1))
	{
		piece_reset(piece, 1);
		return (-1);
	}
	return (1);
}

int		set_piece(t_piece *piece,t_board  *board,int  boardsize)
{
	int shifted;
	int i;

	shifted = 1;
	while (shifted != -1)
	{
		i = 0;
		while (i < 4 && ((board->bin_board[piece->firstrow + i] & piece->placed[i]) == 0))
		{
			i++;
		}
		if (i == 4)
		{
			i = 0;
			while (i < 4)
			{
				board->bin_board[piece->firstrow + i] = board->bin_board[piece->firstrow + i] | piece->placed[i];
				++i;
			}
			return (1);
		}
		shifted = piece_shift(piece, boardsize);
	}
	return (-1);
}

int		set_board(t_piece *pieces, int p, t_board *board, int *boardsize, int shiftback)
{
static int calls;
calls++;
printf("pp %i\n",p);
printf("callllls %i\n", calls);
	if (calls > 10000)
		(*boardsize)++;
	if (p > board->nbr_pieces + 1)
	{
		return (1);
	}
	if (shiftback == 1) //last attemt of settng piece failed. Unset previous piece, shift, and re-set
	{
		if (p < 0) //cant fit first piece. start again with bigger board (room for increasing program speed by placing other conditionals here)
		{
			(*boardsize)++;
printf("boardsize in stb %i\n",*boardsize);
			return (set_board(pieces, 0, board, boardsize, 0));
		}
		unset_piece(board, &pieces[p]);
		if (piece_shift(&pieces[p], *boardsize) == 1)
				return (set_board(pieces, p, board, boardsize, 0));
		else
			return (set_board(pieces, --p, board, boardsize, 1));
	}
	else if (set_piece(&pieces[p], board, *boardsize) == -1)	  // piece not set
		return (set_board(pieces, --p, board, boardsize, 1)); // replace the previous piece 
	else
		return (set_board(pieces, ++p, board, boardsize, 0)); //piece set move on to next piece
}
