#include "Schedule.h"

int Schedule::avaliable_cpunode (int resource_nodes[128][8]) {
	int c_num = 0;
	for (int i = 0; i < 120; i++) {
		if (resource_nodes[i][2] == 0) {
			c_num = c_num + 1;
		}	
	}
	return c_num;
}

int Schedule::avaliable_gpunode(int resource_nodes[128][8]) {
	int g_num = 0;
	for (int i = 120; i < 128; i++) {
		if (resource_nodes[i][2] == 0) {
			g_num = g_num + 1;
		}
	}
	return g_num;
};

int Schedule::next_hugejob_id(int totalnum_queue, vector<vector<int>>  job_queue) {
	for (int i = 0; i < totalnum_queue; i++) {
		if (job_queue[i][5] == 0 && (job_queue[i][4] !=5)) {
			return i;  //the order of the job
			break;
		}
		else {
			return -1;
			cout << "All jobs finished." << endl;
		}
	}
}

int Schedule::next_weekjob_id(int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = 0; i < totalnum_queue; i++) {
		if (job_queue[i][5] == 0 && job_queue[i][4] == 5) {
			return i;  //the order of the job
			break;
		}
		else {
			return -1;
			cout << "All jobs finished." << endl;
		}
	}
}



void Schedule::loop_job(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = 0; i < totalnum_queue;i++) {
		int cpu_num = avaliable_cpunode(resource_nodes); //how many available cpu
		int gpu_num= avaliable_gpunode(resource_nodes);//how many available gpu
		int next_weekjobid = next_weekjob_id(totalnum_queue, job_queue);
		int next_hugejobid = next_hugejob_id(totalnum_queue, job_queue);
		if (next_weekjobid < 0 && next_hugejobid<0) {
			cout << "All jobs are running or finished." << endl;
			exit(1);
		}
		
		if (week_hours > 0) {    //weekday
			if (job_queue[next_weekjobid][4] == 4 ) {    //gpu resource
				if (job_queue[next_weekjobid][3]> 8) {
					cout << "the job "<< next_weekjobid<<" is not available one, because its nodes more than 8 GPU."<<endl;

				}else if (job_queue[next_weekjobid][3]> gpu_num){
					job_wait();
					resource_wait();
				}
				else {
					job_run();
					resource_run();
				}
			}
			else {

			}



			week_hours = week_hours - 1;
			if (week_hours == 0) {
				weekend_hours = 64;
			}
		}
		else if (week_hours == 0 && weekend_hours > 0) {




			weekend_hours = weekend_hours - 1;
			if (weekend_hours == 0) {
				week_hours = 104;
			}
		}

	}

	left_weekhours=week_hours-1;
	if (left_weekhours>0){//weekday
		loop_job(resource_nodes, totalnum_queue, job_queue);
	}
	else {//weekend

	}


}


void Schedule::job_wait() {
	cout << "job wait" << endl;
};
void Schedule::resource_wait() {
	cout << "resource wait" << endl;
};
void Schedule::job_run() {
	cout << "job run" << endl;
};
void Schedule::resource_run() {
	cout << "job wait" << endl;
};