using UnityEngine;
using System.Collections;
using System;

public class MyTimer : MonoBehaviour {
	
	private event Action m_actTimeElapsed = null;

	private void Start(){}
	private void Update(){}

	private void ComputeTimer(){}

	public void Start(float fTime,Action actCallback){
		Start (fTime, actCallback, false, null);
	}

	public void Start(float fTime,Action actCallback,Action actSecUpdateCallback){
		Start (fTime, actCallback, false, actSecUpdateCallback);
	}

	//if bStop is true, stop eventually a timer that is running, otherwise doesn't restart
	public void Start(float fTime,Action actCallback, bool bStop){
		Start (fTime, actCallback, bStop, null);
	}

	public void Start(float fTime,Action actCallback, bool bStop,Action actSecUpdateCallback){
		m_actTimeElapsed = actCallback;
	}

}
