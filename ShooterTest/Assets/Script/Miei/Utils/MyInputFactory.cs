using UnityEngine;
using System.Collections;

public class MyInputFactory{
	public static MyInputBase GetInput(MyInputManager.eMyInputSource eInputType)
	{
		MyInputBase oInputImplementation = null;
		switch(eInputType)
		{
		case MyInputManager.eMyInputSource.PLAYER:
//			if(Input.touchSupported)
//			{
//				oInputImplementation = new InputPlayerTouch();
//			}
//			else
//			{
				oInputImplementation = new MyInputSwipe();
//			}
			break;
		case MyInputManager.eMyInputSource.AI:
			Debug.LogWarning("AI input not yet available - Replay fallback");
//			oInputImplementation = new InputReplay();
			break;
		case MyInputManager.eMyInputSource.NETWORK:
			Debug.LogWarning("AI network not yet available - Replay fallback");
//			oInputImplementation = new InputReplay();
			break;
		case MyInputManager.eMyInputSource.REPLAY:
			Debug.LogWarning("Replay not yet available - Replay fallback");
//			oInputImplementation = new InputReplay();
			break;
		};
		
		if(oInputImplementation == null)
		{
			Debug.LogError("Input implementation not available!");
		}
		
		return oInputImplementation;
	}
}
