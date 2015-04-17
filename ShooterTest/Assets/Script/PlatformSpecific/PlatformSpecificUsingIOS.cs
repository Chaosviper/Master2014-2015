using UnityEngine;
using System.Collections;

public class PlatformSpecificUsingIOS
{
	#if UNITY_IOS

	public static void InitPlatofrm()
	{
		Debug.Log("Init IOS platform");
	}

	public static float GetShootingInterval()
	{
		return s_fShootInterval;
	}


	private static float s_fShootInterval = 0.33f;
	#endif
}
