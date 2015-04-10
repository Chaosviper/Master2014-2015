using UnityEngine;
using System.Collections;

public class MyCart : MonoBehaviour{
	
//	// Use this for initialization
//	void Start () {
//		this.m_OPool = new Pool<Executable>();
//		this.m_Owner = this.gameObject.transform.parent.gameObject.GetComponent<ValeShooter>();
//
//		Executable [] temp = new Executable[m_ICapacity];
//		for(int i = 0; i<m_ICapacity; i++){
//
//			//set Go projectiles child of cart's owner, set MyProjectile script as owned by this cart
//			GameObject instantiated = (GameObject) GameObject.Instantiate(ProjectileType);
//			instantiated.transform.parent = this.gameObject.transform.parent;
//
//			temp[i] = instantiated.GetComponent<MyProjectileExecutable>();
//			temp[i].SetExcutioner(this.m_Owner);
//		}
//		this.m_OPool = new Pool<Executable>(m_ICapacity,temp);
//	}
//
//	public Executable getProjectile(){
//		Executable projectile = this.m_OPool.getElement();
//		return projectile;
//	}
//
//	//this method can be inherited: this is the standard, if projectile impacts it is istantaneally reloaded
//	public void canFreeOneUsedProjectile(Executable projectile){
//		projectile.StopExecute();
//		this.m_OPool.freeElement(projectile);
//	}
//
//	public GameObject ProjectileType;
//	public int m_ICapacity;
//	
//	private Executioner m_Owner;
//	private Pool<Executable> m_OPool;
}
