#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include<string.h>
#include<stdlib.h>
#include<glut.h>
#include<iostream>
#define PI 3.1416

using namespace std;
int n;
int wt[6];						//waiting time for fcfs
int tat[6];						//turnaround time for fcfs
int at[] = { 0, 1, 2, 3, 4 };	//arrival time of processes for fcfs
int bt[] = { 4, 3, 1, 2, 5 };	//burst time of processes for fcfs

int wtrr[3];					//waiting time for rr
int tatrr[3];					//turnaround time for rr
int btrr[] = { 10,5,8 };		//burst time of processes for rr
int rem_bt[3];					//remaining burst time
int tq = 2;						//time quantum

int total_wt, total_tat, compl_time_fcfs[5];
int compl_time_rr[12] = { 2,4,6,8,10,12,14,15,17,19,21,23 };
int c = 0;
char p1[] = "P1", p2[] = "P2", p3[] = "P3", p4[] = "P4", p5[] = "P5";
char num[2];
int x, y;						//position values to display text

//initialize orthogonal space
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
}

//convert int to char
void int_str(int a, char num[])
{
	sprintf(num, "%d", a);
}

//function to display characters
void output(int x, int y, char* string)
{
	glColor3f(0, 0, 0);
	int len, i;
	len = (int)strlen(string);
	glRasterPos2f(x, y);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
}

void output1(int x, int y, char* string)
{
	glColor3f(0, 0, 1);
	int len, i;
	len = (int)strlen(string);
	glRasterPos2f(x, y);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24
			, string[i]);
}

//main page
void mainpage() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	char heading[] = "SCHEDULING ALGORITHMS";
	output1(-115, 450, heading);
	char string[] = "Scheduling algorithms schedule processes on the processor in an efficient and effective manner. This scheduling is done by a Process Scheduler.";
	char string2[] = "It maximizes CPU utilization by increasing throughput.Following are the popular process scheduling algorithms.";
	char string3[] = "1. First - Come, First - Served(FCFS) Scheduling";
	char string4[] = "2.Shortest - Job - First(SJF) Scheduling.";
	char string5[] = "3. Priority Scheduling";
	char string6[] = "4. Shortest Remaining Time";
	char string7[] = "5. Round Robin(RR) Scheduling";
	char string8[] = "6. Multiple - Level Queues Scheduling";
	char string9[] = "7. Multilevel Feedback Queues Scheduling";
	char string10[] = "8. Highest Response Ratio Next ";
	char string11[] = "Press f for viewing the first come first serve algorithm";
	char string12[] = "Press r for executing round robin algorithm";

	output(-400, 400, string);
	output(-400, 370, string2);
	output(-400, 340, string3);
	output(-400, 310, string4);
	output(-400, 280, string5);
	output(-400, 250, string6);
	output(-400, 220, string7);
	output(-400, 190, string8);
	output(-400, 160, string9);
	output(-400, 130, string10);
	output(-400, 100, string11);
	output(-400, 70, string12);
	glFlush();
}

//display function
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	mainpage();
}

//display question for fcfs algorithm
void fcfs_ques() {
	cout<<"Enter number of processes(3<=n<=5)"<<endl;
	cin >> n;
	if (n < 3 || n>5)
		exit(0);
	cout << "Enter arrival time" << endl;
	for (int i = 0; i < n; i++)
		cin >> at[i];
	cout << "Enter burst time" << endl;
	for (int i = 0; i < n; i++)
		cin >> bt[i];

	//table
	glBegin(GL_LINE_LOOP);
	glVertex2i(-400, 220);
	glVertex2i(-150, 220);
	glVertex2i(-150, 30);
	glVertex2i(-400, 30);
	glEnd();

	//process heading and values
	char proc[] = "Processes";
	output(-390, 190, proc);
	x=-380, y = 160;
	for (int i = 0; i < n; i++)
	{
		int_str(i + 1, num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-320, 220);
	glVertex2f(-320, 30);
	glEnd();

	char att[] = "Arrival Time";
	output(-310, 190, att);
	x = -280, y = 160;
	for (int i = 0; i < n; i++)
	{
		int_str(at[i], num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-230, 220);
	glVertex2f(-230, 30);
	glEnd();

	char btt[] = "Burst Time";
	output(-220, 190, btt);
	x = -200, y = 160;
	for (int i = 0; i < n; i++)
	{
		int_str(bt[i], num);
		output(x, y, num);
		y -= 30;
	}

	glFlush();
}

//function for introduction of fcfs
void fcfs() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	char string3[] = "First Come First Serve Algorithm";
	char string[] = "First Come First Serve is the simplest scheduling algorithm. It simply queues the processes in the order in which they arrive";
	char string1[] = "FIFO simply queues processes in the order that they arrive in the ready queue. ";
	char string2[] = "In this, the process that comes first will be executed firstand next process starts only after the previous gets fully executed.";

	output(-400, 400, string3);
	output(-400, 370, string);
	output(-400, 340, string1);
	output(-400, 310, string2);
	glLineWidth(2.0);

	glFlush();

}

//display table for fcfs
void fcfs_table() {
	glBegin(GL_LINE_LOOP);

	glVertex2i(-400, -30);
	glVertex2i(50, -30);
	glVertex2i(50, -220);
	glVertex2i(-400, -220);
	glEnd();

	char proc[] = "Processes";

	output(-390, -60, proc);
	x = -390, y = -90;
	for (int i = 0; i < n; i++)
	{
		int_str(i + 1, num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-320, -30);
	glVertex2f(-320, -220);
	glEnd();

	char att[] = "Arrival Time";
	output(-310, -60, att);
	x = -280, y = -90;
	for (int i = 0; i < n; i++)
	{
		int_str(at[i], num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-230, -30);
	glVertex2f(-230, -220);
	glEnd();

	char btt[] = "Burst Time";
	output(-220, -60, btt);
	x = -200, y = -90;
	for (int i = 0; i < n; i++)
	{
		int_str(bt[i], num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-150, -30);
	glVertex2f(-150, -220);
	glEnd();

	char wtt[] = "Waiting Time";
	output(-140, -60, wtt);
	x = -110, y = -90;
	for (int i = 0; i < n; i++)
	{
		int_str(wt[i], num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-60, -30);
	glVertex2f(-60, -220);
	glEnd();

	char tatt[] = "Turnaround time";
	output(-50, -60, tatt);
	x = -10, y = -90;
	for (int i = 0; i < n; i++)
	{
		int_str(tat[i], num);
		output(x, y, num);
		y -= 30;
	}
	glFlush();
}

//algorithm for fcfs
void fcfs_alg() {
	wt[0] = 0;
	for (int i = 1; i < n; i++)
		wt[i] = (at[i - 1] + bt[i - 1] + wt[i - 1]) - at[i];
	for (int i = 0; i < n; i++)
		tat[i] = bt[i] + wt[i];
	for (int i = 0; i < n; i++)
	{
		//total_wt = total_wt + wt[i];
		//total_tat = total_tat + tat[i];
		compl_time_fcfs[i] = tat[i] + at[i];
		//cout << compl_time_fcfs[i] << " ";
	}
	fcfs_table();	//display table with answer after executing the alg
}

void fcfs_gantt3()
{
	char head[] = "GANTT CHART";
	output(170, -60, head);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(140, -120);
	glVertex2f(100, -120);
	glVertex2f(100, -160);
	glVertex2f(140, -160);
	glEnd();
	output(115, -145, p1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(180, -120);
	glVertex2f(140, -120);
	glVertex2f(140, -160);
	glVertex2f(180, -160);
	glEnd();
	output(155, -145, p2);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(220, -120);
	glVertex2f(180, -120);
	glVertex2f(180, -160);
	glVertex2f(220, -160);
	glEnd();
	output(195, -145, p3);

	char c1[] = "0";
	output(100, -180, c1);
	x = 140, y = -180;
	for (int i = 0; i < 3; i++)
	{
		int_str(compl_time_fcfs[i], num);
		output(x, y, num);
		x += 40;
	}
	glFlush();
}

void fcfs_gantt4()
{
	char head[] = "GANTT CHART";
	output(170, -60, head);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(140, -120);
	glVertex2f(100, -120);
	glVertex2f(100, -160);
	glVertex2f(140, -160);
	glEnd();
	output(115, -145, p1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(180, -120);
	glVertex2f(140, -120);
	glVertex2f(140, -160);
	glVertex2f(180, -160);
	glEnd();
	output(155, -145, p2);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(220, -120);
	glVertex2f(180, -120);
	glVertex2f(180, -160);
	glVertex2f(220, -160);
	glEnd();
	output(195, -145, p3);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(260, -120);
	glVertex2f(220, -120);
	glVertex2f(220, -160);
	glVertex2f(260, -160);
	glEnd();
	output(235, -145, p4);

	char c1[] = "0";
	output(100, -180, c1);
	x = 140, y = -180;
	for (int i = 0; i < 4; i++)
	{
		int_str(compl_time_fcfs[i], num);
		output(x, y, num);
		x += 40;
	}
	glFlush();
}

void fcfs_gantt()
{
	char head[] = "GANTT CHART";
	output(170, -60, head);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(140, -120);
	glVertex2f(100, -120);
	glVertex2f(100, -160);
	glVertex2f(140, -160);
	glEnd();
	output(115, -145, p1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(180, -120);
	glVertex2f(140, -120);
	glVertex2f(140, -160);
	glVertex2f(180, -160);
	glEnd();
	output(155, -145, p2);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(220, -120);
	glVertex2f(180, -120);
	glVertex2f(180, -160);
	glVertex2f(220, -160);
	glEnd();
	output(195, -145, p3);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(260, -120);
	glVertex2f(220, -120);
	glVertex2f(220, -160);
	glVertex2f(260, -160);
	glEnd();
	output(235, -145, p4);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(300, -120);
	glVertex2f(260, -120);
	glVertex2f(260, -160);
	glVertex2f(300, -160);
	glEnd();
	output(275, -145, p5);

	char c1[] = "0";
	output(100, -180, c1);
	x = 140, y = -180;
	for (int i = 0; i < 5; i++)
	{
		int_str(compl_time_fcfs[i], num);
		output(x, y, num);
		x += 40;
	}
	glFlush();
}

void rr_table() {
	glBegin(GL_LINE_LOOP);
	glVertex2i(-400, -70);
	glVertex2i(-20, -70);
	glVertex2i(-20, -200);
	glVertex2i(-400, -200);
	glEnd();

	char proc[] = "Processes";

	output(-390, -100, proc);
	output(-380, -130, p1);
	output(-380, -160, p2);
	output(-380, -190, p3);

	glBegin(GL_LINES);
	glVertex2f(-320, -70);
	glVertex2f(-320, -200);
	glEnd();

	char bt[] = "Burst Time";
	output(-310, -100, bt);
	x = -280, y = -130;
	for (int i = 0; i < 3; i++)
	{
		int_str(btrr[i], num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-230, -70);
	glVertex2f(-230, -200);
	glEnd();

	char wt[] = "Waiting Time";
	output(-220, -100, wt);
	x = -190, y = -130;
	for (int i = 0; i < 3; i++)
	{
		int_str(wtrr[i], num);
		output(x, y, num);
		y -= 30;
	}

	glBegin(GL_LINES);
	glVertex2f(-140, -70);
	glVertex2f(-140, -200);
	glEnd();

	char tat[] = "Turnaround Time";
	output(-130, -100, tat);
	x = -100, y = -130;
	for (int i = 0; i < 3; i++)
	{
		int_str(tatrr[i], num);
		output(x, y, num);
		y -= 30;
	}

	glFlush();
}

//algorithm for rr algorithm
void rr_alg()
{
	for (int i = 0; i < 3; i++)
		rem_bt[i] = btrr[i];

	int t = 0; // Current time

	while (1)
	{
		bool done = true;

		for (int i = 0; i < 3; i++)
		{
			if (rem_bt[i] > 0)
			{
				done = false; // There is a pending process

				if (rem_bt[i] > tq)
				{
					t += tq;
					rem_bt[i] -= tq;
				}
				else
				{
					t = t + rem_bt[i];
					wtrr[i] = t - btrr[i];
					rem_bt[i] = 0;
				}
			}
		}
		if (done == true)
			break;
	}

	for (int i = 0; i < 3; i++)
		tatrr[i] = btrr[i] + wtrr[i];

	//cout << "PID" << "\t" << "BT" << "\t" << "WT" << "\t" << "TAT" << endl;
	//for (int i = 0; i < 3; i++)
		//cout << (i + 1) << "\t" << btrr[i] << "\t" << wtrr[i] << "\t" << tatrr[i] << endl;
	rr_table();
}

//introduction to rr
void rr() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	char string[] = "Round Robin Aalgorithm";
	char string1[] = "Round Robin is a CPU scheduling algorithm where each process is assigned a fixed time slot in a cyclic way. ";
	char string2[] = "It is basically the preemptive version of First come First Serve CPU Scheduling algorithm. ";
	char string3[] = "Round Robin CPU Algorithm generally focuses on Time Sharing technique.";
	char string4[] = "The period of time for which a process or job is allowed to run in a pre - emptive method is called time quantum.";
	char string5[] = "Each process or job present in the ready queue is assigned the CPU for that time quantum, ";
	char string6[] = "if the execution of the process is completed during that time then the process will end else the process ";
	char string7[] = "will go back to the waiting tableand wait for the its next turn to complete the execution.";	output(-400, 400, string);

	output(-400, 370, string1);
	output(-400, 340, string2);
	output(-400, 310, string3);
	output(-400, 280, string4);
	output(-400, 250, string5);
	output(-400, 220, string6);
	output(-400, 190, string7);

	glLineWidth(2.0);

	glFlush();
}

//question for rr algorithm
void rr_ques() {
	char ques[] = "Consider the following table of burst time for three processes P1, P2 and P3 and given Time Quantum = 2";
	output(-400, 130, ques);

	glBegin(GL_LINE_LOOP);
	glVertex2i(-400, 100);
	glVertex2i(-230, 100);
	glVertex2i(-230, -30);
	glVertex2i(-400, -30);
	glEnd();

	char proc[] = "Processes";

	output(-390, 70, proc);
	output(-380, 40, p1);
	output(-380, 10, p2);
	output(-380, -20, p3);

	glBegin(GL_LINES);
	glVertex2f(-320, 100);
	glVertex2f(-320, -30);
	glEnd();

	char bt[] = "Burst Time";
	output(-310, 70, bt);
	x = -300, y = 40;
	for (int i = 0; i < 3; i++)
	{
		int_str(btrr[i], num);
		output(x, y, num);
		y -= 30;
	}

	glFlush();
}

void rr_gantt() {
	char head[] = "GANTT CHART";
	output(170, -60, head);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(40, -120);
	glVertex2f(0, -120);
	glVertex2f(0, -160);
	glVertex2f(40, -160);
	glEnd();
	output(15, -145, p1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(80, -120);
	glVertex2f(40, -120);
	glVertex2f(40, -160);
	glVertex2f(80, -160);
	glEnd();
	output(55, -145, p2);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(120, -120);
	glVertex2f(80, -120);
	glVertex2f(80, -160);
	glVertex2f(120, -160);
	glEnd();
	output(95, -145, p3);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(261, -120);
	glVertex2f(120, -120);
	glVertex2f(120, -160);
	glVertex2f(160, -160);
	glEnd();
	output(135, -145, p1);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(200, -120);
	glVertex2f(160, -120);
	glVertex2f(160, -160);
	glVertex2f(200, -160);
	glEnd();
	output(175, -145, p2);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(240, -120);
	glVertex2f(200, -120);
	glVertex2f(200, -160);
	glVertex2f(240, -160);
	glEnd();
	output(215, -145, p3);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(280, -120);
	glVertex2f(240, -120);
	glVertex2f(240, -160);
	glVertex2f(280, -160);
	glEnd();
	output(255, -145, p1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(320, -120);
	glVertex2f(280, -120);
	glVertex2f(280, -160);
	glVertex2f(320, -160);
	glEnd();
	output(295, -145, p2);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(360, -120);
	glVertex2f(320, -120);
	glVertex2f(320, -160);
	glVertex2f(360, -160);
	glEnd();
	output(335, -145, p3);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(400, -120);
	glVertex2f(360, -120);
	glVertex2f(360, -160);
	glVertex2f(400, -160);
	glEnd();
	output(375, -145, p1);

	glColor3f(1, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(440, -120);
	glVertex2f(400, -120);
	glVertex2f(400, -160);
	glVertex2f(440, -160);
	glEnd();
	output(415, -145, p3);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(480, -120);
	glVertex2f(440, -120);
	glVertex2f(440, -160);
	glVertex2f(480, -160);
	glEnd();
	output(455, -145, p1);

	char c1[] = "0";
	output(0, -180, c1);
	x = 40, y = -180;
	for (int i = 0; i < 12; i++)
	{
		int_str(compl_time_rr[i], num);
		output(x, y, num);
		x += 40;
	}

	glFlush();
}

void edgedetect(float x1, float y1, float x2, float y2, int* le,
	int* re)
{
	float mx, x, temp;
	int i;
	if ((y2 - y1) < 0)
	{
		temp = y1; y1 = y2; y2 = temp;
		temp = x1; x1 = x2; x2 = temp;
	}
	if ((y2 - y1) != 0)
		mx = (x2 - x1) / (y2 - y1);
	else
		mx = x2 - x1;
	x = x1;
	for (i = y1; i <= y2; i++)
	{
		if (x < (float)le[i])
			le[i] = (int)x;
		if (x > (float)re[i])
			re[i] = (int)x;
		x += mx;
	}
}

void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void scanfill(float x1, float y1, float x2, float y2, float
	x3, float y3, float x4, float y4)
{
	int le[500], re[500];
	int i, y;
	for (i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}
	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);
	for (y = 0; y < 500; y++)
	{
		if (le[y] <= re[y])
			for (i = (int)le[y]; i < (int)re[y]; i++)
				draw_pixel(i, y);
	}
}

void scanline()
{
	//glClearColor(1, 1, 1, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	float x1 = -200.0, y1 = 0.0, x2 = -200.0, y2 = 20.0;
	float x3 = 200.0, y3 = 20.0, x4 = 200.0, y4 = 0.0;
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4,y4);
	glEnd();
	scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
	//scanfill(x5, y5, x6, y6, x7, y7, x8, y8);
	glFlush();
}

//function which is called when character is pressed
void mykey(unsigned char key, int x, int y)
{
	if (key == 'f')
	{
		c = 1;
		scanline();
		fcfs();
	}
	else if (key == 'r')
	{
		c = 10;
		scanline();
		rr();
	}
	else if (key == 'n' && c == 10)
	{
		c++;
		rr_ques();
	}
	else if (key == 'n' && c == 11)
	{
		c++;
		rr_alg();
	}
	else if (key == 'n' && c == 12) {
		c++;
		rr_gantt();
	}
	else if (key == 'n' && c == 1) {
		c++;
		fcfs_ques();
	}
	else if (key == 'n' && c == 2) {
		c++;
		fcfs_alg();
	}
	else if (key == 'n' && c == 3) {
		c++;
		if (n == 3)
			fcfs_gantt3();
		else if (n == 4)
			fcfs_gantt4();
		else if (n == 5)
			fcfs_gantt();
	}

	else {
		exit(0);
	}

}

int main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(1275, 1275);
	glutCreateWindow("Scheduling algorithm");
	myinit();
	//glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);
	glutMainLoop();
	return 0;
}
