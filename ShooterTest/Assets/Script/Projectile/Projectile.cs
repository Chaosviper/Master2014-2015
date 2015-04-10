using UnityEngine;
using System.Collections;
using System;

public class Projectile : MonoBehaviour 
{
	//Add events for hit and expire
	//Add direction set and shoot function
	//Call projectile form Shooter
	public delegate void ProjectileHit(Projectile oProjectile, GameObject oHitObject);
	public delegate void ProjectileExpired(Projectile oProjectile);
	public event ProjectileHit OnProjectileHit;
	public event ProjectileExpired OnProjectileExpired;

	void Start()
	{
	}
	
	void Update()
	{
		if(m_bShooted)
		{
			ComputeTrajectory();
		}
	}

	private void ComputeTrajectory()
	{
		transform.position += m_vDirection * (m_fSpeed * Time.deltaTime);

		m_fElapsedTime += Time.deltaTime;
		if(m_fElapsedTime >= m_fExpiringTime)
		{
			if(OnProjectileExpired != null)
			{
				OnProjectileExpired(this);
			}

			m_bShooted = false;
		}
	}

	public void Shoot(Vector3 vDirection)
	{
		if(m_bShooted)
		{
			Debug.LogWarning("Shooting twice the same projectile");
		}

		//Normalized direction expected
		m_vDirection = vDirection;
		m_bShooted = true;

		m_fElapsedTime = 0.0f;

	}

	void OnCollisionEnter(Collision oCollision) 
	{
		Debug.Log("OnCollisionEnter");
		if(m_bShooted)
		{
			if(OnProjectileHit != null)
			{
				OnProjectileHit(this, oCollision.gameObject);
			}

			m_bShooted = false;
		}
	}

	[SerializeField] private float m_fSpeed = 1.0f;
	[SerializeField] private float m_fExpiringTime = 3.0f;

	private bool 	m_bShooted = false;
	private Vector3 m_vDirection = Vector3.one;

	private float 	m_fElapsedTime = 0.0f;
}
