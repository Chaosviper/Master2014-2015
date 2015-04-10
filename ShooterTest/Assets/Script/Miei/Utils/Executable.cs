using UnityEngine;

public interface Executable{
	void Execute();
	void StopExecute();
	bool IsExecuting();

	void SetExcutioner(Executioner exec);
	void NotifyExecutioner(bool success);

}
