#include <iostream>
#include<fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string> 
#include <queue>
#include<time.h>
#include "Resource_Nodes.h"
#include "User_Job.h"
#include "Schedule.h"
using namespace std;



int main() {

	int resource_nodes[128][8];// contain the information of resource node 
	Resource_Nodes resour_n;
	resour_n.Create_Resource(resource_nodes);
	cout << "prepare resource node successfully" << endl;

	int choice;
	cout << "please choose random or excel, 1 or 2?"<<endl;
	cin >> choice;
	if (choice == 1) {
		int num_sq, num_rq, num_itq;//contain request number of different roles
		cout << "Please put in the number of student request: " << endl;
		cin >> num_sq;
		cin >> num_rq;
		cin >> num_itq;


	}
	else if (choice == 2) {
		int totalnum_job;
		cout << "please put in the number of the job:" << endl;
		cin >> totalnum_job;
		vector<vector<int>>  job_queue(totalnum_job);
		for (int i = 0; i < totalnum_job; i++) {
			job_queue[i].resize(10);
		}
		User_Job Q;
		Q.excel_Queue(totalnum_job, job_queue);
		Schedule Sche1;
		Sche1.loop_job(resource_nodes, totalnum_job, job_queue);



	}
	else {
		cout << "please put in the right choice.";
	}
	

	

}




