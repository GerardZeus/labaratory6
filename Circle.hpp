#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace mt
{

	class Circle
	{
		float m_r; // Переменная для радиуса
		float m_x, m_y; //Переменные для координат 
		float m_v; // Скорость круга
		float m_vx, m_vy; // Векторы скорости по X и Y 
		float m_alfa; // Угол направления 
		sf::CircleShape m_shape; // Объект класса CircleShape для круга

	public:
		Circle() = default; // Конструктор по-умолчанию

		Circle(float x, float y, float r, float v, float alfa) // Конструктор инициализирует координаты, скорость и угол направления 
		{
			Setup(x, y, r, v, alfa); // Вызывается метод для инициализации параметров 
		}

		void Setup(float x, float y, float r, float v, float alfa) //Метод для настройки параметров координат, скорости и угла направления 
		{
			m_x = x; // Устанавливаем координату X
			m_y = y; // Устанавливаем координату Y
			m_r = r; // Устанавливаем радиус
			m_v = v; // Устанавливаем скорость
			m_alfa = alfa; // Устанавливаем угол направления 
			m_vx = m_v * cos(m_alfa); // Вычисляем вектор скорости по X
			m_vy = m_v * sin(m_alfa); // Вычисляем вектор скорости по Y
			m_shape.setOrigin(m_r, m_r); // Устанавливаем начало координат в центр круга
			m_shape.setRadius(m_r); // Устанавливаем радуис кргуа
			m_shape.setPosition(m_x, m_y); // Устанавливаем координаты круга на экране
			int color_r = rand() % 256; // Случайный оттенок красного
			int color_g = rand() % 256; // Случайный оттенок зелёного 
			int color_b = rand() % 256; // Случайный оттенок синего
			m_shape.setFillColor(sf::Color::Color(color_r, color_b, color_g, 255)); // Устанавливаем цвет заливки круга
			m_shape.setOutlineThickness(-10.f); // Устанавливаем толщину границы круга
			m_shape.setOutlineColor(sf::Color(250, 150, 100)); // Устанвливаем цвет круга
		}

		sf::CircleShape Get() // Геттер для получения круга
		{
			return m_shape;
		}

		float X() { return m_x; } // Геттер для получения X 
		float Y() { return m_y; } // Геттер для получения Y
		float R() { return m_r; } // Геттер для получения радиуса
		float Alfa() { return m_alfa; } // Геттер для получения угла напрваления
		//void Alfa(float alfa)
		//{
		//	m_alfa = alfa;
		//}

		float V() { return m_v; } // Геттер для получения скорости

		void Vx(float vx) { m_vx = vx; } // Метод для установки вектора скороси по X
		void Vy(float vy) { m_vy = vy; } // Метод для установки вектора скорости по Y
		float Vx() { return m_vx; } // Геттер для получения вектора скорости по X
		float Vy() { return m_vy; } // Геттер для получения вектора скорости по Y


		void Move(float dt) // Метод для перемещения круга
		{
			m_x += m_vx * dt; // Обновляем координату X кругра в зависимости от времени 
			m_y += m_vy * dt; // Обновляем координату Y кругра в зависимости от времени 
			m_shape.setPosition(m_x, m_y); // Устанавливаем новую позицию круга
		}
	};

}

