#include "fillit.h"

unsigned int		g_piece[21] =
{
	PIECE_1,
	PIECE_2,
	PIECE_3,
	PIECE_4,
	PIECE_5,
	PIECE_6,
	PIECE_7,
	PIECE_8,
	PIECE_9,
	PIECE_10,
	PIECE_11,
	PIECE_12,
	PIECE_13,
	PIECE_14,
	PIECE_15,
	PIECE_16,
	PIECE_17,
	PIECE_18,
	PIECE_19,
	PIECE_20,
	PIECE_21,
};

/*
** valid_pieces creates a comparison int, which contains the whole piece as
** binary representation. In the first loop I set the first byte of the comp
** int to the first row, the second byte to second row and so on. That is done
** by shifting the long longs of each row at least 48 bites o the left, so
** that they can be compared with the int. The second row will be shifted 4 more
** so that it can be compared to the second byte, the third row will be shifted
** 8 more and so on.
** In the second part that int representation of the piece will be compared to
** the possible tetrimos, assuming they are set to the upper left corner, which
** is done one step before.
*/

int			valid_pieces(t_piece *pieces, t_board *board)
{
	int				i;
	int				j;
	int				ret;
	unsigned int	comp;

	i = -1;
	while (++i <= board->nbr_pieces)
	{
		j = -1;
		comp = 0;
		while (++j < 4)
			comp = comp | (pieces[i].origin[j] >> (48 + (4 * j)));
		ret = -1;
		j = -1;
		while (++j < 21 && ret != 1)
		{
			if (comp == g_piece[j])
				ret = 1;
		}
		if (ret == -1)
			return (-1);
	}
	return (0);
}

/*
** recieves the row and the columns of the character '#' found in the file.
** Calculates the piece number and the row number for each piece in order
** to set the bit in each long long of the piece to the right value.
*/

void		p_bin(int col, int rows, t_piece *pieces, t_board *board)
{
	int					nbr;
	unsigned long long	value;
	int					row_piece;
	char				alph;

	alph = 'A';
	nbr = rows / 5;
	(pieces[nbr].piece_nbr == 0) ? (pieces[nbr].piece_nbr = nbr) : (0);
	value = 1LLU << (63 - col);
	row_piece = rows % 5;
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

/*
** reads the file line by line and checks if the input is valid. It does check
** if the input is anything else than a piece or a newline. If it is a '#' it
** will be passed to the function that converts it into the binary
** representaion. It doesn't check though if the piece is actually valid,
** that will be done in another step.
*/

int			validate(char *file, t_piece *pieces, t_board *board)
{
	char	*line;
	int		fd;
	int		col;
	int		row;
	int		ret_value;

	ret_value = 0;
	row = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strjoin(line, "\n");
		col = -1;
		while (line[++col])
		{
			if ((line[col] == '.' || line[col] == '#') && col < 4)
				(line[col] == '#') ? (p_bin(col, row, pieces, board)) : (0);
//?shouldnt it be line[col] and not line[0]?////////////////////////////////////////////////////////////////////////////////////////////////////////////////////?
			else if ((!(line[0] == '\n' && row % 5 == 4) &&
				!(col == 4 && line[col] == '\n')) || row >= 131)
				return (-1);
		}
		free(line);
		row++;
	}
	close(fd);
	return (ret_value);
}

/*
** init_board_pieces allocates the needed memory and sets the values to zero.
*/

void		init_board_pieces(t_board *board, t_piece *pieces)
{
	int	cnt;
	int	cnt2;
	int	cnt3;

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
		pieces[cnt].origin = (unsigned long long *)
			malloc(sizeof(unsigned long long) * 4);
		pieces[cnt].placed = (unsigned long long *)
			malloc(sizeof(unsigned long long) * 4);
		cnt2 = -1;
		while (++cnt2 < 4)
			pieces[cnt].origin[cnt2] = 0;
	}
}
