#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string>

using namespace std;

const int sizematrix = 9; // 9x9
const int sizematrixcell = 3; //3x3

// Вывод матрицы в консоль
string outMatrix(int outputmatrix[sizematrix][sizematrix]) {

	string outSting;
	outSting.append("  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
	outSting.append("--|-----------+-----------+-----------|\n");
	for (int s = 0; s < sizematrix; s++) {

		for (int c = 0; c < sizematrix; c++) {
			if (c == 0) {
				outSting.append(to_string(s + 1));
				outSting.append(" | ");
			}

			if (outputmatrix[s][c] != 0) {
				outSting.append(to_string(outputmatrix[s][c]));
				outSting.append(" | ");
			}
			else {
				outSting.append(" ");
				outSting.append(" | ");
			}
		}
		outSting.append("\n");
		if (s == 2 || s == 5)
			outSting.append("  |-----------+-----------+-----------|\n");
	}
	outSting.append("  |-----------+-----------+-----------|\n");
	return outSting;
}
