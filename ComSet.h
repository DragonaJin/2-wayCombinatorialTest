#pragma once
#include "Comb.h"

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#define incre 10

class ComSet {
public:
	Comb* element;//集合元素即组合对
	int count;//集合元素个数
	int max;//集合当前最大容量

	ComSet();
	ComSet(int initSize);

	~ComSet();
	

	bool contain(Comb e); //判断集合中是否包含元素e
	bool add(Comb e); //往集合中添加元素e
	ComSet Intersection(ComSet cset);
	int IntersectionNum(ComSet cset);
	ComSet Union(ComSet cset);
	void print();
	ComSet SubSet(ComSet cset);
	int getCount();

};