#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int x0board;
int y0board;

void Pos(vector <vector <int> > a) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int getXpos(int x) {
	int xpos;
	xpos = x0board + 65 * (x - 1) + 5;
	return xpos;
}

int getYpos(int y) {
	int ypos;
	ypos = y0board + 65 * (y - 1) + 5;
	return ypos;
}

bool checkOneStepZeroPlace(vector<vector <int> > pos, int x, int y) {
	int k = 0;
	if (pos[y + 1][x + 1] == 0)
		k++;
	if (pos[y - 1][x - 1] == 0)
		k++;
	if (pos[y + 1][x - 1] == 0)
		k++;
	if (pos[y - 1][x + 1] == 0)
		k++;
	if (k > 0) return true;
	else
		return false;
}

bool checkTwoStepZeroPlace(vector<vector <int> > pos, int x, int y) {
	int k = 0;
	if (pos[y + 2][x + 2] == 0)
		k++;
	if (pos[y - 2][x - 2] == 0)
		k++;
	if (pos[y + 2][x - 2] == 0)
		k++;
	if (pos[y - 2][x + 2] == 0)
		k++;
	if (k > 0) return true;
	else
		return false;
}

bool checkOneStepOtherChess(vector<vector <int> > pos, int x, int y) {
	int k = 0;
	if (abs(pos[y + 1][x + 1] - pos[y][x]) == 1)
		k++;
	if (abs(pos[y - 1][x - 1] - pos[y][x]) == 1)
		k++;
	if (abs(pos[y - 1][x + 1] - pos[y][x]) == 1)
		k++;
	if (abs(pos[y + 1][x - 1] - pos[y][x]) == 1)
		k++;
	if (k > 0) return true;
	else
		return false;
}

bool checkTwoStepOtherChess(vector<vector <int> > pos, int x, int y) {
	int k = 0;
	if (abs(pos[y + 2][x + 2] - pos[y][x]) == 1)
		k++;
	if (abs(pos[y - 2][x - 2] - pos[y][x]) == 1)
		k++;
	if (abs(pos[y - 2][x + 2] - pos[y][x]) == 1)
		k++;
	if (abs(pos[y + 2][x - 2] - pos[y][x]) == 1)
		k++;
	if (k > 0) return true;
	else
		return false;
}

int main()
{

	err().rdbuf(NULL);

	RenderWindow check(VideoMode(1, 1), "saski", Style::Fullscreen);
	Vector2u size = check.getSize();
	check.close();

	float width = size.x;
	float height = size.y;

	if (width > 1920)
		width = 1920;
	if (height > 1080)
		width = 1080;


	RenderWindow window(VideoMode(width, height), "Checkers", Style::Fullscreen);

	Texture BackG;
	BackG.loadFromFile("images/background.png");
	Sprite background;
	background.setTexture(BackG);

	Texture chess_board;
	chess_board.loadFromFile("images/chess.png");
	Sprite board;
	board.setTexture(chess_board);

	Texture WhiteChess;
	WhiteChess.loadFromFile("images/p1.png");
	Sprite white;
	white.setTexture(WhiteChess);

	Texture BlackChess;
	BlackChess.loadFromFile("images/p2.png");
	Sprite black;
	black.setTexture(BlackChess);

	Texture SelectW;
	SelectW.loadFromFile("images/p1Select.png");
	Sprite SelWhite;
	SelWhite.setTexture(SelectW);

	Texture SelectB;
	SelectB.loadFromFile("images/p2Select.png");
	Sprite SelBlack;
	SelBlack.setTexture(SelectB);

	Texture BlackW;
	BlackW.loadFromFile("images/black_wins.png");
	Sprite BlackWin;
	BlackWin.setTexture(BlackW);

	Texture WhiteW;
	WhiteW.loadFromFile("images/white_wins.png");
	Sprite WhiteWin;
	WhiteWin.setTexture(WhiteW);

	WhiteWin.setPosition(1920, 1080);
	BlackWin.setPosition(1920, 1080);
	background.setPosition(0, 0);



	background.setScale(Vector2f(width / 1600, height / 900)); // Сжатие заднего фона

	pair <int, int> boardsetpos;
	boardsetpos.first = (width - 584) / 2; // x координата самой левой верхней точки доски
	boardsetpos.second = (height - 584) / 2; // y координата самой левой верхней точки доски

	board.setPosition(boardsetpos.first, boardsetpos.second);

	x0board = boardsetpos.first + 32;
	y0board = boardsetpos.second + 32;

	vector <vector <int> > pos(10, vector <int>(10, 0));

	for (int i = 0; i < 10; i++)
		pos[i][0] = 9;

	for (int i = 0; i < 10; i++)
		pos[i][9] = 9;

	for (int j = 0; j < 10; j++)
		pos[0][j] = 9;

	for (int j = 0; j < 10; j++)
		pos[9][j] = 9;

	vector <Sprite> wchess(12);
	vector <Sprite> bchess(12);
	for (int i = 0; i < 12; i++)
		wchess[i].setTexture(WhiteChess);
	for (int i = 0; i < 12; i++)
		bchess[i].setTexture(BlackChess);
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 9; j++) {
			if ((i + j) % 2 != 0)
				pos[i][j] = 2;
		}
	}
	for (int i = 6; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if ((i + j) % 2 != 0)
				pos[i][j] = 1;
		}
	}
	int wh = 0;
	int bl = 0;
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 9; j++) {
			if (pos[i][j] == 1) {
				wchess[wh].setPosition(getXpos(j), getYpos(i));
				wh++;
			}
			if (pos[i][j] == 2) {
				bchess[bl].setPosition(getXpos(j), getYpos(i));
				bl++;
			}
			if (pos[i][j] == 3) {
				SelWhite.setPosition(getXpos(j), getYpos(i));
			}
			if (pos[i][j] == 4) {
				SelBlack.setPosition(getXpos(j), getYpos(i));
			}
		}
	bool OneMore = false;
	bool END = false;
	int xmouse = 0;
	int ymouse = 0;
	int xcor = 0;
	int ycor = 0;
	int xSel;
	int ySel;
	int WhiteDead = 0;
	int BlackDead = 0;
	// 1 - белые 2 - чёрные
	int x, y; // номера клетки
	bool Select = false;
	pair <int, int> corner;

	int side = 1;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			for (int i = 0; i < 12; i++)
				wchess[i].setPosition(1920, 1080);
			for (int i = 0; i < 12; i++)
				bchess[i].setPosition(1920, 1080);
			SelWhite.setPosition(1920, 1080);
			SelBlack.setPosition(1920, 1080);
			wh = 0;
			bl = 0;
			for (int i = 1; i < 9; i++)
				for (int j = 1; j < 9; j++) {
					if (pos[i][j] == 1) {
						wchess[wh].setPosition(getXpos(j), getYpos(i));
						wh++;
					}
					if (pos[i][j] == 2) {
						bchess[bl].setPosition(getXpos(j), getYpos(i));
						bl++;
					}
					if (pos[i][j] == 3) {
						SelWhite.setPosition(getXpos(j), getYpos(i));
					}
					if (pos[i][j] == 4) {
						SelBlack.setPosition(getXpos(j), getYpos(i));
					}
				}

			if (WhiteDead == 12) {
				BlackWin.setPosition(boardsetpos.first, boardsetpos.second);
				END = true;
			}
			if (BlackDead == 12) {
				WhiteWin.setPosition(boardsetpos.first, boardsetpos.second);
				END = true;
			}

			if (event.type == Event::Closed)
				window.close();


			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					window.close();


			if (END)
				if (event.type == Event::KeyPressed)
					if (event.key.code == Keyboard::Enter) {

						WhiteWin.setPosition(1920, 1080);
						BlackWin.setPosition(1920, 1080);

						for (int i = 0; i < 12; i++) {
							wchess[i].setPosition(1920, 1080);
							bchess[i].setPosition(1920, 1080);
						}

						SelBlack.setPosition(1920, 1080);
						SelWhite.setPosition(1920, 1080);

						for (int i = 1; i < 4; i++) {
							for (int j = 1; j < 9; j++) {
								if ((i + j) % 2 != 0)
									pos[i][j] = 2;
							}
						}

						for (int i = 6; i < 9; i++) {
							for (int j = 1; j < 9; j++) {
								if ((i + j) % 2 != 0)
									pos[i][j] = 1;
							}
						}
						WhiteDead = 0;
						BlackDead = 0;
						END = false;
					}

			if (!END)
				if (event.type == Event::MouseButtonPressed) {
					if (event.mouseButton.button == Mouse::Left) {

						xmouse = event.mouseButton.x;
						ymouse = event.mouseButton.y;

						x = (xmouse - x0board) / 65 + 1;
						y = (ymouse - y0board) / 65 + 1;

						corner.first = (xmouse - x0board) / 65 * 65 + x0board + 5;
						corner.second = (ymouse - y0board) / 65 * 65 + y0board + 5;

						if (xmouse >= x0board && ymouse >= y0board && xmouse <= x0board + 520 && ymouse <= y0board + 520) {
							if (Select && x == xSel && y == ySel && !OneMore) {
								pos[y][x] = side;
								Select = false;
							}
							else
								if (Select && abs(x - xSel) == 2 && abs(y - ySel) == 2) {
									if (side == 1 && Select) {
										if (pos[y + (ySel - y) / 2][x + (xSel - x) / 2] == 2 && pos[y][x] == 0) {
											pos[y + (ySel - y) / 2][x + (xSel - x) / 2] = 0;
											pos[y][x] = 1;
											pos[ySel][xSel] = 0;
											Select = false;
											OneMore = false;
											BlackDead++;
											side = 2;
											if (pos[y + 1][x + 1] == 2 && pos[y + 2][x + 2] == 0) {
												Select = true;
												OneMore = true;
												pos[y][x] = 3;
												xSel = x;
												ySel = y;
												side = 1;
											}
											if (pos[y - 1][x - 1] == 2 && pos[y - 2][x - 2] == 0) {
												Select = true;
												OneMore = true;
												pos[y][x] = 3;
												xSel = x;
												ySel = y;
												side = 1;
											}
											if (pos[y - 1][x + 1] == 2 && pos[y - 2][x + 2] == 0) {
												Select = true;
												OneMore = true;
												pos[y][x] = 3;
												xSel = x;
												ySel = y;
												side = 1;
											}
											if (pos[y + 1][x - 1] == 2 && pos[y + 2][x - 2] == 0) {
												Select = true;
												OneMore = true;
												pos[y][x] = 3;
												xSel = x;
												ySel = y;
												side = 1;
											}
										}
									}
									else
										if (side == 2 && Select) {
											if (pos[y + (ySel - y) / 2][x + (xSel - x) / 2] == 1 && pos[y][x] == 0) {
												pos[y + (ySel - y) / 2][x + (xSel - x) / 2] = 0;
												pos[y][x] = 2;
												pos[ySel][xSel] = 0;
												Select = false;
												OneMore = false;
												WhiteDead++;
												side = 1;
												if (pos[y + 1][x + 1] == 1 && pos[y + 2][x + 2] == 0) {
													Select = true;
													OneMore = true;
													pos[y][x] = 4;
													xSel = x;
													ySel = y;
													side = 2;
												}
												if (pos[y - 1][x - 1] == 1 && pos[y - 2][x - 2] == 0) {
													Select = true;
													OneMore = true;
													pos[y][x] = 4;
													xSel = x;
													ySel = y;
													side = 2;
												}
												if (pos[y - 1][x + 1] == 1 && pos[y - 2][x + 2] == 0) {
													Select = true;
													OneMore = true;
													pos[y][x] = 4;
													xSel = x;
													ySel = y;
													side = 2;
												}
												if (pos[y + 1][x - 1] == 1 && pos[y + 2][x - 2] == 0) {
													Select = true;
													OneMore = true;
													pos[y][x] = 4;
													xSel = x;
													ySel = y;
													side = 2;
												}
											}
										}

								}
								else
									if (Select && abs(x - xSel) == 1 && abs(y - ySel) == 1 && pos[y][x] == 0 && !OneMore) {
										if (side == 1 && Select) {
											pos[ySel][xSel] = 0;
											pos[y][x] = 1;
											side = 2;
											Select = false;
										}
										if (side == 2 && Select) {
											pos[ySel][xSel] = 0;
											pos[y][x] = 2;
											side = 1;
											Select = false;
										}
									}
									else {
										if (!Select && side == 1) {
											if ((checkOneStepZeroPlace(pos, x, y) || (pos[y + 1][x + 1] == 2 && pos[y + 2][x + 2] == 0) || (pos[y - 1][x - 1] == 2 && pos[y - 2][x - 2] == 0) || (pos[y - 1][x + 1] == 2 && pos[y - 2][x + 2] == 0) || (pos[y + 1][x - 1] == 2 && pos[y + 2][x - 2] == 0))) {
												if (pos[y][x] == 1) {
													pos[y][x] = 3;
													Select = true;
													ySel = y;
													xSel = x;
												}
											}
										}
										if (!Select && side == 2) {
											if ((checkOneStepZeroPlace(pos, x, y) || (pos[y + 1][x + 1] == 1 && pos[y + 2][x + 2] == 0) || (pos[y - 1][x - 1] == 1 && pos[y - 2][x - 2] == 0) || (pos[y - 1][x + 1] == 1 && pos[y - 2][x + 2] == 0) || (pos[y + 1][x - 1] == 1 && pos[y + 2][x - 2] == 0))) {
												if (pos[y][x] == 2) {
													pos[y][x] = 4;
													Select = true;
													ySel = y;
													xSel = x;
												}
											}
										}
									}
						}
					}
					Pos(pos);
				}
		}
		window.clear();
		window.draw(background);
		window.draw(board);
		for (int i = 0; i < 12; i++) {
			window.draw(wchess[i]);
		}
		for (int i = 0; i < 12; i++) {
			window.draw(bchess[i]);
		}
		window.draw(SelBlack);
		window.draw(SelWhite);
		window.draw(BlackWin);
		window.draw(WhiteWin);
		window.display();
	}
	return 1;
}