#include "SpriteFile.h"

SpriteFile::SpriteFile()
	:m_SettingsPath(""), m_PngPaths(0), m_SpriteData(0) {}

void SpriteFile::SetSettingsPath(std::string settingsPath)
{
	m_SettingsPath = settingsPath;
}

void SpriteFile::AddPngPath(std::string pngPath)
{
	m_PngPaths.push_back(pngPath);
}

void SpriteFile::AddLayerPath(std::string layerPath)
{
	m_LayerPaths.push_back(layerPath);
}

void SpriteFile::AddSprite(cv::Mat sprite)
{
	m_SpriteData.push_back(sprite);
	m_IsSpriteEdited.push_back(false);
}

void SpriteFile::AddLayerSprite(cv::Mat sprite)
{
	m_LayersData.push_back(sprite);
	m_IsLayerEdited.push_back(false);
}

void SpriteFile::PrintSettingsPath()
{
	std::cout << m_SettingsPath << std::endl;
}

void SpriteFile::PrintPngPaths()
{
	for (size_t i = 0; i < m_PngPaths.size(); i++)
	{
		std::cout << m_PngPaths[i] << std::endl;
	}
}

void SpriteFile::PrintLayerPaths()
{
	for (size_t i = 0; i < m_PngPaths.size(); i++)
	{
		std::cout << m_LayerPaths[i] << std::endl;
	}
}

void SpriteFile::ShowSprites()
{
	for (size_t i = 0; i < m_SpriteData.size(); i++)
	{
		cv::imshow(m_PngPaths[i], m_SpriteData[i]);
	}
}

void SpriteFile::ShowNewSprites()
{
	for (size_t i = 0; i < m_NewSpriteData.size(); i++)
	{
		cv::imshow(m_PngPaths[i], m_NewSpriteData[i]);
	}
}

void SpriteFile::ShowLayers()
{
	for (size_t i = 0; i < m_SpriteData.size(); i++)
	{
		cv::imshow(m_LayerPaths[i], m_LayersData[i]);
	}
}

bool SpriteFile::RemoveCrosshairs()
{
	bool foundCrossHair = false;

	for (size_t i = 0; i < m_SpriteData.size(); i++)
	{
		cv::Mat splitChannels[4];

		cv::split(m_SpriteData[i], splitChannels);

		for (size_t r = 0; r < m_SpriteData[0].rows; r++)
		{
			for (size_t c = 0; c < m_SpriteData[0].cols; c++)
			{
				if (splitChannels[0].at<uint8_t>(r, c) >= 255
					&& splitChannels[1].at<uint8_t>(r, c) == 0
					&& splitChannels[2].at<uint8_t>(r, c) >= 255)
				{
					m_IsSpriteEdited[i] = true;

					splitChannels[0].at<uint8_t>(r, c) = 0;
					splitChannels[1].at<uint8_t>(r, c) = 0;
					splitChannels[2].at<uint8_t>(r, c) = 0;
					splitChannels[3].at<uint8_t>(r, c) = 0;
				}
			}
		}

		cv::Mat output;
		cv::merge(splitChannels, 4, output);

		m_NewSpriteData.push_back(output);
	}

	for (size_t i = 0; i < m_SpriteData.size(); i++)
	{
		if (m_IsSpriteEdited[i])
		{
			foundCrossHair = true;
			std::cout << m_PngPaths[i] << std::endl;
		}
	}

	//layers
	for (size_t i = 0; i < m_LayersData.size(); i++)
	{
		cv::Mat splitChannels[4];

		cv::split(m_LayersData[i], splitChannels);

		for (size_t r = 0; r < m_LayersData[0].rows; r++)
		{
			for (size_t c = 0; c < m_LayersData[0].cols; c++)
			{
				if (splitChannels[0].at<uint8_t>(r, c) >= 255
					&& splitChannels[1].at<uint8_t>(r, c) == 0
					&& splitChannels[2].at<uint8_t>(r, c) >= 255)
				{
					m_IsLayerEdited[i] = true;

					splitChannels[0].at<uint8_t>(r, c) = 0;
					splitChannels[1].at<uint8_t>(r, c) = 0;
					splitChannels[2].at<uint8_t>(r, c) = 0;
					splitChannels[3].at<uint8_t>(r, c) = 0;
				}
			}
		}

		cv::Mat output;
		cv::merge(splitChannels, 4, output);

		m_NewSpriteData.push_back(output);
	}

	for (size_t i = 0; i < m_LayersData.size(); i++)
	{
		if (m_IsLayerEdited[i])
		{
			foundCrossHair = true;
			std::cout << m_LayerPaths[i] << std::endl;
		}
	}

	return foundCrossHair;
}

void SpriteFile::SaveSpriteData()
{
	for (size_t i = 0; i < m_PngPaths.size(); i++)
	{
		if (m_IsSpriteEdited[i])
		{
			cv::imwrite(m_PngPaths[i], m_NewSpriteData[i]);
		}
	}

	for (size_t i = 0; i < m_LayerPaths.size(); i++)
	{
		if (m_IsLayerEdited[i])
		{
			cv::imwrite(m_LayerPaths[i], m_NewSpriteData[i]);
		}
	}
}
