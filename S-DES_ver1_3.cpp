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

//�����/����
void prt(int c[8]) {
	for (int i = 0; i < 8; i++)
		cout << c[i] << " ";
	cout << endl;
}

//�����㷨
void encipher(int c[], int k[]) {
	//int c[8] = {1, 0, 0, 1, 1, 0, 1, 0}; //����
	//int k[10] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, cipher_key[2][8]; //��Կ
	int cipher_key[2][8];
	creatkey(k, cipher_key); //������Կ1,2
	IP(c, 0); //��ʼ�û�
	//��һ����S-DES����
	f(c, cipher_key[0]);
	//��������
	swap(c);
	//�ڶ�����S-DES����
	f(c, cipher_key[1]);
	IP(c, 1); //�����û�
}

//�����㷨
void decrypt(int p[], int k[]) {
	//int c0[8] = {1, 1, 1, 0, 1, 1, 1, 1}; //����
	//int k[10] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, cipher_key[2][8]; //��Կ
	int cipher_key[2][8];
	creatkey(k, cipher_key); //������Կ1,2
	IP(p, 0); //��ʼ�û�
	//��һ����S-DES����
	f(p, cipher_key[1]);
	//��������
	swap(p);
	//�ڶ�����S-DES����
	f(p, cipher_key[0]);
	IP(p, 1); //�����û�
}

//������S-DES
void num() {
	int cipher[8], key[10], code;
	cout << "������8λ��������/����:" << endl;
	for (int i = 0; i < 8; i++) {
		cin >> cipher[i];
	}
	cout << "������10λ��������Կ:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> key[i];
	}
	cout << "����������0������������1" << endl;
	cin >> code;
	if (code == 0) {
		encipher(cipher, key);
		cout << "���ģ�";
		prt(cipher);
	} else {
		decrypt(cipher, key);
		cout << "���ģ�";
		prt(cipher);
	}
}

//�ַ���ת���ɶ�����
void changeTOnum(string a, int c[][8]) {//��������ʡ��
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

//������ת����ʮ����
void changeTOasc(int c[], int &sum) { //��������ʡ��
	int temp = 128;
	sum = 0;
	for (int j = 0; j < 8; j++) {
		sum = sum + c[j] * temp;
		temp = temp / 2;
	}
}

//�ַ���S-DES
void str() {
	string p;//����
	int key[10], code, c[8]; //c[8]����
	cout << "������10λ��������Կ:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> key[i];
	}
	cout << "����������0������������1" << endl;
	cin >> code;
	//����
	if (code == 0) {
		cout << "�������ַ�������:" << endl;
		cin >> p;
		int cipher[p.size()][8];
		changeTOnum(p, cipher);//ת���ɶ�����
		for (int i = 0; i < p.size(); i++) {
			encipher(cipher[i], key);
			cout << "���ģ�";
			prt(cipher[i]);
		}
		//����
	} else {
		for (int i = 0; i < 8; i++) {
			cout << "������8λ����������:" << endl;
			for (int j = 0; j < 8; j++)
				cin >> c[j];
			decrypt(c, key);
			int temp;
			changeTOasc(c, temp);
			printf("��Ӧ�ַ���%c\n", temp);//���Ϊ�ַ�
		}
	}
}

int main() {
	int choose;
	cout << "���ּ�/����������0���ַ�����/����������1�������ƽ�������2" << endl;
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

//������Կ
void creatkey(int k[], int cipher_key[][8]) {
	//ֱ���û�
	P10(k);
	//������
	int left_key[5], right_key[5];
	for (int i = 0; i < 5; i++) {
		left_key[i] = k[i];
		right_key[i] = k[i + 5];
	}
	//�ֻ�
	for (int i = 0; i < 2; i++) {
		//����
		leftshift(left_key);
		leftshift(right_key);

		//ƴ������
		for (int i = 0; i < 5; i++) {
			k[i] = left_key[i];
			k[i + 5] = right_key[i];
		}

		//ѹ���û��õ�ki
		P8(k, cipher_key, i);

	}

}

//������Կ�ĵ�һ��P-Box
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

//����
void leftshift(int k[]) {
	int temp[5];
	for (int i = 0; i < 5; i++) {
		temp[i] = k[(i + 1) % 5];
	}
	for (int i = 0; i < 5; i++) {
		k[i] = temp[i];
	}
}

//������Կ�ĵڶ���P-BOX
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

//�û�
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

//S-DES����
void f(int c[], int k[]) {
	//������
	int l[4], r[4];
	for (int i = 0; i < 4; i++) {
		l[i] = c[i];
		r[i] = c[i + 4];
	}
	//�ֺ���F
	F(r, k);
	//�������,����ƴ��
	for (int i = 0; i < 4; i++) {
		l[i] = l[i] ^ r[i];
		c[i] = l[i];
	}

}

void F(int r[], int k[]) {
	//��չ�û�
	//cout << "��չ�û������";
	int temp[8];
	int E_P_Box[] = {3, 0, 1, 2, 1, 2, 3, 0};
	for (int i = 0; i < 8; i++) {
		temp[i] = r[E_P_Box[i]];
		//cout << temp[i] << " ";
	}
	//cout << endl;

	//������Կ
	//cout << "������Կ�����";
	for (int i = 0; i < 8; i++) {
		temp[i] = temp[i] ^ k[i];
		//cout << temp[i] << " ";
	}
	//cout << endl;

	//�滻��S-Boxes
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
	int row, col; //���к�
	//ǰ��λ�滻
	row = 2 * temp[0] + 1 * temp[3];
	col = 2 * temp[1] + 1 * temp[2];
	int trans = SBox_1[row][col]; //���ڽ�ʮ����ת��Ϊ������
	r[0] = trans / 2;
	r[1] = trans % 2;
	//�滻����λ
	row = 2 * temp[4] + 1 * temp[7];
	col = 2 * temp[5] + 1 * temp[6];
	trans = SBox_2[row][col];
	//cout << "trans=" << trans << endl;
	r[2] = trans / 2;
	r[3] = trans % 2;
	//cout << "�滻�еĽ����";
	//for (int i = 0; i < 4; i++) {
	//	cout << r[i] << " ";
	//}
	//cout << endl;

	//ֱ���û�
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

//�ж����������ư�λ��/�����Ƿ����
bool isEqual(int a[], int b[]) {
	for (int i = 0; i < 8; i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

//�����ƽ�
void BFA() {
	int c[8], p[8], key[10], binary[10];
	cout << "�������λ���������ģ�" << endl;
	for (int i = 0; i < 8; i++) {
		cin >> c[i];
	}
	cout << "�������λ���������ģ�" << endl;
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
			cout << "�������ĶԶ�Ӧ����Կ�ǣ�";
			for (int j = 0; j < 10; j++) {
				cout << binary[j];
			}
			cout << endl;
		}
	}
	end = clock();
	// ����ʱ��
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	cout << "����ʱ��: " << time_taken << " ��" << endl;
}













