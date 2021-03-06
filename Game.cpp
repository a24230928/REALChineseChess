#include "Game.h"
#include <fstream>

using namespace std;

Coord Game::controller;

// default constructor
// clear all record
// player = RED
// controller's coord = (0, 0)
Game::Game()
{
	history.clear();
	report.clear();
	player = PLAYER_RED;
	controller.x = 0;
	controller.y = 0;
}

// continue previous game
// player = last character in file
// controller's coord = (0, 0)
Game::Game(const string &fileName)
{
	loadFile(fileName);
	// set controller's coord
	controller.x = 0;
	controller.y = 0;
}

void Game::saveFile(const string &fileName)
{
	ofstream save(fileName, std::ofstream::out);
	for (int16_t row = 0; row < 10; row++)
	{
		for (int16_t col = 0; col < 9; col++)
		{
			Coord currLoc;
			currLoc.x = col;
			currLoc.y = row;
			Chess &c = board.getChess(currLoc);
			save << c.getKind() << " ";
		}
		save << endl;
	}
	save << player;
	save.close();
}

void Game::loadFile(const string &fileName)
{
	// load file and set chess
	ifstream save;
	save.open(fileName);
	if (save.is_open())
	{ // uid start at 0
		for (int16_t row = 0, uid = 0; row < 10; row++)
		{
			for (int16_t col = 0; col < 9; col++, uid++)
			{
				// set data
				Coord currLoc;
				currLoc.x = col;
				currLoc.y = row;
				int32_t kind;
				save >> kind;
				// create chess
				board.setChess(uid, kind, currLoc);
			}
		}
		// set player
		save >> player;
	}
	save.close();
}
//0 no thing 1 black win 2 red win
const int Game::isCheckmate()
{
	int black = 0, red = 0;
	for (int i = 3, other = 0, die = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			Coord temp;
			temp.x = i;
			temp.y = j;
			if (board.getChess(temp).getKind() == 1)
			{
				black = 1;
			}
			if (board.getChess(temp).getKind() == 8)
			{
				red = 1;
			}
		}
	}
	for (int i = 3, other = 0, die = 0; i <= 5; i++)
	{
		for (int j = 7; j <= 9; j++)
		{
			Coord temp;
			temp.x = i;
			temp.y = j;
			if (board.getChess(temp).getKind() == 8)
			{
				red = 1;
			}
			if (board.getChess(temp).getKind() == 1)
			{
				black = 1;
			}
		}
	}
	if (red == 1 && black == 1)
	{
		return 0;
	}
	else if (red == 1 && black == 0)
	{
		return 2;
	}
	else if (red == 0 && black == 1)
	{
		return 1;
	}
}
ChessBoard &Game::getboard()
{
	return board;
}
const bool Game::isCheck()
{
	Coord general_coord;
	// check player_red is been check
	if (player == PLAYER_RED)
	{
		for (int i = 3, flag = 0; i <= 5; i++)
		{
			for (int j = 7; j <= 9; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				Chess &general = board.getChess(temp);
				if (general.getKind() == 1)
				{
					general_coord.x = i;
					general_coord.y = j;
					flag = 1;
					break;
				}
				if (flag == 1)
				{
					break;
				}
			}
		}
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				if (board.isMovable(general_coord, temp, PLAYER_BLACK) == true)
				{
					return 1;
				}
			}
		}
	}
	// check player_black is been check
	else if (player == PLAYER_BLACK)
	{
		for (int i = 3, flag = 0; i <= 5; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				Chess &general = board.getChess(temp);
				if (general.getKind() == 1)
				{
					general_coord.x = i;
					general_coord.y = j;
					flag = 1;
					break;
				}
				if (flag == 1)
				{
					break;
				}
			}
		}
		for (int i = 0; i <= 8; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				Coord temp;
				temp.x = i;
				temp.y = j;
				if (board.isMovable(general_coord, temp, PLAYER_RED) == true)
				{
					return 1;
				}
			}
		}
	}
	return false;
}
vector<Coord> Game::promptCapture(const Coord curr)
{
	vector<Coord> Capture;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			Coord temp;
			temp.x = i;
			temp.y = j;
			if (board.getChess(temp).getKind() != -1 && board.isMovable(temp, curr, player) == true && board.getChess(curr).getKind() != -1)
			{
				Capture.push_back(temp);
			}
		}
	}
	return Capture;
}
vector<Coord> Game::promptMovement(const Coord curr)
{
	vector<Coord> Movement;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			Coord temp;
			temp.x = i;
			temp.y = j;
			if (board.getChess(temp).getKind() == -1 && board.isMovable(temp, curr, player) == true && board.getChess(curr).getKind() != -1)
			{
				Movement.push_back(temp);
			}
		}
	}
	return Movement;
}

void Game::writeReport(Coord pre, Coord controller)
{
	int kind = board.getChess(controller).getKind();
	Coord curr = controller;
	// define string
	const static string duplicateofChinese[4] = { "前後", "前中後", "前中後", "前二三後" };
	string kindofChinese = "將士象車馬包足帥仕相車馬炮兵"s;
	const static string numberChinese[2] = { "１２３４５６７８９", "九八七六五四三二一" };
	const static string verbofChinese = "平進退";
	string text = ""s;
	// Set the first word
	text += kindofChinese[(kind - 1) * 2];
	text += kindofChinese[(kind - 1) * 2 + 1];
	// check the how many same kind of chess on the same x INDEX [0](how many) [1]this
	// chess index [2] the bool of
	short duplicate[3] = { 0, 0, 0 };
	// check duplicate and set second word
	for (int i = 0; i <= 9; i++)
	{
		Coord checkCoord;
		checkCoord.x = pre.x;
		checkCoord.y = i;
		const Chess& checkChess = board.getChess(checkCoord);
		if (pre.x == checkCoord.x && pre.y == checkCoord.y)
		{
			duplicate[0] += 1;
			duplicate[1] = duplicate[0];
		}
		else if (checkChess.getKind() == kind && (controller.x != checkCoord.x && controller.y != checkCoord.y))
		{
			duplicate[0] += 1;
		}
		if (duplicate[0] > 1 && i == 9)
		{
			duplicate[2] = 1;
			if (player == 1)
			{
				text += duplicateofChinese[duplicate[0] - 2][(duplicate[1] - 1) * 2];
				text += duplicateofChinese[duplicate[0] - 2][(duplicate[1] - 1) * 2 + 1];
			}
			else
			{
				text += duplicateofChinese[duplicate[0] - 2]
					[(duplicate[0] - duplicate[1]) * 2];

				text += duplicateofChinese[duplicate[0] - 2]
					[(duplicate[0] - duplicate[1]) * 2 + 1];
			}
		}
		else if (i == 9)
		{
			text += numberChinese[player][(pre.x) * 2];
			text += numberChinese[player][(pre.x) * 2 + 1];
		}
	}
	if (player == 1)
	{
		//text = "紅：" + text;
		if (pre.x == curr.x)
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[2];
				text += verbofChinese[3];
				text += numberChinese[1][numberChinese[1].size() - (pre.y - curr.y - 1) * 2 - 2];
				text += numberChinese[1][numberChinese[1].size() - (pre.y - curr.y - 1) * 2 - 1];
			}
			else
			{
				text += verbofChinese[4];
				text += verbofChinese[5];
				text += numberChinese[1][numberChinese[1].size() - (curr.y - pre.y - 1) * 2 - 2];
				text += numberChinese[1][numberChinese[1].size() - (curr.y - pre.y - 1) * 2 - 1];
			}
		}
		else if (pre.y == curr.y)
		{
			text += verbofChinese[0];
			text += verbofChinese[1];
			text += numberChinese[1][(curr.x) * 2];
			text += numberChinese[1][(curr.x) * 2 + 1];
		}
		else
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[2];
				text += verbofChinese[3];
				text += numberChinese[1][(curr.x) * 2];
				text += numberChinese[1][(curr.x) * 2 + 1];
			}
			else
			{
				text += verbofChinese[4];
				text += verbofChinese[5];
				text += numberChinese[1][(curr.x) * 2];
				text += numberChinese[1][(curr.x) * 2 + 1];
			}
		}
	}
	else
	{
		//text = "黑：" + text;
		if (pre.x == curr.x)
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[4];
				text += verbofChinese[5];
				text += numberChinese[0][(pre.y - curr.y - 1) * 2];
				text += numberChinese[0][(pre.y - curr.y - 1) * 2 + 1];
			}
			else
			{
				text += verbofChinese[2];
				text += verbofChinese[3];
				text += numberChinese[0][(curr.y - pre.y - 1) * 2];
				text += numberChinese[0][(curr.y - pre.y - 1) * 2 + 1];
			}
		}
		else if (pre.y == curr.y)
		{
			text += verbofChinese[0];
			text += verbofChinese[1];
			text += numberChinese[0][(curr.x) * 2];
			text += numberChinese[0][(curr.x) * 2 + 1];
		}
		else
		{
			if (curr.y < pre.y)
			{
				text += verbofChinese[4];
				text += verbofChinese[5];
				text += numberChinese[0][(curr.x) * 2];
				text += numberChinese[0][(curr.x) * 2 + 1];
			}
			else
			{
				text += verbofChinese[2];
				text += verbofChinese[3];text += numberChinese[0][(curr.x) * 2];
        text += numberChinese[0][(curr.x) * 2 + 1];
      }
    }
  }
  // write report
  report.push_back(text);
}

void Game::writeHistory(const BattleArea &oldArea)
{
	history.push_back(oldArea);
}
void Game::switchPlayer() 
{ 
	if (player == PLAYER_BLACK)
		player = PLAYER_RED;
	else
		player = PLAYER_BLACK;
}
BattleReport Game::getReport()
{
	return report;
}
const uint16_t Game::playerNow() const { return player; }

void Game::controll(const int32_t &xOffset, const int32_t &yOffset)
{
	controller.x += xOffset;
	controller.y += yOffset;
}
// specified
void Game::controll(const int32_t &specifed)
{
	// x < BoardInitX or x >= max_x
	// let contoller.x be the specifed value (max_x - 1 or BoardInitX)
	if (specifed == max_x - 1 || specifed == 32)
		controller.x = specifed;

	// y < BoardInitY or y >= max_y
	// let controller.y be the specifed value(max_y - 1 or BoardInitY)
	if (specifed == max_y - 1 || specifed == 2)
		controller.y = specifed;
}

Coord Game::getController()
{
	return controller;
}

void Game::undo()
{
	if (history.size() > 0) 
	{
		board.getArea() = *(history.end() - 1);
		history.pop_back();
	}
}