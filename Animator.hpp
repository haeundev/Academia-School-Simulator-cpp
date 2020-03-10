#pragma once

template<typename T>
void Animator::SetParameter(string key, T data)
{
	string dataType = typeid(data).name();
	if (dataType == "int")
	{
		if (intData.find(key) == intData.end())
			return;

		intData[key] = data;
	}
	else if (dataType == "float")
	{
		if (floatData.find(key) == floatData.end())
			return;

		floatData[key] = data;
	}
	else if (dataType == "bool")
	{
		if (boolData.find(key) == boolData.end())
			return;

		boolData[key] = data;
	}
}

template<typename T>
T Animator::GetData(string key)
{
	string dataType = typeid(T).name();
	if (dataType == "int")
		return intData[key];
	else if (dataType == "float")
		return floatData[key];
	else if (dataType == "bool")
		return boolData[key];
}

template<typename T>
void Animator::AddParameter(string key)
{
	string dataType = typeid(T).name();
	if (dataType == "int")
		intData.insert(make_pair(key, false));
	else if (dataType == "float")
		floatData.insert(make_pair(key, false));
	else if (dataType == "bool")
		boolData.insert(make_pair(key, false));
}