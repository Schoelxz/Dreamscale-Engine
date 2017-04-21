#include "ProjectHandler.h"

//Note string.c_str() to make string write files

bool ProjectHandler::FileExists(const std::string& fileName)
{
	struct stat buf;
	if (stat(fileName.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

void ProjectHandler::SetFilename(const std::string fileName)
{
	_fileName = fileName;
}

std::string ProjectHandler::GetFilename()
{
	return _fileName;
}

void ProjectHandler::SaveProject(const std::string fileText)
{
	_myFile.open(GetFilename(), std::fstream::out);

	_myFile << fileText.c_str();

	_myFile.close();
}

void ProjectHandler::LoadProject()
{
	//_myFile.open(GetFilename(), std::fstream::out);
	//load?
	//_myFile.close();
}

ProjectHandler::ProjectHandler()
{
	std::cout << "class : ProjectHandler : Constructed!" << std::endl;
}


ProjectHandler::~ProjectHandler()
{
	std::cout << "class : ProjectHandler : Destroyed!" << std::endl;
}