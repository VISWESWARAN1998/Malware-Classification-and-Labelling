// SWAMI KARUPPASWAMI THUNNAI

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <experimental/filesystem>
#include <fstream>

class header_compiler
{
public:
	header_compiler();
	void compile();

private:
	std::vector<std::string> frequency_file;
	std::set<std::string> function_set;
	bool check_file_existense();
	bool is_string_hungarian(std::string function_name);
	bool does_string_has_special_char(std::string function_name);
	void add_to_omitted(std::string func_name);
	std::string stem(std::string function_name);
};

header_compiler::header_compiler()
{
	// Load all the frequency files
	frequency_file.push_back("backdoor/frequency.txt");
	frequency_file.push_back("downloader/frequency.txt");
	frequency_file.push_back("keylogger/frequency.txt");
	frequency_file.push_back("miner/frequency.txt");
	frequency_file.push_back("ransom/frequency.txt");
	frequency_file.push_back("rouge/frequency.txt");
	frequency_file.push_back("trojan/frequency.txt");
	frequency_file.push_back("worm/frequency.txt");
	std::cout << "[$] Loaded all the frequency files!\n";
}

bool header_compiler::check_file_existense()
{
	std::vector<std::string>::iterator itr1 = frequency_file.begin();
	std::vector<std::string>::iterator itr2 = frequency_file.end();
	for (std::vector<std::string>::iterator itr = itr1; itr != itr2; ++itr)
	{
		if (!std::experimental::filesystem::exists(*itr)) return false;
	}
	return true;
}

bool header_compiler::is_string_hungarian(std::string function_name)
{
	if (function_name.size() > 0)
	{
		if (isupper(function_name[0])) return true;
	}
	return false;
}

bool header_compiler::does_string_has_special_char(std::string function_name)
{
	for (char ch : function_name)
	{
		if (ch == '$') return true;
		else if (ch == '@') return true;
		else if (ch == '[') return true;
		else if (ch == ']') return true;
		else if (ch == '%') return true;
	}
	return false;
}

void header_compiler::compile()
{
	if (!check_file_existense())
	{
		std::cout << "[$] A FILE IS MISSING.\n";
		return;
	}
	for (std::string file : frequency_file)
	{
		std::ifstream loader;
		loader.open(file);
		if (loader.is_open())
		{
			std::cout << "[$] Loading: " << file << "\n";
			while (!loader.eof())
			{
				std::string function;
				std::getline(loader, function);
				if (!is_string_hungarian(function))
				{
					// Only add lower case functions if it's berkely compatible socket functions.
					if(function == "send") function_set.insert(function);
					else if(function == "recv") function_set.insert(function);
					else if(function == "connect") function_set.insert(function);
					else if(function == "accept") function_set.insert(function);
					else if (function == "listen") function_set.insert(function);
					else if (function == "bind") function_set.insert(function);
					else if (function == "socket") function_set.insert(function);
					else if (function == "getsockname") function_set.insert(function);
					else if (function == "closesocket") function_set.insert(function);
					else if (function == "nthos") function_set.insert(function);
					else if (function == "htons") function_set.insert(function);
					else if (function == "inet_ntoa") function_set.insert(function);
					else if (function == "inet_addr") function_set.insert(function);
					else if (function == "getservbyname") function_set.insert(function);
					else if (function == "gethostbyname") function_set.insert(function);
					else if (function == "gethostbyaddr") function_set.insert(function);
					else add_to_omitted(function);
				}
				else if (does_string_has_special_char(function)) add_to_omitted(function);
				else
				{
					if (function.size() > 0)
					{
						std::string stemmed_function = stem(function);
						if(stemmed_function.size() > 0) function_set.insert(stemmed_function);
					}
				}
			}
			loader.close();
		}
	}
	std::ofstream file;
	file.open("header.txt");
	if (file.is_open())
	{
		for (std::string function_name : function_set)
		{
			file << function_name << "\n";
		}
		file.close();
	}
}

void header_compiler::add_to_omitted(std::string func_name)
{
	std::ofstream file;
	file.open("omitted.txt", std::ios::app);
	if (file.is_open())
	{
		file << func_name << "\n";
		file.close();
	}
}

std::string header_compiler::stem(std::string function_name)
{
	std::string stemmed = "";
	if ((function_name[function_name.size() - 1] == 'A') || (function_name[function_name.size() - 1] == 'W'))
	{
		for (int i = 0; i < function_name.size() - 1; i++)
		{
			stemmed += function_name[i];
		}
		std::ofstream file;
		file.open("stemmed.txt", std::ios::app);
		if (file.is_open())
		{
			file << function_name << " is stemmed to: " << stemmed << "\n";
		}
	}
	else stemmed = function_name;
	return stemmed;
}


int main()
{
	header_compiler compiler;
	compiler.compile();
	std::cout << "Completed!";
	int stay;
	std::cin >> stay;
}
