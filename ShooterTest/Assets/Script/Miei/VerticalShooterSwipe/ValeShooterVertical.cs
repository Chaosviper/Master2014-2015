using UnityEngine;
using System.Collections;

/*
Modified by: Valerio Ceraudo
Originally based on:

Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico

Excercise: Having trouble figuring out what's causing an intermittent bug. The issue is that sometimes the "explosionA" animation 
will trigger multiple times when either holding the A key or pressing it rapidly, but not always.

Base Solution
 */

public class ValeShooterVertical : MonoBehaviour,Executioner {
	
	//--------------------Executioner Interface
	
	//dall'executable potrei in futuro prendere info
	
	public void NotifyExecuteEndFail(Executable shoot){
		Debug.Log("...mancato!");
		this.m_oProjectiles.FreeElement(shoot as MyProjectileExecutable);
	}
	
	public void NotifyExecuteEndSuccess(Executable shoot){
		this.m_oProjectiles.FreeElement(shoot as MyProjectileExecutable);
	}
	//--------------------Executioner Interface
	
	void Start(){
		if(m_oPlatformManager == null){
			Debug.LogWarning("m_oPlatformManager not linked");
			
			m_oPlatformManager = GameObject.FindObjectOfType<PlatformManager>();
			
			if(m_oPlatformManager == null){
				Debug.LogError("No PlatformManager in the scene");
				return;
			}
		}

		m_oInptuManager = GameObject.FindObjectOfType<MyInputManager>();
		
		if(m_oInptuManager == null)
		{
			Debug.LogError("No InputManager in the scene");
		}

		m_fShootingTime = m_oPlatformManager.GetShootingInterval();
		
		Debug.Log("Platform shooting time = " + m_fShootingTime);
		
		//aggiungo il timer
		this.m_oTimer = gameObject.AddComponent<Timer>();
		//lo registro
		this.m_oTimer.Start(m_fShootingTime,AllowShooting);
		
		//add default cart
		this.m_oProjectiles = new AllocatorMonoBehaviour<MyProjectileExecutable>(5,projectilePrefab);
	}
	
	public void test<T>(T t) where T:MonoBehaviour,Executable{
		
	}
	
	private void AllowShooting(){
		this.m_bShootingAllowed = true;
	}
	
	private void ComputeShoot(Vector3 endPoint){
		m_bShootingAllowed = false;
		this.m_oTimer.Start(m_fShootingTime,AllowShooting);
		
		MyProjectileExecutable projectile = this.m_oProjectiles.GetElement();
		if(projectile != null){
//			Debug.Log("Firing: "+projectile.GetInstanceID());
			projectile.SetExcutioner(this);
			projectile.transform.position = this.transform.localPosition;
			projectile.Direction = (endPoint - projectile.transform.position)/(endPoint - projectile.transform.position).magnitude;

			Vector3 angle = new Vector3(0f,0f,Vector3.Angle(Vector3.up,projectile.Direction));
			projectile.transform.localEulerAngles = angle * Mathf.Sign(Vector3.Cross(Vector3.up, projectile.Direction).z);

			projectile.Execute();
		}else{
			Debug.Log("NO NO NO NO!!!!! NIENTE PROIETTILE NON ORA!");
		}
	}

	private void OnEnable()
	{
		if(m_oInptuManager == null)
		{
			m_oInptuManager = GameObject.FindObjectOfType<MyInputManager>();
			
			if(m_oInptuManager == null)
			{
				Debug.LogError("No InputManager in the scene");
				return;
			}
		}
		
		m_oInptuManager.OnShoot += ComputeShoot;
	}
	
	private void OnDisable()
	{
		m_oInptuManager.OnShoot -= ComputeShoot;
	}

	
	//VARS
	[SerializeField] private PlatformManager 						m_oPlatformManager;
	
	private float 													m_fElapsedTime = 0.0f;
	private float 													m_fShootingTime = 0.0f;
	private bool 													m_bShootingAllowed = false;
	private Timer 													m_oTimer;

	public GameObject	 											projectilePrefab;
	private AllocatorMonoBehaviour<MyProjectileExecutable>			m_oProjectiles;
	private MyInputManager 											m_oInptuManager;
}
