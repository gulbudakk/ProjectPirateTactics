#pragma once

class Character {
private:
	int m_id;
	double m_xTextureCoord;
	double m_yTextureCoord;
	double m_xMaxTextureCoord;
	double m_yMaxTextureCoord;
	double m_xOffset;
	double m_yOffset;
	double m_sizeX;
	double m_sizeY;
	double m_xAdvance;
	double m_yAdvance;

public:
	Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize,
		double xOffset, double yOffset, double sizeX, double sizeY, double xAdvance, double yAdvance) {
		this->m_id = id;
		this->m_xTextureCoord = xTextureCoord;
		this->m_yTextureCoord = yTexSize + yTextureCoord + (yAdvance / 100);
		this->m_xOffset = xOffset;
		this->m_yOffset = yOffset;
		this->m_sizeX = sizeX;
		this->m_sizeY = sizeY;
		this->m_xMaxTextureCoord = xTexSize + xTextureCoord;
		this->m_yMaxTextureCoord = yTextureCoord + (yAdvance / 100);
		this->m_xAdvance = xAdvance;
		this->m_yAdvance = (yAdvance / 100);
	}

	Character(){}

	int getId() {
		return m_id;
	}

	double getxTextureCoord() {
		return m_xTextureCoord;
	}

	double getyTextureCoord() {
		return m_yTextureCoord;
	}

	double getXMaxTextureCoord() {
		return m_xMaxTextureCoord;
	}

	double getYMaxTextureCoord() {
		return m_yMaxTextureCoord;
	}

	double getxOffset() {
		return m_xOffset;
	}

	double getyOffset() {
		return m_yOffset;
	}

	double getSizeX() {
		return m_sizeX;
	}

	double getSizeY() {
		return m_sizeY;
	}

	double getxAdvance() {
		return m_xAdvance;
	}
};

