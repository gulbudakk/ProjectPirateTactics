#include "Text.h"

Text::Text(Font& font, float lineMaxSize, int numberOfLines, string text, float fontSize, bool centerText) : m_font(font), m_text(text), m_fontSize(fontSize), m_lineMaxSize(lineMaxSize), m_numberOfLines(numberOfLines), m_centerText(centerText) {
	UpdateVertices();
}

void Text::UpdateVertices() {
	m_vertexPositions.clear();
	m_textureCoords.clear();

	vector<Line> lines = CreateStructure();
	CreateQuadVertices(lines);

	m_Va.Bind();

	 m_pb = VertexBuffer(m_vertexPositions, m_vertexPositions.size() * sizeof(float));
	 m_tb = VertexBuffer(m_textureCoords, m_textureCoords.size() * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(m_pb.GetID(), 2);
	m_Va.AddBuffer(m_pb, layout);

	layout.Push<float>(m_tb.GetID(), 2);
	m_Va.AddBuffer(m_tb, layout);
	
}

vector<Line> Text::CreateStructure() {
	vector<Line> lines;
	Line* currentLine = new Line(m_font.getSpaceWidth(), m_fontSize, m_lineMaxSize);
	Word* currentWord = new Word(m_fontSize);

	for (unsigned int i = 0; i < m_text.length(); i++) {
		int ascii = (int)m_text[i];
		if (ascii == m_font.GetSpaceAscii()) {
			bool added = currentLine->attemptToAddWord(*currentWord);
			if (!added) {
				lines.push_back(*currentLine);
				currentLine = new Line(m_font.getSpaceWidth(),m_fontSize, m_lineMaxSize);
				currentLine-> attemptToAddWord(*currentWord);
			}
			currentWord = new Word(m_fontSize);
			continue;
		}
		Character character = m_font.GetCharacter(ascii);
		currentWord->addCharacter(character);
	}
	CompleteStructure(lines, currentLine, *currentWord);
	return lines;
}

void Text::CompleteStructure(vector<Line>& lines, Line* currentLine, Word currentWord) {
	bool added = currentLine->attemptToAddWord(currentWord);
	if (!added) {
		lines.push_back(*currentLine);
		currentLine = new Line(m_font.getSpaceWidth(), m_fontSize, m_lineMaxSize);
		currentLine->attemptToAddWord(currentWord);
	}
	lines.push_back(*currentLine);
}

void Text::CreateQuadVertices(vector<Line> lines) {
	m_numberOfLines = lines.size();

	double curserX = 0;
	double curserY = 0;

	for (Line line : lines) {
		if (m_centerText) {
			curserX = (line.getMaxLength() - line.getLineLength()) / 2;
		}
		for (Word word : line.getWords()) {
			for (Character letter : word.getCharacters()) {
				addVerticesForCharacter(curserX, curserY, letter, m_fontSize, m_vertexPositions);
				addTexCoords(m_textureCoords, letter.getxTextureCoord(), letter.getyTextureCoord(),
					letter.getXMaxTextureCoord(), letter.getYMaxTextureCoord());
				curserX += letter.getxAdvance() * m_fontSize;
			}
			curserX += m_font.getSpaceWidth() * m_fontSize;
		}
		curserX = 0;
		curserY += m_font.GetLineHeight() * m_fontSize;
	}
}

void Text::addVerticesForCharacter(double curserX, double curserY, Character character, double fontSize,
	vector<float>& vertices) {
	double x = curserX + (character.getxOffset() * fontSize);
	double y = curserY + (character.getyOffset() * fontSize);
	double maxX = x + (character.getSizeX() * fontSize);
	double maxY = y + (character.getSizeY() * fontSize);
	double properX = (2 * x) - 1;
	double properY = (-2 * y) + 1;
	double properMaxX = (2 * maxX) - 1;
	double properMaxY = (-2 * maxY) + 1;
	addVertices(vertices, properX, properY, properMaxX, properMaxY);
}

void Text::addVertices(vector<float>& vertices, double x, double y, double maxX, double maxY) {
	vertices.push_back((float)x);
	vertices.push_back((float)y);
	vertices.push_back((float)x);
	vertices.push_back((float)maxY);
	vertices.push_back((float)maxX);
	vertices.push_back((float)maxY);
	vertices.push_back((float)maxX);
	vertices.push_back((float)maxY);
	vertices.push_back((float)maxX);
	vertices.push_back((float)y);
	vertices.push_back((float)x);
	vertices.push_back((float)y);
}

void Text::addTexCoords(vector<float>& texCoords, double x, double y, double maxX, double maxY) {
	texCoords.push_back((float)x);
	texCoords.push_back((float)y);
	texCoords.push_back((float)x);
	texCoords.push_back((float)maxY);
	texCoords.push_back((float)maxX);
	texCoords.push_back((float)maxY);
	texCoords.push_back((float)maxX);
	texCoords.push_back((float)maxY);
	texCoords.push_back((float)maxX);
	texCoords.push_back((float)y);
	texCoords.push_back((float)x);
	texCoords.push_back((float)y);
}