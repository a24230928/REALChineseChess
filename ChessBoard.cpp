#include "ChessBoard.h"
#include<cmath>
// default constructor
// create a 9*10 area that all chess are NULL_CHESS
ChessBoard::ChessBoard()
{
    area.clear();
    Chess emptyChess;
    area = BattleArea(9, vector<Chess>(10, emptyChess));
    turn = 0;
}
// TODO: horse / elephant / Soldier 's rules and all rule
bool ChessBoard::isMovable(const Coord &aftercod, const Coord &beforecod) 
{
	Coord before = beforecod;
	Coord after = aftercod;
	if (turn % 2 == 0)//black PLAYER
	{
		switch (area[before.x][before.y].getKind())//which kind of chess
		{
		case 1:
			if (after.x <= 5 && after.x >= 3 && after.y <= 2 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) == 1)
				{
					return 1;
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 0)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 2:
			if (after.x <= 5 && after.x >= 3 && after.y <= 2 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 1)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 3:
			if (after.x <= 8 && after.x >= 0 && after.y <= 4 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 2 && area[(after.x + before.x) / 2][(before.y + after.y) / 2].getKind() == -1)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 4:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0 )
				{
					if (before.y < after.y)
					{
						for (Coord i = before; i.y < after.y; i.y++)
						{
							if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
							{
								return 0;
							}
						}
					}
					else 
					{
						for (Coord i = before; i.y > after.y; i.y--)
						{
							if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
							{
								return 0;
							}
						}
					}
					return 1;
				}
				else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
				{
					if (before.x < after.x)
					{
						for (Coord i = before; i.x < after.x; i.x++)
						{
							if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
							{
								return 0;
							}
						}
					}
					else
					{
						for (Coord i = before; i.x > after.x; i.x--)
						{
							if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
							{
								return 0;
							}
						}
					}
					return 1;
				}
			}
			return 0;
			break;
		case 5:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 1)
				{
					if (before.x < after.x)
					{
						if (area[before.x + 1][before.y].getKind() == -1)
						{
							return 1;
						}
					}
					else
					{
						if (area[before.x - 1][before.y].getKind() == -1)
						{
							return 1;
						}
					}
				}
				else if (abs(after.x - before.x) ==1 && abs(after.y - before.y) == 2)
				{
					if (before.y < after.y)
					{
						if (area[before.x][before.y+1].getKind() == -1)
						{
							return 1;
						}
					}
					else
					{
						if (area[before.x][before.y-1].getKind() == -1)
						{
							return 1;
						}
					}
				}
				return 0;
			}
			return 0;
			break;
		case 6:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0)
			{
				if (area[after.x][after.y].getKind() == -1)//move
				{
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									return 0;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									return 0;
								}
							}
						}
						return 1;
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.y < after.x; i.x++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									return 0;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									return 0;
								}
							}
						}
						return 1;
					}
				}
				else if (area[after.x][after.y].getKind() > 7)//eat
				{
					int eatable = 0;
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.y < after.x; i.x++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
					}
					if (eatable == 1)
					{
						return 1;
					}
				}
			}
			return 0;
			break;
		case 7:
			if (before.x <= 8 && before.x >= 0 && before.y <= 4 && before.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == 1)
				{
					return 1;
				}
			}
			else if (before.x <= 8 && before.x >= 0 && before.y <=9  && before.y >= 5 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() > 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == 1)
				{
					return 1;
				}
				else if (abs(after.x - before.x) == 1 && after.y - before.y == 0)
				{
					return 1;
				}
			}
			return 0;
			break;
		case -1:
			return 0;
			break;
		}
	}
	else if(turn % 2 == 1)//red PLAYER
	{
		switch (area[before.x][before.y].getKind())
		{
		case 8:
			if (after.x <= 5 && after.x >= 3 && after.y <= 9 && after.y >= 7 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) == 1)
				{
					return 1;
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 0)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 9:
			if (after.x <= 5 && after.x >= 3 && after.y <= 9 && after.y >= 7 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 1)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 10:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 5 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 2 && area[(after.x + before.x) / 2][(before.y + after.y) / 2].getKind() == -1)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 11:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
				{
					if (before.y < after.y)
					{
						for (Coord i = before; i.y < after.y; i.y++)
						{
							if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
							{
								return 0;
							}
						}
					}
					else
					{
						for (Coord i = before; i.y > after.y; i.y--)
						{
							if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
							{
								return 0;
							}
						}
					}
					return 1;
				}
				else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
				{
					if (before.x < after.x)
					{
						for (Coord i = before; i.x < after.x; i.x++)
						{
							if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
							{
								return 0;
							}
						}
					}
					else
					{
						for (Coord i = before; i.x > after.x; i.x--)
						{
							if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
							{
								return 0;
							}
						}
					}
					return 1;
				}
			}
			return 0;
			break;
		case 12:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 2 && abs(after.y - before.y) == 1)
				{
					if (before.x < after.x)
					{
						if (area[before.x + 1][before.y].getKind() == -1)
						{
							return 1;
						}
					}
					else
					{
						if (area[before.x - 1][before.y].getKind()== -1)
						{
							return 1;
						}
					}
				}
				else if (abs(after.x - before.x) == 1 && abs(after.y - before.y) == 2)
				{
					if (before.y < after.y)
					{
						if (area[before.x][before.y + 1].getKind() == -1)
						{
							return 1;
						}
					}
					else
					{
						if (area[before.x][before.y - 1].getKind() == -1)
						{
							return 1;
						}
					}
				}
				return 0;
			}
			return 0;
			break;
		case 13:
			if (after.x <= 8 && after.x >= 0 && after.y <= 9 && after.y >= 0)
			{
				if (area[after.x][after.y].getKind() == -1)//move
				{
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									return 0;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									return 0;
								}
							}
						}
						return 1;
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.y < after.x; i.x++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									return 0;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									return 0;
								}
							}
						}
						return 1;
					}
				}
				else if (area[after.x][after.y].getKind() <= 7 && area[after.x][after.y].getKind() >= 1)//eat
				{
					int eatable = 0;
					if (abs(after.x - before.x) == 0 && abs(after.y - before.y) > 0)
					{
						if (before.y < after.y)
						{
							for (Coord i = before; i.y < after.y; i.y++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.y > after.y; i.y--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.y != before.y)
								{
									eatable += 1;
								}
							}
						}
					}
					else if (abs(after.x - before.x) > 0 && abs(after.y - before.y) == 0)
					{
						if (before.x < after.x)
						{
							for (Coord i = before; i.y < after.x; i.x++)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
						else
						{
							for (Coord i = before; i.x > after.x; i.x--)
							{
								if (area[i.x][i.y].getKind() != -1 && i.x != before.x)
								{
									eatable += 1;
								}
							}
						}
					}
					if (eatable == 1)
					{
						return 1;
					}
				}
			}
			return 0;
			break;
		case 14:
			if (before.x <= 8 && before.x >= 0 && before.y <= 9 && before.y >= 5 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == -1)
				{
					return 1;
				}
			}
			else if (before.x <= 8 && before.x >= 0 && before.y <= 4 && before.y >= 0 && (area[after.x][after.y].getKind() == -1 || area[after.x][after.y].getKind() <= 7))
			{
				if (abs(after.x - before.x) == 0 && after.y - before.y == -1)
				{
					return 1;
				}
				else if (abs(after.x - before.x) == 1 && after.y - before.y == 0)
				{
					return 1;
				}
			}
			return 0;
			break;
		case -1:
			return 0;
			break;
		}
	}
	return 1;
}
// set chess on board
void ChessBoard::setChess(const int32_t &uid, const int32_t &kind, const Coord &loc)
{
    area[loc.y][loc.x] = Chess(uid, kind, loc);
}
// get chess ref
Chess &ChessBoard::getChess(const Coord &loc) { return area[loc.y][loc.x]; }
void ChessBoard::moveChess(Chess &c, const Coord &cursorLoc)
{
    if (isMovable(cursorLoc, c.getCurrCoord()))
    {
        // replace the chess on cursor loc
        area[cursorLoc.y][cursorLoc.x] = c;

        // clear current loc
        Chess cleaner;
        area[c.getCurrCoord().y][c.getCurrCoord().x] = cleaner;

        // update the loc
        c.moveCoord(cursorLoc);
    }
}

// set turn
void ChessBoard::setTurn(const int32_t &t) { turn = t; }
// get turn
const int32_t ChessBoard::getTurn() const { return turn; }

// draw
void ChessBoard::drawBoard(const BattleArea &board) const {}
void ChessBoard::undo() {}
void ChessBoard::redo() {}
