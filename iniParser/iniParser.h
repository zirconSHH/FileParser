#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;

class value
{
public:
	value();
	value(const bool& b);
	value(const int& i);
	value(const double& d);
	value(const char* c);
	value(const string& s);

	void printvalue();
	string getvalue();

	operator bool();
	operator int();
	operator double();
	operator string();

private:
	string objvalue;

};


typedef map<string,value> section;

class iniParser
{
public:
	iniParser();
	int load(const string& filepath);

	void printini();

private:
	string filepath;
	map<string,section> iniIndex;

};



inline value::value()
{
}

inline value::value(const bool& b)
{
	if (b == true)
		objvalue = "true";
	else
		objvalue = "false";

}

inline value::value(const int& i)
{
	stringstream ss;
	ss << i;
	ss >> objvalue;
}

inline value::value(const double& d)
{
	stringstream ss;
	ss << d;
	ss >> objvalue;
}

inline value::value(const char* c)
{
	objvalue = c;
}

inline value::value(const string& s)
{
	objvalue = s;
}

inline void value::printvalue()
{
	cout << objvalue << endl;
}

inline string value::getvalue()
{
	return objvalue;
}

inline value::operator bool()
{
	if (objvalue == "true")
		return true;
	return false;

}

inline value::operator int()
{
	return atoi(objvalue.c_str());
}

inline value::operator double()
{
	return atof(objvalue.c_str());
}

inline value::operator string()
{
	return objvalue;
}

inline iniParser::iniParser()
{
}

int iniParser::load(const string& filepath)
{
	ifstream ifs(filepath, ios::in);
	if (ifs.fail())
		return -1;

	string context;
	string sectionname;
	while (getline(ifs, context))
	{
		if (context == "" || context[0] == '#')
			continue;
		if (context[0] == '[')
		{
			int pos = context.find_first_of(']');
			if (pos == string::npos)
			{
				cout << "syntax error:no ']'" << endl;
				return -2;
			}
			sectionname = context.substr(1, pos - 1);

			//bool find = false;
			//for (map<string, section>::iterator it = iniIndex.begin(); it != iniIndex.end(); it++)
			//{
			//	if (it->first == sectionname)
			//		find = true;
			//}
			//if (find == false)
			//	iniIndex[sectionname] = section();
			
		}
		else
		{
			int pos = context.find_first_of('=');
			if (pos == string::npos)
			{
				cout << "syntax error:no '='" << endl;
				return -3;
			}
			
			string key = context.substr(0, pos);
			key.erase(remove(key.begin(), key.end(), ' '), key.end());
			string val = context.substr(pos + 1, context.length() - pos - 1);
			val.erase(remove(val.begin(), val.end(), ' '), val.end());
			//cout << key << "|" << val << "|" << endl;
			iniIndex[sectionname][key] = val;
		}
	}

	ifs.close();
	return 0;
}

inline void iniParser::printini()
{
	for (map<string, section>::iterator it = iniIndex.begin(); it != iniIndex.end(); it++)
	{
		for (map<string, value>::iterator i = it->second.begin(); i != it->second.end(); i++)
		{
			cout << it->first << ":" << i->first << "|" << i->second.getvalue() << "|" << endl;
		}
	}
}
