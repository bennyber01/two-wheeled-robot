#pragma once

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

bool CreateDirectoryFromFilePath(std::string fileName)
{
	unsigned indx = fileName.find_last_of("/\\");

	if (std::string::npos == indx)
		return true;

	boost::filesystem::path filePath = fileName.substr (0, indx);

	bool isDirectoriesExist = boost::filesystem::is_directory(filePath);
	if (isDirectoriesExist)
		return true;

	bool isDirectoriesCreated = boost::filesystem::create_directories(filePath);
	return isDirectoriesCreated;
}