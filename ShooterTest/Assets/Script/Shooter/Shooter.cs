using UnityEngine;
using System.Collections;

/*
Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico
 */

public class Shooter : MonoBehaviour 
{
	void Start() 
	{
		if(m_oPlatformManager == null)
		{
			Debug.LogWarning("m_oPlatformManager not linked");

			m_oPlatformManager = GameObject.FindObjectOfType<PlatformManager>();

			if(m_oPlatformManager == null)
			{
				Debug.LogError("No PlatformManager in the scene");
				return;
			}
		}

		m_oInptuManager = GameObject.FindObjectOfType<InputManager>();

		if(m_oInptuManager == null)
		{
			Debug.LogError("No InputManager in the scene");
		}

		m_fShootingTime = m_oPlatformManager.GetShootingInterval();

		m_oTimer = gameObject.AddComponent<Timer>();

		m_oTimer.Start(m_fShootingTime, AllowShooting);

		m_oTransform = this.transform;

		CreateProjectiles();
	}

	private void OnEnable()
	{
		if(m_oInptuManager == null)
		{
			m_oInptuManager = GameObject.FindObjectOfType<InputManager>();
			
			if(m_oInptuManager == null)
			{
				Debug.LogError("No InputManager in the scene");
				return;
			}
		}

		m_oInptuManager.OnShoot += ShootDetected;
	}

	private void OnDisable()
	{
		m_oInptuManager.OnShoot -= ShootDetected;
	}

	private void CreateProjectiles()
	{
		m_aoProjectiles = new Projectile[mk_iProjectilesCount];

		for(int i = 0; i < mk_iProjectilesCount; ++i)
		{
			m_aoProjectiles[i] = ((GameObject)GameObject.Instantiate(m_oOriginalProjectile)).GetComponent<Projectile>();
			m_aoProjectiles[i].gameObject.SetActive(false);
		}

		m_oOriginalProjectile.SetActive(false);
	}

	void Update()
	{
		ComputeRotation();
	}

	private void AllowShooting()
	{
		m_bShootingAllowed = true;
	}

	private void ComputeRotation()
	{
		m_oTransform.Rotate(0.0f, 90.0f * Time.deltaTime, 0.0f);
	}

	private void ShootDetected()
	{
		if (m_bShootingAllowed)
		{
			Shoot();
			m_bShootingAllowed = false;
			m_oTimer.Start(m_fShootingTime, AllowShooting);
		}
	}

	private void Shoot()
	{
		if(m_aoProjectiles[m_iNextProjectile].gameObject.activeInHierarchy)
		{
			Debug.LogWarning("Projectile pool size too small!");
		}

		m_aoProjectiles[m_iNextProjectile].gameObject.SetActive(true);
		m_aoProjectiles[m_iNextProjectile].OnProjectileHit += ProjectileCollided;
		m_aoProjectiles[m_iNextProjectile].OnProjectileExpired += ProjectileExpired;
		m_aoProjectiles[m_iNextProjectile].transform.position = m_oTransform.position;
		m_aoProjectiles[m_iNextProjectile].transform.rotation = m_oTransform.rotation;
		m_aoProjectiles[m_iNextProjectile].Shoot(m_oTransform.forward);

		m_iNextProjectile = (m_iNextProjectile + 1) % mk_iProjectilesCount;
	}

	private void ProjectileCollided(Projectile oProjectile, GameObject oHitObject)
	{
		oHitObject.SetActive(false);

		oProjectile.OnProjectileHit -= ProjectileCollided;
		oProjectile.OnProjectileExpired -= ProjectileExpired;

		oProjectile.gameObject.SetActive(false);
	}

	private void ProjectileExpired(Projectile oProjectile)
	{
		oProjectile.OnProjectileHit -= ProjectileCollided;
		oProjectile.OnProjectileExpired -= ProjectileExpired;

		oProjectile.gameObject.SetActive(false);
	}

	//VARS
	[SerializeField] private PlatformManager 	m_oPlatformManager;
	[SerializeField] private GameObject 		m_oOriginalProjectile;

	private float 		m_fShootingTime = 0.0f;
	private bool 		m_bShootingAllowed = false;
	private Timer 		m_oTimer;
	private Transform 	m_oTransform;

	private InputManager 	m_oInptuManager;
	private Projectile[] 	m_aoProjectiles;
	private int 			m_iNextProjectile = 0;
	private const int 		mk_iProjectilesCount = 20;
}
