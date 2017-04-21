#pragma once
#include <vector>
#include <fstream>
#include <iostream>


	class ProjectHandler
	{
	public:

		bool FileExists(const std::string& fileName);	//Done

		void SetFilename(const std::string fileName);	//Done

		std::string GetFilename();						//Done

		void SaveProject(const std::string fileText);	//InProgress

		void LoadProject();								//InProgress

		ProjectHandler();
		~ProjectHandler();

	protected:

		std::string _fileName;
		std::fstream _myFile;
	};

