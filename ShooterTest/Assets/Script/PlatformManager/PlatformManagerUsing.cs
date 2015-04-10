using UnityEngine;
using System.Collections;

#if UNITY_IOS
using PlatformSpecific = PlatformSpecificUsingIOS;
#elif UNITY_ANDROID
using PlatformSpecific = PlatformSpecificUsingAndroid;
#else
using PlatformSpecific = PlatformSpecificUsingPC;
#endif

public class PlatformManagerUsing 
{
	private static void InitPlatform()
	{
		PlatformSpecific.InitPlatofrm();
		
		s_bInitialized = true;
	}

	public static float GetShootingInterval()
	{
		if(!s_bInitialized)
		{
			InitPlatform();
		}

		return PlatformSpecific.GetShootingInterval();
	}


	//VARS
	private static bool s_bInitialized = false;
}
