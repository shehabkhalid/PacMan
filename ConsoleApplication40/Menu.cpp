#include"stdafx.h"

#include "menu.h"


Menu::Menu(float width, float height)
{


	font.loadFromFile("CrackMan.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Magenta);
	menu[0].setString("1 Player");
	menu[0].setPosition(Vector2f(width / 1.75, height / (4 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("2 Players ");
	menu[1].setPosition(Vector2f(width / 3, height / (4 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Options");
	menu[2].setPosition(Vector2f(width / 1.75, height / (4 + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(Vector2f(width / 2.45, height / (4 + 1) * 4));

	menu[4].setFont(font);
	menu[4].setFillColor(Color::White);
	menu[4].setString("Sound");
	menu[4].setCharacterSize(12);
	menu[4].setPosition(Vector2f(width / 1.19, height / 27.5));//width/15.5


	players[0].setFont(font);
	players[0].setFillColor(Color::Magenta);
	players[0].setString(" Player 1 : ");
	players[0].setCharacterSize(24);
	players[0].setPosition(Vector2f(width / 15.5, height / 18));

	players[1].setFont(font);
	players[1].setFillColor(Color::White);
	players[1].setString(" 1- Move up : UP ");
	players[1].setCharacterSize(12);
	players[1].setPosition(Vector2f(width / 17, height / (5 + 1)*1.25));//18

	players[2].setFont(font);
	players[2].setFillColor(Color::White);
	players[2].setCharacterSize(12);
	players[2].setString(" 2- Move down : Down ");
	players[2].setPosition(Vector2f(width / 19.5, height / (5 + 1) * 2));

	players[3].setFont(font);
	players[3].setFillColor(Color::White);
	players[3].setCharacterSize(12);
	players[3].setString(" 3- Move right : Right ");
	players[3].setPosition(Vector2f(width / 17, height / (5 + 1)*2.75));//19.5

	players[4].setFont(font);
	players[4].setFillColor(Color::White);
	players[4].setCharacterSize(12);
	players[4].setString("4- Move left : Left ");
	players[4].setPosition(Vector2f(width / 19.5, height / (5 + 1)*3.5));

	players[5].setFont(font);
	players[5].setFillColor(Color::Red);
	players[5].setCharacterSize(24);
	players[5].setString(" Player 2 : ");
	players[5].setPosition(Vector2f(width / 1.7, height / 18));

	players[6].setFont(font);
	players[6].setFillColor(Color::White);
	players[6].setCharacterSize(12);
	players[6].setString(" 1- Move up : W ");
	players[6].setPosition(Vector2f(width / 1.5, height / (5 + 1)*1.25));


	players[7].setFont(font);
	players[7].setFillColor(Color::White);
	players[7].setCharacterSize(12);
	players[7].setString("2- Move down : S ");
	players[7].setPosition(Vector2f(width / 1.5, height / (5 + 1) * 2));

	players[8].setFont(font);
	players[8].setFillColor(Color::White);
	players[8].setCharacterSize(12);
	players[8].setString(" 3- Move right : D ");
	players[8].setPosition(Vector2f(width / 1.5, height / (5 + 1)*2.75));

	players[9].setFont(font);
	players[9].setFillColor(Color::White);
	players[9].setCharacterSize(12);
	players[9].setString("4- Move left : A ");
	players[9].setPosition(Vector2f(width / 1.5, height / (5 + 1)*3.5));

	players[10].setFont(font);
	players[10].setFillColor(Color::Magenta);
	players[10].setCharacterSize(18);
	players[10].setString(" Play Sound : ");
	players[10].setPosition(Vector2f(width / 3.20, height / (5 + 1)*4.5));

	players[11].setFont(font);
	players[11].setFillColor(Color::Red);
	players[11].setCharacterSize(18);
	players[11].setString(" Stop Sound : ");
	players[11].setPosition(Vector2f(width / 3.20, height / (5 + 1)*5.25));

	players[12].setFont(font);
	players[12].setFillColor(Color::White);
	players[12].setCharacterSize(24);
	players[12].setString(" P ");
	players[12].setPosition(Vector2f(width / 1.6, height / (5 + 1)*4.5));

	players[13].setFont(font);
	players[13].setFillColor(Color::White);
	players[13].setCharacterSize(24);
	players[13].setString(" S ");
	players[13].setPosition(Vector2f(width / 1.6, height / (5 + 1)*5.25));

	diff[0].setFont(font);
	diff[0].setFillColor(Color::White);
	diff[0].setCharacterSize(36);
	diff[0].setString(" Press E for Easy ");
	diff[0].setPosition(Vector2f(width / 9, height / 5.5));

	diff[1].setFont(font);
	diff[1].setFillColor(Color::White);
	diff[1].setCharacterSize(36);
	diff[1].setString(" Press M for Medium ");
	diff[1].setPosition(Vector2f(width / 17, height / 2.4));

	diff[2].setFont(font);
	diff[2].setFillColor(Color::White);
	diff[2].setCharacterSize(36);
	diff[2].setString(" Press H for Hard ");
	diff[2].setPosition(Vector2f(width / 9, height / 1.5));

	index = 0;

}


void Menu::draw(RenderWindow &MainMenu)
{
	for (int i = 0; i < max_index; i++)
		MainMenu.draw(menu[i]);

}

void Menu::drawPlayers(RenderWindow &MainMenuxd) {
	for (int i = 0; i < max2; i++)
		MainMenuxd.draw(players[i]);
}

void Menu::drawdiff(RenderWindow &MainMenuxdd) {
	for (int i = 0; i < 3; i++)
		MainMenuxdd.draw(diff[i]);
}

void Menu::moveup()
{
	menu[index].setFillColor(Color::White);
	if (index > 0)
		index--;
	else
		index = max_index - 2;
	menu[index].setFillColor(Color::Magenta);


}

void Menu::movedown()
{

	menu[index].setFillColor(Color::White);
	if (index < max_index - 2) {
		index++;
	}
	else
		index = 0;
	menu[index].setFillColor(Color::Magenta);
}

