#pragma once
#include <string>
using namespace std;
class UI abstract
{
protected:
	UI() {}
	string name;
	int lineNumber = 0;
public:
	virtual void Render() = 0;
	void SetLineNumber(int _lineNumber) { lineNumber = _lineNumber; }
	int GetLineNumber() { return lineNumber; }
};

