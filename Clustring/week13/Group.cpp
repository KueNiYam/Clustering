#include "clustering.h"

bool Group::hasDuplicateItem(int item) const
{
	for (int i = 0; i < length; i++)
	{
		if (item == stack[i])
			return true;
	}

	return false;
}

void Group::put(int item)
{
	stack[length++] = item;
}

int Group::pop()
{
	int forPop = stack[length - 1];
	length--;
	return forPop;
}

int Group::getItem(int index) const
{
	return stack[index];
}

int Group::getLength() const
{
	return length;
}

double Group::getSumOfDistances() const
{
	return sumOfDistances;
}

void Group::addDistance(double value)
{
	sumOfDistances += value;
}

void Group::clearCore()
{
	initByZero();
}

void Group::clearStack()
{
	length = 0;
	sumOfDistances = 0;
}

void Group::showItems() const
{
	for (int i = 0; i < length; i++)
		cout << stack[i] << ' ';
	cout << endl;
}

bool Group::operator==(const Group& other) const
{
	if (length != other.length)
		return false;

	for (int i = 0; i < length; i++)
	{
		if (stack[i] != other.stack[i])
			return false;
	}

	return true;
}