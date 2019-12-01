#pragma once
#include "Comb.h"

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#define incre 10

class ComSet {
public:
	Comb* element;//����Ԫ�ؼ���϶�
	int count;//����Ԫ�ظ���
	int max;//���ϵ�ǰ�������

	ComSet();
	ComSet(int initSize);

	~ComSet();
	

	bool contain(Comb e); //�жϼ������Ƿ����Ԫ��e
	bool add(Comb e); //�����������Ԫ��e
	ComSet Intersection(ComSet cset);
	int IntersectionNum(ComSet cset);
	ComSet Union(ComSet cset);
	void print();
	ComSet SubSet(ComSet cset);
	int getCount();

};