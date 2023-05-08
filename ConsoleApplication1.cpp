#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void add(int*, int*, int*);
void sub(int*, int*, int*);
void mul(int*, int*, int*);
void AND(int*, int*, int*);
void OR(int*, int*, int*);
void XOR(int*, int*, int*);
void addi(int*, int*, int);
void muli(int*, int*, int);
void ANDI(int*, int*, int);
void ORI(int*, int*, int);
void XORI(int*, int*, int);
/*bool beq(int*, int*);
bool bne(int*, int*);
bool blt(int*, int*);
bool bge(int*, int*);
bool bltu(int*, int*);
bool bgeu(int*, int*);*/
int main() {
	int* x0, * x5, * x6, * x7, * x28, * x29, * x30, * x31, * rd, * rs1, * rs2;
	x0 = new int;
	*x0 = 0;
	x5 = new int;
	*x5 = INT_MIN;
	x6 = new int;
	*x6 = INT_MIN;
	x7 = new int;
	*x7 = INT_MIN;
	x28 = new int;
	*x28 = INT_MIN;
	x29 = new int;
	*x29 = INT_MIN;
	x30 = new int;
	*x30 = INT_MIN;
	x31 = new int;
	*x31 = INT_MIN;
	rd = nullptr;
	rs1 = nullptr;
	rs2 = nullptr;
	string instruction, rdTemp, rs1Temp, rs2Temp, immediate;
	//string label;
	ifstream textFile;
	cout << "Registers before implementing the instructions:\n";
	cout << "x0 = " << *x0 << "\n";
	for (int i = 5; i <= 7; i++)
		cout << "x" << i << " is not yet initialized.\n";
	for (int i = 28; i <= 31; i++)
		cout << "x" << i << " is not yet initialized.\n";
	cout << endl;
	textFile.open("testCase.txt");
	if (textFile.is_open()) {
		while (!textFile.eof()) {
			textFile >> instruction;
			textFile >> rdTemp;
			textFile >> rs1Temp;
			if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "and") || (instruction == "or") || (instruction == "xor"))
				textFile >> rs2Temp;
			else if ((instruction == "addi") || (instruction == "muli") || (instruction == "andi") || (instruction == "ori") || (instruction == "xori"))
				textFile >> immediate;
			/*else if ((instruction == "beq") || (instruction == "bne") || (instruction == "blt") || (instruction == "bge") || (instruction == "bltu") || (instruction == "bgeu"))
				textFile >> label;*/
			if (rdTemp == "x0,") {
				cout << "You can not change the value of the saved register x0.\n";
				return 0;
			}
			else if (rdTemp == "x5,")
				rd = x5;
			else if (rdTemp == "x6,")
				rd = x6;
			else if (rdTemp == "x7,")
				rd = x7;
			else if (rdTemp == "x28,")
				rd = x28;
			else if (rdTemp == "x29,")
				rd = x29;
			else if (rdTemp == "x30,")
				rd = x30;
			else if (rdTemp == "x31,")
				rd = x31;
			if (rs1Temp == "x0,")
				rs1 = x0;
			else if (rs1Temp == "x5,")
				rs1 = x5;
			else if (rs1Temp == "x6,")
				rs1 = x6;
			else if (rs1Temp == "x7,")
				rs1 = x7;
			else if (rs1Temp == "x28,")
				rs1 = x28;
			else if (rs1Temp == "x29,")
				rs1 = x29;
			else if (rs1Temp == "x30,")
				rs1 = x30;
			else if (rs1Temp == "x31,")
				rs1 = x31;
			if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "and") || (instruction == "or") || (instruction == "xor")) {
				if (rs2Temp == "x0")
					rs2 = x0;
				else if (rs2Temp == "x5")
					rs2 = x5;
				else if (rs2Temp == "x6")
					rs2 = x6;
				else if (rs2Temp == "x7")
					rs2 = x7;
				else if (rs2Temp == "x28")
					rs2 = x28;
				else if (rs2Temp == "x29")
					rs2 = x29;
				else if (rs2Temp == "x30")
					rs2 = x30;
				else if (rs2Temp == "x31")
					rs2 = x31;
			}
			if (instruction == "add")
				add(rd, rs1, rs2);
			else if (instruction == "sub")
				sub(rd, rs1, rs2);
			else if (instruction == "mul")
				mul(rd, rs1, rs2);
			else if (instruction == "and")
				AND(rd, rs1, rs2);
			else if (instruction == "or")
				OR(rd, rs1, rs2);
			else if (instruction == "xor")
				XOR(rd, rs1, rs2);
			else if (instruction == "addi")
				addi(rd, rs1, stoi(immediate));
			else if (instruction == "muli")
				muli(rd, rs1, stoi(immediate));
			else if (instruction == "andi")
				ANDI(rd, rs1, stoi(immediate));
			else if (instruction == "ori")
				ORI(rd, rs1, stoi(immediate));
			else if (instruction == "xori")
				XORI(rd, rs1, stoi(immediate));
		}
	}
	else
		cout << "File does not exists\n";
	cout << "Registers after implementing the instructions:\n";
	cout << "x0 = " << *x0 << "\n";
	if (*x5 == INT_MIN)
		cout << "x5 is not yet initialized.\n";
	else
		cout << "x5 = " << *x5 << "\n";
	if (*x6 == INT_MIN)
		cout << "x6 is not yet initialized.\n";
	else
		cout << "x6 = " << *x6 << "\n";
	if (*x7 == INT_MIN)
		cout << "x7 is not yet initialized.\n";
	else
		cout << "x7 = " << *x7 << "\n";
	if (*x28 == INT_MIN)
		cout << "x28 is not yet initialized.\n";
	else
		cout << "x28 = " << *x28 << "\n";
	if (*x29 == INT_MIN)
		cout << "x29 is not yet initialized.\n";
	else
		cout << "x29 = " << *x29 << "\n";
	if (*x30 == INT_MIN)
		cout << "x30 is not yet initialized.\n";
	else
		cout << "x30 = " << *x30 << "\n";
	if (*x31 == INT_MIN)
		cout << "x31 is not yet initialized.\n";
	else
		cout << "x31 = " << *x31 << "\n";
	cout << endl;
	system("pause");
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
void AND(int* x, int* y, int* z) {
	*x = *y & *z;
}
void OR(int* x, int* y, int* z) {
	*x = *y | *z;
}
void XOR(int* x, int* y, int* z) {
	*x = *y ^ *z;
}
void addi(int* x, int* y, int z) {
	*x = *y + z;
}
void muli(int* x, int* y, int z) {
	*x = *y * z;
}
void ANDI(int* x, int* y, int z) {
	*x = *y & z;
}
void ORI(int* x, int* y, int z) {
	*x = *y | z;
}
void XORI(int* x, int* y, int z) {
	*x = *y ^ z;
}
/*bool beq(int* x, int* y) {
	if (*x == *y)
		return true;
	else
		return false;
}
bool bne(int* x, int* y) {
	if (*x != *y)
		return true;
	else
		return false;
}
bool blt(int* x, int* y) {
	if (*x < *y)
		return true;
	else
		return false;
}
bool bge(int* x, int* y) {
	if ((*x > *y) || (*x == *y))
		return true;
	else
		return false;
}
bool bltu(int* x, int* y) {
	if (abs(*x) < abs(*y))
		return true;
	else
		return false;
}
bool bgeu(int* x, int* y) {
	if ((abs(*x) > abs(*y)) || (abs(*x) == abs(*y)))
		return true;
	else
		return false;
}*/