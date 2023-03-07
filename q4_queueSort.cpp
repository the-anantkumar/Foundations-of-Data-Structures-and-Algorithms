#include <iostream>
#include <queue>
#include <stack>
using namespace std;

bool canSortQueue(queue<int> q) {
    int n = q.size();
    queue<int> aux;
    stack<int> st;
    int expected = 1;
    while (!q.empty()) 
    {
        //accessing each element
        int curr = q.front();
        q.pop();

        if (curr == expected)
        {
            //the current element is sorted
            expected++;
        } 
        else 
        {
            if (!st.empty() && st.top() == expected) 
            {
                //utilize the stack to check if the top elements can be used
                st.pop();
                expected++;
                q.push(curr);
            } 
            else if (aux.empty()) 
            {
                //moving the current element to the auxilliary vector
                aux.push(curr);
            }
             else if (!aux.empty() && aux.back() < curr) 
             {
                //sorting condition
                return false;
            } 
            else 
            {
                while (!aux.empty() && aux.back() >= curr) 
                {
                    //can be sorted so perform the desired operation
                    st.push(aux.back());
                    aux.pop();
                }
                aux.push(curr);
            }
        }
    }
    //utilize the stack to check if the top elements can be used
    while (!st.empty() && st.top() == expected) {
        st.pop();
        expected++;
    }
    while (!aux.empty() && aux.front() == expected) {
        aux.pop();
        expected++;
    }
    return st.empty() && aux.empty();
}

int main() {
    int n, t;
    cout<<"Enter the number of iterations: ";
    cin>>t;
    while(t--)
    {
    cout<<"Enter the number of elements in the queue: ";
    cin>>n;
    queue<int>q;
    cout<<"Enter the elements of the queue: ";
    for (int i = 0; i < n; i++) {
        int num;
        cin>>num;
        q.push(num);
    }
    if (canSortQueue(q)) {
        cout<<"Yes"<<endl;
    } else {
        cout<<"No"<<endl;
    }
    }

    return 0;
}
