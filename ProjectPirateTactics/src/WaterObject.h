#pragma once
#include "GameObject.h"
#include "FrameBuffer.h"
#include "WaterRenderer.h"

class WaterObject : public GameObject
{
private:
	FrameBuffer m_reflectionBuffer;
	FrameBuffer m_refractionBuffer;
	WaterRenderer m_renderer;

	Object3D& m_waterQuad;
	Transform m_transform;
	Shader& m_shader;
protected:
	void Update(){}

public:
	WaterObject(Camera& camera, int reflectionWidth, int reflectionHeight, int refractionWidth, int refractionHeight, Object3D& quad, Shader& waterShader) : 
		m_reflectionBuffer(FrameBuffer(reflectionWidth, reflectionHeight, DepthBuffer(reflectionWidth, reflectionHeight))),
		m_refractionBuffer(FrameBuffer(refractionWidth, refractionHeight, Texture(refractionWidth, refractionHeight, NULL, GL_DEPTH_COMPONENT32))),
		m_waterQuad(quad), m_shader(waterShader), m_transform(Transform()), 
		m_renderer(WaterRenderer(camera, quad, m_transform, waterShader, m_reflectionBuffer.GetTexture(), m_refractionBuffer.GetTexture())) {}

public:
	void Tick() {

		//m_reflectionBuffer.Bind();
		m_renderer.Draw();
		//m_reflectionBuffer.Unbind();

		Update();
	}

	void Clear() { m_renderer.Clear(); }

	Transform& GetTransform() { return m_transform; }

	FrameBuffer& GetReflectionBuffer() { return m_reflectionBuffer; }
	FrameBuffer& GetRefractionBuffer() { return m_refractionBuffer; }
};

