#include "fillit.h"

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
	int					p;
	int					k;
	int					h;
	unsigned long long	control;

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
					board->result[pieces[p].firstrow + k][h] =
					pieces[p].alph_piece;
				control = control >> 1;
			}
		}
	}
	print_board(board, boardsize);
}
