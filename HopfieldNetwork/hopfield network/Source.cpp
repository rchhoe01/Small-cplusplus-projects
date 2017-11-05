
#include <iostream>
#include <vector>
using namespace std;

std::vector<vector<int>> temp1;
std::vector<int> temp2;

//multiplies two matricies
vector<vector<int>> vectMult(vector<vector<int>> a, vector<vector<int>> b)
{
	temp1.clear();
	int aRows = a.size();
	int aColumns = a[0].size();
	int bRows = b.size();
	int bColumns = b[0].size();

	if (aColumns == bRows) {
		//fills the temporary matrix with 0
		for (int i = 0; i < aRows; i++) {
			for (int j = 0; j < bColumns; j++) {
				temp2.push_back(0);
			}
			temp1.push_back(temp2);
			temp2.clear();
		}
		//performs matrix multiplication and stores the values in temp1
		for (int i = 0; i < aRows; i++) { // aRow
			for (int j = 0; j < bColumns; j++) { // bColumn
				for (int k = 0; k < aColumns; k++) { // aColumn
					temp1[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}
	return temp1;

}
//adds two matricies
vector<vector<int>> vectAdd(vector<vector<int>> a, vector<vector<int>> b) {
	temp1.clear();
	int aRows = a.size();
	int aColumns = a[0].size();
	int bRows = b.size();
	int bColumns = b[0].size();

	if ((aRows == bRows) && (aColumns == bColumns)) {
		for (int i = 0; i < aRows; i++) {
			for (int j = 0; j < bColumns; j++) {
				temp2.push_back(0);
			}
			temp1.push_back(temp2);
			temp2.clear();
		}
		for (int i = 0; i < aRows; i++) {
			for (int j = 0; j < bColumns; j++) {
				temp1[i][j] = a[i][j] + b[i][j];
			}
		}
	}
	return temp1;
}
//makes the diagonals of a matrix 0
vector<vector<int>> vectDiagonalize(vector<vector<int>> a) {
	int aRows = a.size();
	int aColumns = a[0].size();
	if (aRows == aColumns) {
		for (int i = 0; i < aRows; i++) {
			a[i][i] = 0;
		}
	}
	return a;
}
//rotates the matrix for transposition
vector<vector<int>> vectRotate(vector<vector<int>> a) {
	temp1.clear();
	int aRows = a.size();
	int aColumns = a[0].size();
	//fills the temporary matrix with 0
	for (int i = 0; i < aColumns; i++) {
		for (int j = 0; j < aRows; j++) {
			temp2.push_back(0);
		}
		temp1.push_back(temp2);
		temp2.clear();
	}
	int tempCol = 0;
	//rotates the matrix
	for (int i = aRows -1; i >= 0; i--) {
		for (int j = 0; j < aColumns; j++) {
			temp1[j][tempCol] = a[i][j];
		}
		tempCol++;
	}

	return temp1;
}
//turns the matrix values into 1s and -1s
vector<vector<int>> vectReduce(vector<vector<int>> a) {
	int aRows = a.size();
	int aColumns = a[0].size();
	
	for (int i = 0; i < aRows; i++) {
		for (int j = 0; j < aColumns; j++) {
			if (a[i][j] < 0) {
				a[i][j] = -1;
			}
			else {
				a[i][j] = 1;
			}
		}
	}
	return a;
}
//checks if two matricies are equal
bool vectEqual(vector<vector<int>> a, vector<vector<int>> b) {
	int aRows = a.size();
	int aColumns = a[0].size();
	int bRows = b.size();
	int bColumns = b[0].size();
	if ((aRows == bRows) && (aColumns == bColumns)) {
		for (int i = 0; i < aRows; i++) {
			for (int j = 0; j < bColumns; j++) {
				if (a[i][j] != b[i][j]) {
					return false;
				}
			}
		}
	}
	else {
		return false;
	}
	return true;
}
//does the main operations of xm + x then reduces to 1s and -1s in a loop
void loop(vector<vector<int>> X, vector<vector<int>> P1, vector<vector<int>> P2, vector<vector<int>> M) {
	int count = 0;
	while (count>=0) {
		X = vectReduce(vectAdd(vectMult(M, X), X));
		
		if (vectEqual(X, P1)) {
			cout << "The Process converges to P1" << endl;
			break;
		}

		if (vectEqual(X, P2)) {
			cout << "The Process converges to P2" << endl;
			break;
		}

		count++;
		
		if (count==1000) {
			cout << "The Process does not converge(1000 iterations tested)" << endl;
			break;
		}
	}

	


}

int main()
{
	vector<int> temp3;
	vector<vector<int>> P1;
	temp3.push_back(-1);
	temp3.push_back(1);
	temp3.push_back(1);
	temp3.push_back(1);
	P1.push_back(temp3);
	temp3.clear();
	vector<vector<int>> P2;
	temp3.push_back(1);
	temp3.push_back(1);
	temp3.push_back(-1);
	temp3.push_back(-1);
	P2.push_back(temp3);
	temp3.clear();
	vector<vector<int>> X1;
	temp3.push_back(-1);
	temp3.push_back(1);
	temp3.push_back(1);
	temp3.push_back(-1);
	X1.push_back(temp3);
	temp3.clear();
	vector<vector<int>> X2;
	temp3.push_back(-1);
	temp3.push_back(1);
	temp3.push_back(-1);
	temp3.push_back(-1);
	X2.push_back(temp3);
	temp3.clear();
	vector<vector<int>> X3;
	temp3.push_back(1);
	temp3.push_back(-1);
	temp3.push_back(1);
	temp3.push_back(-1);
	X3.push_back(temp3);
	temp3.clear();
	vector<vector<int>> M = vectDiagonalize(vectAdd(vectMult(vectRotate(P1),P1),vectMult(vectRotate(P2),P2)));
	
	//checks x1, x2, x3, if they converge or not, it will go through 1000 iterations to check
	cout << "for X1: ";
	loop(vectRotate(X1), vectRotate(P1), vectRotate(P2), M);
	cout << "for X2: ";
	loop(vectRotate(X2), vectRotate(P1), vectRotate(P2), M);
	cout << "for X3: ";
	loop(vectRotate(X3), vectRotate(P1), vectRotate(P2), M);

	/*for (int m = 0; m < M.size(); m++) {
		for (int n = 0; n < M[0].size(); n++) {
			cout << M[m][n] << +"    ";
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}*/



}