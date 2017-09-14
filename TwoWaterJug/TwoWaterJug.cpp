// TwoWaterJug.cpp : Defines the entry point for the console application.
/*
You are at the side of a river. You are given a m litre jug and a n litre jug where 0 < m < n. Both the jugs are
initially empty. The jugs don’t have markings to allow measuring smaller quantities. You have to use the jugs to 
measure d litres of water where d < n. Determine the minimum no of operations to be performed to obtain d litres of 
water in one of jug.
The operations you can perform are:

1. Empty a Jug
2. Fill a Jug
3. Pour water from one jug to the other until one of the jugs is either empty or full.

Ref: http://www.geeksforgeeks.org/two-water-jug-puzzle
*/

#include "stdafx.h"
#include <iostream>

using namespace std;

int min(int a, int b)
{
	return a < b ? a : b;
}

int pour(int D, int fromCap, int toCap)
{
	int from = fromCap; //step -> 1
	int to = 0;

	int steps = 1; 

	while (to != D && from != D)
	{
		//max amount that cab be poured...
		int maxTemp = min(from, toCap - to);
		//pour maxTemp from 'from' to 'to'
		to += maxTemp;
		from -= maxTemp;
		//increament count of steps;
		steps++;
		//check the water level in jugs
		if (from == D || to == D) break;
		//if first jug becomes empty ...fill it
		if (from == 0)
		{
			from = fromCap;
			steps++;
		}

		//if 2nd jug is full...empty it
		if (to == toCap)
		{
			to = 0;
			steps++;
		}
	}

	return steps;
}

int GCD(int a, int b)
{
	if (a == 0) return b;
	return GCD(b%a, a);
}

int min_operation_to_measure(int D, int M, int N)
{
	if (M > N) {
		swap(M, N);
	}

	if (D > N) return -1; //cant measure more than N
	if (D % GCD(M, N) != 0) return -1; //solution not possible

	return min(pour(D, M, N), pour(D, N, M));
}

int min_steps_util(int M, int N, int D) //pouring from M jug to N jug;
{
	int steps = 0;
	int mJug = 0;
	int nJug = 0;
	while (1)
	{
		if (mJug == 0)
		{
			//fill it
			mJug = M;
			steps++;
		}
		if (nJug == N)
		{
			//empty it
			nJug = 0;
			steps++;
		}
		//pour from mJug to nJug;
		int pour = min(N - nJug, mJug);
		//update amounts in both jugs
		mJug -= pour;
		nJug += pour;
		steps++;
		//now check if we have achieved the result
		if (mJug == D || nJug == D)
		{
			return steps;
		}
		if (mJug == 0 && nJug == N) //we have reached initial state
		{
			return -1;
		}
	}

	return steps;
}

int min_steps(int M, int N, int D)
{
	if (D > M && D > N) return -1;
	if (D == M) return 1;
	if (D == N) return 1;

	return min(min_steps_util(M, N, D), min_steps_util(N, M, D));
}

int main()
{
	int M, N, D; // jug capacities M & N  (1 <= M <= N) and quatity to be measured (D < N)

	cin >> M >> N >> D;

	cout << min_operation_to_measure(D, M, N) << endl;
	cout << min_steps(M, N, D) << endl;
    return 0;
}

