using UnityEngine;
using System.Collections;
using System;

public class InputBase
{
	public virtual void InputUpdate()
	{
	}

	protected void InternalJumpDetected()
	{
		if(m_actJumpCallback != null)
		{
			m_actJumpCallback();
		}
	}

	protected void InternalShootDetected()
	{
		if(m_actShootCallback != null)
		{
			m_actShootCallback();
		}
	}

	public void Activate(Action actJumpInput, Action actShootInput)
	{
		m_actJumpCallback = actJumpInput;
		m_actShootCallback = actShootInput;

		m_bActive = true;
	}
	
	public void Deactivate()
	{
		m_actJumpCallback = null;
		m_actShootCallback = null;

		m_bActive = false;
	}

	//VARS
	private bool m_bActive = false;

	protected event Action m_actJumpCallback = null;
	protected event Action m_actShootCallback = null;
}
