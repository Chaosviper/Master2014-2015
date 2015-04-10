using UnityEngine;
using System.Collections;

public class Allocator{

	//COSTRUCTOR-----------------------------------
	public Allocator(){}
	/// <summary>
	/// Initializes a new instance of the <see cref="Allocator"/> class.
	/// GameObject.instantiate(prefab)
	/// </summary>
	/// <param name="capacity">Capacity.</param>
	/// <param name="prefab">Prefab.</param>
	public Allocator(int capacity,GameObject prefab){
		this.m_iCapacity = capacity;
		GameObject [] instances = new GameObject[this.m_iCapacity];

		for(int i=0; i<this.m_iCapacity; i++){
			instances[i] = GameObject.Instantiate(prefab) as GameObject;
		}

		this.m_oPool = new Pool<GameObject>(this.m_iCapacity,instances);
	}
	//COSTRUCTOR-----------------------------------


	//PUBLIC METHOD--------------------------------
	public GameObject GetElement(){
		return this.m_oPool.getElement();
	}

	public void FreeElement(GameObject element){
		this.m_oPool.freeElement(element);
	}
	//PUBLIC METHOD--------------------------------


	private Pool<GameObject> m_oPool;
	protected int m_iCapacity;
	public virtual int Capacity{
		get{
			return this.m_iCapacity;
		}
	}
}
