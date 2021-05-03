#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/gtc/matrix_transform.hpp>
class LightSource

{   
    public:
	LightSource(glm::vec3 position_ = glm::vec3(), float ambience_ = 0.0f,
			float diff_ = 0.0f, float spec_ = 0.0f, glm::vec3 colour_ = glm::vec3());
	~LightSource();
	glm::vec3 GetPosition() const;
	glm::vec3 GetColour() const;
	float GetAmbience() const;
	float GetDiff() const;
	float GetSpec() const;

	void SetPosition(glm::vec3 position_);
	void SetColour(glm::vec3 colour_);
	void SetAmbience(float ambience_);
	void SetDiff(float diff_);
	void SetSpec(float spec_);

private:
	glm::vec3 position;
	glm::vec3 lightColour;
	float ambience = 0.0f;
	float diff = 0.0f;
	float spec = 0.0f;

};
#endif
