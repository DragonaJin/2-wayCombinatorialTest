#pragma once
class Comb {
	/**
	��϶��������ͣ�һ����϶���ΪcomSet��һ��Ԫ��
	���磬��p1��q1������һ������϶ԣ���p1��r1��s2����һ������϶�
	*/
	
public:
	int x, y, z;
	//Comb();
	Comb(int a, int b); //����϶Թ��캯��
	Comb(int a, int b, int c); //����϶Թ��캯��
	~Comb(); //��������
	bool combEqual(Comb e);
};