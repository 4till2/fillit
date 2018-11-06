/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 19:11:03 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/06 10:23:06 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"

#define BIT_SIZE 63
#define PIECE_1
typedef struct			s_board
{
	char				**result;
	unsigned long long	*bin_board;
	int					nbr_pieces;
	int					last_placed_piece;
}						t_board;

typedef struct			s_piece
{
	unsigned long long	*origin; //origin
	int					lastrow_origin;
	unsigned long long	*placed; //placed
	char				alph_piece;
	int					piece_nbr;
	int					row_placed;
	int					firstrow;
	int					lastrow;
}						t_piece;

unsigned long long		on_bit(unsigned long long p, int n);
int						unset_piece(t_board *board,t_piece *piece);
int						down_shift(t_piece *piece,int boardsize);
int						right_shift(t_piece *piece,int boardsize);
int						piece_shift(t_piece *piece, int boardsize);
int						set_piece(t_piece *piece,t_board  *board,int  boardsize);
int						set_board(t_piece *pieces, int p, t_board *board, int *boardsize, int shiftback);
unsigned long long		convert(unsigned long long dec);
int						piece_reset(t_piece *piece, int full);
int						set_board(t_piece *pieces, int p, t_board *board, int *boardsize, int shiftback);
int    					get_next_line(const int fd, char **line);
void					prntbin(t_piece *pieces);
void					prntdec(t_piece *pieces);
void					print_board(t_board *board, int boardsize);
void					get_alph_board(t_piece *pieces, t_board *board, int boardsize);
void					init_board_pieces(t_board *board, t_piece *pieces);
int						validate(char *file, t_piece *pieces, t_board *board);
void					piece_to_binary(int count_columns, int count_rows, t_piece *pieces, t_board *board);
int						valid_pieces(t_piece *pieces, t_board *board);
void					set_pieces_to_left(t_piece *pieces, t_board *board);
void					set_piece_to_top(t_piece *pieces, int i);
#endif
