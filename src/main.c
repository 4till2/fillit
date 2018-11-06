/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserkez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:25:24 by yserkez           #+#    #+#             */
/*   Updated: 2018/11/06 10:46:28 by yserkez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fillit.h"

int		main(int argc, char **argv)
{
	t_board	board;
	t_piece	*pieces;
	int		boardsize;

	boardsize = 4;
	pieces =  (t_piece *)malloc(sizeof(t_piece) * 26);
	init_board_pieces(&board, pieces);
	if (argc != 2 || validate(argv[1], pieces, &board) == -1)
	{
		write(2, "error", 5);
		return (-1);
	}
	//prntem(pieces);
	set_pieces_to_left(pieces, &board);
	if (valid_pieces(pieces, &board) == -1)
	{
		write(2, "error", 5);
		return (-1);
	}
	int i = -1;
	while (++i < board.nbr_pieces + 1)
		piece_reset(&pieces[i], 1);

	prntdec(pieces);
//	board.bin_board[0] = pieces[0].placed[0];
//	board.bin_board[1] = pieces[0].placed[1];
//	board.bin_board[2] = pieces[0].placed[2];
//	board.bin_board[3] = pieces[0].placed[3];
//
	set_board(pieces,0, &board, &boardsize, 0);
printf("board : %llu\n",convert(board.bin_board[0]));
printf("board : %llu\n",board.bin_board[1]);
printf("board : %llu\n",board.bin_board[2]);
printf("board : %llu\n",board.bin_board[3]);
//	prntbin(pieces);
	get_alph_board(pieces, &board, boardsize);
printf("\n %i", boardsize);
	//printf("%i", boardsize);
}
