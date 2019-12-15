#ifndef User_Job_H
#define User_Job_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class User_Job {
public:
	//0 int uid; //user ID  unique
	//1 int jid;//job id   unique
	//2 int role;//1 IT , 2 researcher , 3 student
	//3 int nodes;//how many nodes the job needs
	//4 int job_size; //1 short, 2 medium, 3 large, 4 gpu, 51 huge-cpu  52 huge-gpu
	//5 int job_status;// 0 means waiting, 1 means running, 2 means done, 3 means stop,4 means failure 
	//6 int job_time;  //the time of total job needs
	//7 int run_time; //the time of job implement
	//8 int left_time;
	//9 int wait_time;
	//10 int price;
	void Create_job(string job_size);
	int random_jobnode(int maximum);
	void excel_Queue(int totalnum_queue, vector<vector<int>>*  job_queue);
	



};

#endif