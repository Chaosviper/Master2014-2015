using UnityEngine;
using System.Collections;

public class EnemyMovement : MonoBehaviour,Executable,Allocable {

	//EXECUTABLE INTERFACE-------------------
	[SerializeField] private Executioner 	m_oExecutioner;

	public void Execute(){
		this.m_fLife = 0f;
		this.m_bCollided = false;
		this.enabled = true;
	}
	public void StopExecute(){
		this.enabled = false;
	}
	public bool IsExecuting(){
		return this.enabled;
	}	
	public void SetExcutioner(Executioner exec){
		this.m_oExecutioner = exec;
	}
	public void NotifyExecutioner(bool success){
		if(success){
			this.m_oExecutioner.NotifyExecuteEndSuccess(this);
		}else{
			this.collider.isTrigger = true;
			this.transform.position = new Vector3(100f,100f,0);
			this.m_oExecutioner.NotifyExecuteEndFail(this);
		}
	}
	//EXECUTABLE INTERFACE-------------------

	//ALLOCABLE INTERFACE--------------------
	[SerializeField] private Allocator		m_oAllocatorOwner;

	public void SetAllocator(Allocator alloc){
		this.m_oAllocatorOwner = alloc;
	}
	public Allocator GetAllocator(){
		return this.m_oAllocatorOwner;
	}
	
	public GameObject GetGameObject(){
		return this.gameObject;
	}
	//ALLOCABLE INTERFACE--------------------

	// Use this for initialization
	void Start () {
		this.m_bCollided = false;
		this.StopExecute();
		this.m_fSpeed = 1.5f;
		this.m_fTimeToLife = 10f;
	}
	
	// Update is called once per frame
	void Update () {
		this.MoveEnemy();
	}

	private void MoveEnemy(){
		this.m_fLife += Time.deltaTime;
		if(this.m_fLife > this.m_fTimeToLife){
			this.StopExecute();
			this.NotifyExecutioner(false);
		}

		this.m_vDirection = Vector3.down;
		if(this.transform.position.y < 0f){
			this.m_vDirection.x = -Mathf.Lerp(this.transform.position.x, 0f, 0.001f);
		}
		this.transform.Translate(this.m_vDirection*Time.deltaTime*this.m_fSpeed);
	}

	private void OnTriggerEnter(Collider other){
		if(!this.m_bCollided && other.tag.Equals("Projectile")){
			this.m_bCollided = true;
			this.StopExecute();
			this.NotifyExecutioner(false);
		}
	}

	private void OnCollisionEnter(Collision other){
		if(!this.m_bCollided && other.gameObject.tag.Equals("Player")){
			this.m_bCollided = true;
			this.StopExecute();
			this.NotifyExecutioner(true);
		}
	}

	[SerializeField] private Vector3 		m_vDirection;
	[SerializeField] private float 			m_fSpeed;
	[SerializeField] private float 			m_fTimeToLife;
	[SerializeField] private float 			m_fLife;
	[SerializeField] private bool			m_bCollided;
}
