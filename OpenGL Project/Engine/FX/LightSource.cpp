#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambience_, float diff_ ,float spec_, glm::vec3 colour_ )
	:position(glm::vec3()), lightColour(glm::vec3()), ambience(1.0f), diff(0.0f), spec(0.0f)
{
	position = position_;
	lightColour = colour_;
	ambience = ambience_;
	diff = diff_;
	spec = spec_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

glm::vec3 LightSource::GetColour() const
{
	return lightColour;
}

float LightSource::GetAmbience() const
{
	return ambience;
}

float LightSource::GetDiff() const
{
	return diff;
}

float LightSource::GetSpec() const
{
	return spec;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetColour(glm::vec3 colour_)
{
	lightColour = colour_;
}

void LightSource::SetAmbience(float ambience_)
{
	ambience = ambience_;
}

void LightSource::SetDiff(float diff_)
{
	diff = diff_;
}

void LightSource::SetSpec(float spec_)
{
	spec = spec_;
}
