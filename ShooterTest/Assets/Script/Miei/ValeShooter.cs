using UnityEngine;
using System.Collections;

/*
Modified by: Valerio Ceraudo, lovely ispired to Bordelands!
Originally based on:

Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico

Excercise: Having trouble figuring out what's causing an intermittent bug. The issue is that sometimes the "explosionA" animation 
will trigger multiple times when either holding the A key or pressing it rapidly, but not always.

Base Solution
 */

public class ValeShooter : MonoBehaviour,Executioner {

	//--------------------Executioner Interface

	//dall'executable potrei in futuro prendere info

	public void NotifyExecuteEndFail(Executable shoot){
		Debug.Log("...mancato!");
//		Debug.Log(shoot.GetPool().ToString());
//		if(shoot.GetPool().Equals(this.m_oDefaultCart)){
//			this.m_oDefaultCart.canFreeOneUsedProjectile(shoot);
//		}else{
//			this.m_oRotatingProjectileCart.canFreeOneUsedProjectile(shoot);
//		}
	}

	public void NotifyExecuteEndSuccess(Executable shoot){
		Debug.Log ("AHAHAHAHAH PRESO!");
//		Debug.Log(shoot.GetPool().ToString());
//		if(shoot.GetPool().Equals(this.m_oDefaultCart)){
//			this.m_oDefaultCart.canFreeOneUsedProjectile(shoot);
//		}else{
//			this.m_oRotatingProjectileCart.canFreeOneUsedProjectile(shoot);
//		}
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
		
		m_fShootingTime = m_oPlatformManager.GetShootingInterval();
		
		Debug.Log("Platform shooting time = " + m_fShootingTime);
		
		//aggiungo il timer
		this.m_oTimer = gameObject.AddComponent<Timer>();
		//lo registro
		this.m_oTimer.Start(m_fShootingTime,AllowShooting);

		//add default cart
		GameObject cartObj = GameObject.Instantiate(defaultProjectileCart) as GameObject;
		//set default cart as child of player
		cartObj.transform.parent = this.transform;
		this.m_oDefaultCart = cartObj.GetComponent<MyCart>();

		//add rotating projectiles cart
		GameObject rotatingProjectilesCart = GameObject.Instantiate(rotatingProjectileCart) as GameObject;
		//set rotating projectiles cart as child of player
		rotatingProjectilesCart.transform.parent = this.transform;
		this.m_oRotatingProjectileCart = rotatingProjectilesCart.GetComponent<MyCart>();
	}

	public void test<T>(T t) where T:MonoBehaviour,Executable{

	}
	
	void Update(){
		ComputeShoot();
	}
	
	private void AllowShooting(){
		this.m_bShootingAllowed = true;
	}
	
	private void ComputeShoot(){
//		if (m_bShootingAllowed && Input.GetKey(KeyCode.A)){
//		
//			m_bShootingAllowed = false;
//			this.m_oTimer.Start(m_fShootingTime,AllowShooting);
//
//			Executable projectile = this.m_oDefaultCart.getProjectile();
//			if(projectile != null){
//				Debug.Log("Shoot!!");
//				projectile.Execute();
//			}else{
//				Debug.Log("NO NO NO NO!!!!! NIENTE PROIETTILE NON ORA!");
//			}
//		}
//		if (m_bShootingAllowed && Input.GetKey(KeyCode.S)){
//			
//			m_bShootingAllowed = false;
//			this.m_oTimer.Start(m_fShootingTime,AllowShooting);
//			
//			Executable projectile = this.m_oRotatingProjectileCart.getProjectile();
//			if(projectile != null){
//				Debug.Log("Shoot Rotating!!");
//				projectile.Execute();
//			}else{
//				Debug.Log("NO NO NO NO!!!!! NIENTE PROIETTILE NON ORA!");
//			}
//		}
	}
	
	//VARS

	public GameObject defaultProjectileCart;
	public GameObject rotatingProjectileCart;

	[SerializeField] private PlatformManager m_oPlatformManager;
	
	private float 	m_fElapsedTime = 0.0f;
	private float 	m_fShootingTime = 0.0f;
	private bool 	m_bShootingAllowed = false;
	private Timer 	m_oTimer;
	private MyCart	m_oDefaultCart;
	private MyCart	m_oRotatingProjectileCart;
}
