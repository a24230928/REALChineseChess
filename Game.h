#pragma once
#define PLAYER_RED 1
#define PLAYER_BLACK 0

#include "ChessBoard.h"

using namespace std;

typedef vector<BattleArea> BattleHistory;
typedef vector<string> BattleReport;

class Game
{
public:
    Game();
    Game(const string &fileName);

    void saveFile(const string &fileName) const;
    void loadFile(const string &fileName);
	ChessBoard& getboard();
    const bool isCheckmate();
    const bool isCheck();
	vector<Coord> promptMovement(Coord);
	vector<Coord> promptCapture(Coord);
    void controll();
    void writeReport();
    const uint16_t playerNow() const;

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
    Coord controller;
};