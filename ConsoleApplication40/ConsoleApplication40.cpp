#include"stdafx.h"
#include"menu.h"
#include<SFML\Graphics.hpp>
#include<iostream>
#include<iterator>
#include<map>
#include<SFML\Audio.hpp>
#include<set>
#include<queue>
#include<string>
#include<fstream>
#include<cmath>
#include<iterator>
#include<stack>
using namespace std;
using namespace sf;

//global
int lives = 3, lives2 = 3;
int framecounter = 0, frame = 0, framecounter2 = 0, frame2 = 0, framecounterdemon = 0, framedemon = 0, frameangel = 0, framecounterangel = 0, framecounterrobot = 0, framerobot = 0;
int state = 5;
bool firstmovepacone = false, firstmovepactwo = false;
char selector;
bool g1 = 0, g2 = 0, g3 = 0, NextRun1 = 0, NextRun2 = 0, NextRun3 = 0;
bool oncegameover = 0;
pair<int, int>direction, direction2, direction3;
char prevchoice1 = 'p', prevchoice2 = 'p', demon = 'r', angel = 'r', robot = 'r';
int score1 = 0, score2 = 0;
bool pickupschecker[36][28] = { { 0 } };
bool pickupschecker2[36][28] = { { 0 } };
stack<pair<int, int>>path, path2, path3;
set <int > close_set;
//map ( ID , pair[ f value, pair( x, y ) ] ) : akbar habda fe hayat shehab
map<int, pair<int, pair<int, int>>>open_set;
pair<int*, int*>ghost_real_pos, ghost2_real_pos, ghost3_real_pos;

//initializing ghosts positions
pair<int, int>Blueghost_pos = make_pair(17, 14), Redghost_pos = make_pair(17, 13), Orangeghost_pos = make_pair(17, 15);

//characters inside the map file
string avaialble_moves_RLUD[4] = { "-+ud<*", "+-ud>/", "+d<>|", "+|u><" };

struct Astar
{
	char pixel, AI = ' ';
	int h, g = 0, f;
	pair< int, int> parent;
	int id;
};

//function akbar habda fe hayat shehab
pair<int, pair<int, int>> Min_F(map<int, pair<int, pair<int, int>>> openst)
{
	map<int, pair<int, pair<int, int>>>::iterator it;

	it = openst.begin();
	pair<int, int>min = make_pair(-1, it->second.first);
	for (auto i = openst.begin()++; i != openst.end(); i++)
	{

		if (i->second.first < min.second)
		{
			it = i;
			min.first = i->first;
			min.second = i->second.first;

		}
	}
	return  make_pair(it->first, make_pair(it->second.second.first, it->second.second.second));

}

void PathFind(Astar ary[36][28], int ghost_start_row, int ghost_start_col, int target_row, int target_col, char y)
{
	char k = y;

	pair<int, int>pathfinder;
	pathfinder.first = ary[target_row][target_col].parent.first;
	pathfinder.second = ary[target_row][target_col].parent.second;

	if (y == 'R')
	{
		ary[pathfinder.first][pathfinder.second].AI = 'R';
		path.push(make_pair(pathfinder.first, pathfinder.second));

	}

	else if (y == 'B')
	{

		ary[pathfinder.first][pathfinder.second].AI = 'B';
		path2.push(make_pair(pathfinder.first, pathfinder.second));




	}
	else
	{


		path3.push(make_pair(pathfinder.first, pathfinder.second));


	}



	if (pathfinder.first != ghost_start_row || pathfinder.second != ghost_start_col)
		PathFind(ary, ghost_start_row, ghost_start_col, pathfinder.first, pathfinder.second, k);


}





void AI(Astar ary[36][28], int ghost_position_row, int ghost_position_col, int target_first_row, int target_first_col, char x)
{
	char y = 'i', z = 'i'; int cost = 0;
	if (x == 'O')
	{

		y = 'i'; z = 'R';
		cost = 100;

	}
	else if (x == 'B')
	{
		cost = 100000;
		y = 'R', z = 'R';
	}



	//Up                                                                 //.count is a function that finds values in sets
	if (close_set.count(ary[ghost_position_row - 1][ghost_position_col].id) == 0)
	{

		if (open_set.count(ary[ghost_position_row - 1][ghost_position_col].id) == 0)
		{

			ary[ghost_position_row - 1][ghost_position_col].h = (abs(ghost_position_row - 1 - target_first_row) + abs(ghost_position_col - target_first_col));
			ary[ghost_position_row - 1][ghost_position_col].g = ary[ghost_position_row][ghost_position_col].g + 1;
			ary[ghost_position_row - 1][ghost_position_col].f = ary[ghost_position_row - 1][ghost_position_col].h + ary[ghost_position_row - 1][ghost_position_col].g;
			if (ary[ghost_position_row - 1][ghost_position_col].AI == y || ary[ghost_position_row + 1][ghost_position_col].AI == z)
				ary[ghost_position_row - 1][ghost_position_col].f += cost;




			//setting pairent


			ary[ghost_position_row - 1][ghost_position_col].parent.first = ghost_position_row;
			ary[ghost_position_row - 1][ghost_position_col].parent.second = ghost_position_col;

			open_set[ary[ghost_position_row - 1][ghost_position_col].id] = make_pair(ary[ghost_position_row - 1][ghost_position_col].f, make_pair(ghost_position_row - 1, ghost_position_col));
			if (ary[ghost_position_row - 1][ghost_position_col].pixel == '0')
				open_set.erase(ary[ghost_position_row - 1][ghost_position_col].id);


		}
	}


	//down
	if (close_set.count(ary[ghost_position_row + 1][ghost_position_col].id) == 0)
	{

		if (open_set.count(ary[ghost_position_row + 1][ghost_position_col].id) == 0)
		{

			ary[ghost_position_row + 1][ghost_position_col].h = (abs(ghost_position_row + 1 - target_first_row) + abs(ghost_position_col - target_first_col));
			ary[ghost_position_row + 1][ghost_position_col].g = ary[ghost_position_row][ghost_position_col].g + 1;
			ary[ghost_position_row + 1][ghost_position_col].f = ary[ghost_position_row + 1][ghost_position_col].h + ary[ghost_position_row + 1][ghost_position_col].g;
			if (ary[ghost_position_row + 1][ghost_position_col].AI == y || ary[ghost_position_row + 1][ghost_position_col].AI == z)
				ary[ghost_position_row + 1][ghost_position_col].f += cost;
			//setting parent

			ary[ghost_position_row + 1][ghost_position_col].parent.first = ghost_position_row;
			ary[ghost_position_row + 1][ghost_position_col].parent.second = ghost_position_col;
			open_set[ary[ghost_position_row + 1][ghost_position_col].id] = make_pair(ary[ghost_position_row + 1][ghost_position_col].f, make_pair(ghost_position_row + 1, ghost_position_col));

			if (ary[ghost_position_row + 1][ghost_position_col].pixel == '0')
				open_set.erase(ary[ghost_position_row + 1][ghost_position_col].id);


		}

	}


	// right
	if (close_set.count(ary[ghost_position_row][ghost_position_col + 1].id) == 0)
	{


		if (open_set.count(ary[ghost_position_row][ghost_position_col + 1].id) == 0)
		{


			ary[ghost_position_row][ghost_position_col + 1].h = (abs(ghost_position_row - target_first_row) + abs(ghost_position_col + 1 - target_first_col));
			ary[ghost_position_row][ghost_position_col + 1].g = ary[ghost_position_row][ghost_position_col].g + 1;
			ary[ghost_position_row][ghost_position_col + 1].f = ary[ghost_position_row][ghost_position_col + 1].h + ary[ghost_position_row][ghost_position_col + 1].g;
			if (ary[ghost_position_row][ghost_position_col + 1].AI == y || ary[ghost_position_row + 1][ghost_position_col].AI == z)
				ary[ghost_position_row][ghost_position_col + 1].f += cost;




			//setting parent

			ary[ghost_position_row][ghost_position_col + 1].parent.first = ghost_position_row;
			ary[ghost_position_row][ghost_position_col + 1].parent.second = ghost_position_col;

			open_set[ary[ghost_position_row][ghost_position_col + 1].id] = make_pair(ary[ghost_position_row][ghost_position_col + 1].f, make_pair(ghost_position_row, ghost_position_col + 1));
			if (ary[ghost_position_row][ghost_position_col + 1].pixel == '0')
			{
				open_set.erase(ary[ghost_position_row][ghost_position_col + 1].id);

			}
		}


	}


	//left
	if (close_set.count(ary[ghost_position_row][ghost_position_col - 1].id) == 0)
	{


		if (open_set.count(ary[ghost_position_row][ghost_position_col - 1].id) == 0)
		{


			ary[ghost_position_row][ghost_position_col - 1].h = (abs(ghost_position_row - target_first_row) + abs(ghost_position_col - 1 - target_first_col));
			ary[ghost_position_row][ghost_position_col - 1].g = ary[ghost_position_row][ghost_position_col].g + 1;
			ary[ghost_position_row][ghost_position_col - 1].f = ary[ghost_position_row][ghost_position_col - 1].h + ary[ghost_position_row][ghost_position_col - 1].g;
			if (ary[ghost_position_row][ghost_position_col - 1].AI == y || ary[ghost_position_row + 1][ghost_position_col].AI == z)
				ary[ghost_position_row][ghost_position_col - 1].f += cost;



			//setting parent

			ary[ghost_position_row][ghost_position_col - 1].parent.first = ghost_position_row;
			ary[ghost_position_row][ghost_position_col - 1].parent.second = ghost_position_col;

			open_set[ary[ghost_position_row][ghost_position_col - 1].id] = make_pair(ary[ghost_position_row][ghost_position_col - 1].f, make_pair(ghost_position_row, ghost_position_col - 1));
			if (ary[ghost_position_row][ghost_position_col - 1].pixel == '0')
			{
				open_set.erase(ary[ghost_position_row][ghost_position_col - 1].id);

			}
		}

	}



	// Erasing from open_set

	close_set.insert(ary[ghost_position_row][ghost_position_col].id);
	open_set.erase(ary[ghost_position_row][ghost_position_col].id);

	//next position
	pair<int, int> Next_Ghost_pos;
	Next_Ghost_pos.first = Min_F(open_set).second.first;
	Next_Ghost_pos.second = Min_F(open_set).second.second;


	//check if target reached
	if (Next_Ghost_pos.first != target_first_row || Next_Ghost_pos.second != target_first_col)
		AI(ary, Next_Ghost_pos.first, Next_Ghost_pos.second, target_first_row, target_first_col, x);

	else
	{

		pair<int, int>pathfinder;
		pathfinder.first = target_first_row, pathfinder.second = target_first_col;
		if (x == 'R')
			path.push(make_pair(pathfinder.first, pathfinder.second));

		else if (x == 'B')
			path2.push(make_pair(pathfinder.first, pathfinder.second));

		else if (x == 'O')
			path3.push(make_pair(pathfinder.first, pathfinder.second));


		if (x == 'R')
			PathFind(ary, *ghost_real_pos.first, *ghost_real_pos.second, target_first_row, target_first_col, x);
		else if (x == 'B')
			PathFind(ary, *ghost2_real_pos.first, *ghost2_real_pos.second, target_first_row, target_first_col, x);
		else if (x == 'O')
			PathFind(ary, *ghost3_real_pos.first, *ghost3_real_pos.second, target_first_row, target_first_col, x);


	}
}

//moving the ghost
void  moving(RectangleShape &ghost, pair<int, int>last, pair<int, int>now)
{


	if (last.first == now.first && last.second < now.second)
		ghost.move(25.0 / 10.0, 0);


	if (last.first == now.first && last.second > now.second)
		ghost.move(-25.0 / 10.0, 0);


	if (last.first < now.first&&last.second == now.second)
		ghost.move(0, 25.0 / 10.0);


	if (last.first > now.first&&last.second == now.second)
		ghost.move(0, -25.0 / 10.0);

}

//next astar search loc
pair<int, int> next(pair<int, int>last, pair<int, int>now, pair<int, int>red, stack<pair<int, int>>st, char &khara)
{
	if (st.size() != 0)
	{
		if (last.first == now.first&&last.second < now.second)
		{

			khara = 'd';
			return make_pair(red.first, red.second + 1);
		}
		if (last.first == now.first&&last.second > now.second)
		{
			khara = 'a';
			return make_pair(red.first, red.second - 1);
		}
		if (last.first < now.first&&last.second == now.second)
		{
			khara = 's';
			return make_pair(red.first + 1, red.second);
		}
		if (last.first > now.first&&last.second == now.second)
		{
			khara = 'w';
			return make_pair(red.first - 1, red.second);
		}
	}
}

//return to start pos
bool start(RectangleShape &ghost, RectangleShape &ghost2, RectangleShape &ghost3, RectangleShape &ghost4, CircleShape &palyer, CircleShape &palyer2, int &row, int &col, int &col2, int &row2, char &x, char &y)
{
	if (ghost.getGlobalBounds().intersects(palyer.getGlobalBounds()))
	{
		if (!g1)
		{
			lives--;
			g2 = 0, g3 = 0;
			row = 4, col = 1;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(15 * 25, 17 * 25);
			Blueghost_pos = make_pair(17, 14),
				Redghost_pos = make_pair(17, 13),
				Orangeghost_pos = make_pair(17, 15),
				ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
			x = 'p';
			prevchoice1 = 'p';
		}
		else
		{
			g1 = 0;

			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(25 * Blueghost_pos.second, 25 * Blueghost_pos.first);
			ghost3.setPosition(25 * Orangeghost_pos.second, 25 * Orangeghost_pos.first);
			Redghost_pos = make_pair(17, 13);
			ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;


		}
		palyer.setPosition(col * 25, row * 25);
		palyer2.setPosition(row2 * 25, col2 * 25);
		return 1;


	}
	else if (ghost2.getGlobalBounds().intersects(palyer.getGlobalBounds()))
	{
		if (!g2)
		{
			lives--;
			g1 = 0, g3 = 0;
			row = 4, col = 1;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(15 * 25, 17 * 25);
			Blueghost_pos = make_pair(17, 14),
				Redghost_pos = make_pair(17, 13),
				Orangeghost_pos = make_pair(17, 15),
				ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
			x = 'p';
			prevchoice1 = 'p';
		}
		else
		{
			g2 = 0;
			ghost.setPosition(25 * Redghost_pos.second, 25 * Redghost_pos.first);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(25 * Orangeghost_pos.second, 25 * Orangeghost_pos.first);
			Blueghost_pos = make_pair(17, 14);
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
		}
		palyer.setPosition(col * 25, row * 25);
		palyer2.setPosition(row2 * 25, col2 * 25);
		return 1;


	}
	else if (ghost3.getGlobalBounds().intersects(palyer.getGlobalBounds()))
	{
		if (!g3)
		{
			lives--;
			g2 = 0, g1 = 0;
			row = 4, col = 1;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(15 * 25, 17 * 25);
			Blueghost_pos = make_pair(17, 14),
				Redghost_pos = make_pair(17, 13),
				Orangeghost_pos = make_pair(17, 15),
				ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
			x = 'p';
			prevchoice1 = 'p';
		}
		else
		{
			g3 = 0;
			ghost.setPosition(25 * Redghost_pos.second, 25 * Redghost_pos.first);
			ghost2.setPosition(25 * Blueghost_pos.second, 25 * Blueghost_pos.first);
			ghost3.setPosition(15 * 25, 17 * 25);
			Orangeghost_pos = make_pair(17, 15);
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
		}
		palyer.setPosition(col * 25, row * 25);
		palyer2.setPosition(row2 * 25, col2 * 25);
		return 1;


	}


	else if (ghost.getGlobalBounds().intersects(palyer2.getGlobalBounds()))
	{
		if (!g1)
		{
			lives2--;
			g2 = 0, g3 = 0;
			y = 'p';
			prevchoice2 = 'p';
			col2 = 4;
			row2 = 26;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(15 * 25, 17 * 25);
			Blueghost_pos = make_pair(17, 14),
				Redghost_pos = make_pair(17, 13),
				Orangeghost_pos = make_pair(17, 15),
				ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;


		}
		else
		{
			g1 = 0;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(25 * Blueghost_pos.second, 25 * Blueghost_pos.first);
			ghost3.setPosition(25 * Orangeghost_pos.second, 25 * Orangeghost_pos.first);
			Redghost_pos = make_pair(17, 13);
			ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
		}
		palyer2.setPosition(row2 * 25, col2 * 25);
		palyer.setPosition(col * 25, row * 25);
		return 1;

	}
	else if (ghost2.getGlobalBounds().intersects(palyer2.getGlobalBounds()))
	{
		if (!g2)
		{
			lives2--;
			g1 = 0, g3 = 0;
			y = 'p';
			prevchoice2 = 'p';
			col2 = 4;
			row2 = 26;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(15 * 25, 17 * 25);
			Blueghost_pos = make_pair(17, 14),
				Redghost_pos = make_pair(17, 13),
				Orangeghost_pos = make_pair(17, 15),
				ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;


		}
		else
		{
			g2 = 0;
			ghost.setPosition(25 * Redghost_pos.second, 25 * Redghost_pos.first);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(25 * Orangeghost_pos.second, 25 * Orangeghost_pos.first);
			Blueghost_pos = make_pair(17, 14);
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
		}
		palyer2.setPosition(row2 * 25, col2 * 25);
		palyer.setPosition(col * 25, row * 25);
		return 1;
	}
	else if (ghost3.getGlobalBounds().intersects(palyer2.getGlobalBounds()))
	{
		if (!g3)
		{
			lives2--;
			g2 = 0, g1 = 0;
			y = 'p';
			prevchoice2 = 'p';
			col2 = 4;
			row2 = 26;
			ghost.setPosition(25 * 13, 17 * 25);
			ghost2.setPosition(14 * 25, 17 * 25);
			ghost3.setPosition(15 * 25, 17 * 25);
			Blueghost_pos = make_pair(17, 14),
				Redghost_pos = make_pair(17, 13),
				Orangeghost_pos = make_pair(17, 15),
				ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
			ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
		}
		else
		{
			g3 = 0;
			ghost.setPosition(25 * Redghost_pos.second, 25 * Redghost_pos.first);
			ghost2.setPosition(25 * Blueghost_pos.second, 25 * Blueghost_pos.first);
			ghost3.setPosition(15 * 25, 17 * 25);
			Orangeghost_pos = make_pair(17, 15);
			ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
		}
		palyer2.setPosition(row2 * 25, col2 * 25);
		palyer.setPosition(col * 25, row * 25);
		return 1;

	}

}
//drawing function of the map

void drawing(RenderWindow &w, Astar ary[36][28], RectangleShape box, CircleShape  &pac, CircleShape  &pac2, RectangleShape pickup, RectangleShape pickup2, bool pickupschecker[36][28], bool pickupschecker2[36][28], RectangleShape ghost1, RectangleShape ghost2, RectangleShape ghost3, RectangleShape ghost4, char x, char y, RectangleShape returntomenu, RectangleShape heart, RectangleShape gameoverrect)
{
	if (state == 0 && lives <= 0)
	{
		w.clear();
		w.draw(gameoverrect);
		w.display();
	}
	else if (lives <= 0 && lives2 <= 0)
	{
		w.clear();
		w.draw(gameoverrect);
		w.display();
	}
	else
	{

		w.draw(box);
		// animation
		// player 1 skeleton animation
		Texture skeleton;
		skeleton.loadFromFile("122.png");
		pac.setTexture(&skeleton);

		if (!firstmovepacone)
		{
			pac.setTextureRect(IntRect(37 * frame, 3, 34, 34));
			firstmovepacone = true;
		}
		else if (x == 'd')
		{
			pac.setTextureRect(IntRect(37 * frame, 3, 34, 34));
			if (framecounter == 7)
			{
				frame = (frame + 1) % 4;
				framecounter = 0;

			}
			framecounter++;
		}
		else if (x == 'a')
		{
			pac.setTextureRect(IntRect(37 * frame, 39, 34, 34));
			if (framecounter == 7)
			{
				frame = (frame + 1) % 4;
				framecounter = 0;

			}
			framecounter++;
		}
		else if (x == 'w')
		{

			pac.setTextureRect(IntRect(37 * frame, 76, 34, 34));
			if (framecounter == 7)
			{
				frame = (frame + 1) % 4;
				framecounter = 0;

			}
			framecounter++;
		}
		else if (x == 's')
		{

			pac.setTextureRect(IntRect(37 * frame, 110, 34, 34));
			if (framecounter == 7)
			{
				frame = (frame + 1) % 4;
				framecounter = 0;

			}
			framecounter++;
		}

		// player 2 red pac
		Texture redpac;
		redpac.loadFromFile("redpac.png");
		pac2.setTexture(&redpac);

		if (!firstmovepactwo)
		{
			pac2.setTextureRect(IntRect(35 * frame2, 50, 34, 34));
			firstmovepactwo = true;
		}
		else if (y == 'd')
		{
			pac2.setTextureRect(IntRect(35 * frame2, 7, 34, 34));
			if (framecounter2 == 7)
			{
				frame2 = (frame2 + 1) % 4;
				framecounter2 = 0;

			}
			framecounter2++;
		}
		else if (y == 'a')
		{
			pac2.setTextureRect(IntRect(35 * frame2, 50, 34, 34));
			if (framecounter2 == 7)
			{
				frame2 = (frame2 + 1) % 4;
				framecounter2 = 0;

			}
			framecounter2++;
		}
		else if (y == 'w')
		{

			pac2.setTextureRect(IntRect(36 * frame2, 140, 34, 34));
			if (framecounter2 == 7)
			{
				frame2 = (frame2 + 1) % 4;
				framecounter2 = 0;

			}
			framecounter2++;
		}
		else if (y == 's')
		{

			pac2.setTextureRect(IntRect(37 * frame2, 95, 34, 34));
			if (framecounter2 == 7)
			{
				frame2 = (frame2 + 1) % 4;
				framecounter2 = 0;

			}
			framecounter2++;
		}
		//demon ghost
		Texture demonn;
		demonn.loadFromFile("demon22.JPG");
		ghost1.setTexture(&demonn);
		if (demon == 'd')
		{
			ghost1.setTextureRect(IntRect(39 * framedemon, 2, 34, 34));
			if (framecounterdemon == 7)
			{
				framedemon = (framedemon + 1) % 3;
				framecounterdemon = 0;

			}
			framecounterdemon++;
		}
		else if (demon == 'a')
		{
			ghost1.setTextureRect(IntRect(39 * framedemon, 45, 34, 34));
			if (framecounterdemon == 7)
			{
				framedemon = (framedemon + 1) % 3;
				framecounterdemon = 0;

			}
			framecounterdemon++;
		}
		else if (demon == 'w')
		{

			ghost1.setTextureRect(IntRect(37 * framedemon, 90, 34, 34));
			if (framecounterdemon == 7)
			{
				framedemon = (framedemon + 1) % 3;
				framecounterdemon = 0;

			}
			framecounterdemon++;
		}
		else if (demon == 's')
		{

			ghost1.setTextureRect(IntRect(37 * framedemon, 137, 34, 34));
			if (framecounterdemon == 7)
			{
				framedemon = (framedemon + 1) % 3;
				framecounterdemon = 0;

			}
			framecounterdemon++;
		}
		// angel ghost
		Texture angell;
		angell.loadFromFile("angel.jpg");
		ghost2.setTexture(&angell);



		if (angel == 'd')
		{
			ghost2.setTextureRect(IntRect(40 * frameangel, 3, 34, 34));
			if (framecounterangel == 7)
			{
				frameangel = (frameangel + 1) % 3;
				framecounterangel = 0;

			}
			framecounterangel++;
		}
		else if (angel == 'a')
		{
			ghost2.setTextureRect(IntRect(40 * frameangel, 45, 34, 34));
			if (framecounterangel == 7)
			{
				frameangel = (frameangel + 1) % 3;
				framecounterangel = 0;

			}
			framecounterangel++;
		}
		else if (angel == 'w')
		{

			ghost2.setTextureRect(IntRect(40 * frameangel, 90, 34, 34));
			if (framecounterangel == 7)
			{
				frameangel = (frameangel + 1) % 3;
				framecounterangel = 0;

			}
			framecounterangel++;
		}
		else if (angel == 's')
		{

			ghost2.setTextureRect(IntRect(40 * frameangel, 135, 34, 34));
			if (framecounterangel == 7)
			{
				frameangel = (frameangel + 1) % 3;
				framecounterangel = 0;

			}
			framecounterangel++;
		}
		//ROBOT

		Texture robott;
		robott.loadFromFile("robot.jpg");
		ghost3.setTexture(&robott);



		if (robot == 'd')
		{
			ghost3.setTextureRect(IntRect(43 * framerobot, 7, 34, 34));
			if (framerobot == 7)
			{
				framerobot = (framerobot + 1) % 3;
				framecounterrobot = 0;

			}
			framecounterrobot++;
		}
		else if (robot == 'a')
		{
			ghost3.setTextureRect(IntRect(43 * framerobot, 52, 35, 35));
			if (framecounterrobot == 7)
			{
				framerobot = (framerobot + 1) % 3;
				framecounterrobot = 0;

			}
			framecounterrobot++;
		}
		else if (robot == 'w')
		{

			ghost3.setTextureRect(IntRect(49 * framerobot, 100, 35, 35));
			if (framecounterrobot == 7)
			{
				framerobot = (framerobot + 1) % 3;
				framecounterrobot = 0;

			}
			framecounterrobot++;
		}
		else if (robot == 's')
		{

			ghost3.setTextureRect(IntRect(40 * framerobot, 155, 34, 34));
			if (framecounterrobot == 7)
			{
				framerobot = (framerobot + 1) % 3;
				framecounterrobot = 0;

			}
			framecounterrobot++;
		}
		//end of animation

		// pick ups for player 1
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 36; j++)
			{
				if (ary[j][i].pixel != '0'&&ary[j][i].pixel != 'x')
				{
					if (ary[j][i].pixel == 'u' || ary[j][i].pixel == 'd')
					{
						pickup.setPosition(i * 25, j * 25);
						pickup.setSize(Vector2f(12.5, 12.5));
						pickup.setFillColor(Color::Yellow);
					}
					else
					{
						pickup.setSize(Vector2f(2.5, 2.5));
						pickup.setFillColor(Color::White);
						pickup.setPosition(i * 25 + 2.5, j * 25);

						pickup.setOrigin(-12.5, -12.5);
					}
					if (pac.getGlobalBounds().intersects(pickup.getGlobalBounds()) || ((ary[j][i].pixel == 'u' || ary[j][i].pixel == 'd') && pac2.getGlobalBounds().intersects(pickup.getGlobalBounds())))
					{
						if (!pickupschecker[j][i])
						{
							if (ary[j][i].pixel == 'u' || ary[j][i].pixel == 'd')
							{
								g1 = 1; g2 = 1; g3 = 1;
								NextRun1 = 0, NextRun2 = 0, NextRun3 = 0;
							}
							pickupschecker[j][i] = 1;
							score1++;
						}



						//cout << "score1 : " << score1 << endl;
					}


					if (!pickupschecker[j][i])
						w.draw(pickup);
				}

			}
		}
		// pickups for player 2
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 36; j++)
			{
				if (ary[j][i].pixel != '0'&&ary[j][i].pixel != 'x')
				{
					pickup2.setPosition(i * 25, j * 25);

					pickup2.setOrigin(-12.5, -12.5);

					if (pac2.getGlobalBounds().intersects(pickup2.getGlobalBounds()))
					{
						if (pickupschecker2[j][i] == 0)
						{
							pickupschecker2[j][i] = 1;
							score2++;
						}

					}

					if (!pickupschecker2[j][i])
						if (state == 1)
							w.draw(pickup2);
				}

			}
		}
		(g1) ? ghost1.setFillColor(Color::Green) : ghost1.setFillColor(Color::White);
		(g2) ? ghost2.setFillColor(Color::Green) : ghost2.setFillColor(Color::White);
		(g3) ? ghost3.setFillColor(Color::Green) : ghost3.setFillColor(Color::White);

		if (lives > 0)w.draw(pac);
		if (state == 0)pac2.setPosition(0, 0);
		if (state == 1 && lives2>0)w.draw(pac2);
		w.draw(ghost1);
		w.draw(ghost2);
		w.draw(ghost3);
		if (lives <= 0)score1 = -1;
		if (lives2 <= 0) score2 = -1;
		for (int i = 0; i< lives; i++)
		{
			heart.setPosition(200 + (20 * i), 40);
			w.draw(heart);
		}
		for (int i = 0; i< lives2; i++)
		{
			heart.setPosition(450 + (20 * i), 40);
			w.draw(heart);
		}
		w.draw(returntomenu);
		//w.draw(ghost4);
		w.display();
		w.clear();
	}
}

void pacman_movement(Astar map[36][28], char &x, int locmap1, int locmap2, string id)
{
	bool up, down, left, right;
	char *prev_pointer;
	if (id == "player1")
	{
		up = Keyboard::isKeyPressed(Keyboard::Up);
		down = Keyboard::isKeyPressed(Keyboard::Down);
		left = Keyboard::isKeyPressed(Keyboard::Left);
		right = Keyboard::isKeyPressed(Keyboard::Right);
		prev_pointer = &prevchoice1;
	}
	else
	{
		up = Keyboard::isKeyPressed(Keyboard::W);
		down = Keyboard::isKeyPressed(Keyboard::S);
		left = Keyboard::isKeyPressed(Keyboard::A);
		right = Keyboard::isKeyPressed(Keyboard::D);
		prev_pointer = &prevchoice2;
	}

	//a funtion that stores the last key pressed ( in player control ) and acts on it as soon as it's available
	if (right)
	{
		*prev_pointer = 'd';
	
		if (avaialble_moves_RLUD[0].find(map[locmap1][locmap2].pixel) != -1)
			if (map[locmap1][locmap2].pixel != '>')
				x = 'd';

	}
	else if (left)
	{
		*prev_pointer = 'a';
		

		if (avaialble_moves_RLUD[1].find(map[locmap1][locmap2].pixel) != -1)
			if (map[locmap1][locmap2].pixel != '<')
				x = 'a';



	}
	else if (up)
	{
		*prev_pointer = 'w';
	
		if (avaialble_moves_RLUD[2].find(map[locmap1][locmap2].pixel) != -1)
			if (map[locmap1][locmap2].pixel != 'u')
				x = 'w';


	}
	else if (down)
	{
		//"+-ud<*>/|"
		*prev_pointer = 's';
		

		if (avaialble_moves_RLUD[3].find(map[locmap1][locmap2].pixel) != -1)
			if (map[locmap1][locmap2].pixel != 'd')
				x = 's';


	}
	if (*prev_pointer == 'a' && (map[locmap1][locmap2].pixel == '+' || map[locmap1][locmap2].pixel == '>' || map[locmap1][locmap2].pixel == 'u' || map[locmap1][locmap2].pixel == 'd'))
	{
		x = *prev_pointer;
		*prev_pointer = 'p';
	}
	else if (*prev_pointer == 'd' && (map[locmap1][locmap2].pixel == '+' || map[locmap1][locmap2].pixel == '<' || map[locmap1][locmap2].pixel == 'u' || map[locmap1][locmap2].pixel == 'd'))
	{
		x = *prev_pointer;
		*prev_pointer = 'p';
	}
	else if (*prev_pointer == 'w' && (map[locmap1][locmap2].pixel == '+' || map[locmap1][locmap2].pixel == '>' || map[locmap1][locmap2].pixel == '<' || map[locmap1][locmap2].pixel == 'd'))
	{
		x = *prev_pointer;
		*prev_pointer = 'p';
	}
	else if (*prev_pointer == 's' && (map[locmap1][locmap2].pixel == '+' || map[locmap1][locmap2].pixel == '>' || map[locmap1][locmap2].pixel == 'u' || map[locmap1][locmap2].pixel == '<'))
	{
		x = *prev_pointer;
		*prev_pointer = 'p';
	}

}

void player2_move_checker(CircleShape &player2, Astar map[36][28], char y, int &pl2_locmap2, int &pl2_locmap1, int i)
{

	if (y == 'd'&&map[pl2_locmap2][pl2_locmap1 + 1].pixel != '0')
	{
		if (i == 9)

			pl2_locmap1++;

		player2.move(25.0 / 10.0, 0);


	}
	if (y == 's'&&map[pl2_locmap2 + 1][pl2_locmap1].pixel != '0')
	{

		if (i == 9)
			pl2_locmap2++;
		player2.move(0, 25.0 / 10.0);


	}
	if (y == 'a'&&map[pl2_locmap2][pl2_locmap1 - 1].pixel != '0')
	{


		if (i == 9)
			pl2_locmap1--;
		player2.move(-(25.0 / 10.0), 0);

	}


	if (y == 'w'&&map[pl2_locmap2 - 1][pl2_locmap1].pixel != '0')
	{

		if (i == 9)
			pl2_locmap2--;
		player2.move(0, -(25.0 / 10.0));



	}


}
void clearing_path(stack<pair<int, int>>&st)
{
	if (!st.empty())
	{
		st.pop();
		clearing_path(st);
	}
}
void portal(Astar map[36][28], int &locmap1, int &locmap2, CircleShape &player, char x)
{
	if (map[locmap1][locmap2].pixel == '/'&&x == 'a')
	{
		locmap2 = 27;
		player.setPosition(Vector2f(float(27 * 25), float(17 * 25)));

	}
	else if (map[locmap1][locmap2].pixel == '*'&&x == 'd')
	{
		locmap2 = 0;
		player.setPosition(Vector2f(float(25 * 0), float(17 * 25)));

	}
}
void last_current(stack<pair<int, int>>&path, pair<int, int>&last, pair<int, int>&cur)
{
	if (path.size() != 1)
	{
		last = make_pair(path.top().first, path.top().second);
		path.pop();
		cur = make_pair(path.top().first, path.top().second);
	}
}
bool Can_Calculate(Astar map[36][28], int aix, int aiy, pair<int*, int*>Highscore_trace)
{
	if (abs((aix + aiy) - (*Highscore_trace.first + *Highscore_trace.second)) != 0 && (map[*Highscore_trace.first][*Highscore_trace.second].pixel == '+' || map[*Highscore_trace.first][*Highscore_trace.second].pixel == 'd' || map[*Highscore_trace.first][*Highscore_trace.second].pixel == '<' || map[*Highscore_trace.first][*Highscore_trace.second].pixel == '>' || map[*Highscore_trace.first][*Highscore_trace.second].pixel == 'u' || map[*Highscore_trace.first][*Highscore_trace.second].pixel == '*' || map[*Highscore_trace.first][*Highscore_trace.second].pixel == '/'))
		return 1;
	else
		return 0;
}
void del_AI(Astar map[36][28], char x)
{
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (map[i][j].AI == x)
				map[i][j].AI = ' ';
		}
	}
}

//habda men el homma to2al
void AI_Calling(Astar map[36][28], pair<int*, int*>&Highscore_trace, int & locmap1, int & locmap2, int & pl2_locmap1, int & pl2_locmap2, bool &stop1, int &aix, int & aiy)
{

	if (score1 >= score2)
		Highscore_trace.first = &locmap1, Highscore_trace.second = &locmap2;
	else
		Highscore_trace.first = &pl2_locmap2, Highscore_trace.second = &pl2_locmap1;


	//AI calling

	if (Can_Calculate(map, aix, aiy, Highscore_trace) || path.size() < 3 || stop1)
	{

		if (g1 && !NextRun1)
			direction = make_pair(4, 1);
		else if (!g1)
			direction = make_pair(*Highscore_trace.first, *Highscore_trace.second);
		else if (g1 && NextRun1)
			direction = make_pair(32, 1);


		if (abs(Redghost_pos.first - direction.first) + abs(Redghost_pos.second - direction.second) == 1 && !NextRun1)
			NextRun1 = 1;
		else if (abs(Redghost_pos.first - direction.first) + abs(Redghost_pos.second - direction.second) == 1 && NextRun1)
			NextRun1 = 0, g1 = 0;

		clearing_path(path);
	

		AI(map, Redghost_pos.first, Redghost_pos.second, direction.first, direction.second, 'R');

		open_set.clear();
		close_set.clear();


	}

	if (Can_Calculate(map, aix, aiy, Highscore_trace) || path2.size() < 3 || stop1)
	{
		if (g2 && !NextRun2)
			direction2 = make_pair(4, 26);
		else if (!g2)
			direction2 = make_pair(*Highscore_trace.first, *Highscore_trace.second);
		else if (g2 && NextRun2)
			direction2 = make_pair(32, 26);


		if (abs(Blueghost_pos.first - direction2.first) + abs(Blueghost_pos.second - direction2.second) == 1 && !NextRun2)
			NextRun2 = 1;
		else if (abs(Blueghost_pos.first - direction2.first) + abs(Blueghost_pos.second - direction2.second) == 1 && NextRun2)
			NextRun2 = 0, g2 = 0;

		clearing_path(path2);
	
		AI(map, Blueghost_pos.first, Blueghost_pos.second, direction2.first, direction2.second, 'B');

		open_set.clear();
		close_set.clear();

	}

	if (Can_Calculate(map, aix, aiy, Highscore_trace) || path3.size() < 3 || stop1)
	{

		if (g3 && !NextRun3)
			direction3 = make_pair(32, 1);
		else if (!g3)
			direction3 = make_pair(*Highscore_trace.first, *Highscore_trace.second);
		else if (g3 && NextRun3)
			direction3 = make_pair(4, 26);


		if (abs(Orangeghost_pos.first - direction3.first) + abs(Orangeghost_pos.second - direction3.second) == 8 && !NextRun3)
			NextRun3 = 1;
		else if (abs(Orangeghost_pos.first - direction3.first) + abs(Orangeghost_pos.second - direction3.second) == 8 && NextRun3)
			NextRun3 = 0, g3 = 0;
		clearing_path(path3);
		
		AI(map, Orangeghost_pos.first, Orangeghost_pos.second, direction3.first, direction3.second, 'O');

		open_set.clear();
		close_set.clear();

	}


	if (Can_Calculate(map, aix, aiy, Highscore_trace))
	{
		aix = *Highscore_trace.first;
		aiy = *Highscore_trace.second;

	}

	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			map[i][j].AI = ' ';
			map[i][j].f = 0;
		}
	}


}
void  game(Astar map[36][28], char & x, char & y, int &locmap1, int & locmap2, int &pl2_locmap1, int & pl2_locmap2, pair<int, int> last, pair<int, int>last2, pair<int, int>last3, pair<int, int> cur, pair<int, int>cur2, pair<int, int>cur3, stack<pair<int, int>> path, stack<pair<int, int>> path2, stack<pair<int, int>> path3, RectangleShape &ghost, RectangleShape &ghost2, RectangleShape &ghost3, RectangleShape &ghost4, CircleShape &player, CircleShape &player2, RenderWindow & gameplay, RectangleShape Maptexture, RectangleShape & pickup, RectangleShape &pickup2, RectangleShape returntomenu, RectangleShape heart, RectangleShape gameoverrect)
{
	

	if (x == 'd' && map[locmap1][locmap2 + 1].pixel != '0')
	{

		locmap2++;


		if (path.size() != 1)
			Redghost_pos = next(last, cur, Redghost_pos, path, demon);
		if (path2.size() != 1)
			Blueghost_pos = next(last2, cur2, Blueghost_pos, path2, angel);
		if (path3.size() > 8)
			Orangeghost_pos = next(last3, cur3, Orangeghost_pos, path3, robot);

		for (int i = 0; i < 10; i++)
		{

			if (path.size() != 1)
				moving(ghost, last, cur);
			if (path2.size() != 1)
				moving(ghost2, last2, cur2);
			if (path3.size() > 8)
				moving(ghost3, last3, cur3);


			if (start(ghost, ghost2, ghost3, ghost4, player, player2, locmap1, locmap2, pl2_locmap2, pl2_locmap1, x, y))
			{

				break;
			}
			player2_move_checker(player2, map, y, pl2_locmap2, pl2_locmap1, i);
			player.move(25.0 / 10.0, 0);
			drawing(gameplay, map, Maptexture, player, player2, pickup, pickup2, pickupschecker, pickupschecker2, ghost, ghost2, ghost3, ghost4, x, y, returntomenu, heart, gameoverrect);

		}
	}
	else if (x == 's' && map[locmap1 + 1][locmap2].pixel != '0')
	{

		locmap1++;


		if (path.size() != 1)
			Redghost_pos = next(last, cur, Redghost_pos, path, demon);
		if (path2.size() != 1)
			Blueghost_pos = next(last2, cur2, Blueghost_pos, path2, angel);
		if (path3.size() > 8)
			Orangeghost_pos = next(last3, cur3, Orangeghost_pos, path3, robot);
		for (int i = 0; i < 10; i++)
		{

			if (path.size() != 1)
				moving(ghost, last, cur);
			if (path2.size() != 1)
				moving(ghost2, last2, cur2);
			if (path3.size() > 8)
				moving(ghost3, last3, cur3);


			if (start(ghost, ghost2, ghost3, ghost4, player, player2, locmap1, locmap2, pl2_locmap2, pl2_locmap1, x, y))
			{

				break;
			}
			player2_move_checker(player2, map, y, pl2_locmap2, pl2_locmap1, i);
			player.move(0, 25.0 / 10.0);
			drawing(gameplay, map, Maptexture, player, player2, pickup, pickup2, pickupschecker, pickupschecker2, ghost, ghost2, ghost3, ghost4, x, y, returntomenu, heart, gameoverrect);
		}
	}
	else    if (x == 'a' && map[locmap1][locmap2 - 1].pixel != '0')
	{
		locmap2--;

		if (path.size() != 1)
			Redghost_pos = next(last, cur, Redghost_pos, path, demon);
		if (path2.size() != 1)
			Blueghost_pos = next(last2, cur2, Blueghost_pos, path2, angel);
		if (path3.size() > 8)
			Orangeghost_pos = next(last3, cur3, Orangeghost_pos, path3, robot);

		for (int i = 0; i < 10; i++)
		{

			if (path.size() != 1)
				moving(ghost, last, cur);
			if (path2.size() != 1)
				moving(ghost2, last2, cur2);
			if (path3.size() > 8)
				moving(ghost3, last3, cur3);


			if (start(ghost, ghost2, ghost3, ghost4, player, player2, locmap1, locmap2, pl2_locmap2, pl2_locmap1, x, y))
			{

				break;
			}
			player2_move_checker(player2, map, y, pl2_locmap2, pl2_locmap1, i);
			player.move(-(25.0 / 10.0), 0);

			drawing(gameplay, map, Maptexture, player, player2, pickup, pickup2, pickupschecker, pickupschecker2, ghost, ghost2, ghost3, ghost4, x, y, returntomenu, heart, gameoverrect);
		}
	}
	else if (x == 'w' && map[locmap1 - 1][locmap2].pixel != '0')
	{
		locmap1--;


		if (path.size() != 1)
			Redghost_pos = next(last, cur, Redghost_pos, path, demon);
		if (path2.size() != 1)
			Blueghost_pos = next(last2, cur2, Blueghost_pos, path2, angel);
		if (path3.size() > 8)
			Orangeghost_pos = next(last3, cur3, Orangeghost_pos, path3, robot);

		for (int i = 0; i < 10; i++)
		{

			if (path.size() != 1)
				moving(ghost, last, cur);
			if (path2.size() != 1)
				moving(ghost2, last2, cur2);
			if (path3.size() > 8)
				moving(ghost3, last3, cur3);

			if (start(ghost, ghost2, ghost3, ghost4, player, player2, locmap1, locmap2, pl2_locmap2, pl2_locmap1, x, y))
			{

				break;
			}
			player2_move_checker(player2, map, y, pl2_locmap2, pl2_locmap1, i);
			player.move(0, -(25.0 / 10.0));

			drawing(gameplay, map, Maptexture, player, player2, pickup, pickup2, pickupschecker, pickupschecker2, ghost, ghost2, ghost3, ghost4, x, y, returntomenu, heart, gameoverrect);

		}
	}
	else
	{


		if (path.size() != 1)
			Redghost_pos = next(last, cur, Redghost_pos, path, demon);
		if (path2.size() != 1)
			Blueghost_pos = next(last2, cur2, Blueghost_pos, path2, angel);
		if (path3.size() > 8)
			Orangeghost_pos = next(last3, cur3, Orangeghost_pos, path3, robot);

		for (int i = 0; i < 10; i++)
		{


			if (path.size() != 1)
				moving(ghost, last, cur);
			if (path2.size() != 1)
				moving(ghost2, last2, cur2);
			if (path3.size() > 8)
				moving(ghost3, last3, cur3);

			if (start(ghost, ghost2, ghost3, ghost4, player, player2, locmap1, locmap2, pl2_locmap2, pl2_locmap1, x, y))
			{


				break;
			}
			player2_move_checker(player2, map, y, pl2_locmap2, pl2_locmap1, i);

			drawing(gameplay, map, Maptexture, player, player2, pickup, pickup2, pickupschecker, pickupschecker2, ghost, ghost2, ghost3, ghost4, x, y, returntomenu, heart, gameoverrect);


		}
	}

}

void Mainmenufun()
{
	state = 5;
	firstmovepacone = false;
	firstmovepactwo = false;
	string sound_status = "souund.png";
	int cooldown = 0;
	int i = 0;
	int button = 0;
	bool soundOn = true;
	bool oneplayer = false, twoplayers = false;

	RenderWindow MainMenu(VideoMode(500, 500), "Main Menu", Style::Default);

	MainMenu.setKeyRepeatEnabled(true);

	Music music;
	music.openFromFile("ghost.wav");
	music.play();

	Menu menu(MainMenu.getSize().x, MainMenu.getSize().y);
	Menu players(MainMenu.getSize().x, MainMenu.getSize().y);
	Menu diff(MainMenu.getSize().x, MainMenu.getSize().y);
	Texture background;
	background.loadFromFile("Sc3.png");
	Sprite back;
	back.setTexture(background);
	back.setTextureRect(IntRect(0, 0, 500, 500));


	Texture sound;
	sound.loadFromFile("sound-mute.png");
	Sprite soundy;
	soundy.setTexture(sound);
	soundy.setTextureRect(IntRect(0, 0, 24.3, 23));
	soundy.setPosition(Vector2f(500 / 1.06, 500 / 102));

	Texture sound2;
	sound2.loadFromFile("souund.png");
	Sprite soundy2;
	soundy2.setTexture(sound2);
	soundy2.setTextureRect(IntRect(0, 0, 24.3, 23));
	soundy2.setPosition(Vector2f(500 / 1.06, 500 / 102));

	Texture texture;
	texture.loadFromFile("player11.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(500 / 7.9, 500 / 1.5));

	Texture texture3;
	texture3.loadFromFile("redpac2.png");
	Sprite redpac;
	redpac.setTexture(texture3);
	redpac.setPosition(Vector2f(500 / 1.4, 500 / 1.21));

	RectangleShape soundpos(Vector2f(20.0f, 20.0f));
	soundpos.setPosition(soundy.getPosition());
	soundpos.setFillColor(Color::Red);

	int soundcounter = 0;

	RectangleShape Mousepos(Vector2f(20.0f, 20.0f));
	Mousepos.setFillColor(Color::Red);
	int twice = 0;
	while (MainMenu.isOpen()) {
		if (twice <3)
			MainMenu.display();
		twice++;
		Mousepos.setPosition((Vector2f(Mouse::getPosition().x - 447, Mouse::getPosition().y - 170)));


		soundcounter++;
		if (Mousepos.getGlobalBounds().intersects(soundpos.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && soundcounter >= 50000)
		{
			if (soundOn)
			{
				soundOn = 0;
				cout << "music is off" << endl;
				music.pause();
			}
			else if (!soundOn)
			{
				soundOn = 1;
				cout << "music is on" << endl;
				music.play();
			}

			soundcounter = 0;
		}

		Event e;
		while (MainMenu.pollEvent(e)) {


			switch (e.type) {
			case Event::Closed:
				MainMenu.close();
				break;

			case Event::KeyPressed:


				if (Keyboard::isKeyPressed(Keyboard::Up))
				{

					menu.moveup();
					if (button > 0)
						button--;
					else button = 3;

				}
				else if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (button < 3)
						button++;
					else button = 0;
					menu.movedown();
				}

				else if (Keyboard::isKeyPressed(Keyboard::P))
				{
					music.play();
					soundOn = 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::S))
				{
					music.pause();
					soundOn = 0;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					MainMenu.close();
					state = 5;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Return))
				{

					if (button == 0)
					{

						//state = 0;
						i = 2;
						oneplayer = true;
						//MainMenu.close();
						break;
					}

					else if (button == 1)
					{
						i = 2;
						twoplayers = true;
						break;
					}

					else if (button == 2) {
						i = 1;
						break;
					}
					else if (button == 3) {
						MainMenu.close();
						break;
					}
				}

			case Keyboard::BackSpace:
				i = 0;
				break;




			}

			if (i == 0) {
				MainMenu.clear();
				MainMenu.draw(back);
				menu.draw(MainMenu);
				if (soundOn)
				{

					MainMenu.draw(soundy2);
				}
				else if (!soundOn)
				{
					MainMenu.draw(soundy);
				}

			}

			if (i == 1) {
				MainMenu.clear();
				players.drawPlayers(MainMenu);
				MainMenu.draw(sprite);
				MainMenu.draw(redpac);
			}
			if (i == 2) {
				MainMenu.clear();
				diff.drawdiff(MainMenu);
			}
			if (oneplayer)
			{
				if (Keyboard::isKeyPressed(Keyboard::H))
				{
					MainMenu.close();
					selector = 'h';
					state = 0;
				}
				else if (Keyboard::isKeyPressed(Keyboard::M))
				{
					MainMenu.close();
					selector = 'm';
					state = 0;
				}
				else if (Keyboard::isKeyPressed(Keyboard::E))
				{
					MainMenu.close();
					selector = 'e';
					state = 0;
				}
			}
			else if (twoplayers)
			{
				if (Keyboard::isKeyPressed(Keyboard::H))
				{
					MainMenu.close();
					selector = 'h';
					state = 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::M))
				{
					MainMenu.close();
					selector = 'm';
					state = 1;
				}
				else if (Keyboard::isKeyPressed(Keyboard::E))
				{
					MainMenu.close();
					selector = 'e';
					state = 1;
				}
			}
			MainMenu.display();

		}


	}
}
////////////////////////////////////////////////
/////////////////////////////////////////
//////////////////////////////////////
void  initializiing() {
	int framecounter = 0; frame = 0; framecounter2 = 0; frame2 = 0; framecounterdemon = 0; framedemon = 0; frameangel = 0; framecounterangel = 0; framecounterrobot = 0; framerobot = 0;
	int state = 5;
	bool firstmovepacone = false; firstmovepactwo = false;
	selector = 'v';
	bool g1 = 0; g2 = 0; g3 = 0; NextRun1 = 0; NextRun2 = 0; NextRun3 = 0;

	char prevchoice1 = 'p'; prevchoice2 = 'p'; demon = 'r'; angel = 'r'; robot = 'r';
	score1 = 0; score2 = 0;
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			pickupschecker[i][j] = 0;
			pickupschecker2[i][j] = 0;
		}
	}
	string avaialble_moves_RLUD[4] = { "-+ud<*", "+-ud>/", "+d<>|", "+|u><" };
	pair<int, int>initializingdirection, initializingdirection2, initializingdirection3;
	direction = initializingdirection; direction2 = initializingdirection2; direction3 = initializingdirection3;
	stack<pair<int, int>>initializingpath, initializingpath2, initializingpath3;
	path = initializingpath; path2 = initializingpath2; path3 = initializingpath3;
	set <int > initializingclose_set;
	close_set = initializingclose_set;
	map<int, pair<int, pair<int, int>>>initializingopen_set;
	open_set = initializingopen_set;
	pair<int*, int*>initializingghost_real_pos, initializingghost2_real_pos, initializingghost3_real_pos;
	ghost_real_pos = initializingghost_real_pos; ghost2_real_pos = initializingghost2_real_pos; ghost3_real_pos = initializingghost3_real_pos;
	Blueghost_pos = make_pair(17, 14); Redghost_pos = make_pair(17, 13); Orangeghost_pos = make_pair(17, 15);
	lives2 = 3; lives = 3;

}
bool Maindecleration(bool &continuee)
{
	initializiing();
	continuee = false;
	Mainmenufun();
	if (state == 1 || state == 0) {
		pair<int, int>last, cur, last2, cur2, last3, cur3;
		pair<int*, int*>Highscore_trace;
		int aix = 1, aiy = 1;
		//ghost
		RectangleShape ghost(Vector2f(35.0f, 35.0f));
		ghost.setPosition(25 * 13, 17 * 25);
		ghost.setFillColor(Color::Red);
		//ghost 2
		RectangleShape ghost2(Vector2f(35.0f, 35.0f));
		ghost2.setPosition(14 * 25, 17 * 25);
		ghost2.setFillColor(Color::Blue);
		//ghost3
		RectangleShape ghost3(Vector2f(35.0f, 35.0f));
		ghost3.setPosition(15 * 25, 17 * 25);
		ghost3.setFillColor(Color(255, 165, 0));

		//ghost4(random)
		RectangleShape ghost4(Vector2f(25.0f, 25.0f));
		ghost4.setPosition(16 * 25, 17 * 25);
		ghost4.setFillColor(Color(255, 20, 147));

		//setting pointers
		ghost_real_pos.first = &Redghost_pos.first, ghost_real_pos.second = &Redghost_pos.second;
		ghost2_real_pos.first = &Blueghost_pos.first, ghost2_real_pos.second = &Blueghost_pos.second;
		ghost3_real_pos.first = &Orangeghost_pos.first, ghost3_real_pos.second = &Orangeghost_pos.second;
		// gameover
		Texture gameovertex;
		RectangleShape gameoverrect(Vector2f(650, 250));
		gameoverrect.setPosition(10, 250);
		gameovertex.loadFromFile("gameover.png");
		gameoverrect.setTexture(&gameovertex);

		int locmap1 = 4, locmap2 = 1, pl2_locmap2 = 4, pl2_locmap1 = 26;
		char x = 'p', y = 'p';
		RenderWindow gameplay(VideoMode(700, 900), "GamePlay", Style::Default);

		//struct object
		Astar map[36][28];

		// Map
		Texture layout;
		RectangleShape Maptexture(Vector2f(700, 800));
		Maptexture.setPosition(2.7, 64);
		layout.loadFromFile("pac3.png");
		Maptexture.setTexture(&layout);

		// return to menu
		Texture backtomenu;
		RectangleShape backtomenurect(Vector2f(50, 25));
		backtomenurect.setPosition(30, 40);
		backtomenu.loadFromFile("returntomenu.png");
		backtomenurect.setTexture(&backtomenu);
		backtomenurect.setFillColor(Color::White);
		// lives
		Texture heart;
		RectangleShape heartshape(Vector2f(20, 20));
		heartshape.setPosition(250, 250);
		heart.loadFromFile("heart.jpg");
		heartshape.setTexture(&heart);
		//   pickups
		//for player 1
		RectangleShape pickup(Vector2f(2.5f, 5.0f));
		pickup.setFillColor(Color::Yellow);
		//for player 2
		RectangleShape pickup2(Vector2f(2.5f, 5.0f));
		pickup2.setFillColor(Color::White);
		//mouse
		RectangleShape Mousepos(Vector2f(20.0f, 20.0f));
		Mousepos.setFillColor(Color::Red);

		//make sure to use the new map file
		ifstream pac;
		pac.open("Pac2.txt");
		int r = 0, id = 0;
		while (!pac.eof())
		{
			for (int i = 0; i < 28; i++)
			{
				pac >> map[r][i].pixel;

				id++;
			}

			r++;
		}
		pac.close();
		//setting the id
		r = 0;
		for (int i = 0; i < 36; i++)
			for (int j = 0; j < 28; j++)
			{
				map[i][j].id = r;
				r++;
			}
		//random target location

		bool reached = 0;
		// wall unit
		RectangleShape Wallunit;
		float Wallunit_x = 25.0f, Wallunit_y = 25.0f;
		Wallunit.setSize(Vector2f(Wallunit_x, Wallunit_y));

		// player 1
		CircleShape player(17);
		player.setFillColor(Color::White);
		player.setPosition(25, 100);
		player.setOrigin(0, 1);

		//player 2
		CircleShape player2(17);
		player2.setFillColor(Color::Red);
		player2.setPosition(25 * 26, 25 * 4);
		player2.setOrigin(0, 1);


		drawing(gameplay, map, Maptexture, player, player2, pickup, pickup2, pickupschecker, pickupschecker2, ghost, ghost2, ghost3, ghost4, x, y, backtomenurect, heartshape, gameoverrect);


		while (gameplay.isOpen())
		{

			Mousepos.setPosition((Vector2f(Mouse::getPosition().x - 350, Mouse::getPosition().y + 25)));

			bool stop1 = 0;

			Event e;
			while (gameplay.pollEvent(e))
			{
				if (e.type == e.Closed)
					gameplay.close();
			}

			// check the movement for two players
			pacman_movement(map, x, locmap1, locmap2, "player1");
			pacman_movement(map, y, pl2_locmap2, pl2_locmap1, "player2");

			// portals
			portal(map, pl2_locmap2, pl2_locmap1, player2, y);
			portal(map, locmap1, locmap2, player, x);

			//AI calling
			AI_Calling(map, Highscore_trace, locmap1, locmap2, pl2_locmap1, pl2_locmap2, stop1, aix, aiy);

			//postions for Ai
			last_current(path, last, cur);
			last_current(path2, last2, cur2);
			last_current(path3, last3, cur3);

			//90% of the game in one function;
			game(map, x, y, locmap1, locmap2, pl2_locmap1, pl2_locmap2, last, last2, last3, cur, cur2, cur3, path, path2, path3, ghost, ghost2, ghost3, ghost4, player, player2, gameplay, Maptexture, pickup, pickup2, backtomenurect, heartshape, gameoverrect);
			gameplay.setFramerateLimit(90);
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				return 0;
			else if (Keyboard::isKeyPressed(Keyboard::BackSpace) || (Mousepos.getGlobalBounds().intersects(backtomenurect.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)))
			{
				continuee = true;
				gameplay.close();
			}


		}

	}
}
/////////////////////
int main()
{
	bool continuee = true;

	while (continuee)
		Maindecleration(continuee);
	
	return 0;
}




