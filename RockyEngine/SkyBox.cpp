#include "pch.h"
#include <stb/stb_image.h>
#include "Common.h"
#include "Quad.h"
#include "Mesh.h"
#include "Camera.h"
#include "SkyBox.h"

using namespace Shapes;

SkyBox::SkyBox()
{

}

SkyBox::SkyBox(std::vector<std::string> facePaths)
{
	m_faces = facePaths;
	LoadSkybox();
}

void SkyBox::LoadSkybox()
{
	GL_ATTEMPT(glGenTextures(1, &m_textureID));
	GL_ATTEMPT(glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID));
	
	for (unsigned int i = 0; i < faces; i++)
	{
		unsigned char* data = stbi_load(m_faces[i].c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			LOG_ERROR("Failed to load skybox texture");
			return;
		}
		GL_ATTEMPT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		stbi_image_free(data);
	}
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	skyboxCube = new Mesh(cubeVertices, cubeIndices);
}
void SkyBox::RenderSkyBox(ShaderProgram* m_program)
{
	glm::mat4 view = Application::Instance()->GetCamera()->GetView();
	glm::mat4 projection = Application::Instance()->GetCamera()->GetProj();
	view = glm::mat4(glm::mat3(view));

	glDepthMask(GL_FALSE); // disable depth mask 

	m_program->Use(); // sky shader is shader in use
	m_program->SetUniformMat4("projection", projection);
	m_program->SetUniformMat4("view", view);


	glActiveTexture(GL_TEXTURE0); // set active texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);// binde the texture to use for cube map with texture location

	skyboxCube->Bind();   // render the skybox
	//glDrawElements(GL_TRIANGLES,skyboxCube->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE); // enable the depth mask 

	
}
