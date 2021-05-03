#include "CollisionHandler.h"
#include "../Core/CEngine.h"
#include "Ray.h"


std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartion* CollisionHandler::scenePartion = nullptr;

CollisionHandler::CollisionHandler() {
	prevCollisions.reserve(10);
}
CollisionHandler::~CollisionHandler() {
	OnDestroy();
}
CollisionHandler* CollisionHandler::GetInstance() {
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_) {
	prevCollisions.clear();
	scenePartion = new OctSpatialPartion(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_) {
	scenePartion->AddObject(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_) {

	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
		CEngine::GetInstance()->GetScreenWidth(),
		CEngine::GetInstance()->GetScreenHeight(),
		CEngine::GetInstance()->GetCamera());

	if (scenePartion != nullptr) {
		GameObject* hitResult = scenePartion->GetCollision(mouseRay);
		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}
		for (auto c : prevCollisions) {
			if (hitResult != c && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
		}
		prevCollisions.clear();
		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	}
}


void CollisionHandler::OnDestroy() {
	delete scenePartion;
	scenePartion = nullptr;
	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}