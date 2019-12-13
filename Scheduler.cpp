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

int Schedule::avaliable_gpunode(int resource_nodes[128][8]) {
	int g_num = 0;
	for (int i = 120; i < 128; i++) {
		if (resource_nodes[i][2] == 0) {
			g_num = g_num + 1;

		}
	}
	return g_num;
}

int Schedule::next_hugejob_id(int next_hugejobid,int totalnum_queue, vector<vector<int>>  job_queue) {
	for (int i = next_hugejobid; i <= totalnum_queue; i++) {

		if (i == totalnum_queue || i==-1) {
			return -1;
			break;
		}

		if (job_queue[i][5] == 0 && (job_queue[i][4] == 5)) {
			return i;
			break;
		}

	}
}

int Schedule::next_weekjob_id(int next_weekjobid, int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = next_weekjobid; i <= totalnum_queue; i++) {

		if (i == totalnum_queue ||i==-1) {
			return -1;
			break;
		}
		if (job_queue[i][5] == 0 && job_queue[i][4] != 5) {
			return i; 
			break;
		}

	}
}


int Schedule::running_weekjob_num(int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = 0; i <= totalnum_queue; i++) {

		if (i == totalnum_queue) {
			return -1;

			break;
		}
		if (job_queue[i][5] == 1 && job_queue[i][4] != 5) {
			return i;  //the order of the job
			//cout << "next_weekjob_id." << job_queue[i][2] << endl;
			break;
		}

	}
}

int Schedule::running_weekendjob_num(int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = 0; i <= totalnum_queue; i++) {

		if (i == totalnum_queue) {
			return -1;

			break;
		}
		if (job_queue[i][5] == 1 && job_queue[i][4] == 5) {
			return i;  
			break;
		}

	}
}

int Schedule::done_alljob_num(int totalnum_queue, vector<vector<int>>  job_queue) {
	l = -1;
	for (int i = 0; i <totalnum_queue; i++) {
		
		if (job_queue[i][5] != 2 ) {
			return i;
			break;
		}

	}
	return l;
}


void Schedule::loop_job(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>  job_queue) {
	next_weekjobid = 0;
	do {
		for (int i = 0; i < totalnum_queue; i++) {
			cout << "job_queue" << i << " is : " << job_queue[i][0] << job_queue[i][1] << job_queue[i][2] << job_queue[i][3] << job_queue[i][4] << job_queue[i][5] << job_queue[i][6] << job_queue[i][7] << job_queue[i][8] << job_queue[i][9] << job_queue[i][10] << endl;;
		}
		for (int k = 0; k < 4; k++) {
			cout << "resource " << k << ", status: " << resource_nodes[k][2] << ", runing time: " << resource_nodes[k][4] << " connect with:" << resource_nodes[k][7] << endl;
		}
		for (int k = 120; k < 123; k++) {
			cout << "resource " << k << ", status: " << resource_nodes[k][2] << ", runing time: " << resource_nodes[k][4] << " connect with:" << resource_nodes[k][7] << endl;
		}

		if (weekend_hours == 0 && week_hours > 0) {//weekday

			next_weekjobid = next_weekjob_id(next_weekjobid,totalnum_queue, job_queue);

			if (next_weekjobid != -1) {  //has waiting job
				for (int a = next_weekjobid; a < totalnum_queue; a++) {  //同步所有等待任务，如果资源允许的话
					next_weekjobid = next_weekjob_id(next_weekjobid,totalnum_queue, job_queue);
					
					if (job_queue[next_weekjobid][4] == 4 && next_weekjobid != -1) {    //gpu resource
						gpu_num = avaliable_gpunode(resource_nodes);//how many available gpu
						cout << "gpu_num: " << gpu_num << endl;
						if (job_queue[next_weekjobid][3] > gpu_num) {
							break;
						}
						else {
							job_queue[next_weekjobid][5] = 1;
							job_connect_gnode(resource_nodes, next_weekjobid, job_queue[next_weekjobid][3]);
						}
					}
					else if ((job_queue[next_weekjobid][4] == 1 || job_queue[next_weekjobid][4] == 2 || job_queue[next_weekjobid][4] == 3) && next_weekjobid != -1) {  //cpu resource
						cpu_num = avaliable_cpunode(resource_nodes);
						if (job_queue[next_weekjobid][3] > cpu_num) {
							break;
						}
						else {
							job_queue[next_weekjobid][5] = 1;

							cout << "next_weekjobid: " << next_weekjobid << ", job_queue[next_weekjobid][3]: " << job_queue[next_weekjobid][3] << endl;
							job_connect_cnode(resource_nodes, next_weekjobid, job_queue[next_weekjobid][3]);
						}
					}
				}
				//job_run(resource_nodes, totalnum_queue, job_queue);
			}
			else {  //no waiting job
				if (running_weekjob_num(totalnum_queue, job_queue) == -1) { //no waiting job, no running job
					cout << "week day has no waiting job and no running job. " << endl;
					//exit(0);		
					continue;
				}
			}

			week_hours = week_hours - 1;
			cout << "week_hours: " << week_hours << endl;
			if (week_hours == 0) {
				weekend_hours = 64;
			}
		}
		else if (week_hours == 0 && weekend_hours > 0) {//weekenday
			cpu_num = avaliable_cpunode(resource_nodes);
			gpu_num = avaliable_gpunode(resource_nodes);//how many available gpu
			next_hugejobid = next_hugejob_id(next_hugejobid,totalnum_queue, job_queue);


			if (next_hugejobid != -1) {  //has waiting job
				for (int a = next_hugejobid; a < totalnum_queue; a++) {  //同步所有等待任务，如果资源允许的话
					next_hugejobid = next_hugejob_id(next_hugejobid, totalnum_queue, job_queue);

					if (job_queue[next_hugejobid][4] == 4 && next_hugejobid != -1) {    //gpu resource
						gpu_num = avaliable_gpunode(resource_nodes);//how many available gpu
						cout << "gpu_num: " << gpu_num << endl;
						if (job_queue[next_hugejobid][3] > gpu_num) {
							break;
						}
						else {
							job_queue[next_hugejobid][5] = 1;
							job_connect_gnode(resource_nodes, next_hugejobid, job_queue[next_hugejobid][3]);
						}
					}
					else if ((job_queue[next_hugejobid][4] == 1 || job_queue[next_hugejobid][4] == 2 || job_queue[next_hugejobid][4] == 3) && next_hugejobid != -1) {  //cpu resource
						cpu_num = avaliable_cpunode(resource_nodes);
						if (job_queue[next_hugejobid][3] > cpu_num) {
							break;
						}
						else {
							job_queue[next_hugejobid][5] = 1;

							cout << "next_hugejobid: " << next_hugejobid << ", job_queue[next_hugejobid][3]: " << job_queue[next_hugejobid][3] << endl;
							job_connect_cnode(resource_nodes, next_hugejobid, job_queue[next_hugejobid][3]);
						}
					}
				}
				//job_run(resource_nodes, totalnum_queue, job_queue);
			}
			else {  //no waiting job
				if (running_weekendjob_num(totalnum_queue, job_queue) == -1) { //no waiting job, no running job
					cout << "weekeend day has no waiting job and no running job." << endl;
					break;
				}
			}



			weekend_hours = weekend_hours - 1;
			if (weekend_hours == 0) {
				week_hours = 104;
			}
		}
		//job_run(resource_nodes, totalnum_queue, job_queue);

		///*running process*///

			//修改资源的值
		for (int k = 0; k < 128; k++) {
			if (resource_nodes[k][2] == 0) {
				resource_nodes[k][3] = resource_nodes[k][3] + 1;
				resource_nodes[k][5] = resource_nodes[k][5] + 1;
			}
			else if (resource_nodes[k][2] == 1) {

				resource_nodes[k][4] = resource_nodes[k][4] + 1;
				resource_nodes[k][5] = resource_nodes[k][5] + 1;
				cout << "修改资源值resource " << k << ", status: " << resource_nodes[k][2] << ", runing time: " << resource_nodes[k][4] << " connect with:" << resource_nodes[k][7] << endl;

			}

		}



		//修改队列的值
		for (int a = 0; a < totalnum_queue; a++) {

			if (job_queue[a][5] == 0) {
				//  waiting time of wait job should plus 1
				job_queue[a][9] = job_queue[a][9] + 1;
			}
			else if (job_queue[a][5] == 1) {
				// running time of run job shoule plus 1, left time should minus 1
				cout << "执行前job_queue[a][7]: " << job_queue[a][7] << endl;
				job_queue[a][7] = job_queue[a][7] + 1;

				for (int i = 0; i < totalnum_queue; i++) {
					cout << "job_queue" << i << " is : " << job_queue[i][0] << job_queue[i][1] << job_queue[i][2] << job_queue[i][3] << job_queue[i][4] << job_queue[i][5] << job_queue[i][6] << job_queue[i][7] << job_queue[i][8] << job_queue[i][9] << job_queue[i][10] << endl;;
				}
				cout << "执行后job_queue[a][7]: " << job_queue[a][7] << endl;
				cout << "执行前job_queue[a][8]: " << job_queue[a][8] << endl;
				job_queue[a][8] = job_queue[a][8] - 1;
				cout << "执行后job_queue[a][8]: " << job_queue[a][8] << endl;

				//release the node
				if (job_queue[a][8] == 0) {//多个node的时候如何进行重置   status 改为done 2
					job_queue[a][5] = 2;
					cout << "需要释放资源" << endl;
					int m;
					cin >> m;
					for (int b = 0; b < 128; b++) {
						if (resource_nodes[b][7] == job_queue[a][0]) {
							resource_nodes[b][2] = 0;
							resource_nodes[b][7] = -1;
							cout << "释放资源node" << b << ": 状态改为" << resource_nodes[b][2];
						}
					}
				}
			}
		}


		///*running process*////

		if (done_alljob_num(totalnum_queue,job_queue)==-1) {
			for (int i = 0; i < totalnum_queue; i++) {
				cout << "最后结果job_queue" << i << " is : " << job_queue[i][0] << job_queue[i][1] << job_queue[i][2] << job_queue[i][3] << job_queue[i][4] << job_queue[i][5] << job_queue[i][6] << job_queue[i][7] << job_queue[i][8] << job_queue[i][9] << job_queue[i][10] << endl;;
			}

			for (int i = 0; i < 128; i++) {
				cout << "最后结果resource " << i << ": " << resource_nodes[i][0] << resource_nodes[i][1] << resource_nodes[i][2] << resource_nodes[i][3] << resource_nodes[i][4] << resource_nodes[i][5] << resource_nodes[i][6] << resource_nodes[i][7] << endl;

			}
			exit(0);
		}


	} while (running_weekjob_num(totalnum_queue, job_queue) != -1 || running_weekendjob_num(totalnum_queue, job_queue) != -1 || next_hugejobid != -1 || next_weekjobid != -1);
}




void Schedule::job_connect_cnode(int resource_nodes[128][8], int job_id, int nodes) {
	cout << "nodes: " << nodes;
	for (int j = 0; j < 120; j++) {
		if (resource_nodes[j][2] == 0) {
			resource_nodes[j][2] = 1;
			resource_nodes[j][7] = job_id;
			cout << "cpu修改的node id是：" << j << "job id 是： " << job_id << endl;
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
			cout << "gpu修改的node id是：" << j << "job id 是： " << job_id << endl;
			nodes--;
			if (nodes == 0) {
				break;
			}
		}

	}

}