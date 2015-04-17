using UnityEngine;
using System.Collections;

public class MyRotatingObj : MyProjectileExecutable {
	[SerializeField] private float m_fRotationSpeed = 10f;
	private Vector3 m_vRotation = new Vector3(Random.value,Random.value,Random.value);

	public override void Execute(){
		this.m_vRotation = new Vector3(Random.value,Random.value,Random.value);
		base.Execute();
	}

	protected override void ComputeTrajectory(){
		base.ComputeTrajectory();
		this.transform.Rotate(m_vRotation * m_fRotationSpeed * 10 * Time.deltaTime);
	}
}
