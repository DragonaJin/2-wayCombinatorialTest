#pragma once
class Comb {
	/**
	组合对数据类型，一个组合对作为comSet的一个元素
	例如，（p1，q1）就是一个两组合对；（p1，r1，s2）是一个三组合对
	*/
	
public:
	int x, y, z;
	//Comb();
	Comb(int a, int b); //两组合对构造函数
	Comb(int a, int b, int c); //三组合对构造函数
	~Comb(); //析构函数
	bool combEqual(Comb e);
};