#pragma once
#include "GgaetIp.h"

class LoadDirectory : public Script
{
private:
	vector<string> _vDirectoryList;
	map<string, vector<string>> _mFileList;

public:
	void Load();
	map<string, vector<string>> GetFileList() {	return _mFileList; };
};