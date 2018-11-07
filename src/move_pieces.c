#include "fillit.h"

/*
** the loop of the set_pieces_to_left functiongoes through the array of pieces
** and sets them to the upper left corner. It looks at each row and checks it
** with "control", which is a long long with only one '1' bit at the left end.
** If one of the rows has one '1' bit already there, the piece can't be shifted
** any further to the left.
** The second function, set_piece_to_top, checks if one of the first three rows
** is empty, which means it can be shifted upwards.
*/

void	set_piece_to_top(t_piece *pieces, int i)
{
	int j;

	j = -1;
	while (++j < 3)
	{
		if (pieces[i].origin[0] == 0)
		{
			pieces[i].origin[0] = pieces[i].origin[1];
			pieces[i].origin[1] = pieces[i].origin[2];
			pieces[i].origin[2] = pieces[i].origin[3];
			pieces[i].origin[3] = 0;
		}
	}
	j = 3;
	while (pieces[i].origin[j] == 0)
		--j;
	pieces[i].lastrow_origin = j;
}

void	set_pieces_to_left(t_piece *pieces, t_board *board)
{
	unsigned long long	control;
	int					i;
	int					j;
	int					k;

	i = -1;
	control = 1ULL << 63;
	while (++i <= board->nbr_pieces)
	{
		k = -1;
		while (++k < 3)
		{
			j = -1;
			if (((pieces[i].origin[0] >> 63) == 0) &&
				((pieces[i].origin[1] >> 63) == 0) &&
				((pieces[i].origin[2] >> 63) == 0) &&
				((pieces[i].origin[3] >> 63) == 0))
			{
				while (++j < 4)
					pieces[i].origin[j] = pieces[i].origin[j] << 1;
			}
		}
		set_piece_to_top(pieces, i);
	}
}

int		piece_reset(t_piece **piece, int p,  int full)
{
	t_piece *ptr;

	ptr = *piece;
	ptr[p].placed[3] = ptr[p].origin[3];
	ptr[p].placed[2] = ptr[p].origin[2];
	ptr[p].placed[1] = ptr[p].origin[1];
	ptr[p].placed[0] = ptr[p].origin[0];
	if (full == 1)
	{
		ptr[p].firstrow = 0;
		ptr[p].lastrow = ptr[p].lastrow_origin;
	}
	return (1);
}

int		down_shift(t_piece **piece, int p, int boardsize)
{
	t_piece	*ptr;

	ptr = *piece;
	if (ptr[p].lastrow + 1 >= boardsize)
		return (-1);
	ptr[p].firstrow++;
	ptr[p].lastrow++;
	return (1);
}

int		right_shift(t_piece **piece, int p,  int boardsize)
{
	int	i;
	t_piece *ptr;

	ptr = *piece;
	i = -1;
	while (++i < 4)
	{
		ptr[p].placed[i] = ptr[p].placed[i] >> 1;
		if (on_bit(ptr[p].placed[i], boardsize) == 1)
		{
			piece_reset(piece, p, 0);
			return (-1);
		}
	}
	return (1);
}
