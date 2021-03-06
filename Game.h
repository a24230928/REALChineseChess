#pragma once
#define PLAYER_RED 1
#define PLAYER_BLACK 0
#define max_x 50
#define max_y 22

#include "ChessBoard.h"

using namespace std;

typedef vector<BattleArea> BattleHistory;
typedef vector<string> BattleReport;

class Game
{
public:
    Game();
    Game(const string &fileName);

    void saveFile(const string &fileName);
    void loadFile(const string &fileName);

    ChessBoard &getboard();

    const int isCheckmate();
    const bool isCheck();

    vector<Coord> promptMovement(Coord);
    vector<Coord> promptCapture(Coord);

    void writeReport(Coord,Coord);
    void writeHistory(const BattleArea &oldArea);
    void switchPlayer();
	BattleReport getReport();
    const uint16_t playerNow() const;

	void undo();
	void redo();

    static void controll(const int32_t &xOffset, const int32_t &yOffSet);
    static void controll(const int32_t &specified);
	static Coord getController();

private:
    // Store old battle area
    BattleHistory history;

    // Store battle report(text)
    BattleReport report;

    // player's identity
    uint16_t player;

    // Chess board
    ChessBoard board;

    // Controller's coord
    static Coord controller;
};