#include <Windows.h>

#include <string.h>
#include <iostream>
#include <iomanip> 

using namespace std;

int main(void)
{
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* processInfoBuffer = NULL;
	DWORD bufferLen = 0;

	if (FALSE == GetLogicalProcessorInformationEx(RelationProcessorCore, processInfoBuffer, &bufferLen)){
		// expected "false" return value
		if (bufferLen <= 0) {
			cout << "GetLogicalProcessorInformationEx failed with error " << GetLastError() << endl;
			return -1;
		}
	}
	processInfoBuffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*) new char[bufferLen];
	if (FALSE == GetLogicalProcessorInformationEx(RelationProcessorCore, processInfoBuffer, &bufferLen)) {
		cout << "GetLogicalProcessorInformationEx failed with error " << GetLastError() << endl;
		return -1;
	}

	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* tmpProcessorInfo = processInfoBuffer;
	int offset = 0;
	int processInfoCount = 0;
	while (true){
		PROCESSOR_RELATIONSHIP pr = tmpProcessorInfo->Processor;
		cout << "core index: " << std::setw(2) <<processInfoCount;
		cout << ", hyper thread support: " << (int)pr.Flags;
		cout << ", efficiency class: " << (int)pr.EfficiencyClass; // higher value = more performant
		cout << endl;
		processInfoCount++;
		offset = offset + tmpProcessorInfo->Size;
		tmpProcessorInfo = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)((char*)processInfoBuffer + offset);
		if (offset >= bufferLen) {
			break;
		}
	}
	delete []processInfoBuffer;
	return 0;
}