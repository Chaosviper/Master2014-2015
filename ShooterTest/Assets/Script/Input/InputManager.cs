using UnityEngine;
using System.Collections;

public class InputManager : MonoBehaviour 
{
	public delegate void InputEvent();
	public event InputEvent OnJump;
	public event InputEvent OnShoot;

	void Start()
	{
		InitInput();
	}
	
	void Update()
	{
		if(m_oInput != null)
		{
			m_oInput.InputUpdate();
		}
	}

	private void JumpDetecet()
	{
		if(OnJump != null)
		{
			OnJump();
		}
	}

	private void ShootDetected()
	{
		if(OnShoot != null)
		{
			OnShoot();
		}
	}

	private void InitInput()
	{
		m_oInput = InputFactory.GetInput(m_eInputSource);
		
		if(m_oInput != null)
		{
			m_oInput.Activate(JumpDetecet, ShootDetected);
		}
	}

	public void ChangeInput(eInputSource eNewInputSource)
	{
		if(eNewInputSource != m_eInputSource)
		{
			if(m_oInput != null)
			{
				m_oInput.Deactivate();
				m_oInput = null;
			}

			m_eInputSource = eNewInputSource;

			InitInput(); 
		}
	}

	//VARS
	public enum eInputSource
	{
		PLAYER = 0,
		AI,
		REPLAY,
		NETWORK,
		COUNT
	}
	
	[SerializeField] private eInputSource m_eInputSource = eInputSource.PLAYER;

	private InputBase m_oInput;
}
