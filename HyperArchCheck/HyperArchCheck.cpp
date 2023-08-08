#include <Windows.h>

#include <string.h>
#include <iostream>
#include <iomanip> 
#include <sstream>

using namespace std;



void crash_test()
{
	int* dummy_crash = (int*)100;
	dummy_crash[0] = 1024;
}
int main(void)
{
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* processInfoBuffer = NULL;
	DWORD bufferLen = 0;

	if (FALSE == GetLogicalProcessorInformationEx(RelationAll, processInfoBuffer, &bufferLen)){
		// expected "false" return value
		if (bufferLen <= 0) {
			cout << "GetLogicalProcessorInformationEx failed with error " << GetLastError() << endl;
			return -1;
		}
	}
	processInfoBuffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*) new char[bufferLen];
	if (FALSE == GetLogicalProcessorInformationEx(RelationAll, processInfoBuffer, &bufferLen)) {
		cout << "GetLogicalProcessorInformationEx failed with error " << GetLastError() << endl;
		return -1;
	}

	// crash_test();
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* tmpProcessorInfo = processInfoBuffer;
	int offset = 0;

	while (true) {
		switch (tmpProcessorInfo->Relationship)
		{
		case _LOGICAL_PROCESSOR_RELATIONSHIP::RelationCache:
			cout << "Relationship: RelationCache: ";
			CACHE_RELATIONSHIP cr = tmpProcessorInfo->Cache;
			cout << "Associativity->" << (int)cr.Associativity << ",CacheSize->" << cr.CacheSize 
				<< ",GroupMask.Mask->" << cr.GroupMask.Mask << ",GroupMask.Group->" << cr.GroupMask.Group
				<< ",Level->" << (int)cr.Level << ",LineSize->" << cr.LineSize << ",Type->" << cr.Type << endl;
			break;
		case _LOGICAL_PROCESSOR_RELATIONSHIP::RelationGroup:
			cout << "Relationship: RelationGroup: ";
			GROUP_RELATIONSHIP gr = tmpProcessorInfo->Group;
			cout << "ActiveGroupCount->" << gr.ActiveGroupCount
				<< ",GroupInfo.ActiveProcessorCount->" << (int)gr.GroupInfo->ActiveProcessorCount << ",GroupInfo.ActiveProcessorMask->" << gr.GroupInfo->ActiveProcessorMask << ",GroupInfo.MaximumProcessorCount->" << (int)gr.GroupInfo->MaximumProcessorCount
				<< ",MaximumGroupCount->" << gr.MaximumGroupCount << endl;
			break;
		case _LOGICAL_PROCESSOR_RELATIONSHIP::RelationNumaNode:
			cout << "Relationship: RelationNumaNode: ";
			NUMA_NODE_RELATIONSHIP nr = tmpProcessorInfo->NumaNode;
			cout << "GroupMask.Group->" << nr.GroupMask.Group << ",GroupMask.Mask->" << nr.GroupMask.Mask
				<< ",NodeNumber->" << nr.NodeNumber << endl;
			break;
		case _LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorCore:
			cout << "Relationship: RelationProcessorCore: ";
			PROCESSOR_RELATIONSHIP pr = tmpProcessorInfo->Processor;
			cout << "EfficiencyClass->" << (int)pr.EfficiencyClass << ",Flags->" << (int)pr.Flags // EfficiencyClass 1 is big core, 0 is small core
				<< ",GroupCount->" << pr.GroupCount << ",GroupMask.Group->" << pr.GroupMask->Group << ",GroupMask.Mask->" << std::to_string(pr.GroupMask->Mask) << endl;
			break;
		case _LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorPackage:
			cout << "Relationship: RelationProcessorPackage: " << endl;
			break;
		}
		offset = offset + tmpProcessorInfo->Size;
		tmpProcessorInfo = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)((char*)processInfoBuffer + offset);
		if (offset >= bufferLen) {
			break;
		}
	}
	delete[]processInfoBuffer;
	return 0;
}