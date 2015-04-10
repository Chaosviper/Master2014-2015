using UnityEngine;
using System.Collections;

/*
Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico

Shooter - Platform Specific infos with "using"
 */

public class ShooterUsing : MonoBehaviour 
{
	void Start() 
	{
		m_fShootingTime = PlatformManagerUsing.GetShootingInterval();

		Debug.Log("Platform shooting time = " + m_fShootingTime);
	}
	
	void Update()
	{
		ComputeShoot();
	}

	private void ComputeShoot()
	{
		if(m_fElapsedTime < m_fShootingTime)
		{
			m_fElapsedTime += Time.deltaTime;
		}
		else if (Input.GetKey(KeyCode.A))
		{
			Debug.Log("Shoot!! m_fElapsedTime = " + m_fElapsedTime);
			m_fElapsedTime = 0.0f;
		}
	}

	//VARS
	private float 	m_fElapsedTime = 0.0f;
	private float 	m_fShootingTime = 0.0f;
}
