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
	0 int nid;//node id
	1 string node_type;//0 means cpu  1 means gpu
	2 int resource_status;//0 means waiting, 1 means running;
	3 int resource_wtime;//wait time
	4 int resource_rtime;//running job time
	5 int resource_totaltime;//total running time = wait time+ running job time
	6 int resource_jobindex = -1;//connect with the job array                      
	7 int n_jid;// connect with the job id
	*/

	void Create_Resource(int resource_nodes[128][8]);

};
#endif