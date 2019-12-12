#include "pch.h"
#include "Common.h"
#include "ShadowMapping.h"

ShadowMapping::ShadowMapping()
{
	m_fbo = 0;
	shadowMap = 0;
}

bool ShadowMapping::Init(GLuint width, GLuint height)
{
	shadowWidth = width;
	shadowHeight = height;


	GL_ATTEMPT(glGenFramebuffers(1, &m_fbo));

	GL_ATTEMPT(glGenTextures(1, &shadowMap));
	GL_ATTEMPT(glBindTexture(GL_TEXTURE_2D, shadowMap));
	GL_ATTEMPT(glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));

	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

	float borderColor[]= { 1.f,1.f,1.f,1.f }; 
	GL_ATTEMPT(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

	GL_ATTEMPT(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
	GL_ATTEMPT(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0));

	GL_ATTEMPT(glDrawBuffer(GL_NONE));
	GL_ATTEMPT(glReadBuffer(GL_NONE));//telling opengl that we are not using the color buffer

	GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (err != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG_ERROR("FRAME BUFFER ERROR");
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void ShadowMapping::Write()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void ShadowMapping::Read(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, shadowMap);



}

ShadowMapping::~ShadowMapping()
{
	if (m_fbo)
	{
		glDeleteFramebuffers(1, &m_fbo);
	}

	if (shadowMap)
	{
		glDeleteTextures(1, &shadowMap);
	}
}
