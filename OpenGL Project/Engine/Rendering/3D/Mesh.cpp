#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertexList_, GLuint textureID_, GLuint shaderProgram_)
	:VAO(0), VBO(0), vertexList(std::vector<Vertex>()), shaderProgram(0),textureID(0),
	modelLoc(0),viewLoc(0),projectionLoc(0),textureLoc(0)
{
	textureID = textureID_;
	vertexList = vertexList_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}
Mesh::~Mesh() {

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	vertexList.clear();
}
void Mesh::Render(Camera* camera_, glm::mat4 transform_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	
	glBindVertexArray(VAO);
	glEnable(GL_DEPTH_TEST);
   
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_));
	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
  
	glBindVertexArray(0);
	
}
void Mesh::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex),
		&vertexList[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, textureCoordinates));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, colour));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	position = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPos = glGetUniformLocation(shaderProgram, "position");
	lightAmb = glGetUniformLocation(shaderProgram, "ambience");
	lightDiff = glGetUniformLocation(shaderProgram, "diff");
	lightSpec = glGetUniformLocation(shaderProgram, "spec");
	lightColour = glGetUniformLocation(shaderProgram, "lightColour");
}