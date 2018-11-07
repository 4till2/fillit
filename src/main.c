#include "fillit.h"

int	main(int argc, char **argv)
{
	t_board	board;
	t_piece	*pieces;
	int		i;

	pieces = (t_piece *)malloc(sizeof(t_piece) * 26);
	board.bin_board = (unsigned long long *)
					malloc(sizeof(unsigned long long) * 64);
	init_board_pieces(&board, pieces);
	if (argc != 2 || validate(argv[1], pieces, &board) == -1)
	{
		write(2, "error", 5);
		return (-1);
	}
	set_pieces_to_left(pieces, &board);
	if (valid_pieces(pieces, &board) == -1 || board.nbr_pieces + 1 > 26)
	{
		write(2, "error", 5);
		return (-1);
	}
	i = -1;
	while (++i <= board.nbr_pieces)
		piece_reset(&pieces, i, 1);
	board.boardsize = ft_sqrt(board.nbr_pieces * 4);
write(1,"a..main..\n",10);
	set_board(&pieces, 0, &board, 0);
write(1,"b..main..\n",10);
	get_alph_board(pieces, &board, board.boardsize);
printf("\n NUMBER PIECES = %i\n",board.nbr_pieces + 1);
}
