using UnityEngine;
using System.Collections;

public class MyProjectileExecutable : MonoBehaviour,Executable,Allocable{

	//---------------EXECUTABLE INTERFACE
	public virtual void Execute(){
		this.m_tStartingExecutionTime = 0;
		this.enabled = true;
	}

	public void StopExecute(){
		this.enabled = false;
	}

	public bool IsExecuting(){
		return this.enabled;
	}

	public void SetExcutioner(Executioner exec){
		this.m_iExecutioner = exec;
	}

	public void NotifyExecutioner(bool success){
		if(this.m_iExecutioner != null && this.IsExecuting()){
			this.transform.position = new Vector3(100f,100f,0f);
			if(success){
				this.m_iExecutioner.NotifyExecuteEndSuccess(this);
			}else{
				this.m_iExecutioner.NotifyExecuteEndFail(this);
			}
		}
	}
	//---------------EXECUTABLE INTERFACE

	//---------------ALLOCABLE INTERFACE
	public void SetAllocator(Allocator alloc){
		this.m_oAllocator = alloc;
	}
	public Allocator GetAllocator(){
		return this.m_oAllocator;
	}
	public GameObject GetGameObject(){
		return this.gameObject;
	}
	//---------------ALLOCABLE INTERFACE

	// Use this for initialization
	void Start () {
		m_vDirection = this.transform.up;
		this.m_fTimeToLife = 5f;
		this.m_fSpeed = 5f;
		this.StopExecute();
	}
	
	// Update is called once per frame
	void Update () {
		this.m_tStartingExecutionTime += Time.deltaTime;
		if(m_tStartingExecutionTime < this.m_fTimeToLife){
			ComputeTrajectory();
		}else{
			this.StopExecute();
			this.NotifyExecutioner(false);
		}
	}

	void OnTriggerEnter(Collider other){
		if(other.tag.Equals("Target")){
			this.NotifyExecutioner(true);
		}
	}
	
	protected virtual void ComputeTrajectory(){
		this.transform.position += m_vDirection * (m_fSpeed * Time.deltaTime);
	}

	[SerializeField] protected float 		m_fSpeed;
	[SerializeField] private Vector3	m_vDirection;
	public Vector3 Direction{
		get {
			return this.m_vDirection;
		}
		set{
			this.m_vDirection = value;
		}
	}

	//this is the starting value of projectile's life
	[SerializeField] private float		m_fTimeToLife;
	private float 						m_tStartingExecutionTime = 0f;
	private Executioner					m_iExecutioner;
	private Allocator 					m_oAllocator;
}
