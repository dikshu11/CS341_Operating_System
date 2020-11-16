// CPP Program to Print all possible safe_seq sequences using banker's algorithm 
#include <iostream> 
#include <string.h> 
#include <vector>
#define ll  long long int 
ll total = 0; 
ll res, pro;
using namespace std; 
  
  
// Print all the safe_seq-sequences 
void print_safe_sequence(bool visited[], vector<vector<ll> > allocation_matrix, vector<vector<ll> > req_matrix, 
                   vector<vector<ll> > need_matrix, vector<ll> available_matrix, vector<ll> safe_seq) 
{ 
  
    for (ll i = 0; i < pro; i++) { 
  
        // check if it is not visited 
        // already and can be allocation_matrix 
        if (!visited[i] ) { 
            bool flag = true; 
            for (ll k= 0; k < res; k++) { 
                if (need_matrix[i][k] > available_matrix[k]) 
                    flag = false; 
            } 
            if( flag == false) continue;
            visited[i] = true; 
  
            for (ll j = 0; j < res; j++) 
                available_matrix[j] += allocation_matrix[i][j]; 
  
            safe_seq.push_back(i); 
            // find safe_seq sequence by taking process i 
            print_safe_sequence(visited, allocation_matrix, req_matrix, need_matrix, available_matrix, safe_seq); 
            safe_seq.pop_back(); 
  
            visited[i] = false; 
            for (ll j = 0; j < res; j++) 
                available_matrix[j] -= allocation_matrix[i][j]; 
        } 
    } 
  
    if (safe_seq.size() == pro) { 
    // safe_seq-sequence  found
        if(total == 0)
            cout << "Safe sequences are:" << endl; 

        total++; 
        cout << "Safe sequence " << total << ": ";
        for (ll i = 0; i < pro; i++) { 
  
            cout << "P" << safe_seq[i]; 
            if (i != (pro - 1)) 
                cout << "--> "; 
        } 
  
        cout << endl; 
    } 
} 
  

int main() { 
    
    cout << "Enter the number of processes : \n";
    cin >> pro;
    cout << "Enter the number of resources : \n";
    cin >> res;

    vector<ll> resources(res);

    for (ll i = 0; i < res; i++){
        cout << "Total Amount of the Resource R" << i+1 << ": \n";
        cin >> resources[i];
    }

    cout << "Enter the req_matrix matrix: \n" << endl;

    vector<vector<ll> > req_matrix(pro, vector<ll>(res));

    for (ll i = 0; i < pro; ++i){
        cout << "P" << i << ": \n";
        for (ll j = 0; j < res; ++j) {
            cin >> req_matrix[i][j];
        }
    }

    cout << "Enter the allocation matrix: " << endl;
    vector<vector<ll> > allocation_matrix(pro, vector<ll>(res));

    for (ll i = 0; i < pro; ++i){
        cout << "P" << i << ": \n";
        for (ll j = 0; j < res; ++j) {
            cin >> allocation_matrix[i][j];
        }
    }

    vector<ll> available_matrix(res);
  
    for (ll i = 0; i < res; i++) { 
  
        ll sum = 0; 
        for (ll j = 0; j < pro; j++) 
            sum += allocation_matrix[j][i]; 
  
        available_matrix[i] = resources[i] - sum; 
    } 
  
    vector<ll> safe_seq; 
  
    bool visited[pro]; 
    memset(visited, false, sizeof(visited)); 
  
    vector<vector<ll> > need_matrix(pro, vector<ll>(res));
    for (ll i = 0; i < pro; i++) 
        for (ll j = 0; j < res; j++) 
            need_matrix[i][j] = req_matrix[i][j] - allocation_matrix[i][j]; 
  
    print_safe_sequence(visited, allocation_matrix, req_matrix, need_matrix, available_matrix, safe_seq); 
  
    if(total == 0)
            cout<< "No Safe sequences" << endl; 
    return 0; 
}
