
/*
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
}

int Schedule::next_hugejob_id(int totalnum_queue, vector<vector<int>>  job_queue) {
	for (int i = 0; i <= totalnum_queue; i++) {

		if (i == totalnum_queue) {
			return -1;
			break;
		}

		if (job_queue[i][5] == 0 && (job_queue[i][4] ==5)) {
			return i;  
			break;
		}

	}
}

int Schedule::next_weekjob_id(int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = 0; i <= totalnum_queue; i++) {
		
		if (i == totalnum_queue) {
			return -1;

			break;
		}
		if (job_queue[i][5] == 0 && job_queue[i][4] != 5) {
			return i;  //the order of the job
			//cout << "next_weekjob_id." << job_queue[i][2] << endl;
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
			return i;  //the order of the job
			//cout << "next_weekjob_id." << job_queue[i][2] << endl;
			break;
		}

	}
}


void Schedule::loop_job(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>  job_queue) {

	for (int i = 0; i < totalnum_queue; i++) {
		cout << "job_queue" << i << " is : " << job_queue[i][0] << job_queue[i][1] << job_queue[i][2] << job_queue[i][3] << job_queue[i][4] << job_queue[i][5] << job_queue[i][6] << job_queue[i][7] << job_queue[i][8] << job_queue[i][9] << job_queue[i][10] << endl;;
	}

	for (int i = 0; i < totalnum_queue;i++) {
		int cpu_num = avaliable_cpunode(resource_nodes); //how many available cpu
		cout << "cpu_num: " << cpu_num << endl;
		int gpu_num= avaliable_gpunode(resource_nodes);//how many available gpu
		cout << "gpu_num: " << gpu_num << endl;
		int next_weekjobid = next_weekjob_id(totalnum_queue, job_queue);
		cout << "next_weekjobid: " << next_weekjobid << endl;
		int next_hugejobid = next_hugejob_id(totalnum_queue, job_queue);
		cout << "next_hugejobid: " << next_hugejobid << endl;
		if (next_weekjobid < 0 && next_hugejobid<0) {  //没有待执行的job, 等待running job 执行完就退出

			if (running_weekjob_num(totalnum_queue , job_queue)<0 && running_weekendjob_num(totalnum_queue, job_queue) <0){
			cout << "next_weekjobid: " << next_weekjobid<<", next_hugejobid: "<< next_hugejobid<<endl;
			cout << "All jobs are finished." << endl;
			exit(0);
			}
			else {
				job_run(resource_nodes, totalnum_queue, job_queue);

				for (int i = 0; i < totalnum_queue; i++) {
					cout << "job_queue" << i << " is : " << job_queue[i][0] << job_queue[i][1] << job_queue[i][2] << job_queue[i][3] << job_queue[i][4] << job_queue[i][5] << job_queue[i][6] << job_queue[i][7] << job_queue[i][8] << job_queue[i][9] << job_queue[i][10] << endl;;
				}

			}
		}
		
		//有待执行的job
		if (weekend_hours ==0 && week_hours > 0 && next_weekjobid !=  -1) {    //weekday
			if (job_queue[next_weekjobid][4] == 4 ) {    //gpu resource
				if (job_queue[next_weekjobid][3]> gpu_num){
					job_run(resource_nodes, totalnum_queue,job_queue);
				}
				else {
					job_queue[next_weekjobid][5] = 1;
					job_connect_gnode(resource_nodes, next_weekjobid, job_queue[next_weekjobid][3]);
					job_run(resource_nodes, totalnum_queue, job_queue);
				}
			}
			else{  //cpu resource
				if (job_queue[next_weekjobid][3] > cpu_num) {
					job_run(resource_nodes, totalnum_queue, job_queue);
				}
				else {
					job_queue[next_weekjobid][5] = 1;

					cout << "next_weekjobid: "<< next_weekjobid <<", job_queue[next_weekjobid][3]: "<< job_queue[next_weekjobid][3] <<endl;
					job_connect_cnode(resource_nodes, next_weekjobid, job_queue[next_weekjobid][3]);
					job_run(resource_nodes, totalnum_queue, job_queue);
				}

			}

			week_hours = week_hours - 1;
			if (week_hours == 0) {
				weekend_hours = 64;
			}
		}
		else if (week_hours == 0 && weekend_hours > 0 && next_hugejobid !=-1) { 
			//weekend
			if (job_queue[next_hugejobid][3] > cpu_num) {
				job_run(resource_nodes, totalnum_queue, job_queue);
			}
			else {
				job_queue[next_hugejobid][5] = 1;
				job_run(resource_nodes, totalnum_queue, job_queue);
			}


			weekend_hours = weekend_hours - 1;
			if (weekend_hours == 0) {
				week_hours = 104;
			}
		}
		else {
			cout << "the situation is : weekend_hours: "<< weekend_hours<<", week_hours: "<< week_hours <<", next_weekjobid: "<< next_weekjobid <<endl;
			cout << "There is no work to run." << endl;
			break;
		}

	}

	left_weekhours=week_hours-1;
	if (left_weekhours>0){//weekday
		loop_job(resource_nodes, totalnum_queue, job_queue);
	}
	else {//weekend

	}


}


void Schedule::job_run(int resource_nodes[128][8], int totalnum_queue, vector<vector<int>>  job_queue) {

	//修改资源的值
	for (int k = 0; k < 128; k++) {
		if (resource_nodes[k][2]==0) {
			resource_nodes[k][3] = resource_nodes[k][3] + 1;
			resource_nodes[k][5] = resource_nodes[k][5] + 1;
		}
		else if (resource_nodes[k][0]==1) {

			resource_nodes[k][4] = resource_nodes[k][4] + 1;
			resource_nodes[k][5] = resource_nodes[k][5] + 1;
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
			job_queue[a][7] = job_queue[a][7] + 1;
			job_queue[a][8] = job_queue[a][8] - 1;

			//release the node
			if (job_queue[a][8] == 0) {//多个node的时候如何进行重置   status 改为done 2
				job_queue[a][5] = 2;
				for (int b = 0; b < 128; b++) {
					if (resource_nodes[128][6]== job_queue[a][0]){
						resource_nodes[128][2] = 0;
					}
				}
			}
		}
	}
}



void Schedule::job_connect_cnode(int resource_nodes[128][8], int job_id, int nodes) {
	cout <<"nodes: "<< nodes;
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

*/