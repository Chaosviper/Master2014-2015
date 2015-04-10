using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;

public class Timer : MonoBehaviour{	

	private void Start(){}

	// Update is called once per frame
	private void Update(){
		if(m_bRunning && !m_bPaused){
			ComputeTimer();
		}
	}
	
	private void ComputeTimer(){
		m_fElapsedTime += Time.deltaTime;
		m_fSecondTime += Time.deltaTime;

		//si può accumulare ritardo sul timer dovuto a drop ad esempio, quindi tolgo -1 per normalizzare ed accumulo il ritardo
		if((m_actSecUpdate != null) && (m_fSecondTime >= 1f)){
			m_actSecUpdate();
			m_fSecondTime -= 1.0f;
		}
		
		if(m_fElapsedTime >= m_fDuration){
			FinishTimer();
		}
	}
	
	public void FinishTimer(){
		m_bRunning = false;
			
		if(m_actTimeElapsed != null){
			m_actTimeElapsed();
		}	
	}
	
	public void Start(float fTime, Action actCallBack){
		Start(fTime, actCallBack, false, null);
	}
	
	public void Start(float fTime, Action actCallBack, Action actSecUpdateCallBack){
		Start(fTime, actCallBack, false, actSecUpdateCallBack);
	}
	
	public void Start(float fTime, Action actCallBack, bool bStop){
		Start(fTime, actCallBack, bStop, null);
	}
	
	public void Start(float fTime, Action actCallBack, bool bStop, Action actSecUpdateCallBack){
		if(!m_bRunning || bStop){
            if(fTime == 0){
                actCallBack();
                return;
            }

			m_fElapsedTime = 0.0f;
			m_fSecondTime = 0.0f;
			m_fDuration = fTime;
			
			m_actTimeElapsed = actCallBack;
			m_actSecUpdate = actSecUpdateCallBack;
			
			m_bRunning = true;
			m_bPaused = false;
		}
	}
	
	public float GetActualTime(){
		return 	m_fElapsedTime;
	}
	
	public float GetRemainingTime(){
		return 	m_fDuration - m_fElapsedTime;
	}
	
	public void Discard(){
		m_bRunning = false;
		m_bPaused = false;
		m_actTimeElapsed = null;
		m_actSecUpdate = null;
	}
	
	public void Pause(){
		m_bPaused = true;
	}
	
	public void UnPause(){
		m_bPaused = false;
	}
	
	private bool 	m_bRunning = false;
	public bool IsRunning{
		get { return m_bRunning; }
	}
	
	private bool 	m_bPaused = false;
	public bool IsPaused{
		get { return m_bPaused; }
	}
	
	private float 	m_fElapsedTime = 0.0f;
	private float	m_fSecondTime = 0.0f;
	private float 	m_fDuration = 0.0f;
	
	private event Action m_actTimeElapsed = null;
	private event Action m_actSecUpdate = null;
}