/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 19:11:03 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/05 13:42:47 by yserkez          ###   ########.fr       */
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
	unsigned long long	*placed; //placed
	char				alph_piece;
	int					piece_nbr;
	int					row_placed;
	int					firstrow;
	int					lastrow;
}						t_piece;

int	set_board(t_piece *pieces, int p, t_board *board, int *boardsize, int shiftback);
int     get_next_line(const int fd, char **line);
#endif
