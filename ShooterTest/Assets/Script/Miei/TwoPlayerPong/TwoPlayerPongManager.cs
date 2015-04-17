using UnityEngine;
using System.Collections;

public class TwoPlayerPongManager : MonoBehaviour {
	
	public GameObject BallPrefab;

	// Use this for initialization
	void Start () {
		float screenWidth = Screen.width;
		float screenHeight = Screen.height;

		GameObject ballInstance = GameObject.Instantiate(this.BallPrefab) as GameObject;

		Vector3 worldPos = Camera.main.ScreenToWorldPoint(new Vector3(screenWidth,screenHeight,0f));
		worldPos.z = 0f;
		ballInstance.transform.position = worldPos;
	}
	
	// Update is called once per frame
	void Update () {
	
	}



}
