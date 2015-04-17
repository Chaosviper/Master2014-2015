using UnityEngine;
using System.Collections;

public class PlatformSpecificUsingPC 
{
#if UNITY_EDITOR
	
	public static void InitPlatofrm()
	{
		Debug.Log("Init PC platform");
	}
	
	public static float GetShootingInterval()
	{
		return s_fShootInterval;
	}
	
	
	private static float s_fShootInterval = 0.66f;
	#endif
}
