#include "analysis_functions.cpp"

int main() {
	Network x;
	cin >> x;
	cout << x << endl << endl;
	
	vector<string> list_of_nodes = x.list_nodes();
	for(int i = 0 ; i < list_of_nodes.size() ; i++) {
		cout << list_of_nodes[i] << endl;
	}

	vector<double> list_of_times = x.time_intervals();
	for(int i = 0 ; i < list_of_times.size() ; i++) {
		cout << list_of_times[i] << endl;
	}
	
}
