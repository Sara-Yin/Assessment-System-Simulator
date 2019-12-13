#include "Resource_Nodes.h"

void Resource_Nodes::Create_Resource(int resource_nodes[128][8]) {
	
	for (int i = 0; i < 128; i++) {
		resource_nodes[i][0] = i + 1; //id
		if (i < 120) {
			resource_nodes[i][1] = 0;//node type
			//cout << "resource cpu node "<<i<<": " << resource_nodes[i][1] << endl;
		}
		else {
			resource_nodes[i][1] = 1;
			//cout << "resource gpu node " << i << ": " << resource_nodes[i][1] << endl;
		}

		resource_nodes[i][2] = 0; //resource status
		resource_nodes[i][3] = 0;//wait time
		resource_nodes[i][4] = 0;//running job time
		resource_nodes[i][5] = 0;//total running time
		resource_nodes[i][6] = -1;//connect with the job array 可能无用
		resource_nodes[i][7] = -1;//connect with the job id

	}
}