using UnityEngine;
using System.Collections;

public class InputFactory 
{
	public static InputBase GetInput(InputManager.eInputSource eInputType)
	{
		InputBase oInputImplementation = null;

		switch(eInputType)
		{
		case InputManager.eInputSource.PLAYER:
			if(Input.touchSupported)
			{
				oInputImplementation = new InputPlayerTouch();
			}
			else
			{
				oInputImplementation = new InputPlayerKeyboard();
			}
			break;
		case InputManager.eInputSource.AI:
			Debug.LogWarning("AI input not yet available - Replay fallback");
			oInputImplementation = new InputReplay();
			break;
		case InputManager.eInputSource.NETWORK:
			Debug.LogWarning("AI network not yet available - Replay fallback");
			oInputImplementation = new InputReplay();
			break;
		case InputManager.eInputSource.REPLAY:
			oInputImplementation = new InputReplay();
			break;
		};

		if(oInputImplementation == null)
		{
			Debug.LogError("Input implementation not available!");
		}

		return oInputImplementation;
	}
}
