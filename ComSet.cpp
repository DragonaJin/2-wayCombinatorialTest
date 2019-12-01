#include "ComSet.h"



ComSet::ComSet():max(10), count(0)
{
	element = (Comb*)malloc(max * sizeof(Comb)); 
	
	if (!element) throw "分配空间失败";
}

ComSet::ComSet(int initSize):max(initSize),count(0)
{ 
	element = (Comb*)malloc(max * sizeof(Comb));
	
	if (!element) throw "分配空间失败";

}

ComSet::~ComSet()
{
	//free(element);
}

bool ComSet::contain(Comb e)
{
	for (int i = 0; i < count;i++) {
		if (element[i].combEqual(e)) return true;
	}
	return false;
}

bool ComSet::add(Comb e)
{
	if (count == max) {
		printf("集合已满，需要扩充容量");
		int newMax = max + incre;
		Comb* temp = (Comb*)malloc((newMax) * sizeof(Comb));//扩充增量incre
		if (!temp) return false;
		max += incre;
		memcpy(temp, element, count*sizeof(Comb));
		free(element);
		element = temp;
		
	}
	if (!contain(e)) element[count++] = e;//添加元素的具体过程有待商榷 
	return true;
}

ComSet ComSet::Intersection(ComSet cset) {
	ComSet tempSet(cset.count);
	for (int i = 0; i < count; i++) {

			if (cset.contain(element[i])) {
				tempSet.add(element[i]);
			}
		
	}
	return tempSet;
}
int ComSet::IntersectionNum(ComSet cset) {
	ComSet tempSet(cset.count);
	for (int i = 0; i < count; i++) {

		if (cset.contain(element[i])) {
			tempSet.add(element[i]);
		}

	}
	int number = tempSet.count;
	free(tempSet.element);

	return number;
}


ComSet ComSet::Union(ComSet cset) {
	ComSet tempSet(count+cset.count);
	//memcpy(tempSet.element, element, count*sizeof(Comb));
	for (int i = 0; i < count; i++) {
			tempSet.add(element[i]);
		
	}
	for (int i = 0; i < cset.count; i++) {
			tempSet.add(cset.element[i]);
	
	}
	return tempSet;
}

void ComSet::print()
{
	printf("{");
	for (int i = 0; i < count; i++) {
		printf("(%d, %d, %d),", element[i].x, element[i].y, element[i].z);
	}
	printf("}");
}

ComSet ComSet::SubSet(ComSet cset)
{
	ComSet tempSet(count);
	
	for (int i = 0; i < count; i++) {
		
		if (!cset.contain(element[i]))
			tempSet.add(element[i]);
	}
	
	return tempSet;
}
int ComSet::getCount() {
	return count;
}