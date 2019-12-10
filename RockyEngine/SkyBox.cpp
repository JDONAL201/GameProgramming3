//#include "pch.h"
//#include "SkyBox.h"
//#include <stb/stb_image.h>
//#include "Common.h"
//#include "Quad.h"
//#include "Mesh.h"
//
//
//
//SkyBox::SkyBox(std::vector<std::string> facePaths)
//{
//	//m_faces = facePaths;
//	//LoadSkybox();
//}
//
//void SkyBox::LoadSkybox()
//{
//	//GL_ATTEMPT(glGenTextures(1, &m_textureID));
//	//GL_ATTEMPT(glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID));
//
//	//for (unsigned int i = 0; i < faces; i++)
//	//{
//	//	unsigned char* data = stbi_load(m_faces[i].c_str(), &width, &height, &channels, 0);
//	//	if (!data)
//	//	{
//	//		LOG_ERROR("Failed to load skybox texture");
//	//		return;
//	//	}
//	//	GL_ATTEMPT(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
//	//	stbi_image_free(data);
//	//}
//	//GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//	//GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//	//GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
//	//GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//	//GL_ATTEMPT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//
//}
//void SkyBox::RenderSkyBox(ShaderProgram& shader, Mesh& skyboxCube)
//{
//	//glm::mat4 viewMatrix = sceneCamera->GetView();
//	//glm::mat4 projectionMatrix = sceneCamera->GetProj();
//	//glm::mat4 viewMatrix = Application::Instance()->GetCamera()->GetView();
//	//glm::mat4 projectionMatrix = Application::Instance()->GetCamera()->GetProj();
//	//viewMatrix = glm::mat4(glm::mat3(viewMatrix)); // convert the view matrix into a 3x3 to remove transform values, so the cube can still rotate and scale but not move.Cuts to a 3 and then makes a 4 from the n
//
//	//glDepthMask(GL_FALSE); // disable depth mask 
//
//	//shader->Use(); // sky shader is shader in use
//
//	//	//set uniforms here!
//	//glUniformMatrix4fv(glGetUniformLocation(shader->Get(), std::string("projection").c_str()), 1, GL_FALSE, &projectionMatrix[0][0]);
//	//glUniformMatrix4fv(glGetUniformLocation(shader->Get(), std::string("view").c_str()), 1, GL_FALSE, &viewMatrix[0][0]);
//
//
//	//glActiveTexture(GL_TEXTURE0); // set active texture
//	//glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);// binde the texture to use for cube map with texture location
//
//	//skyboxCube->Bind();   // render the skybox
//	//glDrawElements(GL_TRIANGLES,skyboxCube->GetIndiciesCount(), GL_UNSIGNED_INT, 0);
//	//glDepthMask(GL_TRUE); // enable the depth mask 
//
//	
//}
