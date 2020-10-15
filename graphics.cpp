#include "graphics.h"

#include <fstream>
#include <vector>
#include <string>

namespace graphics {
    glm::mat4 viewMatrix = glm::mat4(1.0);
    glm::mat4 projectionMatrix = glm::mat4(1.0);
    camera currentCamera;

    /*
    std::vector<vertex> readVertices(const char* filepath)
    {
        std::vector<vertex> vertices;
        std::ifstream fileStream;
        fileStream.open(filepath, std::ifstream::in);
        std::string lineString = "";
        while (std::getline(fileStream, lineString))
        {
            int vertexIndex = 0;
            int indexCurrent = 0;
            int foundIndex = 0;
            vertex newVertex{
                {0.0f, 0.0f, 0.0f},
                {0.0f, 0.0f}
            };
            while (true)
            {
                foundIndex = (lineString.find(',', indexCurrent));
                if (foundIndex == std::string::npos || indexCurrent >= lineString.size())
                {
                    break;
                }
                else
                {
                    std::string floatStr = lineString.substr(indexCurrent, foundIndex);
                    indexCurrent = foundIndex + 1;
                    floatStr.erase(remove(floatStr.begin(), floatStr.end(), ' '), floatStr.end());
                    if (vertexIndex <= 2)
                    {
                        newVertex.position[vertexIndex] = (std::stof(floatStr));
                    }
                    if (vertexIndex > 2)
                    {
                        newVertex.texCoords[vertexIndex - 3] = (std::stof(floatStr));
                    }
                    vertexIndex += 1;
                }
            }
            vertices.push_back(newVertex);
        }
        return vertices;
    }
    */

    /*
    std::vector<float> convertVertexData(std::vector<vertex> vertexVector)
    {
        std::vector<float> returnFloat;
        for (const vertex& vert : vertexVector)
        {
            returnFloat.push_back(vert.position[0]);
            returnFloat.push_back(vert.position[1]);
            returnFloat.push_back(vert.position[2]);
            returnFloat.push_back(vert.texCoords[0]);
            returnFloat.push_back(vert.texCoords[1]);
        }

        return returnFloat;
    }
    */
}


std::string graphics::readFile(const char* filepath)
{
    std::ifstream fileStream;
    fileStream.open(filepath, std::ifstream::in);
    std::string lineString = "";
    std::string fileString = "";
    while (std::getline(fileStream, lineString))
    {
        fileString += lineString + "\n";
    }
    return fileString;
}

std::vector<float> graphics::readFloats(const char* filepath)
{
    std::vector<float> returnFloats;
    std::ifstream fileStream;
    fileStream.open(filepath, std::ifstream::in);
    std::string lineString = "";
    while (std::getline(fileStream, lineString))
    {
        int indexCurrent = 0;
        int foundIndex = 0;
        while (true)
        {
            foundIndex = (lineString.find(',', indexCurrent));
            if (foundIndex == std::string::npos || indexCurrent >= lineString.size())
            {
                break;
            }
            else
            {
                std::string floatStr = lineString.substr(indexCurrent, foundIndex);
                indexCurrent = foundIndex + 1;
                floatStr.erase(remove(floatStr.begin(), floatStr.end(), ' '), floatStr.end());
                returnFloats.push_back(std::stof(floatStr));
            }
        }
    }
    return returnFloats;
}

std::vector<int> graphics::readInts(const char* filepath)
{
    std::vector<int> returnInts;
    std::ifstream fileStream;
    fileStream.open(filepath, std::ifstream::in);
    std::string lineString = "";
    while (std::getline(fileStream, lineString))
    {
        int indexCurrent = 0;
        int foundIndex = 0;
        while (true)
        {
            foundIndex = (lineString.find(',', indexCurrent));
            if (foundIndex == std::string::npos || indexCurrent >= lineString.size())
            {
                break;
            }
            else
            {
                std::string floatStr = lineString.substr(indexCurrent, foundIndex);
                indexCurrent = foundIndex + 1;
                floatStr.erase(remove(floatStr.begin(), floatStr.end(), ' '), floatStr.end());
                returnInts.push_back(std::stoi(floatStr));
            }
        }
    }
    return returnInts;
}

glm::vec3 graphics::rotateVector(float angleRads, glm::vec3 oldVector, glm::vec3 rotationAxis)
{
    glm::vec3 finalVector = glm::vec3(1.0f, 1.0f, 1.0f);
    float rotationMatrix[9] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    rotationMatrix[0] = cos(angleRads) + (rotationAxis.x * rotationAxis.x) * (1 - cos(angleRads));
    rotationMatrix[1] = rotationAxis.x * rotationAxis.y * (1 - cos(angleRads)) - rotationAxis.z * sin(angleRads);
    rotationMatrix[2] = rotationAxis.x * rotationAxis.z * (1 - cos(angleRads)) + rotationAxis.y * sin(angleRads);
    rotationMatrix[3] = rotationAxis.y * rotationAxis.x * (1 - cos(angleRads)) + rotationAxis.z * sin(angleRads);
    rotationMatrix[4] = cos(angleRads) + (rotationAxis.y * rotationAxis.y) * (1 - cos(angleRads));
    rotationMatrix[5] = rotationAxis.y * rotationAxis.z * (1 - cos(angleRads)) - rotationAxis.x * sin(angleRads);
    rotationMatrix[6] = rotationAxis.z * rotationAxis.x * (1 - cos(angleRads)) - rotationAxis.y * sin(angleRads);
    rotationMatrix[7] = rotationAxis.z * rotationAxis.y * (1 - cos(angleRads)) + rotationAxis.x * sin(angleRads);
    rotationMatrix[8] = cos(angleRads) + (rotationAxis.z * rotationAxis.z) * (1 - cos(angleRads));
    finalVector.x = rotationMatrix[0] * oldVector.x + rotationMatrix[1] * oldVector.y + rotationMatrix[2] * oldVector.z;
    finalVector.y = rotationMatrix[3] * oldVector.x + rotationMatrix[4] * oldVector.y + rotationMatrix[5] * oldVector.z;
    finalVector.z = rotationMatrix[6] * oldVector.x + rotationMatrix[7] * oldVector.y + rotationMatrix[8] * oldVector.z;
    return finalVector;
}