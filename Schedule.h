
#ifndef Schedule_H
#define Schedule_H
#include <vector>
#include "User_Job.h"
using namespace std;

class Schedule {

public:
	int total_cpu_nodes = 120;
	int total_gpu_nodes = 8;
	int left_cpu_nodes;
	int left_gpu_nodes;
	int avaliable_cpunode(int resource_nodes[128][8]);
	int avaliable_gpunode(int resource_nodes[128][8]);
	void loop_job(int resource_nodes[128][8], int totalnum_queue, vector<vector<int> >  job_queue);
	int next_weekjob_id(int totalnum_queue, vector<vector<int> >  job_queue);
	int next_hugejob_id(int totalnum_queue, vector<vector<int> >  job_queue);
	void job_wait();
	void resource_wait();
	void job_run();
	void resource_run();

	//i hour per time, week day has 24*4+8=104,  weekend day has 64
	int week_hours = 104;
	int weekend_hours = 64;
	int left_weekhours, left_weenkendhours;
	
	
};

#endif