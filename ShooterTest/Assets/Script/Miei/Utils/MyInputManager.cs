using UnityEngine;
using System.Collections;

public class MyInputManager : MonoBehaviour {

	public delegate void InputEventEmpty();
	public event InputEventEmpty OnJump;
	public delegate void InputEvent(Vector3 endDir);
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
	
	private void ShootDetected(Vector3 endDiretction)
	{
		if(OnShoot != null)
		{
			OnShoot(endDiretction);
		}
	}
	
	private void InitInput()
	{
		m_oInput = MyInputFactory.GetInput(m_eInputSource);
		
		if(m_oInput != null)
		{
			m_oInput.Activate(JumpDetecet, ShootDetected);
		}
	}
	
	public void ChangeInput(eMyInputSource eNewInputSource)
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
	public enum eMyInputSource
	{
		PLAYER = 0,
		AI,
		REPLAY,
		NETWORK,
		COUNT
	}
	
	[SerializeField] private eMyInputSource m_eInputSource = eMyInputSource.PLAYER;
	
	private MyInputBase m_oInput;
}
