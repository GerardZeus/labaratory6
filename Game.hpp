#pragma once
#include <string> // Библиотека для работы о строками
#include <cmath> // Библиотека для математических функций

namespace mt
{
	const float pi = acos(-1); // Число пи

	class Game // Объвляем класс Game 
	{
		int m_width; // Длина окна
		int m_height; // Ширина окна
		std::string m_capture; // Заголовок окна
		mt::Circle* m_c; // Указатель на массив кругов 
		bool* m_col; // Массив, для указания коллизии кругов 
		int m_n; // Количество кругов
		sf::RenderWindow m_window; // Объкт для отрисовки окна
		//std::vector<sf::Vertex> m_coords; 
		bool m_firstCollision = true; // Переменная для отслеживания первой коллизии

	public:
		Game(int width, int height, const std::string& capture) // Конструктор инициализирует длину, ширину и заголовок окна
		{
			m_width = width; // Устанавливаем дину окна
			m_height = height; // Устанавливае ширину окна
			m_capture = capture; // Устанавливаем заголовок окна 
			//m_coords.push_back(sf::Vector2f(0, 0));
			//m_coords.push_back(sf::Vector2f(0, 0));
		}

		void Setup(int n) // Метод для настройки объектов
		{
			m_n = n; // Количество кругов 
			m_window.create(sf::VideoMode(m_width, m_height), m_capture); // Создаём окно с заданными параметрами

			srand(time(0)); // Генератор случайных чисел(разных при каждом запуске)

			m_c = new mt::Circle[m_n]; //Выделяем память для массива кругов
			m_col = new bool[m_n]; // Выделяем память для массива коллизий
			std::fill(m_col, m_col + m_n, true); // Инициализируем массив коллзий, который будет заполнен true

			for (int i = 0; i < m_n; i++) // Цикл, настраивающий круги
			{
				int r = rand() % 50 + 15;// Случайный радиус круга от 15 до 50
				int x, y; // Координаты круга
				bool Position = false; // Булевая переменная для позиции круга

				while (!Position) // Цикл, для того, чтобы круги не накладывались друг на друга и не выходили за границу при генерации
				{
					x = rand() % (1000 - 2 * r) + r; // Генерация координаты X с учётом радиуса
					y = rand() % (600 - 2 * r) + r; // Генерация координаты Y с учётом радиуса
					Position = true; // Место допустимо 

					for (int j = 0; j < i; j++) // Проверка на наложение кругов
					{
						float dist = sqrt(pow(m_c[j].X() - x, 2) + pow(m_c[j].Y() - y, 2)); // Вычисление расстояния между кругами
						if (dist < m_c[j].R() + r) // Если оно меньше суммы радиусов
						{
							Position = false; // Значит место недопустимо 
							break; // Выход из цикла
						}
					}
				}// И так по новой, пока круги не сгенерируются в подходящих местах

				int v = rand() % 50 + 10; // Случайная скорость 
				float alfa = rand() % 7; // Случайный угол(в радианах)
				m_c[i].Setup(x, y, r, v, alfa); // Инициализация круга с заданными параметрами
				m_col[i] = true; // Устанавливаем статус коллизии для круга
			}
		}

		void TouchBorder(Circle& obj) // Метод для проверки столкновения круга с границей окна 
		{
			float x = obj.X(); // Переменная X круга 
			float y = obj.Y(); // Переменная Y круга
			float r = obj.R(); // Переменная радиус круга

			if (x + r >= m_width || x - r <= 0) //Проверяем столкновение с верхней и нижней границами
			{
				obj.Vx(-obj.Vx()); // Меняем вектор скорости по X на противоположенный 
			}

			if (y + r >= m_height || y - r <= 0) // Проверяем столкновение с правой и левой границами
			{
				obj.Vy(-obj.Vy()); // Меняем вектор скорости по Y на противоположенный
			}
		}

		void Collision(Circle& c1, Circle& c2, int i, int j) //Метод для обработки коллизии между двумя кругами
		{
			float dist = pow(c1.X() - c2.X(), 2) + pow(c1.Y() - c2.Y(), 2); // Расстояни между центрами кругов
			if (dist <= pow(c1.R() + c2.R(), 2)) // Если расстояние меньши суммы радиусов
			{
				if (m_col[i] && m_col[j]) // Тогда круги сталкиваются 
				{
					m_col[i] = false; // Обновляем кллизию для первого круга
					m_col[j] = false; // Обновляем кллизию для второго круга

					//float xm = c1.X() + (c2.X() - c1.X()) * (c1.R() / (c1.R() + c2.R())); 
					//float ym = c1.Y() + (c2.Y() - c1.Y()) * (c1.R() / (c1.R() + c2.R()));

					float px = c2.X() - c1.X(); // Координата вектор между центрами кругов по X
					float py = c2.Y() - c1.Y(); // Координата вектор между центрами кругов по Y

					//m_coords.clear();
					//m_coords.push_back(sf::Vector2f(xm + px * 10, ym + py * 10));
					//m_coords.push_back(sf::Vector2f(xm - px * 10, ym - py * 10));

					float len = sqrt(pow(px, 2) + pow(py, 2)); // Вычисляем длины вектора между центрами кругов
					float beta = acos((px) / len); // Вычисляем угол между вектором и осью OX

					if ((px > 0 && py > 0) || (px < 0 && py > 0)) // Если координаты вектора находятся в первой или второй четвертях
						beta = -beta;// То меням угол на противоположенный 
					//Переходм в новую СК, где одна ось совпадает с линией столкновения и вычисляем в этой СК векторы скорости
					//Используем матрицу поворота
					float v1x = c1.Vx() * cos(beta) - c1.Vy() * sin(beta);
					float v1y = c1.Vx() * sin(beta) + c1.Vy() * cos(beta);
					float v2x = c2.Vx() * cos(beta) - c2.Vy() * sin(beta);
					float v2y = c2.Vx() * sin(beta) + c2.Vy() * cos(beta);

					float v1y_s = v1y;
					float v2y_s = v2y;
					float v1x_s = v2x;
					float v2x_s = v1x;
					// Возврщаемся к исходной системе координат, чтообы определить направление движения шариков после столкновения
					c1.Vx(v1x_s * cos(beta) + v1y_s * sin(beta));
					c1.Vy(-v1x_s * sin(beta) + v1y_s * cos(beta));
					c2.Vx(v2x_s * cos(beta) + v2y_s * sin(beta));
					c2.Vy(-v2x_s * sin(beta) + v2y_s * cos(beta));
				}
			}
			else //Если кргуи не сталкиваются
			{
				m_col[i] = true; // Устанавливаем статус коллизии true, который означает, что круги не сталкваются 
				m_col[j] = true;// Устанавливаем статус коллизии true, который означает, что круги не сталкваются 
			}
		}

		void LifeCycle() // Метод для отображения 
		{
			sf::Clock clock; //Создаём объект класса для отслеживания времени

			while (m_window.isOpen()) // Пока открыто окно
			{
				sf::Event event;
				while (m_window.pollEvent(event)) // Обрабатывать события 
				{
					if (event.type == sf::Event::Closed) // Если событие - закрыть окно
						m_window.close(); // Закрываем онно
				}
				
				float dt = clock.getElapsedTime().asSeconds(); // Получаем время прошедшее с последнего обновления
				clock.restart(); // Сбрасываем тмаймер
				// Функция, отвечающая за перемещение кругов
				for (int i = 0; i < m_n; i++)
					m_c[i].Move(dt);
				// Проверка коллизий между кругами
				for (int i = 0; i < m_n - 1; i++)
					for (int j = i + 1; j < m_n; j++)
						Collision(m_c[i], m_c[j], i, j);
				// Проверка столкновения круга с границей 
				for (int i = 0; i < m_n; i++)
					TouchBorder(m_c[i]);

				m_window.clear(); // Очищаем окно перед отображением 
				// Отображаем каждый круг
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());
				//m_window.draw(m_coords.data(), 2, sf::Lines);
				m_window.display(); 
			}
		}
	};
}

