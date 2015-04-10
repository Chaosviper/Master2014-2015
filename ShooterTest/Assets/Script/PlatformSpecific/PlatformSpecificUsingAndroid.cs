using UnityEngine;
using System.Collections;

public class PlatformSpecificUsingAndroid
{

	#if UNITY_ANDROID
	
	public static void InitPlatofrm()
	{
		Debug.Log("Init Android platform");
	}
	
	public static float GetShootingInterval()
	{
		return s_fShootInterval;
	}
	
	
	private static float s_fShootInterval = 0.5f;
	#endif
}
