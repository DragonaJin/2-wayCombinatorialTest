// setUnion.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include "Comb.h"
#include "ComSet.h"
#include "setUnion.h"
#include <crtdbg.h>
#include <time.h>
using namespace std;


int main()
{
	//_CrtSetBreakAlloc(78);
	printf("请输入系统参数个数:\n");
	scanf_s("%d", &n);
	printf("请输入其中关键参数个数:\n");
	scanf_s("%d", &core);

	int* P = (int*)malloc(n*sizeof(int));//存储参数取值个数的数组
	if (!P) {
		throw "内存空间分配失败";
	}
	else {
		for (int i = 0; i < n; i++) {
			printf("请输入参数取值个数");
			int x = scanf_s("%d", P + i);
			allComb = allComb * (*(P+i));
			if (*(P + i) > maxV) maxV = P[i];
		}
		
	}

	int **testSuite = new int* [allComb];
	bool *solution = (bool*)malloc(allComb*sizeof(bool));
	for (int i = 0; i < allComb; i++)
		solution[i] = false;


	for (int i = 0; i < allComb; i++) {
		testSuite[i] = new int[n];
	}
	for (int i = 0; i < allComb; i++) {
		for (int j = 0; j < n; j++) {
			testSuite[i][j] = 0;
		}
	}// 对测试用例数组进行初始化
	
	int Repeat = 1;//参数某一个取值不同测试用例中重复次数
	int aNew = 1;	//参数取值周期
	 /**
	测试用例全集的生成
	*/
	
	time_t startTime=0, stopTime=0;
	time(&startTime);
	for (int y = n-1; y >= 0; y--) {
		Repeat = aNew; //下一个参数同一周期内的重复次数就是上一个参数的取值周期
		aNew = Repeat * P[y];
		
		printf("Repeat=%d, aNew=%d\n", Repeat, aNew);
		for (int j = 0; j < P[y]; j++) {
			for (int x = j*Repeat; x < allComb; x = x+aNew) {//搜索范围是测试用例全集
				for (int d = 0; d < Repeat; d++) {
					testSuite[x+d][y] = j+1;                                      
				}
			}
			
		}
		
	}
	
	/*
	计算理想全集的元素个数（这要看需要什么样的覆盖强度，两两或两三或三三）
	*/
	int comb22 = 0;
	for (int i = 0; i < n; i++) {
		for(int j=n-1; j>i; j--){
			comb22 = comb22 + P[i] * P[j];   //两两组合

		}
	}
	int comb33 = 0;//三三组合个数
	for (int i = n-core; i < n; i++) {
		for (int j = n - 2; j > i; j--) {
			for (int k = n - 1; k > j; k--) {
				comb33 = comb33 + P[i] * P[j] * P[k];
			}
		}
	}
	free(P);
	printf("两两组合数：%d，三三组合数：%d\n", comb22, comb33);
	
	
	ComSet* dataSet = new ComSet[allComb];//使用默认构造函数解决类无法实例化类数组的问题
	ComSet anwserSet(comb22+comb33);

	
	for (int i = 0; i < allComb; i++) {	
		for (int k = 0; k < n; k++) {   //将两两组合的元素加入集合中
			for (int j = n - 1; j > k; j--) {
				Comb element(testSuite[i][k]+ k*maxV, testSuite[i][j]+j*maxV);   //两两组合
				dataSet[i].add(element);
			}
		}
		
		for (int x = n - core; x < n; x++) {  //将三三组合的元素加入集合中
			for (int j = n - 2; j > x; j--) {
				for (int k = n - 1; k > j; k--) {
					Comb element( testSuite[i][x]+x*maxV, testSuite[i][j]+j*maxV, testSuite[i][k]+k*maxV);
					dataSet[i].add(element);
				}
			}
		}
		
		dataSet[i].print();
		
		

		for (int j = 0; j < n; j++) {
			printf("%d, ", testSuite[i][j]);

		}
		printf("\n");

	}


	bool flag = false;
	ComSet temp1 = anwserSet;
	
	anwserSet = anwserSet.Union(dataSet[0]);
	free(temp1.element);
	int quan = 0;
	/*
	new idea
	*/
	/**************/
	int minJ = 0;//本轮最小交集
	int minJi = 0;//本轮最小交集对应的测试用例
	int intersectionNum = 0;
	bool isSolution = false; //标识当前轮找到解
	//int quan = 0;
	/**************/

	
	for (int j = 0; j < dataSet[0].getCount(); j++) {
		if (isSolution) {
			 isSolution = false;
		}else
			j = minJ;
		printf("j = %d", j);
		quan++;
		minJ = anwserSet.IntersectionNum(dataSet[1]);
		for (int i = 1; i < allComb; i++) {
			//printf("%d, %d\n", anwserSet.count, anwserSet.max);
			if (anwserSet.getCount() == (comb22 + comb33)) {
				flag = true;
				printf("成了");
				break;
			}
			intersectionNum = anwserSet.IntersectionNum(dataSet[i]);
			if (minJ > intersectionNum) {
				minJ = intersectionNum;
				minJi = i;
			}

			if (intersectionNum == j) {
				ComSet temp = anwserSet;
				anwserSet = anwserSet.Union(dataSet[i]);
				free(temp.element);
				solution[i] = true;
				printf("有了");
				isSolution = true;
				minJ = j;
			}
			//printf("%d\n", i);
		}
		if (!isSolution) {
			ComSet temp = anwserSet;
			anwserSet = anwserSet.Union(dataSet[minJi]);
			free(temp.element);
			solution[minJi] = true;
			printf("有了");
		}
		printf("第%d圈\n", quan);
		if (flag) break;
	}

	
	/*for (int j = 0; j < dataSet[0].getCount(); j++) {
		quan++;
		printf("j = %d", j);
		for (int i = 1; i < allComb; i++) {
			//printf("%d, %d\n", anwserSet.count, anwserSet.max);
			if (anwserSet.getCount() == (comb22 + comb33)) {
				flag = true;
				printf("成了");
				break;
			}
			if (anwserSet.IntersectionNum(dataSet[i]) == j) {
				ComSet temp = anwserSet;
				anwserSet = anwserSet.Union(dataSet[i]);
				free(temp.element);
				solution[i] = true;
				printf("有了");
			}
			//printf("%d\n", i);
		}
		printf("第%d圈\n", quan);
		if (flag) break;
	}*/









	printf("\n");
	for (int i = 0; i < allComb; i++) {
		if (i == 0 || i == 255) {
			dataSet[i].print();
		}
		free(dataSet[i].element);
	}
	delete []dataSet;
	printf("\n");
	free(anwserSet.element);
	solution[0] = true;
	int ans = 0;
	printf("\n");
	for (int i = 0; i < allComb; i++) {
		if (solution[i]) {
			for (int j = 0; j < n; j++) {
				printf("%d, ", testSuite[i][j]);
				
			}
			ans++;
			printf("\n");
		}
			
	}
	printf("符合覆盖强度要求的测试用例个数为%d", ans);
	

	for (int i = 0; i < allComb; i++) {
		delete []testSuite[i];
	}
	delete[]testSuite;
	free(solution);
	//printf("%d, %d", anwserSet.count, dataSet[0].count);
	time(&stopTime);
	int spend = stopTime - startTime;
	printf("此次实验耗时%d seconds\n", spend);
	//_CrtDumpMemoryLeaks();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
