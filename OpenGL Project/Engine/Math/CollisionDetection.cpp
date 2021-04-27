#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CEngine.h"

CollisionDetection::~CollisionDetection() {

}

Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_,
	float screenHeight_, Camera* camera_) {
	glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f,
		(mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		-1.0f,
		1.0f);
	glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f,
		(mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		0.0f,
		1.0f);
	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());
	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;
	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;
	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}
bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_) {
	glm::mat4 modelMatrix = box_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->origin;
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;
	float tMin = CEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = CEngine::GetInstance()->GetCamera()->GetFarPlane();
	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	//x
	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z),
		yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z),
		zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	glm::vec3 dotDelta(glm::dot(delta, xAxis),
		glm::dot(delta, yAxis), glm::dot(delta, zAxis));
	glm::vec3 dotDir(glm::dot(rayDirection, xAxis),
		glm::dot(rayDirection, yAxis),
		glm::dot(rayDirection, zAxis));
	if (fabs(dotDir.x) > 0.001f || fabs(dotDir.y) > 0.001f || fabs(dotDir.z) > 0.001f) {
		glm::vec3 t1((dotDelta.x + boxMin.x) / dotDir.y, (dotDelta.y + boxMin.y) / dotDir.y, (dotDelta.z + boxMin.z) / dotDir.z);
		glm::vec3 t2((dotDelta.x + boxMax.x) / dotDir.x, (dotDelta.y + boxMax.y) / dotDir.y, (dotDelta.z + boxMax.z) / dotDir.z);

		if (t1.x > t2.x) {
			float w = t1.x;
			t1.x = t2.x;
			t2.x = w;
		}
		//if (t1.y > t2.y) {
		//	float w = t1.y;
		//	t1.y = t2.y;
		//	t2.y = w;
		//}
		//if (t1.z > t2.z) {
		//	float w = t1.z;
		//	t1.z = t2.z;
		//	t2.z = w;
		//}
		if (t2.x < tMax) {
			tMax = t2.x;
		}
		//if (t2.y < tMax) {
		//	tMax = t2.y;
		//}
		//if (t2.z < tMax) {
		//	tMax = t2.z;
		//}
		if (t1.x > tMin) {
			tMin = t1.x;
		}
		//if (t1.y > tMin) {
		//	tMin = t1.y;
		//}
		//if (t1.z > tMin) {
		//	tMin = t1.z;
		//}
		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if ((-dotDelta.x + boxMin.x > 0.0f || -dotDelta.x + boxMax.x < 0.0f) || (-dotDelta.y + boxMin.y > 0.0f || -dotDelta.y + boxMax.y < 0.0f) || (-dotDelta.z + boxMin.z > 0.0f || -dotDelta.z + boxMax.z < 0.0f)) {

			return true;
		}
	}


	ray_->intersectionDist = tMin;
	return true;
}