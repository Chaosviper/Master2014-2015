using UnityEngine;

public interface Allocable{
	void SetAllocator(Allocator alloc);
	Allocator GetAllocator();

	GameObject GetGameObject();


}
