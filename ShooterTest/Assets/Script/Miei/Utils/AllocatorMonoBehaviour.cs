using UnityEngine;
using System.Collections;

public class AllocatorMonoBehaviour<T>: Allocator where T: MonoBehaviour,Allocable {

	//COSTRUCTOR-----------------------------------
	public AllocatorMonoBehaviour(){}
	/// <summary>
	/// Initializes a new instance of the <see cref="Allocator"/> class.
	/// GameObject.instantiate(prefab)
	/// </summary>
	/// <param name="capacity">Capacity.</param>
	/// <param name="prefab">Prefab.</param>
	public AllocatorMonoBehaviour(int capacity,GameObject prefab){
		base.m_iCapacity = capacity;
		T [] instances = new T[this.m_iCapacity];
		
		for(int i=0; i<base.m_iCapacity; i++){
			GameObject temp = GameObject.Instantiate(prefab) as GameObject;
			if(temp.GetComponent<T>() == null){
				temp.AddComponent<T>();
			}
			instances[i] = temp.GetComponent<T>();
		}
		
		this.m_oPool = new Pool<T>(this.m_iCapacity,instances);
	}
	//COSTRUCTOR-----------------------------------
	
	
	//PUBLIC METHOD--------------------------------
	new public T GetElement(){
		return this.m_oPool.getElement();
	}
	
	public void FreeElement(T element){
		this.m_oPool.freeElement(element);
	}
	//PUBLIC METHOD--------------------------------
	
	
	private Pool<T> m_oPool;
}
