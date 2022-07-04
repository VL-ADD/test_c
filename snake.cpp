#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include<dos.h>


using namespace std;
class coordinate
{
public :
	int x;
	int y;
};

class cell
{
public:
	coordinate self_coordinate;
	int route;
	int size;
	coordinate past_coordinate;
};

class Snake
{
private:
	int lenth = 3;
public:
	cell mass_snake[];
};

class feeld
{

private:

	const int n = 12; // высота пол€
	const int m = 12; // ширина пол€
	
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	inline void create_feeld(char *Feeld[], int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (j == 0 || j == m - 1)
				{
					Feeld[i][j] = '#';
				}
				else
				if (i == 0 || i == n - 1)
				{
					Feeld[i][j] = '#';
				}
				else
				{
					Feeld[i][j] = 176;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	inline void print_feeld(char *Feeld[], int n, int m)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << Feeld[i][j];
			}
			cout << '\n';
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	inline void print_snake(cell snake[], char *Feeld[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			int X = snake[i].self_coordinate.x;
			int Y = snake[i].self_coordinate.y;
			Feeld[X][Y] = 219;
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
	cell* move(cell snake[], /*cell newsnake[],*/ int xpoint, int ypoint, int height, int width)
	{
		coordinate nexTcor;
		int size = snake[0].size;// размер новой змеи
		
		nexTcor.x = 0;
		nexTcor.y = 0;
		int ret = 0;
		bool eatpoint = false;

		if (snake[0].route == 0) // определили координаты нового расположени€ головы змеи
		{
			nexTcor.x = snake[0].self_coordinate.x;
			nexTcor.y = snake[0].self_coordinate.y - 1;
		}
		if (snake[0].route == 1)
		{
			nexTcor.x = snake[0].self_coordinate.x - 1;
			nexTcor.y = snake[0].self_coordinate.y;
		}
		if (snake[0].route == 2)
		{
			nexTcor.x = snake[0].self_coordinate.x;
			nexTcor.y = snake[0].self_coordinate.y + 1;
		}
		if (snake[0].route == 3)
		{
			nexTcor.x = snake[0].self_coordinate.x + 1;
			nexTcor.y = snake[0].self_coordinate.y;
		}

		if (nexTcor.x == snake[1].self_coordinate.x && nexTcor.y == snake[1].self_coordinate.y) // если задали путь назад, перенаправл€ем змею вперЄд
		{
			nexTcor.x = snake[0].self_coordinate.x - (nexTcor.x - snake[0].self_coordinate.x);
			nexTcor.y = snake[0].self_coordinate.y - (nexTcor.y - snake[0].self_coordinate.y);
		}

		if (size >= 5)  ///провер€ем змею на пересечение с собой
		{
			for (int i = 4; i < size; i++)
			{
				if (nexTcor.x == snake[i].self_coordinate.x  &&  nexTcor.y == snake[i].self_coordinate.y)
				{
					ret = -1;
					//break;
				}
			}
		}
	
		if (nexTcor.x == 0 || nexTcor.x == height)/// если зме€ упЄрлась в стенку, то она продолжает движение с другой стороны
		{
			nexTcor.x = height - nexTcor.x;
		}
		if (nexTcor.y == 0 || nexTcor.y == width)
		{
			nexTcor.y = width - nexTcor.y;
		}

		if (nexTcor.x == xpoint && nexTcor.y == ypoint)/// если голова змеи сьела точку увеличиваем длину змеи на 1 и устанавливаем флаг eatpoint 
		{
			size++;
			eatpoint = true;
		}

		cell *newsnake = new cell[size];
		
		newsnake[0].self_coordinate.x = nexTcor.x;///  заполн€ем массив новой змеи 
		newsnake[0].self_coordinate.y = nexTcor.y;
		newsnake[0].size = size;
		if (ret == -1)//флаг пересечени€ с самим собой
		{
			newsnake[0].route = ret;
		}
		else
		{
			newsnake[0].route = snake[0].route;
		}
		for (int i = 1; i < size; i++)
		{
			if (eatpoint == true)
			{
				newsnake[i].self_coordinate.x = snake[i ].self_coordinate.x;
				newsnake[i].self_coordinate.y = snake[i ].self_coordinate.y;
			}
			else
			{
				newsnake[i].self_coordinate.x = snake[i-1].self_coordinate.x;
				newsnake[i].self_coordinate.y = snake[i-1].self_coordinate.y;
			}
		}
		return newsnake;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	inline void print_point(char *Feeld[], int PointX, int PointY)
	{
		Feeld[PointX][PointY] = '@';
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	inline void delite_point(char *Feeld[], int pointX, int pointY)
	{
		Feeld[pointX][pointY] = 176;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	int create_apple(cell snake[], int n_x, int m_y)
	{
		int apple_x = rand() % (n_x - 3) + 1;
		int apple_y = rand() % (m_y - 3) + 1;

		int counter = 0;

	m1:
		for (int i = 0; i < snake[0].size; i++)
		{
			if (apple_x == snake[i].self_coordinate.x)
			{
				counter++;
			}
		}
		if (counter == (n_x - 2))
		{
			apple_x ==  apple_x + 1;
			if (apple_x == n_x - 1)
			{
				apple_x = 1;
			}
			goto m1;
		}

		counter = 0;
	m2:
		for (int i = 0; i < snake[0].size; i++)
		{
			if (apple_y == snake[i].self_coordinate.y)
			{
				counter++;
			}
		}
		if (counter == (m_y - 2))
		{
			apple_y == apple_y + 1;
			if (apple_y == m_y - 1)
			{
				apple_y = 1;
			}
			goto m2;
		}
		//cout << apple_x << "\n" << apple_y << "\n";
		return (apple_x * 100) + apple_y;// y = value % 100;       x = value /100;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

//char finde_button()
//{
//	// int button = 0;
//	 char a = 0;
//	_asm
//	{
//		///*MOV AX, 0040h;
//		//MOV DS, AX;
//		//MOV EBX, 001Eh;
//		//MOV AL, [EBX + 1];
//		//MOV AL, [0041Eh];*/
//
//		XOR AX, AX;
//		INT 16h;
//
//
//		CMP AH, 1Dh;// button W = up
//		JNE m1;
//		MOV AH, 1;
//		MOV a, AH;
//		JMP m;
//	m1:
//		CMP AH, 1Ch;// button A = left
//		JNE m2;
//		MOV AH, 2;
//		MOV a, AH;
//		JMP m;
//	m2:
//		CMP AH, 1Bh;// button S = down
//		JNE m3;
//		MOV AH, 3;
//		MOV a, AH;
//		JMP m;
//	m3:
//		CMP AH, 23h;// button D = right
//		JNE m4;
//		MOV AH, 4;
//		MOV a, AH;
//		JMP m;
//	m4:
//		CMP AH, 76h;// button Ecs = exit
//		JNE m;
//		MOV AH, 5;
//		MOV a, AH;
//	m:
//
//		
//	}
//	return a;
//}


int main()
{
	
	const int n = 12;
	const int Lenth_snake = 3;
	cell Snake[Lenth_snake];
	char FEELD[n][n];

	Snake[0].self_coordinate.x = 3;  // создаЄм начальную змейку из 3 €чеек
	Snake[0].self_coordinate.y = 5;
	Snake[0].route = 3;
	Snake[0].size = 3;
	Snake[1].self_coordinate.x = 2;
	Snake[1].self_coordinate.y = 5;
	Snake[2].self_coordinate.x = 1;
	Snake[2].self_coordinate.y = 5;

	//cout << (sizeof(Snake) / sizeof(*Snake)) << endl;
	int rt = 0;

	//while (1)
	//{
	//	rt = finde_button();
	//	/*if (rt == 0)
	//	{
	//		cout << rt;
	//		getchar();
	//		return 0;
	//	}*/
	//	rt = int(rt);
	//	cout << rt << "\n";
	//	Sleep(500);
	//}



	char *ff[n];
	for (int i = 0; i < n; i++)
	{
		ff[i] = FEELD[i];
	}

	feeld f;


	/*int ee = f.create_apple(Snake, 12, 12);
	int xx = ee / 100;
	int yy = ee % 100;

	cout << xx << "\n" << yy << "\n";

	getchar();

	ee = f.create_apple(Snake, 20,20);
	xx = ee / 100;
	 yy = ee % 100;
	 cout << xx << "\n" << yy << "\n";
	 getchar();*/

	f.create_feeld(ff, 12, 12);
	f.print_snake(Snake, ff, 3);
	
	int ee = f.create_apple(Snake, 20, 20);
	int xx = ee / 100;
	int yy = ee % 100;
	f.print_point(ff, xx, yy);

	f.print_feeld(ff, n, n);
	getchar();
	
	
    Snake[0].size = sizeof(Snake) / sizeof(*Snake);
	cell *newsnake = f.move(Snake, 0, 0, 12, 12);
	int eeee = sizeof(*newsnake) / sizeof(newsnake[0]);

	system("cls");
	f.create_feeld(ff, 12, 12);
	f.print_snake(newsnake, ff, newsnake[0].size);
	f.print_feeld(ff, n, n);

	cout << "\n" << "\n" << sizeof(*newsnake) << endl;

	getchar();
	return 0;

}