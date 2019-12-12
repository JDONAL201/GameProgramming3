#pragma once
class ShadowMapping
{
public:

	ShadowMapping();

	virtual bool Init(GLuint width, GLuint height);
	virtual void Write();
	virtual void Read(GLenum textureUnit);

	GLuint GetShadowWidth() { return shadowWidth; }
	GLuint GetShadowHeight() { return shadowHeight; }

	~ShadowMapping();

protected:
	GLuint m_fbo, shadowMap;
	GLuint shadowWidth, shadowHeight;
};

