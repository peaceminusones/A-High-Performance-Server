#include<iostream>
#include<event2/event.h>
#include<signal.h>
#include<thread>

using namespace std;

static timeval t1={1,0};
//忽略管道信号，发送数据给已关闭的socket
	
void timer1(int sock,short which,void *arg){
	event *ev =(event *)arg;
	cout<<"【hanxiao】"<<endl;
	if(!evtimer_pending(ev,&t1)){
		evtimer_del(ev);
		evtimer_add(ev,&t1);
	}
}

int main(int argc, char const *argv[])
{
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
	event_base *base = event_base_new();

	//定时器
	cout<<"timer test"<<endl;

	//event new普通的定时器
	event *ev1 =evtimer_new(base,timer1,event_self_cbarg());//上下文，定时器，回调函数，
	if(!ev1){
		cout<<"evtimer-new fail!"<<endl;
		return -1;
	}

	evtimer_add(ev1,&t1);

	event_base_dispatch(base);
	event_base_free(base);
	return 0;
}
	
