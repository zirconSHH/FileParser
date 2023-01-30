#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;

class ivalue
{
public:
	ivalue();
	ivalue(const bool& b);
	ivalue(const int& i);
	ivalue(const double& d);
	ivalue(const char* c);
	ivalue(const string& s);

	void printivalue();
	string getivalue();

	operator bool();
	operator int();
	operator double();
	operator string();

private:
	string objivalue;

};


typedef map<string,ivalue> section;

class iniParser
{
public:
	iniParser();
	iniParser(const string& filepath);
	int load(const string& filepath);

	void printini();

	ivalue getinfo(const string& section, const string& key);

private:
	string filename;
	map<string,section> iniIndex;

};


ivalue::ivalue()
{
}

ivalue::ivalue(const bool& b)
{
	if (b == true)
		objivalue = "true";
	else
		objivalue = "false";

}

ivalue::ivalue(const int& i)
{
	stringstream ss;
	ss << i;
	ss >> objivalue;
}

ivalue::ivalue(const double& d)
{
	stringstream ss;
	ss << d;
	ss >> objivalue;
}

ivalue::ivalue(const char* c)
{
	objivalue = c;
}

ivalue::ivalue(const string& s)
{
	objivalue = s;
}

void ivalue::printivalue()
{
	cout << objivalue << endl;
}

string ivalue::getivalue()
{
	return objivalue;
}

ivalue::operator bool()
{
	if (objivalue == "true")
		return true;
	return false;

}

ivalue::operator int()
{
	return atoi(objivalue.c_str());
}

ivalue::operator double()
{
	return atof(objivalue.c_str());
}

ivalue::operator string()
{
	return objivalue;
}

iniParser::iniParser()
{
}

iniParser::iniParser(const string& filepath)
{
	this->load(filepath);
}

int iniParser::load(const string& filepath)
{
	filename = filepath;
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

			iniIndex[sectionname][key] = val;
		}
	}

	ifs.close();
	return 0;
}

void iniParser::printini()
{
	for (map<string, section>::iterator it = iniIndex.begin(); it != iniIndex.end(); it++)
	{
		for (map<string, ivalue>::iterator i = it->second.begin(); i != it->second.end(); i++)
		{
			cout << it->first << ":" << i->first << "|" << i->second.getivalue() << "|" << endl;
		}
	}
}

ivalue iniParser::getinfo(const string& section, const string& key)
{
	return iniIndex[section][key];
}
