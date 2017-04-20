#include "ProjectHandler.h"


		void ProjectHandler::save(std::string stringData, float floatData)
		{
			float hehej = 1.03f;

			textData.push_back(stringData);
			numData.push_back(floatData);

			std::fstream saveFile;
			saveFile.open("ProjectSave.txt", std::fstream::out);
			saveFile << stringData.c_str();
			saveFile << std::endl;
			saveFile << floatData;
			saveFile.close();
		}
		void ProjectHandler::load(std::vector<std::string> txtData, std::vector<float> numData)
		{
			
		}

		ProjectHandler::ProjectHandler()
		{

		}


		ProjectHandler::~ProjectHandler()
		{
		}
	
 //namespace ProjectHandler