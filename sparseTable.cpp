#include <bits/stdc++.h>
using namespace std;
class sparseTable{
private:
    vector<vector<int>>sparseMatrix;
    vector<int>elements;
    int row , col;
public:
    sparseTable(int row , int col , vector<int>elm){
        elements = elm;
        this->row = row;
        this->col = col;
        sparseMatrix = vector<vector<int>>(row , vector<int>(col ,-1));
    }
    void BuildSparseTable(){
        for (int c = 0; c <col ; ++c) {
            for (int r = 0; r < row; ++r) {
                if(!c){
                    sparseMatrix[r][c] = r;
                }
                else{
                    int prevCol = c-1;
                    int nextRow = min(r + (1 <<prevCol) , row-1);
                    int firstIdx = sparseMatrix[r][prevCol];
                    int secondIdx = sparseMatrix[nextRow][prevCol];

                    if(elements[firstIdx] <= elements[secondIdx]){
                        sparseMatrix[r][c] = firstIdx;
                    }
                    else{
                        sparseMatrix[r][c] = secondIdx;
                    }
                }
            }
        }
    }
    int minQuery(int left , int right){
        int length = right - left + 1;
        int col1 = (int) log2(length);
        int minIndex = sparseMatrix[left][col1];

        int remElement = max(length - (1 <<col1) , 0);

        int row2 = min(left + remElement , row-1 );
        int minIndex2 = sparseMatrix[row2][col1];
        if(elements[minIndex] <=elements[minIndex2]){
            return elements[minIndex];
        }
        else{
            return  elements[minIndex2];
        }
    }
    void printSparseMatrix(){
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                cout<<sparseMatrix[r][c]<<' ';
            }
            cout<<'\n';
        }
    }
};
void solve(){
  int n = 6;
  vector<int>elm ={4,6,1,5,7,3};
  int m = (int)log2(n) + 1;
  sparseTable st(n , m ,elm);
  st.BuildSparseTable();
  st.printSparseMatrix();
    cout<<st.minQuery(0,4)<<'\n';
    cout<<st.minQuery(3,5)<<'\n';
    cout<<st.minQuery(0,5)<<'\n';
    cout<<st.minQuery(0,3)<<'\n';
    cout<<st.minQuery(4,5)<<'\n';
    cout<<st.minQuery(3,4)<<'\n';

}

signed main() {
    int tc = 1;
    //cin >> tc;
    while (tc--) {
        solve();
    }
}
