#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define BIT_SIZE 63
# define PIECE_1 35968
# define PIECE_2 58368
# define PIECE_3 19520
# define PIECE_4 19968
# define PIECE_5 36352
# define PIECE_6 51328
# define PIECE_7 57856
# define PIECE_8 17600
# define PIECE_9 59392
# define PIECE_10 50240
# define PIECE_11 11776
# define PIECE_12 35008
# define PIECE_13 52224
# define PIECE_14 27648
# define PIECE_15 50688
# define PIECE_16 19584
# define PIECE_17 35904
# define PIECE_18 61440
# define PIECE_19 34952
# define PIECE_20 57856 //duplicate
# define PIECE_21 51328 //duplicate

typedef struct			s_board
{
	char				**result;
	unsigned long long	*bin_board;
	int					nbr_pieces;
	int					boardsize;
}						t_board;

typedef struct			s_piece
{
	unsigned long long	*origin;
	int					lastrow_origin;
	unsigned long long	*placed;
	char				alph_piece;
	int					piece_nbr;
	int					firstrow;
	int					lastrow;
}						t_piece;

void					set_piece_to_top(t_piece *pieces, int i);
void					set_pieces_to_left(t_piece *pieces, t_board *board);
unsigned long long		on_bit(unsigned long long p, int n);
int						unset_piece(t_board *board, t_piece *piece);
int						down_shift(t_piece *piece, int boardsize);
int						right_shift(t_piece *piece, int boardsize);
int						piece_shift(t_piece *piece, int boardsize);
int						set_piece(t_piece *piece, t_board *board,
		int boardsize);
int						set_board(t_piece *pieces, int p, t_board *board,
		int shiftback);
int						piece_reset(t_piece *piece, int full);
int						get_next_line(const int fd, char **line);
void					print_board(t_board *board, int boardsize);
void					get_alph_board(t_piece *pieces, t_board *board,
		int boardsize);
void					init_board_pieces(t_board *board, t_piece *pieces);
int						validate(char *file, t_piece *pieces, t_board *board);
void					piece_to_binary(int count_columns, int count_rows,
		t_piece *pieces, t_board *board);
int						valid_pieces(t_piece *pieces, t_board *board);
void					set_pieces_to_left(t_piece *pieces, t_board *board);
void					set_piece_to_top(t_piece *pieces, int i);
#endif
