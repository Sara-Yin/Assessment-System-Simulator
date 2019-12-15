#include "Schedule.h"

int Schedule::avaliable_cpunode(int resource_nodes[128][8]) {
	int c_num = 0;
	for (int i = 0; i < 120; i++) {
		if (resource_nodes[i][2] == 0) {
			c_num = c_num + 1;
		}
	}
	return c_num;
}

int Schedule::avaliable_node(int resource_nodes[128][8], int jobType) {
	int c_num = 0;
	int left = 0, right = 128;
	// Small Job node 0 to 12
	if (jobType == 1) {
		right = 12;
	}
	// Medium node 12 to 48
	else if (jobType == 2) {
		left = 12;
		right = 48;
	}
	else if (jobType == 3) {
		left = 48;
		right = 120;
	}
	else if (jobType == 4) {
		left = 120;
	}

	for (int i = left; i < right; i++) {
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
}

int Schedule::next_hugejob_id(int next_hugejobid,int totalnum_queue, vector<vector<int>>*  job_queue) {
	for (int i = next_hugejobid; i <= totalnum_queue; i++) {

		if (i == totalnum_queue || i==-1) {
			return -1;
			break;
		}
		if (job_queue->at(i)[5] == 0 && (job_queue->at(i)[4]/10 == 5)) {
			return i;
			break;
		}
	}
}

int Schedule::next_weekjob_id(int next_weekjobid, int totalnum_queue, vector<vector<int>>*  job_queue) {

	for (int i = next_weekjobid; i <= totalnum_queue; i++) {

		if (i == totalnum_queue ||i==-1) {
			return -1;
			break;
		}
		if (job_queue->at(i)[5] == 0 && job_queue->at(i)[4]/10 != 5) {
			return i; 
			break;
		}

	}
}


int Schedule::running_weekjob_num(int totalnum_queue, vector<vector<int>>*  job_queue) {

	for (int i = 0; i <= totalnum_queue; i++) {

		if (i == totalnum_queue) {
			return -1;

			break;
		}
		if (job_queue->at(i)[5] == 1 && job_queue->at(i)[4]/10 != 5) {
			return i;  
			break;
		}

	}
}

int Schedule::running_weekendjob_num(int totalnum_queue, vector<vector<int>>*  job_queue) {

	for (int i = 0; i <= totalnum_queue; i++) {

		if (i == totalnum_queue) {
			return -1;

			break;
		}
		if (job_queue->at(i)[5] == 1 && job_queue->at(i)[4]/10 == 5) {
			return i;  
			break;
		}

	}
}

int Schedule::done_alljob_num(int totalnum_queue, vector<vector<int>>*  job_queue) {
	//l = -1;
	for (int i = 0; i <totalnum_queue; i++) {
		
		if (job_queue->at(i)[5] != 2  ) {
			return i;
			break;
		}
		

	}
	return -1;
}


void Schedule::loop_job(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>*  job_queue) {
	next_weekjobid = 0;
	next_hugejobid = 0;
	int time = 0;
	do {
		if (weekend_hours == 0 && week_hours > 0) {//weekday
			next_weekjobid = next_weekjob_id(next_weekjobid,totalnum_queue, job_queue);

			if (next_weekjobid != -1) {  //has waiting job
				for (int a = next_weekjobid; a < totalnum_queue; a++) {  //if the available resource is enough, run all the jobs
					
					next_weekjobid = next_weekjob_id(next_weekjobid,totalnum_queue, job_queue);
					if (next_weekjobid < 0) {
						break;
					}else{
					cpu_num = avaliable_node(resource_nodes, job_queue->at(next_weekjobid)[4]);
					}
					if (job_queue->at(next_weekjobid)[3] > cpu_num || (job_queue->at(next_weekjobid)[6]> week_hours)) {
						break;
					}
					else {
						job_queue->at(next_weekjobid)[5] = 1;
						job_connect_node(resource_nodes, next_weekjobid, job_queue->at(next_weekjobid)[3], job_queue->at(next_weekjobid)[4]);
						
					}
				}
			
			}
	

			week_hours = week_hours - 1;
			if (week_hours == 0) {
				weekend_hours = 64;
			}
		}
		else if (week_hours == 0 && weekend_hours > 0) {//weekenday

			next_hugejobid = next_hugejob_id(next_hugejobid,totalnum_queue, job_queue);

			if (next_hugejobid != -1) {  //has waiting job
				for (int a = next_hugejobid; a < totalnum_queue; a++) {  //if there is available nodes, make the jobs run
					next_hugejobid = next_hugejob_id(next_hugejobid, totalnum_queue, job_queue);
					if (next_hugejobid != -1 && job_queue->at(next_hugejobid)[4] == 52) {    //gpu resource
						gpu_num = avaliable_gpunode(resource_nodes);//how many available gpu
				
						if (job_queue->at(next_hugejobid)[3] > gpu_num) {							
							break;
						}
						else {
							job_queue->at(next_hugejobid)[5] = 1;
							job_connect_gnode(resource_nodes, next_hugejobid, job_queue->at(next_hugejobid)[3]);
						}
					}
					else if ( next_hugejobid != -1 &&  job_queue->at(next_hugejobid)[4]==51 ) {  //cpu resource
						cpu_num = avaliable_cpunode(resource_nodes);
						if (job_queue->at(next_hugejobid)[3] > cpu_num) {
							break;
						}
						else {
							job_queue->at(next_hugejobid)[5] = 1;
							job_connect_cnode(resource_nodes, next_hugejobid, job_queue->at(next_hugejobid)[3]);
						}
					}

				}
			}

			weekend_hours = weekend_hours - 1;
			
			if (weekend_hours == 0) {
				//print_result(resource_nodes, time, totalnum_queue, job_queue);
				//exit(0);
				break;
			}
		}

		///*running process*///
		change_resourcequeue_time(resource_nodes);
		change_jobqueue_time(resource_nodes, totalnum_queue, job_queue);
		time++;

		//print_result(resource_nodes, time, totalnum_queue, job_queue);
		//print the result

		if (done_alljob_num(totalnum_queue, job_queue) == -1 || weekend_hours ==0||(job_queue->at(next_hugejobid)[3] > cpu_num && running_weekendjob_num(totalnum_queue, job_queue) == -1)) {
			cout << "print result" << endl;
			for (int i = 0; i < totalnum_queue; i++) {
				job_rtime = job_rtime + job_queue->at(i)[7];
				job_wtime = job_wtime + job_queue->at(i)[9];
				cout << "job_queue->at(i)[5]" << job_queue->at(i)[5] << endl;
				if (job_queue->at(i)[5] == 2) {
					cout << "进入循环计算结果" << job_done << endl;
					job_done = job_done + 1;
					cout << "job_done" << job_done << endl;
					machine_hours += job_queue->at(i)[7] * job_queue->at(i)[3];
					if (job_queue->at(i)[4] == 4 || job_queue->at(i)[4] == 52) {
						job_gpurtime += job_queue->at(i)[7];
						job_gpuwtime += job_queue->at(i)[9];
						job_queue->at(i)[10] = job_queue->at(i)[7] * job_queue->at(i)[3] * 2;

					}
					else {
						job_cpurtime += job_queue->at(i)[7];
						job_cpuwtime += job_queue->at(i)[9];
						job_queue->at(i)[10] = job_queue->at(i)[7] * job_queue->at(i)[3];//each user paid price
					}
				}
				user_price += job_queue->at(i)[10];
			}

			for (int i = 0; i < 128; i++) {
				node_rtime = node_rtime + resource_nodes[i][4];
				node_wtime = node_wtime + resource_nodes[i][3];
			}

			cout << "the number of jobs processed per week: " << job_done << endl;
			cout << "the actual number of machine hours consumed by users jobs: " << machine_hours << endl;
			cout << "the utilization rtio: " << machine_hours / (time * 24 * 128) << endl;
			cout << "the price paid by users: " << user_price << endl;
			cout << "average wait time in each queue: " << job_wtime << endl;
			cout << "average turnaround time ratio: " << (job_wtime + job_rtime) / job_rtime << endl;
			cout << "economic balance of the centre: " << user_price << endl;

			ofstream wFile;
			wFile.open("result.txt");
			if (!wFile.is_open()) {
				cout << "ERROR: not open the file" << endl;
				exit(0);
			}
			wFile << "the number of jobs processed per week: " << job_done << endl;
			wFile << "the actual number of machine hours consumed by users jobs: " << machine_hours << endl;
			wFile << "the utilization rtio: " << machine_hours / (time * 24 * 128) << endl;
			wFile << "the price paid by users: " << user_price << endl;
			wFile << "average wait time in each queue: " << job_wtime << endl;
			wFile << "average turnaround time ratio: " << (job_wtime + job_rtime) / job_rtime << endl;
			wFile << "economic balance of the centre: " << user_price << endl;
			/*
						double timeInWeeks = (double)time / (24.0 * 7.0);*/
	
			exit(0);
		}


	} while (running_weekjob_num(totalnum_queue, job_queue) != -1 || running_weekendjob_num(totalnum_queue, job_queue) != -1 || next_hugejobid != -1 || next_weekjobid != -1);
}




void Schedule::change_resourcequeue_time(int resource_nodes[128][8]) {
	//modify the time value of the resource nodes
	for (int k = 0; k < 128; k++) {
		resource_nodes[k][5] = resource_nodes[k][5] + 1;
		if (resource_nodes[k][2] == 0) {
			resource_nodes[k][3] = resource_nodes[k][3] + 1;
		}
		else if (resource_nodes[k][2] == 1) {
			resource_nodes[k][4] = resource_nodes[k][4] + 1;
		}
	}


}

void Schedule::change_jobqueue_time(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>* job_queue) {

	//change the array value of job queue 
	for (int a = 0; a < totalnum_queue; a++) {

		if (job_queue->at(a)[5] == 0) {
			//  waiting time of wait job should plus 1
			job_queue->at(a)[9] = job_queue->at(a)[9] + 1;
		}
		else if (job_queue->at(a)[5] == 1 || job_queue->at(a)[5] == 3) {
			// running time of run job shoule plus 1, left time should minus 1
			job_queue->at(a)[7] = job_queue->at(a)[7] + 1;
			job_queue->at(a)[8] = job_queue->at(a)[8] - 1;

			//release the node
			if (job_queue->at(a)[8] == 0) {//多个node的时候如何进行重置   status 改为done 2
				job_queue->at(a)[5] = 2;
				//cout << "release nodes when job has been done" << endl;
				//int m;
				//cin >> m;
				for (int b = 0; b < 128; b++) {
					if (resource_nodes[b][7] == job_queue->at(a)[0]) {
						resource_nodes[b][2] = 0;
						resource_nodes[b][7] = -1;
					}
				}
			}
		}
	}

}


void Schedule::job_connect_node(int resource_nodes[128][8], int job_id, int nodes, int jobType) {
	int left = 0, right = 128;
	// Small Job node 0 to 12
	if (jobType == 1) {
		right = 12;
	}
	// Medium node 12 to 48
	else if (jobType == 2) {
		left = 12;
		right = 48;
	}
	else if (jobType == 3) {
		left = 48;
		right = 120;
	}else if (jobType == 4) {
		left = 120;
	}

	for (int j = left; j < right; j++) {
		if (resource_nodes[j][2] == 0) {
			resource_nodes[j][2] = 1;
			resource_nodes[j][7] = job_id;			
			nodes--;
			if (nodes == 0) {
				break;
			}
		}
	}

}



void Schedule::job_connect_cnode(int resource_nodes[128][8], int job_id, int nodes) {
	for (int j = 0; j < 120; j++) {
		if (resource_nodes[j][2] == 0) {
			resource_nodes[j][2] = 1;
			resource_nodes[j][7] = job_id;
			nodes--;
			if (nodes == 0) {
				break;
			}
		}
	}

}


void Schedule::job_connect_gnode(int resource_nodes[128][8], int job_id, int nodes) {

	for (int j = 120; j < 128; j++) {
		if (resource_nodes[j][2] == 0) {
			resource_nodes[j][2] = 1;
			resource_nodes[j][7] = job_id;
			nodes--;
			if (nodes == 0) {
				break;
			}
		}

	}

}