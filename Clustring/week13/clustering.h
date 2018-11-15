#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

enum size
{ 
	input_buff = 256, data_num = 150, max_buff = 20, rand_max = 10, two = 2, dataField = 4
};

//! @Parent-class IrisNumericalInfo
//! @Brief
//! This class has iris's attribute base
class IrisNumericalInfo
{
private:
	//! This data are marked by cm
	double sepalLength;
	double sepalWidth;
	double petalLength;
	double petalWidth;
public:
	/** Constructor */
	IrisNumericalInfo()
	{
		/* Deliberately empty */
	}
	IrisNumericalInfo(double a, double b, double c, double d)
		: sepalLength(a), sepalWidth(b), petalLength(c), petalWidth(d)
	{
		/* Deliberately empty */
	}
	/**************************************************/
	/** Function */
	double getSepalLength() const;
	double getSepalWidth() const;
	double getPetalLength() const;
	double getPetalWidth() const;
	void setSepalLength(double value);
	void setSepalWidth(double value);
	void setPetalLength(double value);
	void setPetalWidth(double value);
	void divide(int num);
	void initByZero();
	void show() const;
	/**************************************************/
	/** Operator */
	IrisNumericalInfo& operator+=(const IrisNumericalInfo& other);
	//! @Return Distance
	//! @Operator -
	//! @Usage
	//! objectA - objectB
	//! @Return
	//! Euclidean distance between objectA and objectB
	//! @Remark
	//! This operator do not change the orginal object's value
	double operator-(const IrisNumericalInfo& other) const;
	//! @Operator <<
	//! @Usage
	//!	 object << ifstream
	//! @Brief
	//!	 read File and write to Object
	friend IrisNumericalInfo& operator<<(IrisNumericalInfo& object, ifstream& fin);
	/**************************************************/
};

//! @Class Iris
//! @Brief 
//!	 This class has iris data information
class Iris : public  IrisNumericalInfo
{
private:
	char name[max_buff];
public:
	/** Constuctor */
	Iris()
	{
		::memset(name, '\0', max_buff);
	}
	//! @Brief 
	//! sepalLength, sepalWidth, petalLength, petalWidth in order
	Iris(double a, double b, double c, double d)
		: IrisNumericalInfo(a, b, c, d)
	{
		::memset(name, '\0', max_buff);
	}
	/**************************************************/
	/** Function */
	void divide(int num);
	void show() const;
	//! @Function divide()
	//! @Brief
	//! divide object by num
	//! @Exception
	//! If num is zero, throw error message
	void csvPrint(ofstream& fout) const;
	void initByZero();
	/**************************************************/
	/** Operator */
	//! @Operator <<
	//! @Usage
	//!	 Iris << ifstream
	//! @Brief
	//!	 read File and write to Object
	friend Iris& operator<<(Iris& object, ifstream& fin);
	/**************************************************/
};

//! @Class Group
//! @Brief
//!	 Use for grouping
class Group : public IrisNumericalInfo
{
private:
	int stack[data_num];
	int length; //< num of item in stack
	double sumOfDistances;
public:
	/** constructor */
	Group()
	{
		init();
	}
	Group(double a, double b, double c, double d)
		:  IrisNumericalInfo(a, b, c, d)
	{
		init();
	}
	//! @Function init
	//! @Brief
	//! use to construct
	void init()
	{
		length = 0;
		sumOfDistances = 0;
		memset(stack, 0, sizeof(int) * data_num);
	}
	/**************************************************/
	/** Function */
	//! @Function hasDuplicateItem()
	//! @Return
	//! true - has duplicate item
	//! False - does not have duplicate item
	bool hasDuplicateItem(int item) const;
	void put(int item);
	//! @Function pop()
	//! @Brief
	//! pop last index
	//! @Remark
	//! do not need pop first index, and can save the cost
	int pop();
	//! @Function getItem()
	//! @Brief
	//! get value of num index while not remove that
	int getItem(int index) const;
	int getLength() const;
	double getSumOfDistances() const;
	void addDistance(double value);
	void clearCore();
	void clearStack();
	void showItems() const;
	/**************************************************/
	/** Operator */
	bool operator==(const Group& other) const;
	/**************************************************/
};

//! @Function whatIsMinimum()
//! @Return
//! What alphabet has minimum value between A and B and C. 
char whatIsMinimum(double A, double B, double C);