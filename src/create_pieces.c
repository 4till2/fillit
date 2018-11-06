/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 validate.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ccodiga <marvin@42.fr>						+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2018/11/02 14:27:21 by ccodiga		   #+#	  #+#			  */
/*	 Updated: 2018/11/04 14:57:06 by ccodiga		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "fillit.h"

/* the loop of the set_pieces_to_left functiongoes through the array of pieces
 * and sets them to the upper left corner. It looks at each row and checks it
 * with "control", which is a long long with only one '1' bit at the left end.
 * If one of the rows has one '1' bit already there, the piece can't be shifted
 * any further to the left.
 * The second function, set_piece_to_top, checks if one of the first three rows
 * is empty, which means it can be shifted upwards. */

void		set_piece_to_top(t_piece *pieces, int i)
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

void		set_pieces_to_left(t_piece *pieces, t_board *board)
{
	unsigned long long	control;
	int					i;
	int					j;
	int					k;

	i = -1;
	control = 1ULL << 63;
	while (++i < board->nbr_pieces)
	{
		k = -1;
		while (++k < 3)
		{
			j = -1;
			if (((pieces[i].origin[0] >> 63) == 0) && ((pieces[i].origin[1] >> 63) == 0) && ((pieces[i].origin[2] >> 63) == 0) && ((pieces[i].origin[3] >> 63) == 0))
			{
				while (++j < 4)
					pieces[i].origin[j] = pieces[i].origin[j] << 1;
			}
		}
		set_piece_to_top(pieces, i);
	}
}

/* valid_pieces creates a comparison int, which contains the whole piece as
 * binary representation. In the first loop I set the first byte of the comp
 * int to the first row, the second byte to second row and so on. That is done
 * by shifting the long longs of each row at least 48 bites o the left, so
 * that they can be compared with the int. The second row will be shifted 4 more
 * so that it can be compared to the second byte, the third row will be shifted
 * 8 more and so on.
 * In the second part that int representation of the piece will be compared to
 * the possible tetrimos, assuming they are set to the upper left corner, which
 * is done one step before. */

int			valid_pieces(t_piece *pieces, t_board *board)
{
	int				i;
	int				j;
	unsigned int	comp;

	i = -1;
	j = -1;
	while (++i < board->nbr_pieces)
	{
		while (++j < 4)
		{
			comp = 0;
			comp = comp | (pieces[i].origin[j] >> (48 + (4 * j)));
		}
		if (((comp & 34952) != comp) && ((comp & 61440) != comp) && ((comp & 55296) !=
			comp) && ((comp & 36352) != comp) && ((comp & 57856) != comp) && ((comp &
			50240) != comp) && ((comp & 11776) != comp) && ((comp & 35008) != comp) &&
			((comp & 59392) != comp) && ((comp & 51328) != comp) && ((comp & 17600) !=
			comp) && ((comp & 19968) != comp) && ((comp & 35968) != comp) && ((comp &
			58368) != comp) && ((comp & 19520) != comp) && ((comp & 19584) != comp) &&
			((comp & 50688) != comp) && ((comp & 35904) != comp) && ((comp & 27648) !=
			comp))
			return (-1);
	}
	return (0);
}

/* recieves the row and the columns of the character '#' found in the file.
 * Calculates the piece number and the row number for each piece in order
 * to set the bit in each long long of the piece to the right value.*/

void		piece_to_binary(int count_columns, int count_rows, t_piece *pieces, t_board *board)
{
	int					nbr;
	unsigned long long	value;
	int					row_piece;
	char				alph;

	alph = 'A';
	nbr = count_rows / 5;
	(pieces[nbr].piece_nbr == 0) ? (pieces[nbr].piece_nbr = nbr) : (0);
	value = 1LLU << (63 - count_columns);
	row_piece = count_rows % 5;
	pieces[nbr].origin[row_piece] = pieces[nbr].origin[row_piece] ^ value;
	if (pieces[nbr].alph_piece == 0)
	{
		while (((int)alph - 65) < nbr)
			alph++;
		pieces[nbr].alph_piece = alph;
	}
	if (board->nbr_pieces < nbr)
		board->nbr_pieces = nbr;
}

/* reads the file line by line and checks if the input is valid. It does check
 * if the input is anything else than a piece or a newline. If it is a '#' it
 * will be passed to the function that converts it into the binary
 * representaion. It doesn't check though if the piece is actually valid,
 * that will be done in another step.*/

int		validate(char *file, t_piece *pieces, t_board *board)
{
	char	*line;
	int		fd;
	int		count_columns;
	int		count_rows;
	int		ret_value;

	ret_value = 0;
	count_rows = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strcat(line, "\n");
		count_columns = 0;
		while (line[count_columns])
		{
			if ((line[count_columns] == '.' || line[count_columns] == '#') && count_columns < 4)
				(line[count_columns] == '#') ? (piece_to_binary(count_columns, count_rows, pieces, board)) : (0);
			else if ((line[0] == '\n' && count_rows % 5 == 4) || (count_columns == 4 && line[count_columns] == '\n'))
			{
				count_columns++;
				continue ;
			}
			else
				ret_value = -1;
			count_columns++;
		}
		(count_rows < 130) ? (count_rows++) : (ret_value = -1);
	}
	close(fd);
	return (ret_value);
}

/* init_board_pieces allocates the needed memory and sets the values to zero.*/

void		init_board_pieces(t_board *board, t_piece *pieces)
{
	int	cnt;
	int cnt2;
	int cnt3;

	board->bin_board = (unsigned long long *)malloc(sizeof(unsigned long long) * 64);
	board->result = (char **)malloc(sizeof(char *) * 64);
	cnt3 = -1;
	while (++cnt3 < 64)
	{
		board->result[cnt3] = ft_strnew(64);
		board->bin_board[cnt3] = 0;
	}
	cnt = -1;
	while (++cnt < 26)
	{
		pieces[cnt].piece_nbr = 0;
		pieces[cnt].alph_piece = (char)0;
		pieces[cnt].origin = (unsigned long long *)malloc(sizeof(unsigned long long) * 4);
		pieces[cnt].placed = (unsigned long long *)malloc(sizeof(unsigned long long) * 4);
		cnt2 = -1;
		while (++cnt2 < 4)
		{
			pieces[cnt].origin[cnt2] = 0;
			pieces[cnt].placed[cnt2] = 0;
		}
	}
}

int		piece_reset(t_piece *piece, int full)
{
	piece->placed[3] = piece->origin[3];
	piece->placed[2] = piece->origin[2];
	piece->placed[1] = piece->origin[1];
	piece->placed[0] = piece->origin[0];
	if (full == 1)
	{
		piece->firstrow = 0;
		piece->lastrow = piece->lastrow_origin;
	}
	return (1);
}
