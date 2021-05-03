#include "Camera.h"
#include "../Core/CEngine.h"

Camera::Camera() : position(glm::vec3()), fieldOfView(0.0f), forward(glm::vec3()), up(glm::vec3()),
    right(glm::vec3()), worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f),
    yaw(0.0f), pitch(0.0f), perspective(glm::mat4()), orthographic(glm::mat4()), view(glm::mat4()) 
{

    fieldOfView = 45.0f;
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    worldUp = up;
    nearPlane = 2.0f;
    farPlane = 50.0f;
    yaw = -90.0f;
    pitch = 0.0f;

    
    perspective = glm::perspective(fieldOfView,
        CEngine::GetInstance()->GetScreenWidth() /
        CEngine::GetInstance()->GetScreenHeight(),
        nearPlane, farPlane);

    orthographic = glm::ortho(0.0f, CEngine::GetInstance()->GetScreenWidth(),
        0.0f, CEngine::GetInstance()->GetScreenHeight(),
        -1.0f, 1.0f);
    UpdateCameraVector();
}

Camera::~Camera()
{
    if (lightSources.size() > 0)
    {
        for (auto l : lightSources)
        {
            delete l;
            l = nullptr;
        }
        lightSources.clear();
    }
}

void Camera::SetPosition(glm::vec3 position_)
{
    position = position_;
    UpdateCameraVector();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
    yaw = yaw;
    pitch = pitch;
    UpdateCameraVector();
}

void Camera::AddLightSource(LightSource* lightSource_)
{
    lightSources.push_back(lightSource_);
}

std::vector<LightSource*> Camera::GetLightList()
{
    return lightSources;
}


glm::mat4 Camera::GetView() const
{
    return view;
}

glm::mat4 Camera::GetPerspective() const
{
    return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
    return orthographic;
}

glm::vec3 Camera::GetPosition()
{
    return position;
}

void Camera::UpdateCameraVector()
{
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    forward = glm::normalize(forward);
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
    view = glm::lookAt(position, position + forward, up);
}

void Camera::ProcessMouseMovement(glm::vec2 offset_) {
    offset_ *= 0.05f;
    pitch += offset_.y;
    yaw += offset_.x;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    if (yaw > 0.0f) {
        yaw += 360.0f;
    }
    if (yaw < 360.0f) {
        yaw -= 360.0f;
    }
    UpdateCameraVector();
}


float Camera::GetNearPlane() const {
    return nearPlane;
}
float Camera::GetFarPlane() const {
    return farPlane;
}
void Camera::ProcessMouseZoom(int y_) {
    if (y_ < 0 || y_ > 0) {
        position += static_cast<float>(y_) * (forward * 2.0f);
    }
    UpdateCameraVector();
}