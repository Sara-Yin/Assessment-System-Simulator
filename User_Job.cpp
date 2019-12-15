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

void User_Job::excel_Queue(int totalnum_queue, vector<vector<int>>*  job_queue){

	ifstream rFile;
	rFile.open("User_Job.txt");
	if (!rFile.is_open()){
		cout << "ERROR: not open the file" << endl;
		exit(0);
	}

	for (int i = 0; i < totalnum_queue; i++) {
		 rFile>> job_queue->at(i)[0]>> job_queue->at(i)[1]>> job_queue->at(i)[2] >> job_queue->at(i)[3] >> job_queue->at(i)[4] >> job_queue->at(i)[5] >> job_queue->at(i)[6] >> job_queue->at(i)[7] >> job_queue->at(i)[8] >> job_queue->at(i)[9] >> job_queue->at(i)[10];
		
	}
	rFile.close();

	/*void check_queue(int totalnum_queue, vector<vector<int>>  job_queue) {
		for (int i=0;)
	}*/
}