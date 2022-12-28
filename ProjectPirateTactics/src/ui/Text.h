#pragma once
#include "Font.h"
#include "../VertexBuffer.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Transform.h"

class Word {
private:
	vector<Character> characters;
	double width = 0;
	double fontSize;

public:
	Word(double fontSize) {
		this->fontSize = fontSize;
	}

	void addCharacter(Character character) {
		characters.push_back(character);
		width += character.getxAdvance() * fontSize;
	}

	vector<Character> getCharacters() {
		return characters;
	}

	double getWordWidth() {
		return width;
	}
};

class Line {
private:
	double maxLength;
	double spaceSize;

	vector<Word> words;
	double currentLineLength = 0;

public:
	Line(double spaceWidth, double fontSize, double maxLength) {
		spaceSize = spaceWidth * fontSize;
		this->maxLength = maxLength;
	}

	bool attemptToAddWord(Word word) {
		double additionalLength = word.getWordWidth();
		additionalLength += !words.empty() ? spaceSize : 0;
		if (currentLineLength + additionalLength <= maxLength) {
			words.push_back(word);
			currentLineLength += additionalLength;
			return true;
		}
		else {
			return false;
		}
	}

	double getMaxLength() {
		return maxLength;
	}

	double getLineLength() {
		return currentLineLength;
	}

	vector<Word> getWords() {
		return words;
	}
};

class Text
{
private:
	string m_text;
	Font& m_font;
	float m_fontSize;
	float m_lineMaxSize;
	int m_numberOfLines;
	bool m_centerText = false;

	vec2 m_translation = vec2(0.0f, 0.0f);
	vec3 m_color = vec3(1.0f, 1.0f, 1.0f);

	vector<float> m_vertexPositions;
	vector<float> m_textureCoords;

	VertexArray m_Va;
	VertexBuffer m_pb;
	VertexBuffer m_tb;

	vector<Line> CreateStructure();
	void CompleteStructure(vector<Line>& lines, Line* currentLine, Word currentWord);
	void CreateQuadVertices(vector<Line> lines);
	void addVerticesForCharacter(double curserX, double curserY, Character character, double fontSize,
		vector<float>& vertices);
	static void addVertices(vector<float>& vertices, double x, double y, double maxX, double maxY);
	static void addTexCoords(vector<float>& texCoords, double x, double y, double maxX, double maxY);
	void UpdateVertices();

public:
	Text(Font& font, float lineMaxSize, int numberOfLines, string text = "", float fontSize = 1, bool centerText = true);

	string GetText() {
		return m_text;
	}

	void SetText(string text) {
		m_text = text;
		UpdateVertices();
	}

	VertexArray& GetVertexArray() {
		return m_Va;
	}

	vec2 GetTranslation() {
		return m_translation;
	}

	vec3 GetColor() {
		return m_color;
	}

	Font& GetFont() {
		return m_font;
	}

	unsigned int GetVertexCount() {
		return m_vertexPositions.size();
	}

	vector<float> GetVertexPositions() {
		return m_vertexPositions;
	}

	vector<float> GetTextureCoordinates() {
		return m_textureCoords;
	}

	void SetPosition(vec2 position) {
		m_translation = position;
	}
};

