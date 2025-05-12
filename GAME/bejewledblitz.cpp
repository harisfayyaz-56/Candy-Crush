#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

//4-571     5-	595   time-815

int score = 0;
int highscore = 0;
int tempscore = 0;

void BlastVer(int Board[][8], int row, int col); //bcz they are used bfore their initialization
void BlastHor(int Board[][8], int row, int col);

bool CheckDestroyer(int Board[][8], int row, int col) //EXTENSION OF CHECK FUNCTION FOR DESTRPYER
{
	bool up = 0;  //TELLS IF DESTROYER VERTICLE GEMS ARE UP OR DOWN
	bool down = 0;
	int index_c = col;
	bool found = 0;
	if (row - 2 >= 0) //ONLY CHECKS IF GEMS ARE IN THE MIDDLE TO AVOID CHECKING JUNK VALUES
	{
		if (Board[row - 1][col] == Board[row][col] && Board[row - 2][col] == Board[row][col])
		{
			found = 1;
			up = 1;
		}
		else if (Board[row - 1][col + 1] == Board[row][col] && Board[row - 2][col + 1] == Board[row][col])
		{
			index_c = col + 1;
			found = 1;
			up = 1;
		}
		else if (Board[row - 1][col + 2] == Board[row][col] && Board[row - 2][col + 2] == Board[row][col])
		{
			index_c = col + 2;
			found = 1;
			up = 1;
		}
	}
	if (row + 2 <= 7)
	{
		if (Board[row + 1][col] == Board[row][col] && Board[row + 2][col] == Board[row][col])
		{
			found = 1;
			down = 1;
		}
		else if (Board[row + 1][col + 1] == Board[row][col] && Board[row + 2][col + 1] == Board[row][col])
		{
			index_c = col + 1;
			found = 1;
			down = 1;
		}
		else if (Board[row + 1][col + 2] == Board[row][col] && Board[row + 2][col + 2] == Board[row][col])
		{
			index_c = col + 2;
			found = 1;
			down = 1;
		}
	}
	if (found == 1 && up == 1) //IF GEMS COMBO IS UP PROCEEEDS TO MAKE THEM -1
	{
		//-1	
		Board[row][col] = -1;
		Board[row][col + 1] = -1;
		Board[row][col + 2] = -1;
		Board[row][index_c] = Board[row - 1][index_c] + 20;
		Board[row - 1][index_c] = -1;
		Board[row - 2][index_c] = -1;
		//-1
		for (int k = 0; k < 3; k++)
		{
			for (int i = row; i > 0; i--) //moves two horizontal element to the top
			{
				if (col + k != index_c)
				{
					swap(Board[i][col + k], Board[i - 1][col + k]);
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int k = (row - 2) + i; k > 0 + i; k--) //uses same logic as CHECK Vertical
				//swaps elements up one by one 
			{
				swap(Board[k][index_c], Board[k - 1][index_c]);
			}
		}
	}
	if (found == 1 && down == 1) //DOES THE SAME FOR DOWN VERTICAL GEMS
	{
		//-1
		Board[row][col] = -1;
		Board[row][col + 1] = -1;
		Board[row][col + 2] = -1;
		Board[row + 2][index_c] = Board[row + 1][index_c] + 20;
		Board[row + 1][index_c] = -1;
		//-1
		for (int k = 0; k < 3; k++)
		{
			for (int i = row; i > 0; i--) //moves two horizontal element to the top
			{
				if (col + k != index_c)
				{
					swap(Board[i][col + k], Board[i - 1][col + k]);

				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int k = row + i; k > 0 + i; k--) //uses same logic as CHECK Vertical
				//swaps elements up one by one 
			{
				swap(Board[k][index_c], Board[k - 1][index_c]);
			}
		}
	}
	if (found == 1)
	{
		score = score + 1800;
		for (int i = 0; i < 3; i++)
		{
			if (col + i == index_c)
			{
				for (int j = 0; j < 2; j++)
					Board[j][index_c] = rand() % 5;
			}
			else
			{
				Board[0][col + i] = rand() % 5;
			}
		}
	}
	return found;
}
void BlastDestroyer(int Board[][8], int row, int col)  //has been extended to destroy all destroyers and special gems in the premise of destroyer
{
	int _col[8] = { -1 - 1, -1 - 1, -1, -1 - 1, -1 }; //keeps count of destroyyers in the same colom 
	int counter_col = 0;

	int _row[8] = { -1, -1, -1 - 1, -1, -1 - 1, -1 }; //keeps count of destroyyers in the same row
	int counter_row = 0;
	int Blast_hor[10] = { -1, -1, -1 - 1, -1, -1 - 1, -1, -1, -1 }; //keeps check of special gems to avoid double swapping 
	int counter_hor = 0;
	for (int i = 0; i < 8; i++) //makes colom -1
	{
		if (i == row)
		{
			_col[counter_col] = i;//stores row
			counter_col++;
		}
		else if (Board[i][col] > 19)	//checks colom if any destroyer 
			//it destroys its row and if in the row there is anoter destroyer it checks in its colom to see other destroyer and destroys their row
		{
			_col[counter_col] = i;
			counter_col++;
			for (int j = 0; j < 8; j++)
			{
				if (Board[i][j] < 20)
				{
					if (Board[i][j] > 9 && Board[i][j] < 20)
					{
						BlastHor(Board, i, j - 1);
						Blast_hor[counter_hor] = i;		//checks special gem in coloumn
						counter_hor++;
						Blast_hor[counter_hor] = j;
						counter_hor++;
					}
					Board[i][j] = -1;
				}
				else
				{
					for (int l = 0; l < 8; l++)
					{
						if (Board[l][j] > 19 && l != i)
						{
							_col[counter_col] = l;
							counter_col++;
							for (int m = 0; m < 8; m++)
							{
								if (Board[l][m] > 9 && Board[l][m] < 20)
								{
									BlastHor(Board, l, m - 1);
									Blast_hor[counter_hor] = l;		//extended code to  check for destroyer in colom
									counter_hor++;					//then destroy it row and keeps record of destroyer row 
									Blast_hor[counter_hor] = m;
									counter_hor++;
								}
								Board[l][m] = -1;
							}
						}
					}
				}
			}
		}
		else if (Board[i][col] > 9 && Board[i][col] < 20)
		{
			BlastVer(Board, i - 1, col);
			for (int cleartop = i; cleartop >= 0; cleartop--) //to make -1 for good animation
				Board[cleartop][col] = -1;

		}
		Board[i][col] = -1;
	}
	for (int i = 0; i < 8; i++) //make row -1
	{
		if (i == col)
		{
			_row[counter_row] = i;		//also includes the destroer in the record which called the function
			counter_row++;
		}
		for (int k = 0; k < counter_col; k++)
		{
			if (Board[_col[k]][i] > 19)
			{
				for (int j = 0; j < 8; j++)		//destroyers colom of all destroyers which were recorded
				{
					if (Board[j][i] > 9 && Board[j][i] < 20)
					{
						BlastVer(Board, j - 1, i);
					}
					Board[j][i] = -1;
				}
				_row[counter_row] = i;
				counter_row++;
			}
		}
		if (Board[row][i] > 9 && Board[row][i] < 20)	//destroys special gems in destroyer region
		{
			BlastHor(Board, row, i - 1);
			Blast_hor[counter_hor] = row;
			counter_hor++;
			Blast_hor[counter_hor] = i;
			counter_hor++;
		}
		Board[row][i] = -1;
	}
	//sorts destroyers to start from 0 row and then proceeed ...random rows may disrupt code logic
	int sorter = counter_col;
	for (int j = 0; j < counter_col; j++)
	{
		int max = _col[0], index = 0;
		for (int i = 0; i < sorter; i++)
		{
			if (max < _col[i])
			{
				max = _col[i];
				index = i;
			}
			//sorts row record to ascending to avoid swaping anomalies

		}
		swap(sorter, index); sorter--;
	}
	for (int j = 0; j < counter_col; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			int flag = 0;
			if (i != col)
			{
				if (counter_hor > 0)
					for (int l = 0; l < counter_hor; l = l + 2)		//swaps all rows in record to top 
						if (_col[j] == Blast_hor[l]) //compares record with blaster to also swap its rows
							if (i == Blast_hor[l + 1])
							{							//+2 because bcz matrix contains first row then colom
								flag = 1;
								i = i + 3;
							}
				for (int k = _col[j]; k > 0 && flag == 0; k--)
				{
					swap(Board[k][i], Board[k - 1][i]);
					//takes elements to the top one 
				}
			}//by one 
			if (flag == 1)
				i--;
		}
	}
	for (int k = 0; k < counter_row; k++)
	{
		for (int i = counter_col; i < 8; i++) //1 bcz row randomizer will give value to elements in record coloms
		{
			Board[i][_row[k]] = rand() % 5;
		}
	}
	for (int i = 0; i < counter_col; i++)
	{
		for (int j = 0; j < 8; j++)		//randomizes rows in record
			Board[i][j] = rand() % 5;
	}
	score = score + 4955;
}

void BlastVer(int Board[][8], int row, int col)
{
	score += 925;
	for (int i = 0; i < 3; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (row + i >= 0 && row + i <= 7 && col + j >= 0 && col + j <= 7)
			{
				Board[row + i][col + j] = -1;
			}
		}
	}
	for (int blast_col = -1; blast_col < 2; blast_col++) //blast destroys 1 col to left and 1 to right
	{
		if (col + blast_col >= 0 && col + blast_col <= 7)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int k = row + i; k > 0 + i; k--) //swaps elements up one by one 
				{
					swap(Board[k][col + blast_col], Board[k - 1][col + blast_col]);
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)  //adds new element at the top for each destroyed row
	{

		for (int j = -1; j < 2; j++)
		{
			Board[i][col + j] = rand() % 5;
		}
	}
}

void BlastHor(int Board[][8], int row, int col)
{


	score += 925;
	for (int blast_row = -1; blast_row <= 1; blast_row++)
	{
		if (row + blast_row <= 7 && row + blast_row >= 0)
		{
			for (int i = 0; i < 3; i++)
			{
				Board[row + blast_row][col + i] = -1; //makes elements that are blasted -1
			}
		}
	}
	for (int blast_row = -1; blast_row <= 1; blast_row++)
	{
		if (row + blast_row <= 7 && row + blast_row >= 0)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int k = row + blast_row; k > 0; k--)
				{
					swap(Board[k][col + i], Board[k - 1][col + i]);
				}
			}
		}
	}
	for (int blast_col = 0; blast_col < 3; blast_col++)  //adds new element at the top for each destroyed colomn
	{
		for (int i = 0; i < 3; i++)
		{
			Board[i][col + blast_col] = rand() % 5;
		}
	}
}

bool CheckVer(int Board[][8])
{
	int point = 0;  //point store for ever vertical check
	bool found = 1;
	bool counter = 0;//to return if any combo was found
	while (found == 1)//keeps loop running as long as combos are being found
	{
		int combo_size = 0;//to return if anycombo
		//to store if 3 combo or 5 or more	
		int special = 0;
		found = 0;
		int temp;
		int index_r = -1;    //store start location of combo
		int index_c = -1;
		int specialgem = 0;
		int index_special;
		for (int i = 0; i < 6 && found == 0; i++)//i<7 to overide checking junk values
		{
			for (int j = 0; j < 8 && found == 0; j++)
			{
				if (Board[i][j] == Board[i + 1][j] && Board[i][j] == Board[i + 2][j])//3 combo
				{
					found = 1;
					index_r = i;
					index_c = j;
					point = point + 100;//100 points for each 3 combo
					combo_size = 3;
					counter = 1;
					if (Board[i][j] == Board[i + 3][j] && i < 5)
					{
						combo_size = 4;
						point = point + 150;
						special = 1;

						if (Board[i][j] == Board[i + 4][j] && i < 4)
						{
							special = 2;
							combo_size = 5;
							point = point + 250;
						}
					}
				}
				else if (Board[i][j] > 9 && Board[i][j] < 20 || Board[i + 1][j] > 9 && Board[i + 1][j] < 20 || Board[i + 2][j] > 9 && Board[i + 2][j] < 20)
				{//converts special elemnt to normal then compare as normal
					for (int k = 0; k < 3; k++)
					{
						if (Board[i + k][j] > 9)
						{
							specialgem = 1;
							index_r = i;
							index_c = j;
							index_special = k;
							temp = Board[i + k][j];
							Board[i + k][j] = temp - 10;
							if (Board[i][j] == Board[i + 1][j] && Board[i][j] == Board[i + 2][j])//3 combo
							{
								found = 1;
							}
							else//if no combo makes them special again same logic for elbow and special
							{
								Board[index_r + index_special][index_c] = temp;
								specialgem = 0;
							}
						}
					}
				}
				else if (Board[i][j] > 19 || Board[i + 1][j] > 19 || Board[i + 2][j] > 19)
				{
					for (int k = 0; k < 3; k++)
					{
						if (Board[i + k][j] > 19)
						{
							specialgem = 2;
							index_r = i;
							index_c = j;
							index_special = k;//store position of special character in combo
							temp = Board[i + k][j];
							Board[i + k][j] = temp - 20;
							if (Board[i][j] == Board[i + 1][j] && Board[i][j] == Board[i + 2][j])//3 combo
							{
								found = 1;
							}
							else
							{
								Board[index_r + index_special][index_c] = temp;
								specialgem = 0;
							}
						}
					}
				}
			}
		}//if special or elbow found blasts them
		if (found == 1 && specialgem == 1)
		{
			BlastVer(Board, index_r, index_c);
			found = 0;
			counter = 1;
		}
		else if (found == 1 && specialgem == 2)
		{
			BlastDestroyer(Board, index_r + index_special, index_c);
			found = 0;
			counter = 1;
		}
		else if (found == 1)//for nomal combos
		{
			if (special > 0)
			{
				Board[index_r + (combo_size - 1)][index_c] = Board[index_r][index_c] + 10;//makes special "+10"
				for (int i = 0; i < combo_size - 1; i++) //separate bcz it prevents checking otherwise
				{
					Board[index_r + i][index_c] = -1;//others -1
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					Board[index_r + i][index_c] = -1;
				}
			}
			for (int i = 0; i < combo_size; i++)
			{
				if (special > 0)
				{
					if (Board[index_r + i][index_c] == -1)
					{
						for (int k = index_r + i; k > 0 + i; k--) //swaps elements up one by one 
						{
							swap(Board[k][index_c], Board[k - 1][index_c]);
						}
					}
				}
				else
				{
					for (int k = index_r + i; k > 0 + i; k--) //swaps elements up one by one 
					{
						swap(Board[k][index_c], Board[k - 1][index_c]);
					}
				}
			}
			if (combo_size == 3)
				combo_size = 4; //other wise formula doesnt work
			for (int i = 0; i < combo_size - 1; i++)
			{
				Board[i][index_c] = rand() % 5;
			}
		}
	}
	score = score + point;
	return counter;
}

bool CheckHor(int Board[][8], int row = -1, int col = -1)
{
	int point = 0;  //point store for ever vertical check
	bool found = 1;
	bool counter = 0;  //to return if anycombo

	while (found == 1)//logic same as checkver
	{
		int temp = -1;
		int combo_size = 0;//to store if 3 combo or 5 or more
		int special = 0;
		found = 0;
		int index_r = -1;
		int index_special = -1;
		int index_c = -1;
		int specialgem = 0;
		int destroyer = 0;//name of elbow combo
		for (int i = 0; i < 8 && found == 0; i++)//i<7 to overide checking junk values
		{
			for (int j = 0; j < 6 && found == 0; j++)
			{
				if (Board[i][j] == Board[i][j + 1] && Board[i][j] == Board[i][j + 2])//3 combo
				{
					counter = 1;
					found = 1;
					index_r = i;
					index_c = j;
					point = point + 100;//100 points for each 3 combo
					combo_size = 3;
					if (CheckDestroyer(Board, i, j) == 1)//check destroyer in horizontal bcz horizontal check is first
					{
						found = 1;
						destroyer = 1;
					}
					else if (Board[i][j] == Board[i][j + 3])
					{
						combo_size = 4;
						point = point + 150;
						special = Board[i][j] + 10;
						if (col == -1)//if combo is made during randomizing it will make special in center of combo
						{
							col = j + 2;
						}
						if (Board[i][j] == Board[i][j + 4])
						{
							combo_size = 5;
							point = point + 250;
						}
					}
				}
				else if (Board[i][j] > 9 && Board[i][j] < 20 || Board[i][j + 1] > 9 && Board[i][j + 1] < 20 || Board[i][j + 2] > 9 && Board[i][j + 2] < 20)
				{
					for (int k = 0; k < 3; k++)
					{
						if (Board[i][j + k] > 9)
						{
							specialgem = 1;
							index_r = i;
							index_c = j;
							index_special = k;
							temp = Board[i][j + k];
							Board[i][j + k] = temp - 10;
							if (Board[i][j] == Board[i][j + 1] && Board[i][j] == Board[i][j + 2])//3 combo
							{
								found = 1;
							}
							else
							{
								Board[index_r][index_c + index_special] = temp;
								specialgem = 0;
							}
						}
					}
				}
				else if (Board[i][j] > 19 || Board[i][j + 1] > 19 || Board[i][j + 2] > 19)
				{
					for (int k = 0; k < 3; k++)
					{
						if (Board[i][j + k] > 19)
						{
							specialgem = 2;
							index_r = i;
							index_c = j;
							index_special = k;
							temp = Board[i][j + k];
							Board[i][j + k] = temp - 20;
							if (Board[i][j] == Board[i][j + 1] && Board[i][j] == Board[i][j + 2])//3 combo
							{
								found = 1;
							}
							else
							{
								Board[index_r][index_c + index_special] = temp;
								specialgem = 0;
							}
						}
					}
				}
			}
		}
		if (found == 1 && specialgem == 1)
		{
			BlastHor(Board, index_r, index_c + index_special - 1);
			found = 0;
			counter = 1;
		}
		else if (found == 1 && specialgem == 2)
		{
			BlastDestroyer(Board, index_r, index_c + index_special);
			found = 0;
			counter = 1;
		}
		//swappin and new gems
		else if (found == 1 && destroyer == 0)
		{
			for (int i = 0; i < combo_size; i++)
			{
				Board[index_r][index_c + i] = -1;
				if (special > 0)
					if (index_c + i == col)
						Board[index_r][index_c + i] = special;//special =gem+10
			}
			counter = 1;
			for (int i = 0; i < combo_size; i++)
			{
				if (special != 0)//skips swappin of special gem
				{
					if (index_c + i != col)
					{
						for (int k = index_r; k > 0; k--)
						{
							swap(Board[k][index_c + i], Board[k - 1][index_c + i]);
							//takes elements to the top one 
						}
					}//by one except special one made at the swap spot
				}
				else
				{
					for (int k = index_r; k > 0; k--)
					{
						swap(Board[k][index_c + i], Board[k - 1][index_c + i]);
					}
				}
			}
			for (int i = 0; i < combo_size; i++)
			{
				if (special == 0)
				{
					Board[0][index_c + i] = rand() % 5;
				}
				else  //prevents replacing of element wich wasnt moved
				{
					if (index_c + i != col)
					{
						Board[0][index_c + i] = rand() % 5;
					}
				}
			}
		}
		row = -1;
		col = -1;
	}
	score = score + point;
	return counter;
}

bool Check(int Board[][8], int row = -1, int col = -1)
{
	bool counter = 0;
	bool check = CheckHor(Board, row, col) + CheckVer(Board);
	while (check != 0)
	{
		check = CheckHor(Board, row, col) + CheckVer(Board);
		counter = 1;
	}
	return counter;
}
Text createButton(const string& buttonText, const Font& font, unsigned int fontSize, const Vector2f& position, const Color& fillColor, const Color& outlineColor = Color::White, float outlineThickness = 2.0f) {
	Text button(buttonText, font, fontSize);
	button.setPosition(position);
	button.setFillColor(fillColor);
	button.setOutlineThickness(outlineThickness);
	button.setOutlineColor(outlineColor);
	return button;
}

Texture loadTexture(const string& filePath) {
	Texture texture;
	if (!texture.loadFromFile(filePath)) {
		cerr << "Error loading texture from file: " << filePath << endl;
	}
	return texture;
}

void game()
{
	ifstream infile("highscore.txt");
	infile >> highscore;
	score = 0;

	system("CLS");
	RenderWindow window(VideoMode(1600, 900), "Play Game", Style::Default); //Creating a new window
	int r = 0;
	int c = 0;
	//Adding font 
	Font font;
	if (!font.loadFromFile("CotaneBeach.otf")) {
		cout << "Error loading font" << endl;
		return;
	}

	Text back = createButton("ESC to Exit ", font, 50, Vector2f(20, 900), Color::Black);
	Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::Red);

	int selectorPos_X = 592;
	int selectorPos_Y = 92;
	RectangleShape selector(Vector2f(70, 70));
	selector.setOutlineThickness(5);
	selector.setOutlineColor(Color::Blue);
	selector.setFillColor(Color::Transparent);
	selector.setPosition(selectorPos_X, selectorPos_Y);


	Texture backgroundTexture = loadTexture("gamebg.jpg");
	Texture black = loadTexture("black.png");
	Texture gem0 = loadTexture("candy0.png");
	Texture gem1 = loadTexture("candy1.png");
	Texture gem2 = loadTexture("candy2.png");
	Texture gem3 = loadTexture("candy3.png");
	Texture gem4 = loadTexture("candy4.png");
	Texture gem10 = loadTexture("candy10.png");
	Texture gem11 = loadTexture("candy11.png");
	Texture gem12 = loadTexture("candy12.png");
	Texture gem13 = loadTexture("candy13.png");
	Texture gem14 = loadTexture("candy14.png");
	Texture gem20 = loadTexture("candy20.png");
	Texture gem21 = loadTexture("candy21.png");
	Texture gem22 = loadTexture("candy22.png");
	Texture gem23 = loadTexture("candy23.png");
	Texture gem24 = loadTexture("candy24.png");

	srand(static_cast<unsigned int>(time(nullptr)));

	const int matrixSize = 8;   // Create an 8x8 matrix and fill it with random numbers
	int matrix[matrixSize][matrixSize];

	for (int i = 0; i < matrixSize; ++i) {
		for (int j = 0; j < matrixSize; ++j) {
			matrix[i][j] = rand() % 5; // Random numbers between 0 and 6
		}
	}
	Sprite background(backgroundTexture);
	Sprite Black(black);
	Sprite Gem0(gem0);
	Sprite Gem1(gem1);
	Sprite Gem2(gem2);
	Sprite Gem3(gem3);
	Sprite Gem4(gem4);
	Sprite Gem10(gem10);
	Sprite Gem11(gem11);
	Sprite Gem12(gem12);
	Sprite Gem13(gem13);
	Sprite Gem14(gem14);
	Sprite Gem20(gem20);
	Sprite Gem21(gem21);
	Sprite Gem22(gem22);
	Sprite Gem23(gem23);
	Sprite Gem24(gem24);


	srand(static_cast<unsigned int>(time(nullptr)));
	int rng = rand() % 4;   // Generate a random number
	int key = 0;
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setPosition(10, 10);
	Text highscoreText;
	highscoreText.setFont(font);
	highscoreText.setCharacterSize(50);
	highscoreText.setPosition(10, 110);

	Text timerText;
	timerText.setFont(font);
	timerText.setCharacterSize(50);
	timerText.setPosition(10, 60);

	Clock clock;
	Time elapsedTime;
	int countdownDuration = 120;
	Time countdownTime = seconds(countdownDuration);
	int secondsRemaining = 1;

	while (window.isOpen() && secondsRemaining)
	{
		Event event;   // Process events
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == Keyboard::Right)
				{
					if (r < 7) {
						selector.move(81, 0);
						if (key == 1)
						{
							swap(matrix[c][r], matrix[c][r + 1]);
						}
						r++;
						key = 0;
					}
				}

				if (event.key.code == Keyboard::Left)
				{
					if (r > 0)
					{
						selector.move(-81, 0);
						if (key == 1)
						{
							swap(matrix[c][r], matrix[c][r - 1]);
						}
						r--;
						key = 0;
					}
				}
				if (event.key.code == Keyboard::Up)
				{
					if (c > 0)
					{
						selector.move(0, -100);
						if (key == 1)
						{
							swap(matrix[c][r], matrix[c - 1][r]);
						}
						c--;
						key = 0;
					}
				}

				if (event.key.code == Keyboard::Down)
				{
					if (c < 7)
					{
						selector.move(0, 100);
						if (key == 1)
						{
							swap(matrix[c][r], matrix[c + 1][r]);
						}
						c++;
						key = 0;
					}
				}
				if (event.key.code == Keyboard::Return)
				{
					if (key == 0)
						key = 1;
					else
						key = 0;
				}

			}
			Check(matrix);
		}
		if (score > highscore)
		{
			tempscore = score;
			ofstream outfile("highscore.txt");
			outfile << tempscore;
		}
		window.clear();

		window.draw(background);
		window.draw(Black);
		window.draw(back);
		window.draw(selector);
		
		elapsedTime = clock.getElapsedTime();
		int secondsElapsed = static_cast<int>(elapsedTime.asSeconds());
		secondsRemaining = countdownDuration - secondsElapsed;
		
		scoreText.setString("Score : " + to_string(score));
		timerText.setString("Time : " + to_string(secondsRemaining) + "s");
		highscoreText.setString("High Score : " + to_string(highscore));
		
		window.draw(scoreText);
		window.draw(timerText);
		window.draw(highscoreText);
		
		int x = 0;
		int y = 0;
		for (int i = 0; i < matrixSize; ++i)
		{
			for (int j = 0; j < matrixSize; ++j)
			{
				// Set the position of the text on the window
				Gem0.setPosition(600 + x, 100 + y);
				Gem1.setPosition(600 + x, 100 + y);
				Gem2.setPosition(600 + x, 100 + y);
				Gem3.setPosition(600 + x, 100 + y);
				Gem4.setPosition(600 + x, 100 + y);
				Gem10.setPosition(585 + x, 85 + y);
				Gem11.setPosition(585 + x, 85 + y);
				Gem12.setPosition(585 + x, 85 + y);
				Gem13.setPosition(585 + x, 85 + y);
				Gem14.setPosition(585 + x, 85 + y);
				Gem20.setPosition(585 + x, 85 + y);
				Gem21.setPosition(585 + x, 85 + y);
				Gem22.setPosition(585 + x, 85 + y);
				Gem23.setPosition(585 + x, 85 + y);
				Gem24.setPosition(585 + x, 85 + y);

				x += 80;
				switch (matrix[i][j])     // Draw the text on the window
				{
				case 0:
					gem0.loadFromFile("candy0.png");
					Gem0.setScale(0.23, 0.23);
					window.draw(Gem0);
					break;

				case 1:
					gem1.loadFromFile("candy1.png");
					Gem1.setScale(0.23, 0.23);
					window.draw(Gem1);
					break;

				case 2:
					gem2.loadFromFile("candy2.png");
					Gem2.setScale(0.23, 0.23);
					window.draw(Gem2);
					break;

				case 3:
					gem3.loadFromFile("candy3.png");
					Gem3.setScale(0.23, 0.23);
					window.draw(Gem3);
					break;

				case 4:
					gem4.loadFromFile("candy4.png");
					Gem4.setScale(0.23, 0.23);
					window.draw(Gem4);
					break;
				case 10:
					gem10.loadFromFile("candy10.png");
					Gem10.setScale(0.45, 0.45);
					window.draw(Gem10);
					break;

				case 11:
					gem11.loadFromFile("candy11.png");
					Gem10.setScale(0.45, 0.45);
					window.draw(Gem11);
					break;
				case 12:
					gem12.loadFromFile("candy12.png");
					Gem12.setScale(0.45, 0.45);
					window.draw(Gem12);
					break;

				case 13:
					gem13.loadFromFile("candy13.png");
					Gem13.setScale(0.45, 0.45);
					window.draw(Gem13);
					break;
				case 14:
					gem14.loadFromFile("candy14.png");
					Gem14.setScale(0.45, 0.45);
					window.draw(Gem14);
					break;
				case 20:
					gem20.loadFromFile("candy20.png");
					Gem20.setScale(0.45, 0.45);
					window.draw(Gem20);
					break;

				case 21:
					gem21.loadFromFile("candy21.png");
					Gem20.setScale(0.45, 0.45);
					window.draw(Gem21);
					break;
				case 22:
					gem22.loadFromFile("candy22.png");
					Gem22.setScale(0.45, 0.45);
					window.draw(Gem22);
					break;

				case 23:
					gem23.loadFromFile("candy23.png");
					Gem23.setScale(0.45, 0.45);
					window.draw(Gem23);
					break;
				case 24:
					gem24.loadFromFile("candy24.png");
					Gem24.setScale(0.45, 0.45);
					window.draw(Gem24);
					break;
					// Handle other cases if needed...

				default:
					// Handle cases outside the range 0-5, if necessary.
					break;
				}
			}
			y += 100;
			x = 0;
		}
		window.display();
	}
	window.clear();
	scoreText.setCharacterSize(100);
	scoreText.setPosition(200, 200);
	window.draw(scoreText);
	window.display();
	sleep(seconds(2.0f));
}

void infoMenu()
{
	system("CLS");
	RenderWindow window(VideoMode(1600, 900), "Play Game", Style::Default); //Creating a new window

	Font font;    //Adding font 
	if (!font.loadFromFile("CotaneBeach.otf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	Text p1 = createButton("1. Press ARROW KEYS to move the cursor.", font, 70, Vector2f(120, 200), Color::Black);
	Text p2 = createButton("2. Select the gem with ENTER BUTTON.", font, 70, Vector2f(120, 350), Color::Black);
	Text p3 = createButton("3. Use ARROW KEYS to swap the gems.", font, 70, Vector2f(120, 500), Color::Black);
	Text back = createButton("ESC to Exit ", font, 30, Vector2f(20, 700), Color::Black);

	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("credbg.jpg"))
	{
		cerr << "Error loading background image" << endl;
		return;
	}

	Texture black = loadTexture("black.png");
	Sprite background(backgroundTexture);
	Sprite Black(black);

	while (window.isOpen())
	{
		Event event;    // Process events
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}

			}
		}

		window.clear();

		window.draw(background);
		window.draw(Black);
		window.draw(p1);
		window.draw(p2);
		window.draw(p3);
		window.draw(back);   //Add window.draw functions here
		window.display();
	}
}

void credMenu()
{
	system("CLS");
	RenderWindow window(VideoMode(1600, 900), "Play Game", Style::Default); //Creating a new window

	Font font;   //Adding font 
	if (!font.loadFromFile("CotaneBeach.otf")) {
		cerr << "Error loading font" << endl;
		return;
	}

	Text p1 = createButton("ALI YOUSAF | 23L - 0737", font, 100, Vector2f(150, 200), Color::Black);
	Text p2 = createButton("HARIS FAYYAZ | 23L - 0767", font, 100, Vector2f(150, 500), Color::Black);
	Text back = createButton("ESC to Exit ", font, 30, Vector2f(20, 700), Color::Black);

	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("credbg.jpg"))
	{
		cerr << "Error loading background image" << endl;
		return;
	}

	Texture black = loadTexture("black.png");
	Sprite background(backgroundTexture);
	Sprite Black(black);

	while (window.isOpen())
	{
		Event event;   // Process events
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear();

		window.draw(background);
		window.draw(Black);
		window.draw(p1);
		window.draw(p2);

		window.draw(back);   //Add window.draw functions here
		window.display();
	}
}

int main() {
	// Create the main window
	RenderWindow window(VideoMode(1600, 900), "Game", Style::Default);

	Font font;    // Define fonts and text
	if (!font.loadFromFile("CotaneBeach.otf")) {
		cout << "Error loading font" << endl;
		return 0;
	}

	Text title = createButton("GEM ODYSSEY", font, 150, Vector2f(400, 50), Color::Black);
	Text playButton = createButton("Play", font, 60, Vector2f(700, 300), Color::Black);
	Text creditButton = createButton("Credit", font, 60, Vector2f(680, 420), Color::Black);
	Text infoButton = createButton("How to Play", font, 60, Vector2f(630, 540), Color::Black);
	Text exitButton = createButton("Exit", font, 60, Vector2f(700, 660), Color::Black);
	Text arrow = createButton("------------------------", font, 50, Vector2f(630, 345), Color::Black);

	// Load and set up the background image
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("gamebg.jpg"))
	{
		cerr << "Error loading background image" << endl;
		return 0;
	}

	Sprite background(backgroundTexture);

	while (window.isOpen())    // Main loop
	{
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			// Check for key presses
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					// Move up in the menu
					if (arrow.getPosition().y > playButton.getPosition().y)
					{
						arrow.move(0, -120);
					}
				}
				else if (event.key.code == Keyboard::Down)
				{
					// Move down in the menu
					if (arrow.getPosition().y < exitButton.getPosition().y)
					{
						arrow.move(0, 120);
					}
				}
				else if (event.key.code == Keyboard::Return)
				{
					// Enter key pressed, perform action based on the selected menu item
					if (arrow.getPosition().y <= playButton.getPosition().y + 60)
					{
						cout << "Start Game selected" << endl;
						game();
					}

					else if (arrow.getPosition().y <= creditButton.getPosition().y + 60)
					{
						cout << "Credit Menu selected" << endl;
						credMenu();
					}

					else if (arrow.getPosition().y <= infoButton.getPosition().y + 60)
					{
						cout << "Instruction selected" << endl;
						infoMenu();
					}

					else if (arrow.getPosition().y <= exitButton.getPosition().y + 60)
					{
						cout << "Exit selected" << endl;
						window.close();
					}
				}
			}
		}
		// Clear the window
		window.clear();

		window.draw(background);   // Draw the background

		window.draw(title);        // Draw the elements
		window.draw(playButton);
		window.draw(exitButton);
		window.draw(creditButton);
		window.draw(infoButton);
		window.draw(arrow);

		window.display(); // Display the content of the window
	}
	return 0;
}