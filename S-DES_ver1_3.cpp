#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

void creatkey(int k[], int cipher_key[][8]);
void P10(int k[]);
void leftshift(int k[]);
void P8(int k[], int cipher_key[][8], int row);
void IP(int k[], bool mode);
void f(int c[], int k[]);
void F(int r[], int k[]);
void swap(int c[]);
bool isEqual(int a[], int b[]);
void BFA();
void getTime();

//输出明/密文
void prt(int c[8]) {
	for (int i = 0; i < 8; i++)
		cout << c[i] << " ";
	cout << endl;
}

//加密算法
void encipher(int c[], int k[]) {
	//int c[8] = {1, 0, 0, 1, 1, 0, 1, 0}; //明文
	//int k[10] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, cipher_key[2][8]; //密钥
	int cipher_key[2][8];
	creatkey(k, cipher_key); //创建密钥1,2
	IP(c, 0); //初始置换
	//第一次用S-DES函数
	f(c, cipher_key[0]);
	//交换左右
	swap(c);
	//第二次用S-DES函数
	f(c, cipher_key[1]);
	IP(c, 1); //最终置换
}

//解密算法
void decrypt(int p[], int k[]) {
	//int c0[8] = {1, 1, 1, 0, 1, 1, 1, 1}; //密文
	//int k[10] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, cipher_key[2][8]; //密钥
	int cipher_key[2][8];
	creatkey(k, cipher_key); //创建密钥1,2
	IP(p, 0); //初始置换
	//第一次用S-DES函数
	f(p, cipher_key[1]);
	//交换左右
	swap(p);
	//第二次用S-DES函数
	f(p, cipher_key[0]);
	IP(p, 1); //最终置换
}

//二进制S-DES
void num() {
	int cipher[8], key[10], code;
	cout << "请输入8位二进制明/密文:" << endl;
	for (int i = 0; i < 8; i++) {
		cin >> cipher[i];
	}
	cout << "请输入10位二进制密钥:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> key[i];
	}
	cout << "加密请输入0，解密请输入1" << endl;
	cin >> code;
	if (code == 0) {
		encipher(cipher, key);
		cout << "密文：";
		prt(cipher);
	} else {
		decrypt(cipher, key);
		cout << "明文：";
		prt(cipher);
	}
}

//字符串转换成二进制
void changeTOnum(string a, int c[][8]) {//列数不可省略
	for (int i = 0; i < a.size(); i++) {
		int temp = a[i];
		for (int j = 0; j < 8; j++) {
			if (temp == 0) {
				c[i][7 - j] = 0;
			} else {
				c[i][7 - j] = temp % 2;
				temp = temp / 2;
			}
		}
	}
}

//二进制转换成十进制
void changeTOasc(int c[], int &sum) { //列数不可省略
	int temp = 128;
	sum = 0;
	for (int j = 0; j < 8; j++) {
		sum = sum + c[j] * temp;
		temp = temp / 2;
	}
}

//字符串S-DES
void str() {
	string p;//明文
	int key[10], code, c[8]; //c[8]密文
	cout << "请输入10位二进制密钥:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> key[i];
	}
	cout << "加密请输入0，解密请输入1" << endl;
	cin >> code;
	//加密
	if (code == 0) {
		cout << "请输入字符串明文:" << endl;
		cin >> p;
		int cipher[p.size()][8];
		changeTOnum(p, cipher);//转换成二进制
		for (int i = 0; i < p.size(); i++) {
			encipher(cipher[i], key);
			cout << "密文：";
			prt(cipher[i]);
		}
		//解密
	} else {
		for (int i = 0; i < 8; i++) {
			cout << "请输入8位二进制密文:" << endl;
			for (int j = 0; j < 8; j++)
				cin >> c[j];
			decrypt(c, key);
			int temp;
			changeTOasc(c, temp);
			printf("对应字符：%c\n", temp);//输出为字符
		}
	}
}

int main() {
	int choose;
	cout << "数字加/解密请输入0，字符串加/解密请输入1，暴力破解请输入2" << endl;
	cin >> choose;
	if (choose == 0) {
		num();
	} else if (choose == 1) {
		str();
	} else if (choose == 2) {
		BFA();
	}
	return 0;
}

//生成密钥
void creatkey(int k[], int cipher_key[][8]) {
	//直接置换
	P10(k);
	//分左右
	int left_key[5], right_key[5];
	for (int i = 0; i < 5; i++) {
		left_key[i] = k[i];
		right_key[i] = k[i + 5];
	}
	//轮换
	for (int i = 0; i < 2; i++) {
		//左移
		leftshift(left_key);
		leftshift(right_key);

		//拼接左右
		for (int i = 0; i < 5; i++) {
			k[i] = left_key[i];
			k[i + 5] = right_key[i];
		}

		//压缩置换得到ki
		P8(k, cipher_key, i);

	}

}

//生成密钥的第一个P-Box
void P10(int k[]) {
	int p10[] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};
	int  temp_key[10];
	for (int i = 0; i < 10; i++) {
		temp_key[i] = k[p10[i]];
	}
	for (int i = 0; i < 10; i++) {
		k[i] = temp_key[i];
	}
}

//左移
void leftshift(int k[]) {
	int temp[5];
	for (int i = 0; i < 5; i++) {
		temp[i] = k[(i + 1) % 5];
	}
	for (int i = 0; i < 5; i++) {
		k[i] = temp[i];
	}
}

//生成密钥的第二个P-BOX
void P8(int k[], int cipher_key[][8], int row) {
	int p8[8] = {5, 2, 6, 3, 7, 4, 9, 8};
	int  temp_key[8];
	for (int i = 0; i < 8; i++) {
		temp_key[i] = k[p8[i]];
	}
	for (int i = 0; i < 8; i++) {
		cipher_key[row][i] = temp_key[i];
	}
}

//置换
void IP(int k[], bool mode) {
	if (mode == 0) {
		int ip[8] = {1, 5, 2, 0, 3, 7, 4, 6};
		int  temp_key[8];
		for (int i = 0; i < 8; i++) {
			temp_key[i] = k[ip[i]];
		}
		for (int i = 0; i < 8; i++) {
			k[i] = temp_key[i];
		}
	} else {
		int ip[8] = {3, 0, 2, 4, 6, 1, 7, 5};
		int  temp_key[8];
		for (int i = 0; i < 8; i++) {
			temp_key[i] = k[ip[i]];
		}
		for (int i = 0; i < 8; i++) {
			k[i] = temp_key[i];
		}
	}
}

//S-DES函数
void f(int c[], int k[]) {
	//分左右
	int l[4], r[4];
	for (int i = 0; i < 4; i++) {
		l[i] = c[i];
		r[i] = c[i + 4];
	}
	//轮函数F
	F(r, k);
	//左右异或,并且拼接
	for (int i = 0; i < 4; i++) {
		l[i] = l[i] ^ r[i];
		c[i] = l[i];
	}

}

void F(int r[], int k[]) {
	//扩展置换
	//cout << "扩展置换结果：";
	int temp[8];
	int E_P_Box[] = {3, 0, 1, 2, 1, 2, 3, 0};
	for (int i = 0; i < 8; i++) {
		temp[i] = r[E_P_Box[i]];
		//cout << temp[i] << " ";
	}
	//cout << endl;

	//加轮密钥
	//cout << "加轮密钥结果：";
	for (int i = 0; i < 8; i++) {
		temp[i] = temp[i] ^ k[i];
		//cout << temp[i] << " ";
	}
	//cout << endl;

	//替换盒S-Boxes
	int SBox_1[][4] = {
		{1, 0, 3, 2},
		{3, 2, 1, 0},
		{0, 2, 1, 3},
		{3, 1, 0, 2}
	};
	int SBox_2[][4] = {
		{0, 1, 2, 3},
		{2, 3, 1, 0},
		{3, 0, 1, 2},
		{2, 1, 0, 3}
	};
	int row, col; //行列号
	//前四位替换
	row = 2 * temp[0] + 1 * temp[3];
	col = 2 * temp[1] + 1 * temp[2];
	int trans = SBox_1[row][col]; //用于将十进制转化为二进制
	r[0] = trans / 2;
	r[1] = trans % 2;
	//替换后四位
	row = 2 * temp[4] + 1 * temp[7];
	col = 2 * temp[5] + 1 * temp[6];
	trans = SBox_2[row][col];
	//cout << "trans=" << trans << endl;
	r[2] = trans / 2;
	r[3] = trans % 2;
	//cout << "替换盒的结果：";
	//for (int i = 0; i < 4; i++) {
	//	cout << r[i] << " ";
	//}
	//cout << endl;

	//直接置换
	int SPBox[] = {1, 3, 2, 0};
	int t[4];
	for (int i = 0; i < 4; i++)
		t[i] = r[i];
	for (int i = 0; i < 4; i++) {
		r[i] = t[SPBox[i]];
	}
}

void swap(int c[]) {
	int temp[4];
	for (int i = 0; i < 4; i++) {
		temp[i] = c[i];
		c[i] = c[i + 4];
		c[i + 4] = temp[i];
	}

}

//判断两个二进制八位明/密文是否相等
bool isEqual(int a[], int b[]) {
	for (int i = 0; i < 8; i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

//暴力破解
void BFA() {
	int c[8], p[8], key[10], binary[10];
	cout << "请输入八位二进制密文：" << endl;
	for (int i = 0; i < 8; i++) {
		cin >> c[i];
	}
	cout << "请输入八位二进制明文：" << endl;
	for (int i = 0; i < 8; i++) {
		cin >> p[i];
	}
	clock_t start, end;
	start = clock();
	for (int i = 0; i < 1024; i++) {
		int ctemp[8];
		for (int x = 0; x < 8; x++) {
			ctemp[x] = c[x];
		}
		int temp = i;
		for (int j = 0; j < 10; j++) {
			binary[9 - j] = key[9 - j] = temp % 2;
			temp = temp / 2;
		}
		decrypt(ctemp, key);
		if (isEqual(ctemp, p) == true) {
			cout << "该明密文对对应的密钥是：";
			for (int j = 0; j < 10; j++) {
				cout << binary[j];
			}
			cout << endl;
		}
	}
	end = clock();
	// 计算时间
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	cout << "所用时间: " << time_taken << " 秒" << endl;
}













