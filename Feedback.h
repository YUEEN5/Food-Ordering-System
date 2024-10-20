#include<string>
using namespace std;

#ifndef FEEDBACK_H
#define FEEDBACK_H

class Feedback
{
public:
	int fbID, rating, custID, orderID;
	string comment;
	Feedback* next;
};

#endif
#pragma once
