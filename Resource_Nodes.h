#ifndef Resource_Nodes_H
#define Resource_Nodes_H
#include <string>
#include <iostream>
using namespace std;
#define  total_nodes 120;
#define  total_gpu = 8;//gpu is the 15 times faster than the gpu;

class Resource_Nodes {
public:
	/* the columns of the resource nodes array
	int nid;//node id
	string node_type;//0 means cpu  1 means gpu
	int resource_status;//0 means not using, 1 means running;
	int resource_wtime;//wait time
	int resource_rtime;//running job time
	int resource_totaltime;//total running time = wait time+ running job time
	int resource_jobindex = -1;//connect with the job array
	int n_jid;// connect with the job id
	*/

	void Create_Resource(int resource_nodes[128][8]);

};
#endif