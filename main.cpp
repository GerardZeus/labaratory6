#include "Circle.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    mt::Game game(1000, 600, "Game!!!"); //Создаём объект класса с заданной длиной, шириной и заголовком.
    game.Setup(10); //Создаём игру с 10 кругами

    game.LifeCycle();// Запускаем функцию отображения всего происходящего


    return 0;
}