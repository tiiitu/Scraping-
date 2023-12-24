#include <bits/stdc++.h>
using namespace std;

vector<string>extract_all_dates(string &input) {
    regex dateRegex("\\b(\\d{1,2})\\s+(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec|jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)\\.\\s+(\\d{4})\\b");

    sregex_iterator iterator(input.begin(), input.end(), dateRegex);

    std::sregex_iterator endIterator; 
    
    vector<string>dates;
    
    while (iterator != endIterator) {
        dates.push_back(iterator->str());
        ++iterator;
    }
    return dates;
}

pair<int,int> extract_index(regex &reg,string &input) {
    smatch match;
    if (regex_search(input,match,reg))
    {
        size_t startIdx = match.position();
        size_t endIdx = startIdx + match.length();
        return {(int)startIdx,(int)endIdx};
    }
    return {-1,-1};
}

string extract_first_name(string &input,int start,int end) {
    string s;
    while(start<end)
    {
        s.push_back(input[start]);
        start++;
    }
    return s;
}

string extract_last_name(string &input,int start) {
    string s;
    while(start<input.size() and (islower(input[start]) or isupper(input[start]) or isdigit(input[start]) or isspace(input[start]))){
        s.push_back(input[start]);
        start++;
    }
    return s;
}

string extract_id(string &input,int start) {
    string s;
    while(start<input.size() and (isdigit(input[start]) or isspace(input[start])))
    {
        s.push_back(input[start]);
        start++;
    }
    return s;
}

string refine(string &myString){
    size_t firstNonSpace = myString.find_first_not_of(" \t");
    if (firstNonSpace != std::string::npos) {
        myString = myString.substr(firstNonSpace);
    }
    size_t lastNonSpace = myString.find_last_not_of(" \t");
    if (lastNonSpace != std::string::npos) {
        myString = myString.substr(0, lastNonSpace + 1);
    }
    return myString;
}

int main() {
    
    string input = "บัตรประจำตัวประชาชน Thai National ID Card 1 1037 02071 81 1 เลขประจำตัวประชาชน Identification Number ชื่อตัวและชื่อสกุล น.ส. ณัฐริกา ยางสวย Name Miss Nattarika Last name Yangsuai เกิดวันที่ 25 มิ.ย. 2539 Date of Birth 25 Jun. 1996 ศาสนา พุทธ ที่อยู่ 111/17 หมู่ที่ 2 ต.ลาดหญ้า อ.เมืองกาญจนบุรี จ.กาญจนบุรี 24 ก.ค. 2553 - วันออกบัตร 24 Jul. 2020 Date of Issue from (นายธนาคม จงจิระ เจ้าพนักงานออกบัตร 24 9.8. 2572 วันบัตรหมดอายุ 24 Jun. 2023 2 Date of Expiry 160 15 _160 150 40 1398-09-07241719";
    
    // cout<<input<<endl;
    
    regex lastNameRegex("\\bLast name\\b");
    regex firstNameRegex("\\bName\\b");
    regex idCard("\\Thai National ID Card\\b");
    
    pair<int,int>x1=extract_index(firstNameRegex,input);
    pair<int,int>x2=extract_index(lastNameRegex,input);
    pair<int,int>x3=extract_index(idCard,input);
    
    
    if(x1.first==-1 || x2.first==-1 || x3.first==-1)
    {
        if(x1.first==-1)
        {
            cout<<"index for first name not found. Hence not able to fetch the first name."<<endl;
        }
        if(x2.first==-1)
        {
            cout<<"index for last name not found. Hence not able to fetch the last name."<<endl;
        }
        if(x3.first==-1)
        {
            cout<<"index for Thai National ID Card not found. Hence not able to fetch the ID."<<endl;
        }
    }
    else
    {
        string firstName=extract_first_name(input,x1.second+1,x2.first);
        string lastName=extract_last_name(input,x2.second+1);
        string id=extract_id(input,x3.second);
        id.erase(remove_if(id.begin(),id.end(),::isspace),id.end());
        firstName=refine(firstName);
        lastName=refine(lastName);
        
        cout<<"First name : "<<firstName<<endl;
        cout<<"Last name : "<<lastName<<endl;
        cout<<"Thai National Id :"<<id<<endl;
        
    }
    
    vector<string>dates=extract_all_dates(input);
    
    if(dates.size()==3)
    {
        cout<<"Date of Birth: "<<dates[0]<<endl;
        cout<<"Date of issue: "<<dates[1]<<endl;
        cout<<"Date of expiry: "<<dates[2]<<endl;
    }
    else
    {
        cout<<"Not enough dates fetched.";
    }
    
    return 0;
}
