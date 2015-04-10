using UnityEngine;
using System.Collections;

public class MyInputSwipe : MyInputBase {

	private bool swiping;
	private Vector3 swipeStartPosition;
	private Vector3 swipeEndPosition;

	public override void InputUpdate(){
		base.InputUpdate();
		
		if(Input.GetMouseButtonDown(0)){
			this.swipeStartPosition =  Camera.main.ScreenToWorldPoint(Input.mousePosition);
			this.swipeStartPosition.z = 0;
		}


		if(Input.GetMouseButtonUp(0)){
			this.swipeEndPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
			this.swipeEndPosition.z = 0;
			if(Mathf.Abs(this.swipeStartPosition.x)<1f && 
			   this.swipeStartPosition.y<-2f && this.swipeStartPosition.y>-4f &&
			   this.swipeEndPosition.y>-4f &&
			   Vector3.Distance(this.swipeStartPosition,this.swipeEndPosition) > 1.5f){
				Debug.DrawLine(this.swipeStartPosition,this.swipeEndPosition,Color.red);
				base.InternalShootDetected(this.swipeEndPosition);
			}
		}
	}
}
