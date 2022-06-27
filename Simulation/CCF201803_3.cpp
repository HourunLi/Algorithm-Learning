/**
 * @file CCF201803_3.cpp
 * @author HourunLi
 * @brief simulation(string process) 
 * @version 0.1
 * @date 2022-06-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<bits/stdc++.h>
using namespace std;

#define N 102
vector<string> rules[N];
string name[N];
bool tail[N];
int n, m;

bool process(vector<string> &vec, string &buffer) {
    int pre = 1, now = buffer.find('/', pre);
    int len = buffer.size();
    while(now != string::npos) {
        // cout << pre <<endl;
        vec.push_back(buffer.substr(pre, now-pre));
        pre = now+1;
        now = buffer.find('/', pre);
    }
    if(pre < len) {
        vec.push_back(buffer.substr(pre));
    }
    return buffer[len-1] == '/';
}

bool processInt(vector<string> &ret, string &buffer) {
    string ans;
    int begin = 0, len = buffer.size();
    for(begin; begin < len; begin++) {
        if(buffer[begin] == '0')
            continue;
        break;
    }
    for(begin; begin < len; begin++) {
        char ch = buffer[begin];
        if(ch < '0' || ch > '9') return true;
        ans += ch;
    }
    if(ans != "")
        ret.push_back(ans);
    return false;
}

bool processStr(vector<string> &ret, string &buffer) {
    string ans;
    int len = buffer.size();
    for(int begin = 0; begin < len; begin++) {
        char ch = buffer[begin];
        if(ch >= '0' && ch <= '9' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '-' || ch == '_' || ch == '.') {
            ans += ch;
        } else{
            return true;
        }
    }
    if(ans != "")
        ret.push_back(ans);
    return false;
}
void match(vector<string> &vec, bool flag) {
    vector<string> ret;
    for(int i = 0; i < n; i++) {
        ret = vector<string>();
        if(tail[i] != flag && rules[i].back() != "<path>") continue;
        if(rules[i].size() > vec.size() || rules[i].size() < vec.size() && rules[i].back() != "<path>") continue;
        bool fail = false;
        for(int j = 0; j < rules[i].size(); j++) {
            if(rules[i][j] == "<int>") {
                if(processInt(ret, vec[j])) {
                    fail = true;
                    break;
                }
            }else if(rules[i][j] == "<str>") {
                if(processStr(ret, vec[j])) {
                    fail = true;
                    break;
                }
            }else if(rules[i][j] == "<path>") {
                string ans = "";
                int len = vec.size();
                for(int l = j; l < len; l++) {
                    ans += vec[l];
                    if(l+1 == len) continue;
                    ans += "/";
                }
                if(flag) {
                    ans += "/";
                }
                ret.push_back(ans);
                break;
            }else if(rules[i][j] != vec[j]){
                fail = true;
                break;
            }
        }
        if(fail) {
            continue;
        }else {
            cout << name[i];
            for(string j : ret) {
                cout << " " << j;
            }
            cout << endl;
            return;
        }
    }
    cout << 404 << endl;
    return;
}
int main() {
    // freopen("input.txt", "r", stdin);
    string buffer;
    cin >> n >> m; 
    for(int i = 0; i < n; i++) {
        cin >> buffer >> name[i];
        tail[i] = process(rules[i], buffer);
    }
    for(int i = 0; i < m; i++) {
        cin >> buffer;
        vector<string> vec;
        bool flag = process(vec, buffer);
        match(vec, flag);
    }
    return 0;
}