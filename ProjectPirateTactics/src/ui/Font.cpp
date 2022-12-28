#include "Font.h"
using namespace std;

Font::Font(Texture& fontAtlasTexture, string fontFilePath) : m_FontAtlasTexture(fontAtlasTexture) {

	m_fontFile.open(fontFilePath);

	if (!m_fontFile.is_open())
	{
		cout << "Unable to open the file." << endl;
		return;
	}

	LoadPaddingData();
	LoadLineSizes();
	int imageWidth = GetValueOfVariable("scaleW");
	LoadCharacters(imageWidth);

	m_fontFile.close();
}

bool Font::ProcessNextLine() {
	m_values.clear();
	string line = "";
	getline(m_fontFile, line);
	cout << line << endl;

	if (line == "") {
		return false;
	}

	vector<string> parts = split(line, m_SPLITTER);
	for (const string& part : parts) {
		vector<string> valuePairs = split(part, "=");
		if (valuePairs.size() == 2) {
			m_values.insert_or_assign(valuePairs[0], valuePairs[1]);
		}
	}
	return true;
}

vector<string> Font::split(const string& str, const string& delimiter) {
	vector<string> parts;

	size_t start = 0;
	size_t end = 0;
	while ((end = str.find(delimiter, start)) != string::npos) {
		string part = str.substr(start, end - start);
		parts.push_back(part);
		start = end + delimiter.length();
	}
	parts.push_back(str.substr(start));

	return parts;
}

void Font::LoadPaddingData() {
	ProcessNextLine();
	m_padding = GetValuesOfVariable("padding");
	m_paddingWidth = m_padding[PAD_LEFT] + m_padding[PAD_RIGHT];
	m_paddingHeight = m_padding[PAD_TOP] + m_padding[PAD_BOTTOM];
}

void Font::LoadLineSizes() {
	ProcessNextLine();
	int lineHeightPixels = GetValueOfVariable("lineHeight") - m_paddingHeight;
	m_verticalPerPixelSize = LINE_HEIGHT / (double)lineHeightPixels;
	m_horizontalPerPixelSize = m_verticalPerPixelSize / m_aspectRatio;
}

int Font::GetValueOfVariable(string variable) {

	return stoi(m_values[variable]);
}

void Font::LoadCharacters(int imageWidth) {
	ProcessNextLine();
	ProcessNextLine();
	while (ProcessNextLine()) {
		Character c = LoadCharacter(imageWidth);
		m_characters[c.getId()] = c;
	}
}

vector<int> Font::GetValuesOfVariable(string variable) {
	vector<string> numbers = split(m_values[variable], m_NUMBER_SEPARATOR);
	vector<int> actualValues;
	for (int i = 0; i < numbers.size(); i++) {
		actualValues.push_back(stoi(numbers[i]));
	}
	return actualValues;
}

Character Font::LoadCharacter(int imageSize) {
	int id = GetValueOfVariable("id");
	if (id == SPACE_ASCII) {
		m_spaceWidth = (GetValueOfVariable("xadvance") - m_paddingWidth) * m_horizontalPerPixelSize;
		return Character();
	}
	double xTex = ((double)GetValueOfVariable("x") + (m_padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
	double yTex = ((double)GetValueOfVariable("y") + (m_padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
	int width = GetValueOfVariable("width") - (m_paddingWidth - (2 * DESIRED_PADDING));
	int height = GetValueOfVariable("height") - ((m_paddingHeight)-(2 * DESIRED_PADDING));
	double quadWidth = width * m_horizontalPerPixelSize;
	double quadHeight = height * m_verticalPerPixelSize;
	double xTexSize = (double)width / imageSize;
	double yTexSize = (double)height / imageSize;
	double xOff = (GetValueOfVariable("xoffset") + m_padding[PAD_LEFT] - DESIRED_PADDING) * m_horizontalPerPixelSize;
	double yOff = (GetValueOfVariable("yoffset") + (m_padding[PAD_TOP] - DESIRED_PADDING)) * m_verticalPerPixelSize;
	double xAdvance = (GetValueOfVariable("xadvance") - m_paddingWidth) * m_horizontalPerPixelSize;
	double yAdvance = GetValueOfVariable("yadvance");
	return Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance, yAdvance);
}
