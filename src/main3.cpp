#include "head.h"

using namespace std;

int cb_id = 1;
int queue_max = 5;
int cashbox_cd = 1;

void cashbox(queue<Customer*> que, int thr_id){
	while (!que.empty()){
		for (int i = 0; i < que.front()->getProducts().size(); i++){
			cout << "cashbox n0 " << thr_id << " product " << que.front()->getProducts()[i] << endl;
			this_thread::sleep_for(chrono::seconds(cashbox_cd));
		}
		cout << "customer done in cashbox n0 " << thr_id << endl;
		que.pop();
	}
	cb_id--;
}

int main(){
	srand(time(0));
	queue<Customer*> custs;
	vector<thread*> thrs;
	//vector<queue<Customer*>> everybody;
	int customer_trigger = 0;
	unsigned int customer_trigger_max = 60;
	Customer* cust = new Customer();
	custs.push(cust);
	while (1){
		for (int i = 0; i < custs.front()->getProducts().size(); i++){
			customer_trigger = rand() % 100;
			if (customer_trigger < customer_trigger_max){
				customer_trigger_max -= 2;
				Customer* cust = new Customer();
				if (custs.size() < queue_max*cb_id)
					custs.push(cust);
				else{
					custs.push(cust);
					cb_id++;
					thrs.push_back(new thread(cashbox, custs, cb_id));
				}
			}
			cout << "cashbox n0 1" << " product " << custs.front()->getProducts()[i] << endl;
			this_thread::sleep_for(chrono::seconds(cashbox_cd));
		}
		cout << "customer done in cashbox n0 1" << endl;
		custs.pop();
		//customer_trigger_max = 60;
		if (custs.empty())
			break;
	}
	getchar();
	return 0;
}