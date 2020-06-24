#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>

const int MAX_COSTUMERS = 5;
std::mutex mutex1;


struct costumer {
	std::vector<int> goods;
};

struct cashbox {
	std::queue<costumer*> costumers;
	std::thread* thread;
};
std::vector<cashbox*> cashboxes;

costumer* create_costumer() {	
	int number_of_products = rand() % 20 + 1;
	costumer* new_costumer = new costumer;
	for (int i = 0; i < number_of_products; i++) {
		new_costumer->goods.push_back(rand() % 101);
	}
	return new_costumer;
}

void process_costumers(cashbox* cashbox) {
	std::cout << "CASHBOX ID - " << std::this_thread::get_id() << "\tSTART" << std::endl;
	while (cashbox->costumers.empty() == false) {
		
		costumer* costumer = cashbox->costumers.front();	
		std::cout << "NUMBER OF GOODS - " << costumer->goods.size() << std::endl;
		for (int item : costumer->goods) {
			std::cout << "GOOD - " << item << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(item * 50));
		}
		std::lock_guard<std::mutex> lock(mutex1);
		cashbox->costumers.pop();
	}
	std::cout << "CASHBOX ID - " << std::this_thread::get_id() << "\tFINISHED" << std::endl;
}

void remove_empty_cashbox() {
	if (cashboxes.empty() == false) {
		for (int i = cashboxes.size() - 1; i >= 0; i--) {
			if (cashboxes[i]->costumers.empty()) {
				delete cashboxes[i]->thread;
				delete cashboxes[i];
				cashboxes.erase(cashboxes.begin() + i);
			}
		}
	}
}


int main() {
	srand(time(0));
	
	while (true) {
		{
			std::lock_guard<std::mutex> lock(mutex1);

			std::cout << "COSTUMER was created" << std::endl;
			costumer* costumer = create_costumer();
			bool added = false;
			remove_empty_cashbox();

			for (int i = 0; i < cashboxes.size(); i++) {
				if (cashboxes[i]->costumers.size() < MAX_COSTUMERS) {
					cashboxes[i]->costumers.push(costumer);
					added = true;
					std::cout << "Has \tEMPTY \tPLACE!" << std::endl;
					break;
				}
			}			
			if (added == false) {
				std::cout << "EMPTY CASHBOXES doesn't exist" << std::endl;
				cashbox* new_cashbox = new cashbox;
				new_cashbox->costumers.push(costumer);
				cashboxes.push_back(new_cashbox);

				new_cashbox->thread = new std::thread(process_costumers, new_cashbox);
				new_cashbox->thread->detach();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 10 + 1) * 1000));
	}
}