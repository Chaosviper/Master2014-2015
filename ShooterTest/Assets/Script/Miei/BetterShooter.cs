using UnityEngine;
using System.Collections;

/*
Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico

Shooter - Better Solution
 */

public class BetterShooter : MonoBehaviour 
{
	void Start() 
	{
	}
	
	void Update()
	{
		if(m_fElapsedTime < m_fTimeBetweenShots)
		{
			m_fElapsedTime += Time.deltaTime;
		}
		else if (Input.GetKey(KeyCode.A))
		{
			Debug.Log("explosion");
			m_fElapsedTime = 0.0f;
		}
	}
	
	//VARS
	[SerializeField] private float m_fTimeBetweenShots = 0.5f;

	private float 	m_fElapsedTime = 0.0f;
}
