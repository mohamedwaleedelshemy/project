#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void print(int*, int, bool);
void li(int*, int);
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
void LUI(int*, int);
void AUIPC(int*, int, int);
void slt(int*, int*, int*);
void slti(int*, int*, int);
void sra(int*, int*, int*);
void srai(int*, int*, int);
void srl(int*, int*, int*);
void srli(int*, int*, int);
void sll(int*, int*, int*);
void slli(int*, int*, int);
void sltu(int*, int*, int*);
void sltiu(int*, int*, int);


/*bool beq(int*, int*);
bool bne(int*, int*);
bool blt(int*, int*);
bool bge(int*, int*);
bool bltu(int*, int*);
bool bgeu(int*, int*);*/

int main() {
	int pc = 0;
	int* x0, * x5, * x6, * x7, * x28, * x29, * x30, * x31, * rd, * rs1, * rs2;

	bool x0Flag = false, x5Flag = false, x6Flag = false, x7Flag = false, x28Flag = false, x29Flag = false, x30Flag = false, x31Flag = false;

	x0 = new int;
	*x0 = 0;
	x0Flag = true;

	x5 = new int;
	x6 = new int;
	x7 = new int;
	x28 = new int;
	x29 = new int;
	x30 = new int;
	x31 = new int;

	rd = nullptr;
	rs1 = nullptr;
	rs2 = nullptr;

	string instruction, rdTemp, rs1Temp, rs2Temp, immediate;

	//string label;
	ifstream textFile;

	cout << "Registers before implementing the instructions:\n";
	print(x0, 0, x0Flag);
	print(x5, 5, x5Flag);
	print(x6, 6, x6Flag);
	print(x7, 7, x7Flag);
	print(x28, 28, x28Flag);
	print(x29, 29, x29Flag);
	print(x30, 30, x30Flag);
	print(x31, 31, x31Flag);
	cout << endl;

	textFile.open("testCase.txt");
	if (textFile.is_open()) {
		while (!textFile.eof()) {

			textFile >> instruction;
			textFile >> rdTemp;
			textFile >> rs1Temp;

			if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "and") || (instruction == "or") || (instruction == "xor") || (instruction == "slt") || (instruction == "sra") || (instruction == "srl") || (instruction == "sll") || (instruction == "sltu"))
				textFile >> rs2Temp;

			else if ((instruction == "addi") || (instruction == "muli") || (instruction == "andi") || (instruction == "ori") || (instruction == "xori") || (instruction == "slti") || (instruction == "srai") || (instruction == "srli") || (instruction == "slli") || (instruction == "sltiu"))
				textFile >> immediate;

			/*else if ((instruction == "beq") || (instruction == "bne") || (instruction == "blt") || (instruction == "bge") || (instruction == "bltu") || (instruction == "bgeu"))
				textFile >> label;*/

				// assigning the destination register
			if (rdTemp == "x0,") {
				cout << "You can not change the value of the saved register x0.\n";
				return 0;
			}
			else if (rdTemp == "x5,") {
				rd = x5;
				x5Flag = true;
			}
			else if (rdTemp == "x6,") {
				rd = x6;
				x6Flag = true;
			}
			else if (rdTemp == "x7,") {
				rd = x7;
				x7Flag = true;
			}
			else if (rdTemp == "x28,") {
				rd = x28;
				x28Flag = true;
			}
			else if (rdTemp == "x29,") {
				rd = x29;
				x29Flag = true;
			}
			else if (rdTemp == "x30,") {
				rd = x30;
				x30Flag = true;
			}
			else if (rdTemp == "x31,") {
				rd = x31;
				x31Flag = true;
			}

			// assigning the first source register
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

			// assigning the second source register if needed
			if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "and") || (instruction == "or") || (instruction == "xor") || (instruction == "slt") || (instruction == "sra") || (instruction == "srl") || (instruction == "sll") || (instruction == "sltu")) {

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
			else if (instruction == "lui")
				LUI(rd, stoi(rs1Temp));
			else if (instruction == "auipc")
				AUIPC(rd, stoi(rs1Temp), pc);
			else if (instruction == "slt")
				slt(rd, rs1, rs2);
			else if (instruction == "slti")
				slti(rd, rs1, stoi(immediate));
			else if (instruction == "li")
				li(rd, stoi(rs1Temp));
			else if (instruction == "sra")
				sra(rd, rs1, rs2);
			else if (instruction == "srai")
				srai(rd, rs1, stoi(immediate));
			else if (instruction == "srl")
				srl(rd, rs1, rs2);
			else if (instruction == "srli")
				srli(rd, rs1, stoi(immediate));
			else if (instruction == "sll")
				sll(rd, rs1, rs2);
			else if (instruction == "slli")
				slli(rd, rs1, stoi(immediate));
			else if (instruction == "sltu")
				sltu(rd, rs1, rs2);
			else if (instruction == "sltiu")
				sltiu(rd, rs1, stoi(immediate));

			pc++;
		}
	}
	else
		cout << "File does not exists\n";

	cout << "Registers after implementing the instructions:\n";
	print(x0, 0, x0Flag);
	print(x5, 5, x5Flag);
	print(x6, 6, x6Flag);
	print(x7, 7, x7Flag);
	print(x28, 28, x28Flag);
	print(x29, 29, x29Flag);
	print(x30, 30, x30Flag);
	print(x31, 31, x31Flag);
	cout << endl;

	system("pause");
	return 0;
}
void print(int* x, int y, bool f) {
	if (f == false)
		cout << "x" << y << " is not yet initialized.\n";

	else {
		cout << "x" << y << " =\n" << "Decimal: " << *x << "\n";

		if (*x == 0)
			cout << "Binary: 0\n";

		else {
			int decimal = *x, binary = 0, remainder, product = 1;
			while (decimal != 0) {
				remainder = decimal % 2;
				binary = binary + (remainder * product);
				decimal = decimal / 2;
				product *= 10;
			}
			cout << "Binary: " << binary << "\n";
		}

		if (*x == 0)
			cout << "Hexadecimal: 0\n";

		else {
			string hexadecimal = "";
			int n = *x;
			while (n != 0) {
				int r = 0;
				char c;
				r = n % 16;
				if (r < 10)
					c = r + 48;
				else
					c = r + 55;
				hexadecimal += c;
				n = n / 16;
			}
			int i = 0, j = hexadecimal.size() - 1;
			while (i <= j)
			{
				swap(hexadecimal[i], hexadecimal[j]);
				i++;
				j--;
			}
			cout << "Hexadecimal: " << hexadecimal << "\n";
		}
	}
}
void li(int* x, int y)
{
	*x = y;
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
void LUI(int* x, int y) {
	*x = y << 12;
}
void AUIPC(int* x, int y, int z) {
	*x = z + (y << 12);
}
void slt(int* x, int* y, int* z)
{
	if (*y < *z)
		*x = 1;
	else
		*x = 0;
}
void slti(int* x, int* y, int z)
{
	if (*y < z)
		*x = 1;
	else
		*x = 0;
}
void sra(int* x, int* y, int* z)
{
	int temp = *z & 0b11111;
	*x = *y >> temp;
}
void srai(int* x, int* y, int z)
{
	int temp = z & 0b11111;
	*x = *y >> temp;
}
void srl(int* x, int* y, int* z)
{
	int temp = *z & 0b11111;
	*x = static_cast<uint32_t>(*y) >> temp;
	cout << "in srl x = " << *x << endl;
}
void srli(int* x, int* y, int z)
{
	int temp = z & 0b11111;
	*x = static_cast<uint32_t>(*y) >> temp;
}
void sll(int* x, int* y, int* z)
{
	int temp = *z & 0b11111;
	*x = *y << temp;
}

void slli(int* x, int* y, int z)
{
	int temp = z & 0b11111;
	*x = *y << temp;
}
void sltu(int* x, int* y, int* z)
{
	uint32_t unsigned_y = static_cast<uint32_t>(*y);
	uint32_t unsigned_z = static_cast<uint32_t>(*z);

	if (unsigned_y < unsigned_z)
	{
		*x = 1;
	}
	else
	{
		*x = 0;
	}
}
void sltiu(int* x, int* y, int z)
{
	uint32_t unsigned_y = static_cast<uint32_t>(*y);
	uint32_t unsigned_z = static_cast<uint32_t>(z);

	if (unsigned_y < unsigned_z)
	{
		*x = 1;
	}
	else
	{
		*x = 0;
	}
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