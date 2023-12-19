#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string>

using namespace std;
const int sizematrix = 9; // 9x9

struct immutable
{
	int string;
	int column;
	int value;
	immutable* next;
	immutable* prev;
};

int searchZeroCells(int ingameMatrix[sizematrix][sizematrix]);
string outMatrix(int outputmatrix[sizematrix][sizematrix]);

bool inputIsCorrect(string choice), 
	checkfullMatrix(int matrixcheck[sizematrix][sizematrix]),
	checkingForAnImmutableValue(immutable* head, int chekColumn, int chekString);

void SubstituteTheValue(immutable* head, int ingameMatrix[sizematrix][sizematrix], string choice),
	fillInImmutableValues(immutable* head, int ingameMatrix[sizematrix][sizematrix]);

bool inTheGame(int matrixFull[sizematrix][sizematrix], int ingameMatrix[sizematrix][sizematrix]) {

	//Вывод первой таблицы
	string choice;
	string outsting = outMatrix(ingameMatrix);

	immutable* head = NULL;
	fillInImmutableValues(head, ingameMatrix);

	cout << endl << outsting << endl;


	int SummEmptyCells = searchZeroCells(ingameMatrix);
	do
	{
		cout << "Enter the column, row, and number numbers separated by /. (Example: 3/3/9): ";
		cin >> choice;
		cout << endl;
		
		if (!inputIsCorrect(choice)){
			cout << "Please repeat the input." << endl;
			continue;
		}
		SubstituteTheValue(head, ingameMatrix, choice);
		if (checkfullMatrix(ingameMatrix)) {
			outsting = outMatrix(ingameMatrix);
			cout << endl << outsting << endl;
		}
		SummEmptyCells = searchZeroCells(ingameMatrix);

	} while (SummEmptyCells != 0);

	cout << "well done" << endl;
	return true;

}

string formatTheString(string choice) {
	
	string formatingString;
	char numbers[10] = { '1','2','3','4','5','6','7','8','9','0' };
	char testchar[1];
	for (int i = 0; i < choice.length(); i++)
	{
		testchar[0] = choice[i];
		for (int c = 0; c < 10; c++)
		{
			if (testchar[0] == numbers[c])
			{
				string v(1, testchar[0]);
				formatingString.append(v);

			}
		}

	}
	return formatingString;
}

void SubstituteTheValue(immutable*head, int ingameMatrix[sizematrix][sizematrix], string choice) {
	
	int selectColumn, selectString, selectValue = 0;
	string formatingChoice = formatTheString(choice);

	try {			
			
		char charColumn[1];
		charColumn[0] = formatingChoice[0];
		if (charColumn[0] != '/' and charColumn[0] != ' ')
		{
			selectColumn = atoi(charColumn) - 1;
		}

		char charString[1];
		charString[0] = formatingChoice[1];
		if (charString[0] != '/' and charString[0] != ' ')
		{
			selectString = atoi(charString) - 1;
		}

		char charValue[1];
		charValue[0] = formatingChoice[2];
		if (charValue[0] != '/' and charValue[0] != ' ')
		{
			selectValue = atoi(charValue);
		}

		if (checkingForAnImmutableValue(head, selectColumn, selectString)) {
			ingameMatrix[selectColumn][selectString] = selectValue;
		}

	}
	catch (int errorInt) {
		cout << "Invalid value entered." << endl;
	}

}

void fillInImmutableValues(immutable* head, int ingameMatrix[sizematrix][sizematrix]) {
	
	immutable* newCell, * tail = NULL;
	for (int s = 0; s < sizematrix; s++)
	{
		for (int c = 0; c < sizematrix; c++)
		{
			if (ingameMatrix[s][c] == 0)
				continue;


			newCell = (struct immutable*)malloc(sizeof(struct immutable));
			newCell->next = NULL;
			newCell->prev = NULL;
			newCell->column = c;
			newCell->string = s;
			newCell->value = ingameMatrix[s][c];

			if (head == NULL){

				head = newCell;
				tail = newCell;
			}
			else
			{
				tail->next = newCell;
				newCell->prev = tail;
				tail = newCell;
			}
		}
	}
}

bool inputIsCorrect(string choice) {
	
	char charValue[1];

	if (!choice.empty()) {
		for (int i = 0; i < choice.length(); i++) {
			try {
				if (choice[i] != '/'){
					charValue[0] = choice[i];
					int testValue = atoi(charValue);
					if (testValue > 9 or testValue < 0){
						throw testValue;
					}
				}
			}
			catch (int errorInt){
				cout << "Invalid value entered." << endl;
				return false;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

bool checkingForAnImmutableValue(immutable* head, int checkColumn, int checkString) {

	immutable* cells = head;

	while (cells != NULL)
	{
		if (cells->column == checkColumn and cells->string == checkString)
		{
			return false;
		}
		cells = cells->next;
	}
	return true;
}

int searchZeroCells(int ingameMatrix[sizematrix][sizematrix]) {

	int SummZerocells = 0;
	for (int s = 0; s < sizematrix; s++) {
		for (int c = 0; c < sizematrix; c++) {
	
			if (ingameMatrix[s][c] == 0)
			{
				++SummZerocells;
			}

		}
	}
	return SummZerocells;
}