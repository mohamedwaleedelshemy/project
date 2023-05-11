#include <iostream>
#include <fstream>
#include <string>
#include<bitset>

using namespace std;

void get_offset(string&, int&);

void print(int*, int, bool);

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

bool beq(int*, int*);
bool bne(int*, int*);
bool blt(int*, int*);
bool bge(int*, int*);
bool bltu(int*, int*);
bool bgeu(int*, int*);

void li(int*, int);

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

void lw(int*, int*, int);
void lh(int*, int*, int);
void lb(int*, int*, int);

void lhu(int*, int*, int);
void lbu(int*, int*, int);

void sw(int*, int*, int);
void sh(int*, int*, int);
void sb(int*, int*, int);

int main() {

	int pc = 0, offset = 0, memory[1024] = { 0 };

	int* x0, * x5, * x6, * x7, * x28, * x29, * x30, * x31, * rd, * rs1, * rs2, * m = &memory[0];

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

	string instruction, rdTemp, rs1Temp, rs2Temp, immediate, label, temp;

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

			textFile >> temp;

			if ((temp == "add") || (temp == "sub") || (temp == "mul") || (temp == "and") || (temp == "or") || (temp == "xor") || (temp == "addi") || (temp == "muli") || (temp == "andi") || (temp == "ori") || (temp == "xori") || (temp == "beq") || (temp == "bne") || (temp == "blt") || (temp == "bge") || (temp == "bltu") || (temp == "bgeu") || (temp == "li") || (temp == "lui") || (temp == "auipc") || (temp == "slt") || (temp == "slti") || (temp == "sra") || (temp == "srai") || (temp == "srl") || (temp == "srli") || (temp == "sll") || (temp == "slli") || (temp == "sltu") || (temp == "sltui") || (temp == "lw") || (temp == "lh") || (temp == "lb") || (temp == "lhu") || (temp == "lbu") || (temp == "sw") || (temp == "sh") || (temp == "sb"))
				instruction = temp;
			else
				textFile >> instruction;

			textFile >> rdTemp;
			textFile >> rs1Temp;

			if ((instruction == "add") || (instruction == "sub") || (instruction == "mul") || (instruction == "and") || (instruction == "or") || (instruction == "xor") || (instruction == "slt") || (instruction == "sra") || (instruction == "srl") || (instruction == "sll") || (instruction == "sltu"))
				textFile >> rs2Temp;

			else if ((instruction == "addi") || (instruction == "muli") || (instruction == "andi") || (instruction == "ori") || (instruction == "xori") || (instruction == "slti") || (instruction == "srai") || (instruction == "srli") || (instruction == "slli") || (instruction == "sltiu"))
				textFile >> immediate;

			else if ((instruction == "beq") || (instruction == "bne") || (instruction == "blt") || (instruction == "bge") || (instruction == "bltu") || (instruction == "bgeu"))
				textFile >> label;

			if ((rdTemp == "x0,") && (instruction != "beq") && (instruction != "bne") && (instruction != "blt") && (instruction != "bge") && (instruction != "bltu") && (instruction != "bgeu")) {
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

			if ((instruction == "lw") || (instruction == "lh") || (instruction == "lb") || (instruction == "sw") || (instruction == "sh") || (instruction == "sb") || (instruction == "lhu") || (instruction == "lbu")) {
				get_offset(rs1Temp, offset);
				if (rs1Temp == "x0")
					rs1 = x0;
				else if (rs1Temp == "x5")
					rs1 = x5;
				else if (rs1Temp == "x6")
					rs1 = x6;
				else if (rs1Temp == "x7")
					rs1 = x7;
				else if (rs1Temp == "x28")
					rs1 = x28;
				else if (rs1Temp == "x29")
					rs1 = x29;
				else if (rs1Temp == "x30")
					rs1 = x30;
				else if (rs1Temp == "x31")
					rs1 = x31;
				else if (rs1Temp == "m")
					rs1 = m;
			}

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
			else if (rs1Temp == "m,")
				rs1 = m;

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
				else if (rs2Temp == "m")
					rs2 = m;
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
			else if (instruction == "beq") {
				if (beq(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string beqTemporary;
					while (beqTemporary != (label + ":"))
						textFile >> beqTemporary;
				}
			}
			else if (instruction == "bne") {
				if (bne(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string bneTemporary;
					while (bneTemporary != (label + ":"))
						textFile >> bneTemporary;
				}
			}
			else if (instruction == "blt") {
				if (blt(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string bltTemporary;
					while (bltTemporary != (label + ":"))
						textFile >> bltTemporary;
				}
			}
			else if (instruction == "bge") {
				if (bge(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string bgeTemporary;
					while (bgeTemporary != (label + ":"))
						textFile >> bgeTemporary;
				}
			}
			else if (instruction == "bltu") {
				if (bltu(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string bltuTemporary;
					while (bltuTemporary != (label + ":"))
						textFile >> bltuTemporary;
				}
			}
			else if (instruction == "bgeu") {
				if (bgeu(rd, rs1) == true) {
					textFile.clear();
					textFile.seekg(0);
					string bgeuTemporary;
					while (bgeuTemporary != (label + ":"))
						textFile >> bgeuTemporary;
				}
			}
			else if (instruction == "li")
				li(rd, stoi(rs1Temp));
			else if (instruction == "lui")
				LUI(rd, stoi(rs1Temp));
			else if (instruction == "auipc")
				AUIPC(rd, stoi(rs1Temp), pc);
			else if (instruction == "slt")
				slt(rd, rs1, rs2);
			else if (instruction == "slti")
				slti(rd, rs1, stoi(immediate));
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
			else if (instruction == "lw")
				lw(rd, rs1, offset);
			else if (instruction == "lh")
				lh(rd, rs1, offset);
			else if (instruction == "lb")
				lb(rd, rs1, offset);
			else if (instruction == "lhu")
				lhu(rd, rs1, offset);
			else if (instruction == "lbu")
				lbu(rd, rs1, offset);
			else if (instruction == "sw")
				sw(rs1, rd, offset);
			else if (instruction == "sh")
				sh(rs1, rd, offset);
			else if (instruction == "sb")
				sb(rs1, rd, offset);

			if ((instruction != "ecall") && (instruction != "ebreak") && (instruction != "fence"))
				pc++;
			else
				break;
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
void get_offset(string& rs1Temp, int& offset) {
	int imm_start = rs1Temp.find("(");
	int imm_end = rs1Temp.find(")");
	offset = stoi(rs1Temp.substr(0, imm_start));
	rs1Temp = rs1Temp.substr(imm_start + 1, imm_end - imm_start - 1);
}
void print(int* x, int y, bool f) {
	if (f == false)
		cout << "x" << y << " is not yet initialized.\n";
	else {
		cout << "x" << y << " =\n" << "Decimal: " << *x << "\n";
		bitset<32> binary(*x);
		cout << "Binary: " << binary << "\n";

		cout << "Hexadecimal: ";
		cout << hex << *x << dec << "\n";
	}
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

bool beq(int* x, int* y) {
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
}
void li(int* x, int y)
{
	*x = y;
}
void LUI(int* x, int y) {
	*x = y << 12;
}
void AUIPC(int* x, int y, int z) {
	*x = z + (y << 12);
}
void slt(int* x, int* y, int* z) {
	if (*y < *z)
		*x = 1;
	else
		*x = 0;
}
void slti(int* x, int* y, int z) {
	if (*y < z)
		*x = 1;
	else
		*x = 0;
}
void sra(int* x, int* y, int* z) {
	int temp = *z & 0b11111;
	*x = *y >> temp;
}
void srai(int* x, int* y, int z) {
	int temp = z & 0b11111;
	*x = *y >> temp;
}
void srl(int* x, int* y, int* z) {
	int temp = *z & 0b11111;
	*x = static_cast<uint32_t>(*y) >> temp;
	cout << "in srl x = " << *x << endl;
}
void srli(int* x, int* y, int z) {
	int temp = z & 0b11111;
	*x = static_cast<uint32_t>(*y) >> temp;
}
void sll(int* x, int* y, int* z) {
	int temp = *z & 0b11111;
	*x = *y << temp;
}
void slli(int* x, int* y, int z) {
	int temp = z & 0b11111;
	*x = *y << temp;
}
void sltu(int* x, int* y, int* z) {
	uint32_t unsigned_y = static_cast<uint32_t>(*y);
	uint32_t unsigned_z = static_cast<uint32_t>(*z);

	if (unsigned_y < unsigned_z) {
		*x = 1;
	}
	else {
		*x = 0;
	}
}
void sltiu(int* x, int* y, int z) {
	uint32_t unsigned_y = static_cast<uint32_t>(*y);
	uint32_t unsigned_z = static_cast<uint32_t>(z);

	if (unsigned_y < unsigned_z) {
		*x = 1;
	}
	else {
		*x = 0;
	}
}
void lw(int* rd, int* rs1, int offset) {
	if (offset % 4 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	int value = *(rs1 + (offset / 4));
	*rd = value;
}
void lh(int* rd, int* rs1, int offset) {
	if (offset % 2 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	int byteIndex = offset % 4;
	int wordIndex = offset / 4;
	int16_t half = *(rs1 + wordIndex) & 0xFFFF;
	*rd = static_cast<int32_t>(half);
}
void lb(int* rd, int* rs1, int offset) {
	int byteIndex = offset % 4;
	int wordIndex = offset / 4;
	int8_t byte = *(rs1 + wordIndex) & 0xFF;
	*rd = static_cast<int32_t>(byte);
}
void lhu(int* rd, int* rs1, int offset) {
	if (offset % 2 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	int byteIndex = offset % 4;
	int wordIndex = offset / 4;
	uint16_t half = *(rs1 + wordIndex) & 0xFFFF;
	*rd = static_cast<uint32_t>(half);
}
void lbu(int* rd, int* rs1, int offset) {
	int byteIndex = offset % 4;
	int wordIndex = offset / 4;
	uint8_t byte = *(rs1 + wordIndex) & 0xFF;
	*rd = static_cast<uint32_t>(byte);
}
void sw(int* rs1, int* rd, int offset) {
	if (offset % 4 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	*(rs1 + (offset / 4)) = *rd;
}
void sh(int* rs1, int* rd, int offset) {
	if (offset % 2 != 0) {
		cout << "Error: offset not valid\n";
		return;
	}
	int byteIndex = offset % 4;
	int wordIndex = offset / 4;
	int16_t half = *rd & 0xFFFF;
	char* bytePtr = (char*)(rs1 + wordIndex);
	bytePtr[byteIndex] = half & 0xFF;
	bytePtr[byteIndex + 1] = (half >> 8) & 0xFF;
}
void sb(int* rs1, int* rd, int offset) {
	int byteIndex = offset % 4;
	int wordIndex = offset / 4;
	int8_t byte = *rd & 0xFF;
	char* bytePtr = (char*)(rs1 + wordIndex);
	bytePtr[byteIndex] = byte;
}