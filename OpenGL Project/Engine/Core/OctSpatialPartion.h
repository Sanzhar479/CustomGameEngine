#ifndef OCTSPATIALPARTION_H
#define OCTSPATIALPARTION_H
#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"
constexpr auto CHILDREN_NUMBER = 8;

enum  class OctChildren {
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,
	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR
};

class OctNode {
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_);
	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);
	void AddCollisionObject(GameObject* obj_);
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;
	std::vector<GameObject*> objectList;
private:
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];

	float size;
	static int childNum;
};
class OctSpatialPartion {
public:
	OctSpatialPartion(float worldSize_);
	~OctSpatialPartion();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cel_, Ray ray_);
};
#endif // !OCTSPATIALPARTION_h