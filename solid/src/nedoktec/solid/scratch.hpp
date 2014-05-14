#ifndef __NEDOKTEC_SOLID_SCRATCH_HPP__
#define __NEDOKTEC_SOLID_SCRATCH_HPP__

// Note:
// I barely remember how to write C++. So this is mostly notes for some of the classes i think i'll need.
// I will try to use SDL for all Window, Input, Drawing, Sound and Music, but i don't know much about it yet.

namespace nedoktec {
namespace solid {
namespace scratch {


class UpdateInterface
{
public:
	void Update(TODO delta) = 0;
};


class Application
	: UpdateInterface
{
public:
	int Main();
	void Update(TODO delta) = 0;
protected:
private:
	SceneManager m_scene_manager;
};


class Camera
	: UpdateInterface
{
public:
	/* RayResult CastRay(from, to, maxDepth, load_chunks_if_needed) */
protected:
private:
	Matrix4 m_world_matrix;
	Vector3 m_position;
	Quartonion m_rotation;
	std::shared_ptr<Vector3> m_look_at;
	float m_near_clip;
	float m_far_clip;
	float m_field_of_view;
	float m_aspect;
};


class SceneManager
	: UpdateInterface
{
public:
	std::shared_ptr<Scene> CurrentScene() const;
	void AddScene(const std::shared_ptr<Scene> scene);
	std::shared_ptr<Camera> Camera() const;
protected:
private:
	/* std::shared_ptr<Camera> m_camera; */
	/* std::map<std::string, Scene> m_scenes; */
};


class Scene
	: UpdateInterface
{
public:
	/* RayResult CastRay(from, to, max_depth, load_chunks_if_needed) */

	void Update(TODO delta)
	{
		// foreach chunk in m_active_chunks
		//     chunk->Update()
	}

protected:
private:
	EnvironmentManager m_environment_manager;  // the master environment (eg. biome, ambient sound, fog). chunks can have an override.
	ChunkManager m_chunk_manager;
	std::vector<std::shared_ptr<Chunk>> m_active_chunks;
};


class EnvironmentManager
{
public:
protected:
private:
	std::map<std::string, Environment> m_environments;
};


class Environment
{
public:
protected:
private:
	FogInterface* m_fog;
	/* MusicInterface* m_music; */
	/* SoundInterface* m_ambient; */
};


class Color
{
public:
	UInt32 SetFromChannels(UInt32 red, UInt32 green, UInt32 blue, UInt32 alpha);
	UInt32 GetRGB(Color color, UInt32 alpha);
	UInt32 GetRed(Color color);
	UInt32 GetGreen(Color color);
	UInt32 GetBlue(Color color);
	UInt32 GetAlpha(Color color);
	// blend/lerp?
protected:
private:
};


class MaterialManager
{
public:
protected:
private:
	std::map<std::string, Material> m_materials;
};


class Material
{
public:
protected:
private:
	std::string m_name;
	Color m_diffuse;
	Color m_specular;
	/* float m_shininess; */
	/* float m_reflective; */
	/* float m_refractive; */
};


// an index of normals will be used for voxels.
class NormalManager
{
public:
protected:
private:
	std::map<UInt32, Vector3> m_normals;
};


class FogInterface
{
public:
	Color GetColor(float distance) const = 0;
};


class FogBasic
	: FogInterface
{
public:
protected:
private:
	Color m_color;
};


class FogLinear
	: FogBasic
{
public:
protected:
private:
	float m_min_distance;
	float m_max_distance;
};


class FogExp
	: FogBasic
{
public:
protected:
private:
	float m_exp;
};


class EntityManager
	: UpdateInterface
{
public:
protected:
private:
	std::map<std::string, Entity> m_entities;
};


class Entity
	: UpdateInterface
{
public:
protected:
private:
	std::string m_name;
};


class ChunkManager
	: UpdateInterface
{
public:
	const size_t DefaultChunkDiamater = 16;
	std::shared_ptr<Chunk> Load(Vector3 position);
	void Unload(std::shared_ptr<Chunk> chunk);
protected:
private:
	size_t m_chunk_diameter;
	/* std::queue<std::shared_ptr<Chunk>> m_loading; */
	/* std::queue<std::shared_ptr<Chunk>> m_unloading; */
};


class Chunk
	: UpdateInterface
{
public:
	bool IsLoaded() const;

	void Update(TODO delta)
	{
	}

	/* RayResult Trace(from, to, current_depth, max_depth, initial_radius) */
	/* void SetVoxelAt(const Vector3& pos, UInt32 current_depth, UInt32 max_depth, bool subdivide_if_needed, Color color, UInt16 material_index, UInt16 attributes); */
	/* std::shared_ptr<Voxel> GetVoxelAt(const Vector3& pos, UInt32 current_depth, UInt32 max_depth); */
protected:
private:
	bool m_loaded;
	Matrix4 m_world_matrix;
	Vector3 m_chunk_position;
	std::string m_environment_name;  // a custom environment to override the scene version. (eg. biome, ambient sound, fog)
	EntityManager m_entity_manager;
	Voxel m_root;
};


// memory reduction idea.
// an idea to save 8 potentially empty pointers on a Voxel type.
// TODO: this probably isnt needed. i think you could do the same thing with something like this:
// a pointer to an array of 8 shared_ptr<voxel>'s. i dont remember how to write it in C++.
//     std::shared_ptr<Voxel>*[8] m_children;
class VoxelBranch
{
public:
protected:
private:
	std::shared_ptr<Voxel>[8] m_children;
};


// a voxel should subdivide a chunk into an octree down to a miniumum size.
// but a voxel does not need to subdivide unless at least one child exists or is different.
// eg. a world chunk in the sky could have a single Voxel node to represent the whole volume as an air voxel.
//     as soon as another voxel node is added, the root node will create one level deep child nodes.
//     only the required depth is created when needed, down to a specific limit.
//     not sure if all child nodes get created at once, or just each child node as needed.
class Voxel
	: UpdateInterface
{
public:
	bool IsLeaf() const
	{
		/* return m_children[0] == nullptr */ 
		/* 	&& m_children[1] == nullptr */
		/* 	&& m_children[2] == nullptr */
		/* 	&& m_children[3] == nullptr */
		/* 	&& m_children[4] == nullptr */
		/* 	&& m_children[5] == nullptr */
		/* 	&& m_children[6] == nullptr */
		/* 	&& m_children[7] == nullptr; */

		// memory reduction idea.
		return m_children_branch == nullptr;
	}

	/* RayResult Trace(from, to, current_depth, max_depth, current_radius) */
	/* void SetAt(const Vector3& pos, UInt32 current_depth, UInt32 max_depth, bool subdivide_if_needed, Color color, UInt16 material_index, UInt16 attributes); */
	/* std::shared_ptr<Voxel> GetVoxelAt(const Vector3& pos, UInt32 current_depth, UInt32 max_depth); */

protected:
private:
	void UpdateColor(int max_depth)
	{
		if (max_depth > 0)
		{
			// foreach child in m_children
			//     child.UpdateColor(max_depth - 1);
		}

		// m_color = blend of children colours
	}

	std::weak_ptr<Voxel> m_parent;
	/* std::shared_ptr<Voxel>[8] m_children; */
	std::shared_ptr<VoxelBranch> m_children_branch;    // memory reduction idea.
	Color m_color;
	UInt16 m_material_index;    // good for 65k materials
	UInt16 m_attributes;        // a bit field of many options. eg. Normal index needs at least 5 bits to cover the minimum of ~24 values, (3 side types [faces/edges/corners] * 8 directions of each for a cube). (is there a std::bitfield?)
};


class RayDetail
{
public:
protected:
private:
	const Vector3 m_from_position;
	const Vector3 m_to_position;
};


// rays are cast in jobs across each chunk separatly and a list of results are returned.
// they can then be analysied to find the closed hit distance for an opaque voxel.
// nearer transparrent voxels can then have their colour applied to add volume to lighting and shadows.
// if a ray hits nothing, then just use an opaque Fog colour.
class RayResult
{
public:
protected:
private:
	const RayDetail m_ray_detail;
	float m_hit_distance;
	const std::shared_ptr<Voxel> m_hit_voxel;
};


} // namespace scratch
} // namespace solid
} // namespace nedoktec

#endif // __NEDOKTEC_SOLID_SCRATCH_HPP__
