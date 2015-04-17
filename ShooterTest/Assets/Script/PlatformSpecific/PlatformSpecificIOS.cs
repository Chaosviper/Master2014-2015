using UnityEngine;
using System.Collections;

public class PlatformSpecificIOS : PlatformSpecificBase
{
	#if UNITY_IOS
	public override void InitPlatofrm()
	{
		base.InitPlatofrm();
		Debug.Log("IOS Init");
	}
	
	public override float GetShootingInterval()
	{
		return mk_fShootingInterval;
	}
	
	private const float mk_fShootingInterval = 0.5f;
	#endif
}
