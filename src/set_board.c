/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:07:56 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/05 11:13:51 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fillit.h"

int		on_bit(unsigned long long p, int n, int direction)
{
	return (direction > 0 ? (p >> (n)) & 1 : (p << (n)) & 1);
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
		board->bin_board[piece->firstrow + i] = board->bin_board[piece->firstrow + i] ^ piece->placed[i];
		++i;
	}
	return (1); 
}

int		down_shift(t_piece *piece,int boardsize)
{
	if (piece->firstrow == boardsize - 4) //piece reached last row
		return (-1);
	piece->firstrow += 1;
	return (1);
}

int		right_shift(t_piece *piece,int boardsize)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		piece->placed[i] =	piece->placed[i] >> 1;
		if (on_bit(piece->placed[i++], boardsize, -1)) //piece cross width boundry
		{
			piece_reset(piece, 0); //reset column but not rows
			return (-1);
		}
	}
	return (1);
}



int		piece_shift(t_piece *piece, int boardsize)
{
	if (!(right_shift(piece, boardsize)) && !(down_shift(piece, boardsize)) &&
		piece_reset(piece, 1))
		return (-1);
	return (1);
}

int		set_piece(t_piece *piece,t_board  *board,int  boardsize)
{
	int shifted;
	int i;

	shifted = 1;
	while (shifted)
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
	if (p > board->nbr_pieces + 1)
		return (1);
	if (shiftback) //last attemt of settng piece failed. Unset previous piece, shift, and re-set
	{
		if (p < 0) //cant fit first piece. start again with bigger board (room for increasing program speed by placing other conditionals here)
			return (set_board(pieces, 0, board, &(*(++boardsize)), 0));
		unset_piece(board, &pieces[p]);
		if (piece_shift(&pieces[p], *boardsize))
				return (set_board(pieces, p, board, boardsize, 0));
		else
			return (set_board(pieces, --p, board, boardsize, 1));
	}
	else if (set_piece(&pieces[p], board, *boardsize) == -1)	  // piece not set
		return (set_board(pieces, --p, board, boardsize, 1)); // replace the previous piece 
	else
		return (set_board(pieces, ++p, board, boardsize, 0)); //piece set move on to next piece
}
