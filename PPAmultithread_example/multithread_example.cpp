#include <windows.h> 
#include <tchar.h>
#include <iostream>
#include <cmath>

//Header declarations
long WINAPI executeThread(long lParam);
long DoSomeWork(long lParam);

CONST int MAX_THREADS = 4;
CONST int DO_SOME_WORK_ITERATIONS=5;

int main(void)
{
  HANDLE hThread[MAX_THREADS];
  DWORD dwID[MAX_THREADS];
  DWORD dwRetVal = 0;
  int param[MAX_THREADS];

  std::cout << "Program start with id: " << GetCurrentThreadId() << std::endl;
  system("pause");

  //release the threads.
  for(int i = 0; i< MAX_THREADS;i++){
	param[i]=i;
  	hThread[i] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)executeThread,&param[i],0,&dwID[i]);
  }
 
  //wait for all threads to complete before continuing
  dwRetVal = WaitForMultipleObjects(MAX_THREADS, hThread, TRUE, INFINITE);
  
  //Display a message: Wait state has finished
  std::cout << "All threads have completed." << std::endl;
 
  //close handles
  for(int i = 0; i< MAX_THREADS;i++)
  	CloseHandle(hThread[i]);

  system("pause");

  //end the main function
  return 0;
}

long WINAPI executeThread(long lParam)
{
  int threadNum = *((int*)lParam);
  std::cout << "Thread " <<  threadNum  << " with id: " << GetCurrentThreadId() <<" start working." << std::endl;

  DoSomeWork(threadNum);
  std::cout << "Thread " << threadNum << " finished working." << std::endl;
  return 0;
}

long DoSomeWork(long times)
{
  double result=0;
  times+=DO_SOME_WORK_ITERATIONS;
  
  for(long i=0 ; i<=times*1000 ;i++) 
    for(long j=0 ; j<=times*1000 ;j++)
	  result+= sqrt(sin((double)i) + cos((double)j));

  return 0;
}
