#include "fillit.h"

unsigned long long	on_bit(unsigned long long p, int n)
{
	return ((p >> (63 - n)) & 1);
}

int					unset_piece(t_board *board, t_piece *piece)
{
	int i;

	i = -1;
	while (++i < 4)
		board->bin_board[piece->firstrow + i] =
		board->bin_board[piece->firstrow + i] ^ piece->placed[i];
	return (1);
}

int					piece_shift(t_piece **pieces, int p, int boardsize)
{
	if ((right_shift(pieces, p, boardsize) == -1) &&
		(down_shift(pieces, p, boardsize) == -1))
	{
		piece_reset(pieces, p, 1);
		return (-1);
	}
	return (1);
}

int					set_piece(t_piece **pieces, int p , t_board *board, int boardsize)
{
	int	shifted;
	int	i;
	t_piece *ptr;


	shifted = 1;
	while (shifted != -1)
	{
		ptr = *pieces;
		i = 0;
		while (i < 4 && ((board->bin_board[ptr[p].firstrow + i] &
			ptr[p].placed[i]) == 0))
			i++;
		if (i == 4)
		{
			i = 0;
			while (i < 4)
			{
				board->bin_board[ptr[p].firstrow + i] =
				board->bin_board[ptr[p].firstrow + i] | ptr[p].placed[i];
				++i;
			}
			return (1);
		}
		shifted = piece_shift(pieces, p, boardsize);
	}
	return (-1);
}

int					reset_all(t_piece **pieces, t_board *board)
{
	int i;

	i = -1;
	while (++i < board->boardsize)
		board->bin_board[i] = 0;
	i = -1;
	while (++i < board->nbr_pieces)
		piece_reset(pieces, i, 1);
	return (1);
}

int					set_board(t_piece **pieces, int p, t_board *board,
					int shiftback)
{
	t_piece *ptr;

	ptr = *pieces;
	if (p > board->nbr_pieces)
		return (1);
	if (shiftback == 1)
	{
		if (p < 0)
		{
			reset_all(pieces, board);
			(board->boardsize)++;
			return (set_board(pieces, 0, board, 0));
		}
		unset_piece(board, &ptr[p]);
		if (piece_shift(pieces, p, board->boardsize) == 1)
			return (set_board(pieces, p, board, 0));
		else
			return (set_board(pieces, --p, board, 1));
	}
	else if (set_piece(pieces, p, board, board->boardsize) == -1)
		return (set_board(pieces, --p, board, 1));
	else
		return (set_board(pieces, ++p, board, 0));
}
