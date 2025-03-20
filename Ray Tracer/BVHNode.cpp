#include "BVHNode.h"

//TODO: Fix divide by zero
void BVHNode::hit(const Ray& ray, vector<Triangle*>& _triangles, float& t) const {

	t = -1;

	float tmin = (lower.x - ray.origin.x) / ray.direction.x;
	float tmax = (upper.x - ray.origin.x) / ray.direction.x;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (lower.y - ray.origin.y) / ray.direction.y;
	float tymax = (upper.y - ray.origin.y) / ray.direction.y;

	if (tymin > tymax) swap(tymin, tymax);

	if (tmin > tymax || tymin > tmax) return;

	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;

	float tzmin = (lower.z - ray.origin.z) / ray.direction.z;
	float tzmax = (upper.z - ray.origin.z) / ray.direction.z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if (tmin > tzmax || tzmin > tmax) return;

	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;

	t = (tmin < 0 && tmax > 0) ? tmax : tmin;

	if (t < 0) return;

	_triangles.insert(_triangles.end(), triangles.begin(), triangles.end());

	if (Left == nullptr && Right == nullptr) return;

	float leftT = -1;
	float rightT = -1;
	if (Left != nullptr) Left->hit(ray, _triangles, leftT);
	if (Right != nullptr) Right->hit(ray, _triangles, rightT);


	t = (leftT < 0 && rightT > 0) ? rightT : leftT;

}

BVHNode* BuildBVH(vector<Triangle*>& triangles, Vec3 lower, Vec3 upper) {
	if (triangles.size() == 0) return nullptr;
	if (triangles.size() == 1) {
		BVHNode* node = new BVHNode(triangles);
		node->upper = triangles[0]->upper();
		node->lower = triangles[0]->lower();
		return node;
	}
	if (lower.x >= upper.x || lower.y >= upper.y || lower.z >= upper.z) {
		BVHNode* node = new BVHNode(triangles);
		node->upper = upper;
		node->lower = lower;
		return node;
	}
	Vec3 diff = upper - lower;
	int axis = 0;
	if (diff.y > diff.x && diff.y > diff.z) axis = 1;
	if (diff.z > diff.x) axis = 2;
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
		cout << "Error: left or right size is 0" << endl;
		BVHNode* node = new BVHNode(triangles);
		node->upper = upper;
		node->lower = lower;
		return node;

	}

	BVHNode* node = new BVHNode();
	node->upper = upper;
	node->lower = lower;
	node->Left = BuildBVH(left, leftLower, leftUpper);
	node->Right = BuildBVH(right, rightLower, rightUpper);
	return node;
}

