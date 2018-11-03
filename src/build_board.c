int	build_board(struct piece, board, start, end)
{
	if (place_piece(piece, board, start, end) == 1)
	{
		if (piece->next)
		{
			if (build_board(piece->next, board, start, end) = -1)
			{
				remove_last(piece);
				build_board(piece, board, start + 1, end);
			}
		}
		else
			return (-1);
	}
	else
		return (1);
}

int	place_piece(struct piece, board, column, row, **end)
{
	int	set;

	set = 0;
	while (column <= end && (set = set_piece(piece, board, column)) < 1)
	{
		row = 1;
		while (row <= end && (set = set_piece(piece, board, row)) < 1)
			++row;
		++column;
	}
	if (i > end) 
	{
		*(++end);
		add_row_and_column(board);
	}
}



