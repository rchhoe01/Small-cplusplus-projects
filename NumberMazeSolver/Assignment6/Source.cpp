#include <iostream>
#include <vector>
#include <fstream> 
#include <string> 


int main() {
	using namespace std;
	ifstream mazeFile("maze.txt", ios::in);

	if (!mazeFile) {
		cerr << "File could not be opened." << endl;
		exit(1);
	}

	int row;
	int col;
	int startRow;
	int startCol;
	int goalRow;
	int goalCol;


	//read the first line to create a matrix and store the start points and goal points
	if (mazeFile >> row >> col >> startRow >> startCol >> goalRow >> goalCol) {
		//cout << row << col << startRow << startCol << goalRow << goalCol << endl;
	}

	//use a 2 dimensional vector to represent the matrix
	vector< vector<int> > v;

	// use a temporary vector to fill a row then input into the main matrix
	vector<int> tmpV;
	//fill the matrix with numbers from the file
	for (int a = 0; a < row; a++) {
		for (int b = 0; b < col; b++) {
			int temp;
			mazeFile >> temp;
			tmpV.push_back(temp);
		}
		v.push_back(tmpV);
		tmpV.clear();
	}


	/* prints arraylist
	for (int a = 0; a < row; a++) {
		for (int b = 0; b < col; b++) {
			cout << v[a][b] ;
		}
		cout << endl;
	}
	*/

	//storage
	vector<int> temp1;
	vector< vector<int> > temp2;
	vector< vector< vector<int> > > zed;
	vector< vector< vector<int> > > temp3;
	vector< vector< vector<int> > > temp4;
	vector< vector< vector<int> > > solutions;

	//goal
	int pointRow = goalRow;
	int pointCol = goalCol;

	//check up
	for (int aa = pointRow - 1; aa >= 0; aa--) {
		if ((aa + v[aa][pointCol] < row) && (aa + v[aa][pointCol] == pointRow)) {
			//cout << "up" << endl;
			temp1.push_back(aa);
			temp1.push_back(pointCol);
			temp2.push_back(temp1);
			temp1.clear();
			zed.push_back(temp2);
			temp2.clear();
		}

	}
	//check down

	for (int aa = pointRow + 1; aa < row; aa++) {
		if (((aa - v[aa][pointCol]) >= 0) && (aa - v[aa][pointCol] == pointRow)) {
			//cout << "down" << endl;
			temp1.push_back(aa);
			temp1.push_back(pointCol);
			temp2.push_back(temp1);
			temp1.clear();
			zed.push_back(temp2);
			temp2.clear();

		}
	}
	//check left
	for (int aa = pointCol - 1; aa >= 0; aa--) {
		if ((aa + v[pointRow][aa] < col) && (aa + v[pointRow][aa] == pointCol)) {
			//cout << "left" << endl;
			temp1.push_back(pointRow);
			temp1.push_back(aa);
			temp2.push_back(temp1);
			temp1.clear();
			zed.push_back(temp2);
			temp2.clear();
		}
	}

	//check right
	for (int aa = pointCol + 1; aa < col; aa++) {
		if ((aa - v[pointRow][aa] >= 0) && (aa - v[pointRow][aa] == pointCol)) {
			//cout << "right" << endl;
			temp1.push_back(pointRow);
			temp1.push_back(aa);
			temp2.push_back(temp1);
			temp1.clear();
			zed.push_back(temp2);
			temp2.clear();
		}
	}

	int lastEl;
	bool added = false;
	bool erased = false;
	bool repeatOrAdded = false;
	int count = 0;

	//perform search
	while (!(zed.empty())) {
		if (!(zed.empty())) {
			//cout << "----------------------------------------" << endl;
			//cout << count << endl;
			lastEl = zed[0].size() - 1;
			/*cout << zed[0][lastEl][0] << ",";
			cout << zed[0][lastEl][1] << endl;*/

			/*for (int b = 0; b < zed.size(); b++) {
				for (int c = 0; c < zed[b].size(); c++) {
					cout << "[" << zed[b][c][0] << "," << zed[b][c][1] << "] ";
				}
				cout << endl;
			}*/



			pointRow = zed[0][lastEl][0];
			pointCol = zed[0][lastEl][1];



			temp3.push_back(zed[0]);

			//check up
			for (int aa = pointRow - 1; aa >= 0; aa--) {
				if ((aa + v[aa][pointCol] < row) && (aa + v[aa][pointCol] == pointRow)) {
					//cout << "up" << endl;
					if (added == false) {
						temp1.push_back(aa);
						temp1.push_back(pointCol);
						zed[0].push_back(temp1);
						temp1.clear();
						added = true;
					}
					else {
						temp4.push_back(zed[0]);
						temp4[0].pop_back();
						temp1.push_back(aa);
						temp1.push_back(pointCol);
						temp4[0].push_back(temp1);
						temp1.clear();
						zed.push_back(temp4[0]);
						temp4.clear();

					}
				}

			}
			//check down

			for (int aa = pointRow + 1; aa < row; aa++) {
				if (((aa - v[aa][pointCol]) >= 0) && (aa - v[aa][pointCol] == pointRow)) {
					//cout << "down" << endl;
					if (!added) {
						temp1.push_back(aa);
						temp1.push_back(pointCol);
						zed[0].push_back(temp1);
						temp1.clear();
						added = true;
					}
					else {
						temp4.push_back(zed[0]);
						temp4[0].pop_back();
						temp1.push_back(aa);
						temp1.push_back(pointCol);
						temp4[0].push_back(temp1);
						temp1.clear();
						zed.push_back(temp4[0]);
						temp4.clear();

					}

				}
			}
			//check left
			for (int aa = pointCol - 1; aa >= 0; aa--) {
				if ((aa + v[pointRow][aa] < col) && (aa + v[pointRow][aa] == pointCol)) {
					//cout << "left" << endl;
					if (!added) {
						temp1.push_back(pointRow);
						temp1.push_back(aa);
						zed[0].push_back(temp1);
						temp1.clear();
						added = true;
					}
					else {
						temp4.push_back(zed[0]);
						temp4[0].pop_back();
						temp1.push_back(pointRow);
						temp1.push_back(aa);
						temp4[0].push_back(temp1);
						temp1.clear();
						zed.push_back(temp4[0]);
						temp4.clear();

					}
				}
			}

			//check right
			for (int aa = pointCol + 1; aa < col; aa++) {
				if ((aa - v[pointRow][aa] >= 0) && (aa - v[pointRow][aa] == pointCol)) {
					//cout << "right" << endl;
					if (!added) {
						temp1.push_back(pointRow);
						temp1.push_back(aa);
						zed[0].push_back(temp1);
						temp1.clear();
						added = true;
					}
					else {
						temp4.push_back(zed[0]);
						temp4[0].pop_back();
						temp1.push_back(pointRow);
						temp1.push_back(aa);
						temp4[0].push_back(temp1);
						temp1.clear();
						zed.push_back(temp4[0]);
						temp4.clear();

					}
				}
			}


			if (temp3[0].size() == zed[0].size()) {
				//cout << "they are equal" << endl;
				zed.erase(zed.begin());

			}

			temp3.clear();
			added = false;
			int it = zed.size() - 1;
			
			for (int p = it; p >= 0; p--) {
				//check if last element is intial value
				if (!zed.empty()) {
					lastEl = zed[p].size() - 1;
					if ((startRow == zed[p][lastEl][0]) && (startCol == zed[p][lastEl][1])) {
						
						//zed[p].pop_back();
						solutions.push_back(zed[p]);
						
						zed.erase(zed.begin() + p);
						
						if (p != 0) { 
							p--; 
						}
					}
					
				}
				//check repeating elements
				if (!zed.empty()) {
					lastEl = zed[p].size() - 1;
					int a = lastEl - 1;
					while ((a >= 0)) {
						if ((zed[p][a][0] == zed[p][lastEl][0]) && (zed[p][a][1] == zed[p][lastEl][1])) {
							zed.erase(zed.begin() + p);
							break;
							
						}
						a--;
					}

				}
			}

		}
		count++;

	}
	if (!(solutions.empty())) {
		for (int b = 0; b < solutions.size(); b++) {
			for (int c = solutions[b].size() - 1; c >= 0; c--)
			{
				cout << "[" << solutions[b][c][0] << "," << solutions[b][c][1] << "] ";
			}
			cout << "[" << goalRow << "]" << "[" << goalCol << "] ";
			cout << endl;
			cout << endl;
		}
		//translate 
		for (int a = 0; a < solutions.size(); a++) {
			for (int b = (solutions[a].size() - 1), c = (solutions[a].size() - 2); b > 0; b--, c--) {
				//the move was up or down
				if (solutions[a][b][1] == solutions[a][c][1]) {
					//the move was up
					if (solutions[a][b][0] > solutions[a][c][0]) {
						cout << "U ";
					}
					//the move was down
					else {
						cout << "D ";
					}
				}
				//the move was left or right
				else {
					//the move was left
					if (solutions[a][b][1] > solutions[a][c][1]) {
						cout << "L ";
					}
					//the move was right
					else {
						cout << "R ";
					}
				}
				if (b == 1) {
					//the move was up or down
					if (solutions[a][c][1] == goalCol) {
						//the move was up
						if (solutions[a][c][0] > goalRow) {
							cout << "U ";
						}
						//the move was down
						else {
							cout << "D ";
						}
					}
					//the move was left or right
					else {
						//the move was left
						if (solutions[a][c][1] > goalCol) {
							cout << "L ";
						}
						//the move was right
						else {
							cout << "R ";
						}
					}
				}
			}
			cout << endl;
		}
	}
	else {
		cout << "NO Solutions found!" << endl;
	}


	cout << "----------------------------------------" << endl;
	system("pause");
	return 0;

}
