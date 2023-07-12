#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include "SpriteFile.h"

namespace fs = std::filesystem;

bool GetPathsToSpecificSpritesForlders(std::string& generalSpritesFolderPath)
{
	for (const auto & entry : fs::directory_iterator(generalSpritesFolderPath))
	{		
		generalSpritesFolderPath = entry.path().string();
		if (fs::is_directory(generalSpritesFolderPath))
		{
			for (const auto & subEntry : fs::directory_iterator(generalSpritesFolderPath))
			{
				if (subEntry.path().string().find("sprites") != std::string::npos)
				{
					generalSpritesFolderPath = subEntry.path().string();
					return true;
				}
			}
		}		
	}
	return false;
}

void GetPathsToSpecificSpritesForlders(std::string& generalSpritesFolderPath, std::vector<std::string>& specificSpritesFolderPaths)
{
	std::cout << "Make sure GameMaker is closed." << std::endl;
	std::cout << "Please enter a string to remove cross hairs from all sprites that contains that string in their name. (e.g., spr_Character_Name, input is case sensitive)" << std::endl;
	std::string subString;
	std::getline(std::cin, subString);

	if (subString != "")
	{
		for (const auto & entry : fs::directory_iterator(generalSpritesFolderPath))
		{
			if (entry.path().string().find(subString) != std::string::npos)
			{
				specificSpritesFolderPaths.push_back(entry.path().string());
			}
		}
		std::cout << std::endl;
	}

	while (specificSpritesFolderPaths.size() == 0)
	{
		std::cout << "No sprites found with substring '" + subString + "'" << std::endl;
		std::cout << "Please enter a string to remove cross hairs from all sprites that contains that string in their name. (e.g., spr_Character_Name, input is case sensitive)" << std::endl;
		std::getline(std::cin, subString);

		if (subString != "")
		{
			for (const auto & entry : fs::directory_iterator(generalSpritesFolderPath))
			{
				if (entry.path().string().find(subString) != std::string::npos)
				{
					specificSpritesFolderPaths.push_back(entry.path().string());
				}
			}
			std::cout << std::endl;
		}
	}
}

void LoadSpriteData(std::vector<std::string>& specificSpritesFolderPaths, std::vector<SpriteFile>& spriteFiles)
{
	for (size_t i = 0; i < specificSpritesFolderPaths.size(); i++)
	{
		spriteFiles.push_back(SpriteFile());

		for (const auto & entry : fs::directory_iterator(specificSpritesFolderPaths[i]))
		{		
			if (entry.path().string().find(".png") != std::string::npos)
			{			
				spriteFiles.back().AddPngPath(entry.path().string());
				spriteFiles.back().AddSprite(cv::imread(entry.path().string(), cv::IMREAD_UNCHANGED));
			}

			if (entry.path().string().find(".yy") != std::string::npos)
			{
				spriteFiles.back().SetSettingsPath(entry.path().string());
			}

			if (entry.path().string().find("layers") != std::string::npos)
			{			
				for (const auto & subEntry : fs::directory_iterator(entry.path()))
				{
					//look for folder with random hash that contains the layer sprites
					if (fs::is_directory(subEntry))
					{
						for (const auto & layerEntry : fs::directory_iterator(subEntry.path()))
						{
							if (layerEntry.path().string().find(".png") != std::string::npos)
							{
								spriteFiles.back().AddLayerPath(layerEntry.path().string());
								spriteFiles.back().AddLayerSprite(cv::imread(layerEntry.path().string(), cv::IMREAD_UNCHANGED));
							}							
						}
					}
				}
			}	
		}
	}
}

bool Confirm(std::vector<std::string>& specificSpritesFolderPaths)
{
	for (size_t i = 0; i < specificSpritesFolderPaths.size(); i++)
	{
		std::cout << specificSpritesFolderPaths[i] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Do you want to remove cross hairs on the above sprites (y/n)?" << std::endl;
	std::string awnser;
	std::getline(std::cin, awnser);
	std::cout << std::endl;

	while (awnser != "y" && awnser != "n")
	{
		std::cout << "Invalid input given '" + awnser + "'" << std::endl;
		std::cout << "Do you want to remove cross hairs on the above sprites (y/n)?" << std::endl;
		std::getline(std::cin, awnser);
	}

	if (awnser == "y")
	{
		std::cout << "Searching for cross hairs. Please wait a few seconds..." << std::endl;
		std::cout << std::endl;
		return true;
	}

	if (awnser == "n") return false;

	std::cout << "Something wrong happened please report this to the idiot who made this shitty tool." << std::endl;
	return false;
	std::cout << std::endl;
}

bool SearchForCrossHairs(std::vector<SpriteFile>& spriteFiles)
{
	bool foundCrossHair = false;

	for (size_t i = 0; i < spriteFiles.size(); i++)
	{
		if (spriteFiles[i].RemoveCrosshairs() == true)
		{
			foundCrossHair = true;
		}
	}

	if (foundCrossHair)
	{
		std::cout << std::endl;
		std::cout << "Found cross hairs in the above sprites." << std::endl;
	}
	else
	{
		std::cout << "No cross hairs found" << std::endl;
	}

	return foundCrossHair;
}

bool saveSprites(std::vector<SpriteFile>& spriteFiles)
{
	std::cout << std::endl;

	std::cout << "Do you want to save changes to the above sprites (y/n)?" << std::endl;
	std::string awnser;
	std::getline(std::cin, awnser);
	std::cout << std::endl;

	while (awnser != "y" && awnser != "n")
	{
		std::cout << "Invalid input given '" + awnser + "'" << std::endl;
		std::cout << "Do you want to save changes to the above sprites (y/n)?" << std::endl;
		std::getline(std::cin, awnser);
	}

	if (awnser == "y")
	{
		std::cout << std::endl;
		std::cout << "Saving, please wait a few seconds..." << std::endl;
		std::cout << std::endl;

		for (size_t i = 0; i < spriteFiles.size(); i++)
		{
			spriteFiles[i].SaveSpriteData();
		}

		std::cout << std::endl;
		std::cout << "Changes have been saved." << std::endl;
		std::cout << std::endl;

		return true;
	}
	if (awnser == "n") return false;

	std::cout << "Something wrong happened please report this to the idiot who made this shitty tool." << std::endl;
	return false;
	std::cout << std::endl;

	return true;
}

int main()
{
	std::string cwd = std::filesystem::current_path().string();
	std::string generalSpritesFolderPath = cwd.substr(0, cwd.find("Dev_Tools", 0));
	std::vector<std::string> specificSpritesFolderPaths;
	std::vector<SpriteFile> spriteFiles;

	/*std::string generalSpritesFolderPath = "C:/Users/aklit/Desktop/projects/Tanuki/Jitsu Squad/Jitsu_Squad/sprites";
	GetPathsToSpecificSpritesForlders(generalSpritesFolderPath, specificSpritesFolderPaths);*/

	if (GetPathsToSpecificSpritesForlders(generalSpritesFolderPath))
	{
		GetPathsToSpecificSpritesForlders(generalSpritesFolderPath, specificSpritesFolderPaths);
	}
	else
	{
		std::cout << "Could not find sprites folder. Make sure the executable is in directory 'Dev_Tools\\CrossHairRemover'. " << std::endl;
		std::cout << "Operation has been canceled. Press the return key to close the program." << std::endl;
		std::cin.get();
		return 0;
	}

	if (Confirm(specificSpritesFolderPaths) == true)
	{
		LoadSpriteData(specificSpritesFolderPaths, spriteFiles);
	}
	else
	{
		std::cout << "Operation has been canceled. Press the return key to close the program." << std::endl;
		std::cin.get();
		return 0;
	}

	cv::waitKey();

	if (SearchForCrossHairs(spriteFiles) == true)
	{
		if (saveSprites(spriteFiles) == false)
		{
			std::cout << "Operation has been canceled. Press the return key to close the program." << std::endl;
			std::cin.get();
			return 0;
		}
	}
	else
	{
		std::cout << "Operation has been canceled. Press the return key to close the program." << std::endl;
		std::cin.get();
		return 0;
	}

	std::cout << "Press the return key to close the program." << std::endl;

	std::cin.get();
}