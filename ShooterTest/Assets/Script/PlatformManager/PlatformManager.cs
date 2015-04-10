using UnityEngine;
using System.Collections;

public class PlatformManager : MonoBehaviour 
{
	// Use this for initialization
	void Awake()
	{
		#if UNITY_IOS
		m_oPlatformSpecific = new PlatformSpecificIOS();
		#elif UNITY_ANDROID
		m_oPlatformSpecific = new PlatformSpecificAndroid();
		#else
		m_oPlatformSpecific = new PlatformSpecificBase();
		#endif

		m_oPlatformSpecific.InitPlatofrm();
	}

	public float GetShootingInterval()
	{
		if(m_oPlatformSpecific != null)
		{
			return m_oPlatformSpecific.GetShootingInterval();
		}

		Debug.LogError("Null platform specific object");
		return float.MaxValue;
	}

	//VARS
	private PlatformSpecificBase m_oPlatformSpecific;
}
