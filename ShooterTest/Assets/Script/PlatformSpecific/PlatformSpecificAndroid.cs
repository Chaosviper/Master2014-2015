using UnityEngine;
using System.Collections;

public class PlatformSpecificAndroid : PlatformSpecificBase 
{
#if UNITY_ANDROID
	public override void InitPlatofrm()
	{
		base.InitPlatofrm();
		Debug.Log("Android Init");
	}
	
	public override float GetShootingInterval()
	{
		return mk_fShootingIntervalAndroid;
	}
	
	private const float mk_fShootingIntervalAndroid = 0.99f;
#endif
}
