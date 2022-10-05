#include "objmesh.h"
#include "vector3d.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"
#include "vertex.h"
#include "texture.h"

ObjMesh::ObjMesh(std::string fileName){
    readFile(fileName);
    mTexture = nullptr;
}

ObjMesh::ObjMesh(std::string fileName, Shader* shader) : VisualObject(shader)
{
    readFile(fileName);
    mMatrix.setToIdentity();
    mTexture = nullptr;
}
ObjMesh::ObjMesh(std::string fileName, Shader* shader, Texture* texture) : VisualObject(shader)
{
    mTexture = texture;

    readFile(fileName);
    mMatrix.setToIdentity();
}
void ObjMesh::init(){
    initializeOpenGLFunctions();
    //Get the model matrix from shader
    mMatrixUniform =  glGetUniformLocation(mShader->getProgram(), "mMatrix");
    //Vertex array object-VAO
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    //Vertex buffer object to hold vertices - VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    //Verts
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //uvs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Element array buffer - EAB
    glGenBuffers(1, &mEAB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEAB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);


    //
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, mTexture->id());
    if(mTexture){
        mTextureUniform = glGetUniformLocation(mShader->getProgram(), "textureSampler");
    }
    glBindVertexArray(0);
}

void ObjMesh::DoPhysics()
{
    qDebug() << "ObjMesh : Called physics!";
}

void ObjMesh::draw(){
    if(mTexture){
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, mTexture->id());
       glUniform1i(mTextureUniform, 0);
    }
    //use my shader
    glUseProgram(mShader->getProgram());
    //Send my model matrix
    mShader->SetUniformMatrix4fv(mMatrix, "mMatrix");
    //Draw object
    glBindVertexArray( mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
void ObjMesh::readFile(std::string filePath){
    std::ifstream file;
    file.open(filePath, std::ifstream::in);
    if(!file){
        qDebug() << "Didnt open file" << QString::fromStdString(filePath);
    }else{
        qDebug() << "Did open file" << QString::fromStdString(filePath);
    }
  ////check if obj file
  std::string copypath = filePath;
  if (copypath.substr(copypath.size() - 4, 4) != ".obj"){
      return;
  }

  ////check if file is not  open
  //if (!file.is_open()){
  //    return; // return if file cant be opened
  //}

    std::vector<Vector3D> tempVertices;
    std::vector<Vector3D> tempNormals;
    std::vector<std::pair<float,float>> tempUVs;

    std::string tmp{};
    std::string type;

    std::string oneLine;
    std::string oneWord;

    unsigned int temp_index = 0;

    while(std::getline(file, oneLine, '\n')){
        //Store one word at a time
        std::stringstream sstream;
        sstream << oneLine;
        //Reset the word
        oneWord = "";
        //Put the sstream word into oneWord
        sstream >> oneWord;

        if(oneWord == "#"){
            //This is a comment, do nothing
            continue;
        }
       //if(type == "m"){
       //    continue;
       //}
       //if(type == "s"){
       //    continue;
       //}
        if(oneWord == ""){
            //Ignores this line
            continue;
        }

        if(oneWord == "v"){
            //Line for vertex positions
            Vector3D tempVertex;
            sstream >> tmp;
            tempVertex.mX = std::stof(tmp);
            sstream >> tmp;
            tempVertex.mY = std::stof(tmp);
            sstream >> tmp;
            tempVertex.mZ = std::stof(tmp);

            tempVertices.push_back(tempVertex);
            continue;
        }
        if(oneWord == "vt"){
            std::pair<float, float> tempUV;
            sstream >> tmp;
            tempUV.first = std::stof(tmp);
            sstream >> tmp;
            tempUV.second = std::stof(tmp);

            tempUVs.push_back(tempUV);
            continue;
        }
        if(oneWord == "vn"){
            //Line for vertex positions
            Vector3D tempNormal;
            sstream >> tmp;
            tempNormal.mX = std::stof(tmp);
            sstream >> tmp;
            tempNormal.mY = std::stof(tmp);
            sstream >> tmp;
            tempNormal.mZ = std::stof(tmp);

            tempNormals.push_back(tempNormal);
            continue;
        }
        if(oneWord == "f"){
            int index, normal, uv;
            //behind f there is 3 words divided by /
            for(int i = 0; i < 3; i++){
                sstream >> oneWord;

                std::stringstream tempWord(oneWord);
                std::string segment;
                std::vector<std::string> segmentArray;
                //Get each number, add them as a string to segment array
                while(std::getline(tempWord, segment, '/')){
                    segmentArray.push_back(segment);
                }
                index = std::stoi(segmentArray[0]);

                //If the uv is blank, set it to 0
                if(segmentArray[1] != ""){
                    uv = std::stoi(segmentArray[1]);
                }else{
                    uv = 0;
                }
                //The normal is the third number, index 2 of the array
                normal = std::stoi(segmentArray[2]);

                //Obj f starts at 1 index, c++ array uses 0 as the starting index
                --index;
                --uv;
                --normal;
                //Check if it has a uv or not
                if(uv > -1){
                    Vertex tempVert(tempVertices[index], tempNormals[normal], tempUVs[uv]);
                    mVertices.push_back(tempVert);

                }else{
                    Vertex tempVert(tempVertices[index], tempNormals[normal], std::pair<float,float>(0,0));
                    mVertices.push_back(tempVert);
                }
                mIndices.push_back(temp_index++);

            }
            continue;
        }

    }
    qDebug() << "Finished reading file" << QString::fromStdString(filePath);
    file.close();
    writeFile(copypath + ".txt");
}

void ObjMesh::writeFile(std::string filePath){
    std::ofstream ut;
       ut.open(filePath.c_str());

       if (ut.is_open())
       {
           auto n = mVertices.size();
           Vertex vertex;
           ut << n << std::endl;
           for (auto it=mVertices.begin(); it != mVertices.end(); it++)
           {
               vertex = *it;
               ut << vertex << std::endl;
           }
           ut.close();
       }

}
