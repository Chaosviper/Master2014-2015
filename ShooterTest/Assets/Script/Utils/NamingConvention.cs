using UnityEngine;
using System.Collections;

/*
Università di Verona - Master Videogame programming 2015
Corso Mobile programming - Roberto Mangiafico

Naming convention for code

- Varibles and functions named in English
- CamelCase for variables and functions 
- "m_typeName" for member class variables
- "s_typeName" for static variables
- "mk_typeName" for member const variables
- "_typeName" for local varibles

*/
public class NamingConvention : MonoBehaviour 
{
	void Start()
	{
		m_aiMyArray = new int[mk_iMyConst];
	}
	
	void Update()
	{
	
	}

	private void MyFooFunction(int iFunctionVar)
	{
		m_iMyInt = iFunctionVar;
	}

	//VARS
	private bool 	m_bMyFlag = false;
	private int 	m_iMyInt = 0;
	private float 	m_fMyFloat = 0.0f;
	private string 	m_sMyString = "Hello!";

	private enum eMyEnum
	{
		NONE = 0,
		FOO,
		FOO_TWO,
		COUNT
	}

	private eMyEnum m_eMyEnumValue = eMyEnum.FOO;

	private int[] m_aiMyArray;

	private const int mk_iMyConst = 10;

	private static float s_fMyStaticFloat = 1.0f;

	[SerializeField] private float m_fMyExposedFloat = 2.0f;
	[HideInInspector] public float m_fMyPrivateFloat = 2.0f;
}
