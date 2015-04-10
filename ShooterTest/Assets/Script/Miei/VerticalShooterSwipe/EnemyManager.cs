using UnityEngine;
using System.Collections;

public class EnemyManager : MonoBehaviour,Executioner {

	//EXECUTIONER INTERFACE---------------------------------------------------------------
	public void NotifyExecuteEndFail(Executable executable){
		if(this.m_fTimeGeneration > 1f){
			this.m_fTimeGeneration -= 0.1f;
		}
		this.m_oEnemies.FreeElement(executable as EnemyMovement);
	}
	public void NotifyExecuteEndSuccess(Executable executable){
		//Should reset
	}
	//EXECUTIONER INTERFACE---------------------------------------------------------------


	// Use this for initialization
	void Start () {
		//enemies allocator
		this.m_oEnemies = new AllocatorMonoBehaviour<EnemyMovement>(20,enemyPrefab);

		//aggiungo il timer
		this.m_oTimer = gameObject.AddComponent<Timer>();
		//lo registro
		this.m_oTimer.Start(m_fTimeGeneration,GenerateEnemies);
	}

	public void GenerateEnemies(){
		EnemyMovement enemy = this.m_oEnemies.GetElement();
		if(enemy != null){
			enemy.SetExcutioner(this);
			enemy.transform.position = new Vector3(Random.Range(-2.3f,2.3f),6.3f,0f);
			enemy.collider.isTrigger = false;
			enemy.Execute();
		}else{
			Debug.Log("Ops... no enemy!");
		}
		this.m_oTimer.Start(m_fTimeGeneration,GenerateEnemies);
	}

	public GameObject	 									enemyPrefab;
	private AllocatorMonoBehaviour<EnemyMovement>			m_oEnemies;
	[SerializeField] private float							m_fTimeGeneration;
	[SerializeField] private bool							m_bCanGenerate;
	private Timer 											m_oTimer;
}
