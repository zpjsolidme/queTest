#include<thread>
#include<mutex>
#include<Windows.h>


std::mutex m;

using namespace cv;
using namespace std;

std::queue<cv::Mat> imgs;


int queSize=10;
int readSize=0;


void reading()
{
	string x="xxxxxxxxxxxx";
	vector<string> filenames;
	glob(x,filenames);
	
	readSize=filenames.size();
	
	Mat tmpImg;
	if(filenames.size()>0)
	{
		cout<<"整个图像共："<<filenames.size()<<"张"<<endl;
	}
	while(1)
	{
		static int index=0;
		if(imgs.size()<queSize)
		{
			Sleep(1);
			if(index==filenames.size())
			{
				break;
			}
			tmpImg=imread(filenames[index]);
			imgs.push(tmpImg);
			index++;
			cout<<"新载入图像："<<index<<endl;
		}
		else
		{
			cout<<"队列已满，正在处理"<<index<<endl;
			Sleep(2000);
		}	
	}
}


void process()
{
	for(;;)
	{
		static int index=0;
		if(!imgs.empty())
		{
			GaussianBlur(imgs.front,img.front(),Size(3,3),0,0);
			imshow("gauss",img.front());
			waitKey(1);
			Sleep(500);
			imgs.pop();
			index++;
			cout<<"完成图像"<<index<<endl;
		}
		if(index==readSize)
		{
			break;
		}
	}
}


void main()
{
	thread th1(reading);
	thread th2(process);
	
	th1.join();
	th2.join();
	
	for(int i=0;i<5;i++)
	{
		cout<<"Main thread is Working !"<<endl;
	}
	system("pause");
}











