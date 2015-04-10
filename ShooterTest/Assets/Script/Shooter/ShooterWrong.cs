using UnityEngine;
using System.Collections;

/*
Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico

Excercise: Having trouble figuring out what's causing an intermittent bug. The issue is that sometimes the "explosionA" animation 
will trigger multiple times when either holding the A key or pressing it rapidly, but not always.

Rewrite the code to solve the problem.
 */
public class ShooterWrong : MonoBehaviour 
{
	void Start() 
	{
		aUsable = true;
		aCooldown = 0.5f;
		aTimer = 0;
	}
	
	void Update()
	{
		CooldownManager();
		Cast();
	}
	
	void Cast() 
	{
		if (Input.GetKey(KeyCode.A) && aUsable)
		{
			Debug.Log("explosion");
			aUsable = false;
		}
	}
	
	void CooldownManager() 
	{
		if (Time.time > aTimer)
		{
			aUsable = true;
			aTimer = Time.time + aCooldown;
		}
	}

	//VARS
	private bool 	aUsable;
	private float 	aCooldown;
	private float 	aTimer;
}
