#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#define order 3
using namespace std;

struct Node{
    vector< pair<int,int> > key;
    vector<Node*>address; 
};
void insert_nonleaf(Node* , Node* , Node* ,pair<int,int>);
Node* Root=NULL;
stack <Node*> parent;
Node* Create_Node(){
    Node* Root_temp=new Node();
    (Root_temp->address).resize(order+1,NULL);
    return Root_temp;
}
bool is_parent_exist(Node* Root_temp){
    if(parent.empty()){
        return false;
    }
    return true;
}
void split_nonleaf(Node* Root_temp){
    int start=0;
    int end=(Root_temp->key).size();
    int mid=(start+end)/2;
    pair<int,int> mid_val = Root_temp->key[mid];
    Node* temp=Create_Node();
    int i=mid+1;
    for(;i<end;i++){
        temp->key.push_back(Root_temp->key[i]);
        temp->address[i-mid-1]=(Root_temp->address[i]);
    }
    temp->address[i-mid-1]=(Root_temp->address[i]);
    i=0;
    for(;i<end-mid;i++){
        Root_temp->key.pop_back();
        Root_temp->address[i+mid+1]=NULL;
    }
    Root_temp->address[end]=NULL;
    if(!is_parent_exist(Root_temp)){
        Node* node=Create_Node();
        node->key.push_back(mid_val);
        node->address[0]=Root_temp;
        node->address[1]=temp;
        Root=node;
    }
    else{
        //Idhar humko tab karna hai jab non-leaf node kaa parent ho tab!!!!!!!!!!!!
        Node* p = parent.top();
        parent.pop();
        insert_nonleaf(p,Root_temp,temp,mid_val);
    }

}
void insert_nonleaf(Node* Root_temp, Node* left, Node* Right,pair<int,int>a){
    if((Root_temp->key).size()<order-1){
        int set=0;
        int j=0;
        vector<pair<int,int> > :: iterator i=(Root_temp->key).begin();

        for(;i!=(Root_temp->key).end() && j<(Root_temp->address).size();i++,j++){
            if (a.first < (*i).first){
                set=1;
                (Root_temp->key).insert(i,make_pair(a.first,a.second));
                for(int x=Root_temp->address.size()-1; x>j+1 ;x--){
                    Root_temp->address[x]=Root_temp->address[x-1];
                }
                Root_temp->address[j+1]=Right;
                break;
            }           
        }
        if (set==0){
            (Root_temp->key).push_back(make_pair(a.first,a.second));
            int index = (Root_temp->key).size();
            (Root_temp->address)[index] = Right;
        }        
    }
    else{
        int set=0;
        int j=0;
        vector<pair<int,int> > :: iterator i=(Root_temp->key).begin();

        for(;i!=(Root_temp->key).end() && j < (Root_temp->address).size();i++,j++){
            if (a.first < (*i).first){
                set=1;
                (Root_temp->key).insert(i,a);
                for(int x=Root_temp->address.size()-1;x>j+1;x--){
                    Root_temp->address[x]=Root_temp->address[x-1];
                }
                Root_temp->address[j+1]=Right;
                break;
            }           
        }
        if (set==0){
            (Root_temp->key).push_back(make_pair(a.first,a.second));
            int index = (Root_temp->key).size();
            (Root_temp->address)[index] = Right;
        }
        if ((Root_temp->key).size()==order){
            split_nonleaf(Root_temp);
        }
    }

}
void split_leaf(Node* Root_temp){
    int start=0;
    int end=(Root_temp->key).size();
    int mid=(start+end)/2;
    Node* temp=Create_Node();
    for(int i=mid;i<end;i++){
        temp->key.push_back(Root_temp->key[i]);
    }
    for(int i=0;i<end-mid;i++){
        Root_temp->key.pop_back();
    }
    temp->address[order-1]=Root_temp->address[order-1];
    Root_temp->address[order-1]=temp;
    if (!is_parent_exist(Root_temp)){
        
        Node* node=Create_Node();
        node->key.push_back(temp->key[0]);
        node->address[0]=Root_temp;
        node->address[1]=temp;
        Root=node;
    }
    else{
        //Idhar humko tab karna hai jab leaf node kaa parent ho tab!!!!!!!!!!!!
        Node* p = parent.top();
        parent.pop();
        insert_nonleaf(p,Root_temp,temp,temp->key[0]);
    }
}

void insert_leaf(int a,Node* Root_temp){
    if((Root_temp->key).size()<order-1){
        int set=0;
        for(vector<pair<int,int> > :: iterator i=(Root_temp->key).begin();i!=(Root_temp->key).end();i++){
            if (a < (*i).first){
                set=1;
                (Root_temp->key).insert(i,make_pair(a,1));
                break;
            }
            else if (a==(*i).first){
                set=1;
                (*i).second+=1;
                break;
            }            
        }
        if (set==0){
            (Root_temp->key).push_back(make_pair(a,1));
        }        
    }
    else{
        int set=0;
        for(vector<pair<int,int> > :: iterator i=(Root_temp->key).begin();i!=(Root_temp->key).end();i++){
            if (a < (*i).first){
                set=1;
                (Root_temp->key).insert(i,make_pair(a,1));
                break;
            }
            if (a==(*i).first){
                set=1;
                (*i).second+=1;
                break;
            }            
        }
        if (set==0){
            (Root_temp->key).push_back(make_pair(a,1));
        }
        if ((Root_temp->key).size()==order){
            split_leaf(Root_temp);
        }
    }
}
bool is_leaf(Node* Root_temp){
    for(int x=0;x <order-1; x++){
        if((Root_temp->address)[x] != NULL){
            return false;
        }
    }
    return true;
}
void insert(int a, Node* Root_temp){
    if (Root_temp->key.size()==0){
        Root_temp->key.push_back(make_pair(a,1));
    }
    else{
    int position=-1;
    for(int i=0;i<(Root_temp->key).size();i++){
        if(a < (Root_temp->key)[i].first){
            position=i;
            break;
        }
        else if(a==(Root_temp->key)[i].first){
            position=i+1;
            break;
        }
      }
      if(is_leaf(Root_temp)){
            insert_leaf(a,Root_temp);
        }
    else{
        parent.push(Root_temp);
        if (position==-1){
            insert(a,Root_temp->address[(Root_temp->key).size()]);
        }
        
        else{
        insert(a,Root_temp->address[position]);
        }
    }
    }
    while(!parent.empty()){
        parent.pop();
    }
}

void Find_helper(int a,Node* Root_temp){
    int position=-1;
    if(is_leaf(Root_temp)){
        for(int i=0;i<Root_temp->key.size();i++){
            if(Root_temp->key[i].first == a){
                cout<<"YES"<<endl;
                return;
            }
        }
        cout<<"NO"<<endl;
        return;
    }
    for(int i=0;i<(Root_temp->key).size();i++){
        if(a < (Root_temp->key)[i].first){
            position=i;
            break;
        }
        else if(a == (Root_temp->key)[i].first){
            position=i+1;
            break;
        }
    }
    if (position==-1){
        Find_helper(a,Root_temp->address[(Root_temp->key).size()]);
    }
        
    else{
        
        Find_helper(a,Root_temp->address[position]);
    }

}
void count_helper(int a,Node* Root_temp){
    int position=-1;
    if(is_leaf(Root_temp)){
        for(int i=0;i<Root_temp->key.size();i++){
            if(Root_temp->key[i].first == a){
                cout<<"Count: "<<Root_temp->key[i].second<<endl;
                return;
            }
        }
        cout<<"Element Doesn't Exists!!!!"<<endl;
        return;
    }
    for(int i=0;i<(Root_temp->key).size();i++){
        if(a < (Root_temp->key)[i].first){
            position=i;
            break;
        }
        else if(a == (Root_temp->key)[i].first){
            position=i+1;
            break;
        }
    }
    if (position==-1){
        count_helper(a,Root_temp->address[(Root_temp->key).size()]);
    }
        
    else{
        count_helper(a,Root_temp->address[position]);
    }

}
void Find(int a){
    cout<<"Finding if "<<a<<" Exists:"<<endl;
    Find_helper(a,Root);
}
void count(int a){
    cout<<"Count of "<<a<<":"<<endl;
    count_helper(a,Root);
}
void Range(int x, int y){
    cout<<"Range: "<<endl;
    Node* Root_temp = Root;
    while(Root_temp->address[0]!=NULL){
        Root_temp=Root_temp->address[0];
    }
    while(1){
        for(int i=0;i<(Root_temp->key).size();i++){
            if (Root_temp->key[i].first>=x && Root_temp->key[i].first<=y){
                for(int j=0;j<Root_temp->key[i].second;j++){
                    cout<<Root_temp->key[i].first<<endl;
                }
            }
        }
        if (Root_temp->address[order-1] != NULL){
        Root_temp = Root_temp->address[order-1];
        }
        else{
            break;
        }
    }
}
vector<string>split(string s,char del){
  stringstream ss(s);
  vector<string>request;
  string temp;
  while(getline(ss,temp,del)){
    request.push_back(temp);
  }
  return request;
}
int main(int argc,char** argv){
    if(argc!=2){
        cout<<"Input Filename not given!!!"<<endl;
        return -1;
    }
    Root= Create_Node();
    string filename = argv[1];

    ifstream in(filename.c_str());

    if(!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    char str[255];

    while(in) {
        in.getline(str, 255);
        vector<string> s;
        s = split(str , ' ' );
        if(in){
            if(s[0]=="INSERT"){
                stringstream temp(s[1]);
                int x=0;
                temp>>x;
                insert(x,Root);
            }
            else if(s[0]=="RANGE"){
                stringstream low(s[1]);
                stringstream high(s[2]);
                int x=0,y=0;
                low >> x;
                high >> y;
                Range(x,y);
            }
            else if(s[0]=="COUNT"){
                stringstream temp(s[1]);
                int x=0;
                temp >> x;
                count(x);
            }
            else if(s[0]=="FIND"){
                stringstream temp(s[1]);
                int x=0;
                temp >> x;
                Find(x);
            }
        }
    }

    in.close();
    return 0;
}