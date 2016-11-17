#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(void)
{

	string path;

	cin >> path;

	cout << endl;

	fstream fs;
	fs.open(path, std::fstream::out);

	fs << "lllllllllllllllllllll";

	fs.close();

	return 0;
}
