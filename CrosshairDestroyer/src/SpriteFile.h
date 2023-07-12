#pragma once
#include <iostream>
#include <string>;
#include <vector>;
#include "opencv2/opencv.hpp"

class SpriteFile
{
public:
	SpriteFile();

	std::string m_SettingsPath;
	std::vector<std::string> m_PngPaths;
	std::vector<std::string> m_LayerPaths;

	std::vector<cv::Mat> m_SpriteData;
	std::vector<cv::Mat> m_NewSpriteData;

	std::vector<cv::Mat> m_LayersData;
	std::vector<cv::Mat> m_NewLayerseData;

	std::vector<bool> m_IsSpriteEdited;
	std::vector<bool> m_IsLayerEdited;

	void SetSettingsPath(std::string settingsPath);

	void AddPngPath(std::string pngPath);
	void AddLayerPath(std::string layerPath);

	void AddSprite(cv::Mat sprite);
	void AddLayerSprite(cv::Mat sprite);


	void PrintSettingsPath();
	void PrintPngPaths();
	void PrintLayerPaths();
	void ShowSprites();
	void ShowNewSprites();
	void ShowLayers();
	void ShowNewLayers();

	bool RemoveCrosshairs();
	void SaveSpriteData();
};

