using UnityEngine;
using System.Collections;

public class PlatformSpecificBase 
{
	public virtual void InitPlatofrm()
	{
		Debug.Log("Base Init");
	}

	public virtual float GetShootingInterval()
	{
		return mk_fShootingInterval;
	}

	private const float mk_fShootingInterval = 0.33f;
}
