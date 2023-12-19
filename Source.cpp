#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>


using namespace std;

const int sizematrix = 9; // 9x9
const int sizematrixcell = 3; //3x3
const int levelSu[5][2]{ { 1, 40 }, { 2, 30 }, { 3, 25 }, { 4, 22 }, { 5, 20 } };

//const int originalMatrix[sizematrix][sizematrix] = {{ 1,2,3,/**/4,5,6,/**/7,8,9 },
//													{ 4,5,6,/**/7,8,9,/**/1,2,3 },
//													{ 7,8,9,/**/1,2,3,/**/4,5,6 },
//													/*--------------------------*/
//													{ 2,3,4,/**/5,6,7,/**/8,9,1 },
//													{ 5,6,7,/**/8,9,1,/**/2,3,4 },
//													{ 8,9,1,/**/2,3,4,/**/5,6,7 },
//													/*--------------------------*/
//													{ 3,4,5,/**/6,7,8,/**/9,1,2 },
//													{ 6,7,8,/**/9,1,2,/**/3,4,5 },
//													{ 9,1,2,/**/3,4,5,/**/6,7,8 }};


bool checkfullMatrix(int matrixcheck[sizematrix][sizematrix]), 
	inTheGame(int matrixFull[sizematrix][sizematrix], int ingameMatrix[sizematrix][sizematrix]),
	checkMatrix(int arrayMatrix[sizematrix][sizematrix], int string, int colum, int checknum),
	checkMiniMatrix(int arrayMatrix[sizematrix][sizematrix], int string, int colum, int numchek);

int selectlvlSU();

void creatSU(int transformedmatrix[sizematrix][sizematrix]),
	copymatrix(int matrix[sizematrix][sizematrix], int copymatrix[sizematrix][sizematrix]),
	tranfomatingMatrixToTree(int creatingSu[sizematrix][sizematrix], int sizeAvailableCells, int outputmatrix[sizematrix][sizematrix]);


int main()
{

	setlocale(LC_ALL, "Russian");
	int levelSudoky = selectlvlSU();
	int creatingSu[sizematrix][sizematrix];

	creatSU(creatingSu);

	int sizeAvailableCells = levelSu[levelSudoky - 1][1]; // получим количество выводных ячеек	
	int outputmatrix[sizematrix][sizematrix];
	//Заполним нулями, для понимания пустых ячеек
	for (int s = 0; s < sizematrix; s++){
		for (int c = 0; c < sizematrix; c++){
			outputmatrix[s][c] = 0;
		}
	}

	tranfomatingMatrixToTree(creatingSu, sizeAvailableCells, outputmatrix);
	inTheGame(creatingSu, outputmatrix);

	//Start The Game

}

int selectlvlSU() {

	int selectedValue = 0;
	bool Selectioncomplete = false;
	cout << "1 - Very simple; 2 - Simple; 3 - Normal; 4 - Difficult; 5 - Very difficult. ";
	do
	{
		cout << "Select a level: ";
		cin >> selectedValue;
		if (selectedValue != 0 and selectedValue < 6)
		{
			Selectioncomplete = true;
		}
		else
		{
			cout << "You have not chosen the difficulty level! Repeat again." << endl << endl;
		}
	} while (!Selectioncomplete);

	return selectedValue;
}

void tranfomatingMatrixToTree(int creatingSu[sizematrix][sizematrix], int sizeAvailableCells, int outputmatrix[sizematrix][sizematrix]) {
	
	for (int i = 0; i < sizeAvailableCells; i++)
	{
		//Сделано 2 рандомных числа, т.к. это упростит выбор и не надо обходить все в цикле
		int randColumn = rand() % 8;
		int randString = rand() % 8;

		if (outputmatrix[randString][randColumn] != creatingSu[randString][randColumn]) {
			outputmatrix[randString][randColumn] = creatingSu[randString][randColumn];
		}
		else {
			tranfomatingMatrixToTree(creatingSu, (sizeAvailableCells - i), outputmatrix);
			break;
		}
	}
}

void creatSU(int transformedmatrix[sizematrix][sizematrix])
{
	//Требуется 2 матрицы, для того чтобы в случае чего, откатить на шаг назад
	int convertedMatrix[sizematrix][sizematrix];
	int originalMatrix[sizematrix][sizematrix] = 
	{	{ 1,2,3,/**/4,5,6,/**/7,8,9 },
		{ 4,5,6,/**/7,8,9,/**/1,2,3 },
		{ 7,8,9,/**/1,2,3,/**/4,5,6 },
		/*--------------------------*/
		{ 2,3,4,/**/5,6,7,/**/8,9,1 },
		{ 5,6,7,/**/8,9,1,/**/2,3,4 },
		{ 8,9,1,/**/2,3,4,/**/5,6,7 },
		/*--------------------------*/
		{ 3,4,5,/**/6,7,8,/**/9,1,2 },
		{ 6,7,8,/**/9,1,2,/**/3,4,5 },
		{ 9,1,2,/**/3,4,5,/**/6,7,8 } 
	};
	copy(&originalMatrix[0][0], &originalMatrix[0][0] + sizematrix * sizematrix, &convertedMatrix[0][0]);
	copy(&originalMatrix[0][0], &originalMatrix[0][0] + sizematrix * sizematrix, &transformedmatrix[0][0]);

	// Транспонирование
	int transorn = 1 + rand() % 2;
	if (transorn == 2) {
		for (int i = 0; i < sizematrix; i++){
			for (int j = 0; j < sizematrix; j++){
				convertedMatrix[j][i] = originalMatrix[i][j];
			}
		}
		copy(&convertedMatrix[0][0], &convertedMatrix[0][0] + sizematrix * sizematrix, &transformedmatrix[0][0]);
	}

	srand(time(0));
	// Перестановка внутри внутр блоков, по колонкам
	int shiftMatrixColum = rand() % 5;
	for (int i = 0; i < shiftMatrixColum; i++)
	{
		int chekingColum = 0;
		int shiftrandColum = rand() % 8; //0 - 8
		if (shiftrandColum <= 2) {
			chekingColum = rand() % 2; // 0 - 2
		}
		else if (shiftrandColum > 2 and shiftrandColum <= 5) {
			chekingColum = 3 + rand() % (5 - 3);// 3 - 5
		}
		else if (shiftrandColum > 5 and shiftrandColum <= 8) {
			chekingColum = 6 + rand() % (8 - 6); // 6 - 8
		}

		if (shiftrandColum != chekingColum and shiftrandColum < 9 and shiftrandColum >=0)
		{
			for (int c = 0; c < sizematrix; c++) {
				convertedMatrix[c][chekingColum] = originalMatrix[c][shiftrandColum];
				convertedMatrix[c][shiftrandColum] = originalMatrix[c][chekingColum];
			}
		}
		else {
			continue;
		}

		if (checkfullMatrix(convertedMatrix)) {
			// Если все хорошо, то копируем в итоговую таблицу
			copy(&convertedMatrix[0][0], &convertedMatrix[0][0] + sizematrix * sizematrix, &transformedmatrix[0][0]);
		}
		else {
			// если находим в таблице задвоение, тогда откатываем назад 
			copy(&transformedmatrix[0][0], &transformedmatrix[0][0] + sizematrix * sizematrix, &convertedMatrix[0][0]);
		}

	}
	//srand(time(0));
	// Перестановка внутри внутр блоков, по строкам
	int shiftMatrixString = rand() % 5; 
	for (int i = 0; i < shiftMatrixString; i++)
	
	{
		int chekingString = 0;
		int shiftrandstring = rand() % 8; //0 - 8
		if (shiftrandstring <= 2){
			chekingString = rand() % 2; // 0 - 2
		}
		else if (shiftrandstring > 2 and shiftrandstring <= 5){
			chekingString = 3 + rand() % (5 - 3);// 3 - 5
		}
		else if (shiftrandstring > 5 and shiftrandstring <= 8){
			chekingString = 6 + rand() % (8 - 6); // 6 - 8
		}

		if (shiftrandstring != chekingString){
			for (int s = 0; s < sizematrix; s++) {
				convertedMatrix[chekingString][s] = transformedmatrix[shiftrandstring][s];
				convertedMatrix[shiftrandstring][s] = transformedmatrix[chekingString][s];
			}
		}
		else {
			continue;
		}

		if (checkfullMatrix(convertedMatrix)) {
			// Если все хорошо, то копируем в итоговую таблицу
			copy(&convertedMatrix[0][0], &convertedMatrix[0][0] + sizematrix * sizematrix, &transformedmatrix[0][0]);
		}
		else {
			// если находим в таблице задвоение, тогда откатываем назад 
			copy(&transformedmatrix[0][0], &transformedmatrix[0][0] + sizematrix * sizematrix, &convertedMatrix[0][0]);
		}
	}

}

bool checkfullMatrix(int matrixcheck[sizematrix][sizematrix]) {
	// Проверка по колонкам и строкам
	for (int c = 0; c < sizematrix; c++) {
		for (int s = 0; s < sizematrix; s++)
		{
			if (!checkMatrix(matrixcheck, s, c, matrixcheck[s][c]) or !checkMiniMatrix(matrixcheck, s, c, matrixcheck[s][c])) //or !checkMatrix(matrixcheck, c, s, matrixcheck[c][s]) 
			{
				return false;
			}
		}
	}
	return true;
}

bool checkMatrix(int arrayMatrix[sizematrix][sizematrix], int string, int colum, int checknum)
{

	for (int i = 0; i < sizematrix; i++) {
		if (arrayMatrix[string][i] != 0
			and (i != colum)
			and arrayMatrix[string][i] == checknum)
		{
			return false;
		}
		
		if (arrayMatrix[i][colum] != 0
			and (i != string)
			and arrayMatrix[i][colum] == checknum)
		{
			return false;
		}
	}
	return true;
}

bool checkMiniMatrix(int arrayMatrix[sizematrix][sizematrix], int string, int colum, int numchek) {

	int shiftmatrixstring, shiftmatrixcolum;
	if (string <= 2) {
		shiftmatrixstring = 0;
	}
	else if (string > 2 and string <= 5) {
		shiftmatrixstring = 2;
	}
	else if (string > 5 and string <= 8) {
		shiftmatrixstring = 5;
	}

	if (colum <= 2) {
		shiftmatrixcolum = 0;
	}
	else if (colum > 2 and colum <= 5) {
		shiftmatrixcolum = 2;
	}
	else if (colum > 5 and colum <= 8) {
		shiftmatrixcolum = 5;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((string != i + shiftmatrixstring and colum != j + shiftmatrixcolum)
				and arrayMatrix[i + shiftmatrixstring][j + shiftmatrixcolum] == numchek)
			{
				return false;
			}
		}
	}
	return true;
}

