// SWAMI KARUPPASWAMI THUNNAI

#pragma once

#include <string>
#include <vector>
#include <set>
#include <Windows.h>

class create_dictionary
{
private:
	std::set<std::string> scanned_hash;
public:
	create_dictionary();
	~create_dictionary();

	// Calculates the MD5 of the file.
	std::string calculate_md5(std::string file_location);
	
	// Mark hash as scanned
	void mark_hash_as_scanned(std::string hash);

	// Check whether the file is scanned already or not. Takes md5 of the file as argument.
	bool is_file_scanned(std::string hash);

	// Create the frequency distribution
	void create(std::string file_location);

	// Get all the import function for PE32
	std::vector<std::string> get_import_function(LPCTSTR exeFileName);

	// checks if non-ascii character is present or not
	bool is_unicode_present(std::string function_name);
};

