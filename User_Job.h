#ifndef User_Job_H
#define User_Job_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class User_Job {
public:
	//int uid; //user ID  unique
	//int jid;//job id   unique
	//int role;//1 IT , 2 researcher , 3 student
	//int nodes;//how many nodes the job needs
	//int job_size; //1 short, 2 medium, 3 large, 4 gpu, 5 huge
	//int job_status;// 0 means waiting, 1 means running, 2 means done, 3 means failure, 
	//int job_time;  //the time of total job needs
	//int current_time; //the time of job implement
	//int left_time;
	//int wait_time;
	//int price;
	void Create_job(string job_size);
	int random_jobnode(int maximum);
	void excel_Queue(int totalnum_queue, vector<vector<int>>  job_queue);


};

#endif