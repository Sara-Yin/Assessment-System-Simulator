
#ifndef Schedule_H
#define Schedule_H
#include <vector>
#include "User_Job.h"
#include <iostream>
#include<fstream>
using namespace std;

class Schedule {

public:
	int total_cpu_nodes = 120;
	int total_gpu_nodes = 8;
	int left_cpu_nodes;
	int left_gpu_nodes;
	int avaliable_cpunode(int resource_nodes[128][8]);
	int avaliable_node(int resource_nodes[128][8], int jobType);
	int avaliable_gpunode(int resource_nodes[128][8]);
	void loop_job(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>*  job_queue);
	int next_weekjob_id(int next_weekjob_id, int totalnum_queue, vector<vector<int>>*  job_queue);
	int next_hugejob_id(int next_hugejobid,int totalnum_queue, vector<vector<int>>* job_queue);
	//void job_run(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>*  job_queue);
	void job_connect_node(int resource_nodes[128][8], int job_id, int nodes, int jobType);
	void job_connect_cnode(int resource_nodes[128][8], int job_id, int nodes);
	void job_connect_gnode(int resource_nodes[128][8], int job_id, int nodes);
	int running_weekendjob_num(int totalnum_queue, vector<vector<int>>* job_queue);
	int running_weekjob_num(int totalnum_queue, vector<vector<int>>* job_queue);
	int done_alljob_num(int totalnum_queue, vector<vector<int>>* job_queue);
	void change_jobqueue_time(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>* job_queue);
	void change_resourcequeue_time(int resource_nodes[128][8]);
	//i hour per time, week day has 24*4+8=104,  weekend day has 64
	int week_hours = 104;
	int weekend_hours = 0;// the total hours is 64, but now should give it a initial value;
	int left_weekhours, left_weenkendhours;

	int cpu_num ;
	int gpu_num ;
	int next_weekjobid;
	int next_hugejobid ;
	int continue_nextweek;// the open button to next week
	//int l;

	//result
	int job_done = 0;//1.store the number of jobs processed per week
	int machine_hours = 0;//2. the actual number of machine hours by user jobs
	int user_price = 0;//4.user price  cpu 1 per hour / gpu 2 per hour 
	int wait_time=0; //5.average wait time
	int job_rtime = 0;
	int job_wtime = 0;
	int node_rtime = 0;
	int node_wtime = 0;
	int job_cpurtime = 0;
	int job_gpurtime = 0;
	int job_cpuwtime = 0;
	int job_gpuwtime = 0;
	
};

#endif