#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>
using namespace std;

struct Feedback{
    int roll;
    string name,subject,comment;
    int rating;
};

vector<Feedback> data;

void load(){
    ifstream in("feedback.txt");
    if(!in) return;
    Feedback f;
    while(in>>f.roll){
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(in,f.name);
        getline(in,f.subject);
        in>>f.rating;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(in,f.comment);
        data.push_back(f);
    }
}
void save(){
    ofstream out("feedback.txt");
    for(auto &f:data){
        out<<f.roll<<"\n"<<f.name<<"\n"<<f.subject<<"\n"<<f.rating<<"\n"<<f.comment<<"\n";
    }
}
void add(){
    Feedback f;
    cout<<"Roll: "; cin>>f.roll; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Name: "; getline(cin,f.name);
    cout<<"Subject: "; getline(cin,f.subject);
    cout<<"Rating(1-5): "; cin>>f.rating; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Comment: "; getline(cin,f.comment);
    data.push_back(f);
    cout<<"Added!\n";
}
void view(){
    if(data.empty()){ cout<<"No records\n"; return; }
    cout<<left<<setw(8)<<"Roll"<<setw(20)<<"Name"<<setw(15)<<"Subject"<<setw(8)<<"Rate"<<"Comment\n";
    for(auto &f:data)
        cout<<setw(8)<<f.roll<<setw(20)<<f.name<<setw(15)<<f.subject<<setw(8)<<f.rating<<f.comment<<"\n";
}
void search(){
    int r; cout<<"Roll: "; cin>>r;
    for(auto &f:data)
        if(f.roll==r){
            cout<<f.name<<" "<<f.subject<<" "<<f.rating<<" "<<f.comment<<"\n";
            return;
        }
    cout<<"Not Found\n";
}
void update(){
    int r; cout<<"Roll: "; cin>>r; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(auto &f:data){
        if(f.roll==r){
            cout<<"New Name: "; getline(cin,f.name);
            cout<<"New Subject: "; getline(cin,f.subject);
            cout<<"New Rating: "; cin>>f.rating; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"New Comment: "; getline(cin,f.comment);
            cout<<"Updated\n"; return;
        }
    }
    cout<<"Not Found\n";
}
void del(){
    int r; cout<<"Roll: "; cin>>r;
    auto it=remove_if(data.begin(),data.end(),[&](Feedback &f){return f.roll==r;});
    if(it!=data.end()){ data.erase(it,data.end()); cout<<"Deleted\n"; }
    else cout<<"Not Found\n";
}
void average(){
    if(data.empty()){ cout<<"No data\n"; return; }
    double s=0;
    for(auto &f:data) s+=f.rating;
    cout<<"Average Rating: "<<fixed<<setprecision(2)<<s/data.size()<<"\n";
}
void subjectAverage(){
    string sub;
    cout<<"Subject: "; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin,sub);
    double s=0; int c=0;
    for(auto &f:data) if(f.subject==sub){ s+=f.rating; c++; }
    if(c) cout<<"Average: "<<s/c<<"\n";
    else cout<<"No records\n";
}
void login(){
    string u,p;
    do{
        cout<<"Username: "; cin>>u;
        cout<<"Password: "; cin>>p;
        if(u!="admin"||p!="admin123") cout<<"Invalid Login\n";
    }while(u!="admin"||p!="admin123");
}
int main(){
    load();
    login();
    int ch;
    do{
        cout<<"\n1.Add\n2.View\n3.Search\n4.Update\n5.Delete\n6.Overall Average\n7.Subject Average\n8.Save\n9.Exit\nChoice: ";
        cin>>ch;
        switch(ch){
            case 1: add(); break;
            case 2: view(); break;
            case 3: search(); break;
            case 4: update(); break;
            case 5: del(); break;
            case 6: average(); break;
            case 7: subjectAverage(); break;
            case 8: save(); cout<<"Saved\n"; break;
            case 9: save(); cout<<"Goodbye\n"; break;
            default: cout<<"Invalid\n";
        }
    }while(ch!=9);
}
