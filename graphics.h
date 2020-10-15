#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics
{

	std::string readFile(const char* filepath);
	std::vector<float> readFloats(const char* filepath);
	std::vector<int> readInts(const char* filepath);
	glm::vec3 rotateVector(float angleRads, glm::vec3 oldVector, glm::vec3 rotationAxis);

	extern glm::mat4 viewMatrix;
	extern glm::mat4 projectionMatrix;

	class shape {
	public:
		enum type { quad, circle , sphere, geoSphere };

		std::vector<float> vertexData;
		std::vector<int> indexData;

		float width, height, depth = 1.0f;
		int detail = 1;
		float capHeight = 1.0f; //height of a cap of sphere
		std::string geoSphereImageLoc;

		void reload(type shapeType);

		shape();
	};

	class object
	{
	public:
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		std::vector<float> vertexData;
		std::vector<int> indexData;
		std::string textureLocation;

		unsigned int vertexArrayObject;
		unsigned int indexBuffer;
		unsigned int textureObject;
	};

	class file_object : public object
	{
	public:
		file_object(const char* vertexDataLocation, const char* indexDataLocation, const char* textureDataLocation);

		void load();
	};

	class shape_object : public object
	{
	public:
		shape* shapeObjectPtr;

		shape_object(shape* shapeObj, const char* textureDataLocation);

		void loadTexture();
		void reloadShape();
	};


	class renderer {
	public:
		static int buildShaderProgram(const char* vertexSource, const char* fragmentSource);
		static void render(object obj, unsigned int shaderProgram);
	};

	class camera {
	public:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		float cameraYaw = -90.0f;
		float cameraPitch = 0.0f;
		float cameraRoll = 0.0f;

		void update();
	};

	extern camera currentCamera;

};

