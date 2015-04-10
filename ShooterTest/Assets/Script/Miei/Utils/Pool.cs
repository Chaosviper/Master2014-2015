using UnityEngine;
using System.Runtime.CompilerServices;
using System.Collections;
using System.Collections.Generic;

public class Pool<U>{

	public Pool(){
		this.m_oElements = null;
		this.m_iNextFreeElement = null;
	}

	public Pool(int capacity, U [] elements){
		//init array and free elements list
		this.m_oElements = elements;
		this.m_iNextFreeElement = new LinkedList<int>();

		//populate the index list
		for(int i = 0;i<this.m_oElements.Length;i++){
			this.m_iNextFreeElement.AddLast(i);
		}
	}

	[MethodImpl(MethodImplOptions.Synchronized)]
	public U getElement(){
		if(this.m_iNextFreeElement.Count > 0){
			int indexNextFree = m_iNextFreeElement.First.Value;
			m_iNextFreeElement.RemoveFirst();
			return this.m_oElements[indexNextFree];
		}else{
			return default(U);
		}
	}

	[MethodImpl(MethodImplOptions.Synchronized)]
	public void freeElement(U element){
		for(int i = 0; i<this.m_oElements.Length; i++){
			if(element.Equals(this.m_oElements[i])){
				this.m_iNextFreeElement.AddLast(i);
			}
		}
	}

	private U [] m_oElements;
	private LinkedList<int> m_iNextFreeElement;
}
