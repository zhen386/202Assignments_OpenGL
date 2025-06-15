//
// Created by MacBook on 25-6-10.
//

#ifndef MYMODEL_H
#define MYMODEL_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader_m.h>
#include <myMesh.h>
#include <iostream>

class MyModel
{
public:
	/*  函数   */
	MyModel(char *path)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	/*  模型数据  */
	std::vector<MyMesh> meshes;
	std::string directory;
	/*  函数   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	MyMesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};
#endif //MYMODEL_H
