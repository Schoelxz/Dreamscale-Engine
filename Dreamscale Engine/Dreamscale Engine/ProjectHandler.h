#pragma once
#include <vector>
#include <fstream>


	class ProjectHandler
	{
	public:

		void save(std::string stringData);
		void save(float floatData);
		void save(std::string stringData, float floatData);

		void load(std::vector<std::string> txtData, std::vector<float> numData);

		ProjectHandler();
		~ProjectHandler();

	private:

		std::vector<std::string> textData;
		std::vector<float> numData;

	};

