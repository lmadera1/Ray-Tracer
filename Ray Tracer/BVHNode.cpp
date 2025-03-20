#include "BVHNode.h"

//TODO: Fix divide by zero
float BVHNode::hit(const Ray& ray, vector<Triangle*>& _triangles) const {

	float tmin = (lower.x - ray.origin.x) / ray.direction.x;
	float tmax = (upper.x - ray.origin.x) / ray.direction.x;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (lower.y - ray.origin.y) / ray.direction.y;
	float tymax = (upper.y - ray.origin.y) / ray.direction.y;

	if (tymin > tymax) swap(tymin, tymax);

	if (tmin > tymax || tymin > tmax) return -1;

	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;

	float tzmin = (lower.z - ray.origin.z) / ray.direction.z;
	float tzmax = (upper.z - ray.origin.z) / ray.direction.z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if (tmin > tzmax || tzmin > tmax) return -1;

	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;

	float t = (tmin < 0 && tmax > 0) ? tmax : tmin;

	if (t < 0) return t;

	_triangles.insert(_triangles.end(), triangles.begin(), triangles.end());

	//Return time if leaf node else continue
	if (Left == nullptr && Right == nullptr) return t;

	float leftT = -1;
	float rightT = -1;
	if (Left != nullptr) leftT = Left->hit(ray, _triangles);
	if (Right != nullptr) rightT = Right->hit(ray, _triangles);


	return (leftT < 0 && rightT > 0) ? rightT : leftT;
}

BVHNode* BuildBVH(vector<Triangle*>& triangles, Vec3 lower, Vec3 upper, int _axis) {
	if (triangles.size() == 0) return nullptr;
	if (triangles.size() == 1) {
		BVHNode* node = new BVHNode(triangles);
		node->upper = triangles[0]->upper();
		node->lower = triangles[0]->lower();
		return node;
	}
	if (lower.x >= upper.x && lower.y >= upper.y && lower.z >= upper.z) {
		BVHNode* node = new BVHNode(triangles);
		node->upper = upper;
		node->lower = lower;
		return node;
	}
	Vec3 diff = upper - lower;
	int axis = _axis;
	if (axis != 0 && axis != 1 && axis != 2) {
		axis = 0;
		if (diff.y > diff.x && diff.y > diff.z) axis = 1;
		if (diff.z > diff.x) axis = 2;
	}

	
	float mid = (upper.get(axis) + lower.get(axis)) / 2;

	Vec3 leftLower = Vec3(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
	Vec3 leftUpper = Vec3(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());
	Vec3 rightLower = Vec3(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
	Vec3 rightUpper = Vec3(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());

	vector<Triangle*> left;
	vector<Triangle*> right;

	for (Triangle* triangle : triangles) {

		Vec3 centroid = triangle->centroid();

		if (centroid.get(axis) < mid) {
			left.push_back(triangle);
			leftLower = Vec3(
				min(leftLower.x, triangle->lower().x),
				min(leftLower.y, triangle->lower().y),
				min(leftLower.z, triangle->lower().z)
			);
			leftUpper = Vec3(
				max(leftUpper.x, triangle->upper().x),
				max(leftUpper.y, triangle->upper().y),
				max(leftUpper.z, triangle->upper().z)
			);
		}
		else {
			right.push_back(triangle);
			rightLower = Vec3(
				min(rightLower.x, triangle->lower().x),
				min(rightLower.y, triangle->lower().y),
				min(rightLower.z, triangle->lower().z)
			);
			rightUpper = Vec3(
				max(rightUpper.x, triangle->upper().x),
				max(rightUpper.y, triangle->upper().y),
				max(rightUpper.z, triangle->upper().z)
			);
		}
	}

	if (left.size() == 0 || right.size() == 0) {
		if (_axis != 0 && _axis != 1 && _axis != 2) {
			int tempAxis = (axis + 1) % 3;
			BVHNode* altSplit = BuildBVH(triangles, lower, upper, tempAxis);

			if (altSplit != nullptr && altSplit->triangles.size() == 0) return altSplit;
			delete altSplit;
			tempAxis = (axis + 2) % 3;
			BVHNode* altSplit2 = BuildBVH(triangles, lower, upper, tempAxis);

			if (altSplit2 != nullptr && altSplit2->triangles.size() == 0) return altSplit2;
			delete altSplit2;

			BVHNode* node = new BVHNode(triangles);
			node->upper = upper;
			node->lower = lower;
			return node;
			


			
		}

		else {
			return nullptr;
		}

	}

	BVHNode* node = new BVHNode();
	node->upper = upper;
	node->lower = lower;
	node->Left = BuildBVH(left, leftLower, leftUpper, -1);
	node->Right = BuildBVH(right, rightLower, rightUpper, -1);
	return node;
}

