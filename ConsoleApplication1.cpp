#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void add(int*, int*, int*);
void sub(int*, int*, int*);
void mul(int*, int*, int*);
void addi(int*, int*, int);
void muli(int*, int*, int);
int main() {
	int* x0, * x5, * x6, * x7, * rd, * rs1, * rs2;
	x0 = new int;
	*x0 = 0;
	x5 = new int;
	*x5 = INT_MIN;
	x6 = new int;
	*x6 = INT_MIN;
	x7 = new int;
	*x7 = INT_MIN;
	rd = nullptr;
	rs1 = nullptr;
	rs2 = nullptr;
	string instruction, rdTemp, rs1Temp, rs2Temp, immediate;
	ifstream textFile;
	cout << "Registers before implementing the instructions:\n";
	cout << "x0 = " << *x0 << "\n";
	if (*x5 == INT_MIN)
		cout << "x5 is not yet initialized\n";
	else
		cout << "x5 = " << *x5 << "\n";
	if (*x6 == INT_MIN)
		cout << "x6 is not yet initialized\n";
	else
		cout << "x6 = " << *x6 << "\n";
	if (*x7 == INT_MIN)
		cout << "x7 is not yet initialized\n";
	else
		cout << "x7 = " << *x7 << "\n";
	cout << "\n";
	textFile.open("testCase.txt");
	if (textFile.is_open()) {
		while (!textFile.eof()) {
			textFile >> instruction;
			textFile >> rdTemp;
			textFile >> rs1Temp;
			if ((instruction == "addi") || (instruction == "muli"))
				textFile >> immediate;
			else if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "muli"))
				textFile >> rs2Temp;
			if (rdTemp == "x5,")
				rd = x5;
			else if (rdTemp == "x6,")
				rd = x6;
			else if (rdTemp == "x7,")
				rd = x7;
			if (rs1Temp == "x0,")
				rs1 = x0;
			else if (rs1Temp == "x5,")
				rs1 = x5;
			else if (rs1Temp == "x6,")
				rs1 = x6;
			else if (rs1Temp == "x7,")
				rs1 = x7;
			if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "muli")) {
				if (rs2Temp == "x0")
					rs2 = x0;
				else if (rs2Temp == "x5")
					rs2 = x5;
				else if (rs2Temp == "x6")
					rs2 = x6;
				else if (rs2Temp == "x7")
					rs2 = x7;
			}
			if (instruction == "addi")
				addi(rd, rs1, stoi(immediate));
			else if (instruction == "muli")
				muli(rd, rs1, stoi(immediate));
			else if (instruction == "add")
				add(rd, rs1, rs2);
			else if (instruction == "sub")
				sub(rd, rs1, rs2);
			else if (instruction == "mul")
				mul(rd, rs1, rs2);
		}
		cout << "Registers after implementing the instructions:\n";
		cout << "x0 = " << *x0 << "\n";
		if (*x5 == INT_MIN)
			cout << "x5 is not yet initialized\n";
		else
			cout << "x5 = " << *x5 << "\n";
		if (*x6 == INT_MIN)
			cout << "x6 is not yet initialized\n";
		else
			cout << "x6 = " << *x6 << "\n";
		if (*x7 == INT_MIN)
			cout << "x7 is not yet initialized\n";
		else
			cout << "x7 = " << *x7 << "\n";
	}
	else
		cout << "File does not exists\n";
	return 0;
}
void add(int* x, int* y, int* z) {
	*x = *y + *z;
}
void sub(int* x, int* y, int* z) {
	*x = *y - *z;
}
void mul(int* x, int* y, int* z) {
	*x = *y * *z;
}
void addi(int* x, int* y, int z) {
	*x = *y + z;
}
void muli(int* x, int* y, int z) {
	*x = *y * z;
}