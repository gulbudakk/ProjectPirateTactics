#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>

#include "../Texture.h"
#include "../Application.h"
#include "Character.h"

using namespace std;

class Font
{
private:
	const double LINE_HEIGHT = 0.03f;
	const static int SPACE_ASCII = 32;

	const static int PAD_TOP = 0;
	const static int PAD_LEFT = 1;
	const static int PAD_BOTTOM = 2;
	const static int PAD_RIGHT = 3;

	const static int DESIRED_PADDING = 3;

	const string m_SPLITTER = " ";
	const string m_NUMBER_SEPARATOR = ",";

	double m_aspectRatio = Application::GetRatio();

	double m_verticalPerPixelSize;
	double m_horizontalPerPixelSize;
	double m_spaceWidth;
	vector<int> m_padding;
	int m_paddingWidth;
	int m_paddingHeight;

	unordered_map<int, Character> m_characters;
	Texture& m_FontAtlasTexture;

	unordered_map<string, string> m_values;

	ifstream m_fontFile;

	bool ProcessNextLine();
	void LoadPaddingData();
	void LoadLineSizes();
	int GetValueOfVariable(string variable);
	vector<int> GetValuesOfVariable(string variable);
	void LoadCharacters(int imageWidth);
	Character LoadCharacter(int imageSize);

	vector<string> split(const string& str, const string& delimiter);
public:
	Font(Texture& fontAtlasTexture, string fontFilePath);

	Character GetCharacter(int ascii) {
		return m_characters[ascii];
	}

	double getSpaceWidth() {
		return m_spaceWidth;
	}

	int GetSpaceAscii() {
		return SPACE_ASCII;
	}

	double GetLineHeight() {
		return LINE_HEIGHT;
	}

	Texture& GetTexture() {
		return m_FontAtlasTexture;
	}
};

