#include "clustering.h"

int main()
{
	/** Data input */
	Iris data[data_num];
	ifstream fin;
	char dataName[input_buff];
	cout << "Input file name: ";
	cin >> dataName;
	fin.open(dataName, fstream::in); 
	if (!fin)
	{
		cerr << "Error: " << "can't open " << dataName << endl;
		::exit(1);
	}
	cout << "#Data" << endl;
	for (int i = 0; i < data_num; i++)
	{
		data[i] << fin;
		data[i].show();
	}
	fin.close();
	/**************************************************/
	/** Make Random data before clustering */
	::srand((unsigned int)time(NULL));
	//!  Group A, B, C
	Group A = Group(rand() % 400 * 0.01 + 4, rand() % 200 * 0.01 + 2, rand() % 600 * 0.01 + 1,
		rand() % 300 * 0.01);
	Group B = Group(rand() % 400 * 0.01 + 4, rand() % 200 * 0.01 + 2, rand() % 600 * 0.01 + 1,
		rand() % 300 * 0.01);
	Group C = Group(rand() % 400 * 0.01 + 4, rand() % 200 * 0.01 + 2, rand() % 600 * 0.01 + 1,
		rand() % 300 * 0.01);
	cout << "#Three random data created within an appropriate range" << endl;
	A.show();
	B.show();
	C.show();
	/**************************************************/
	/** Clustering */
	Group preA, preB, preC;
	double distanceA, distanceB, distanceC; //< distance to coreA, coreB, coreC
	int howMany = 1; //< for print

	while (true)
	{
		char smallerObject;
		for (int i = 0; i < data_num; i++)
		{
			distanceA = A - data[i];
			distanceB = B - data[i];
			distanceC = C - data[i]; 
			smallerObject = ::whatIsMinimum(distanceA, distanceB, distanceC);

			if (smallerObject == 'A')
			{
				A.put(i);
				A.addDistance(distanceA);
			}
			else if (smallerObject == 'B')
			{
				B.put(i);
				B.addDistance(distanceB);
			}
			else
			{
				C.put(i);
				C.addDistance(distanceC);
			}
		}
		// printf()
		cout << "##" << howMany++ << "'s Clustering" << endl;
		cout << "A(" << A.getSepalLength() << ',' << A.getSepalWidth() << ',' << A.getPetalLength() << ','
			<< A.getPetalWidth() << ") ";
		cout << "B(" << B.getSepalLength() << ',' << B.getSepalWidth() << ',' << B.getPetalLength() << ','
			<< B.getPetalWidth() << ") ";
		cout << "C(" << C.getSepalLength() << ',' << C.getSepalWidth() << ',' << C.getPetalLength() << ','
			<< C.getPetalWidth() << ") ";
		cout << "sum of distances : " << A.getSumOfDistances() + B.getSumOfDistances()
			+ C.getSumOfDistances() << endl;
		cout << "#A" << endl;
		A.showItems();
		cout << "#B" << endl;
		B.showItems();
		cout << "#C" << endl;
		C.showItems();
		if ((A == preA) && (B == preB) && (C == preC))
			break;
		else
		{
			preA = A;
			preB = B;
			preC = C;
			A.clearCore();
			B.clearCore();
			C.clearCore();
			for (int i = A.getLength() - 1; i >= 0; i--)
			{
				A += data[A.getItem(i)];
			}
			for (int i = B.getLength() - 1; i >= 0; i--)
			{
				B += data[B.getItem(i)];
			}
			for (int i = C.getLength() - 1; i >= 0; i--)
			{
				C += data[C.getItem(i)];
			}

			//! @Exception devide by zero
			//! If the one of clustering result is gathered in one place, it may be inaccurate clustering,
			//! so it is better for the user to re-run the program
			try
			{
				A.divide(A.getLength());
			}
			catch (char* errorMessage)
			{
				cerr << errorMessage << endl;
				cout << "Recommand try again" << endl;
				::exit(1);
			}
			try
			{
				B.divide(B.getLength());
			}
			catch (char* errorMessage)
			{
				cerr << errorMessage << endl;
				cout << "Recommand try again" << endl;
				::exit(1);
			}
			try
			{
				C.divide(C.getLength());
			}
			catch (char* errorMessage)
			{
				cerr << errorMessage << endl;
				cout << "Recommand try again" << endl;
				::exit(1);
			}
			A.clearStack();
			B.clearStack();
			C.clearStack();
		}
	}
	/**************************************************/
	/** Data output */
	ofstream clusterAcsv, clusterBcsv, clusterCcsv;
	clusterAcsv.open("clusterA.csv", fstream::out);
	clusterBcsv.open("clusterB.csv", fstream::out);
	clusterCcsv.open("clusterC.csv", fstream::out);
	if (!clusterAcsv)
	{
		cerr << "Error: " << "can't open " << "\"clusterA.csv\"" << endl;
		::exit(1);
	}
	if (!clusterBcsv)
	{
		cerr << "Error: " << "can't open " << "\"clusterB.csv\"" << endl;
		::exit(1);
	}
	if (!clusterCcsv)
	{
		cerr << "Error: " << "can't open " << "\"clusterC.csv\"" << endl;
		::exit(1);
	}

	clusterAcsv << "sepal length,sepal width, petal length, petal width,name" << endl;
	clusterBcsv << "sepal length,sepal width, petal length, petal width,name" << endl;
	clusterCcsv << "sepal length,sepal width, petal length, petal width,name" << endl;
	int queueSizeA = A.getLength();
	int queueSizeB = B.getLength();
	int queueSizeC = C.getLength();
	for (int i = 0; i < queueSizeA; i++)
	{
		data[A.getItem(i)].csvPrint(clusterAcsv);
	}
	for (int i = 0; i < queueSizeB; i++)
	{
		data[B.getItem(i)].csvPrint(clusterBcsv);
	}
	for (int i = 0; i < queueSizeC; i++)
	{
		data[C.getItem(i)].csvPrint(clusterCcsv);
	}
	clusterAcsv.close();
	clusterBcsv.close();
	clusterCcsv.close();
	/**************************************************/
	return 0;
}
