#include "User_Job.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void User_Job::Create_job(string job_size) {
	//if (job_size == "Short") {
	//	nodes = random_jobnode(2);

	//}


}

int User_Job::random_jobnode(int maximum) {
	return rand() % maximum;
}

void User_Job::excel_Queue(int totalnum_queue, vector<vector<int>>  job_queue){

	ifstream rFile;
	rFile.open("User_Job.txt");
	if (!rFile.is_open()){
		cout << "ERROR: not open the file" << endl;
		exit(0);
	}

	for (int i = 0; i < totalnum_queue; i++) {
		 rFile>> job_queue[i][0]>> job_queue[i][1]>> job_queue[i][2] >> job_queue[i][3] >> job_queue[i][4] >> job_queue[i][5] >> job_queue[i][6] >> job_queue[i][7] >> job_queue[i][8] >> job_queue[i][9] >> job_queue[i][10];
		
	}

	for (int i = 0; i < totalnum_queue; i++) {
		cout << "job_queue" << i << " is : " << job_queue[i][0] << job_queue[i][1] << job_queue[i][2] << job_queue[i][3] << job_queue[i][4] << job_queue[i][5] << job_queue[i][6] << job_queue[i][7] << job_queue[i][8] << job_queue[i][9] << job_queue[i][10] << endl;;
	}



	/*void check_queue(int totalnum_queue, vector<vector<int>>  job_queue) {
		for (int i=0;)
	}*/
}