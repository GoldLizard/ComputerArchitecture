#include <map>
#include <vector>
using namespace std;       //I redeclare standard map functions to avoid "lookupTable.defaultTable.count()"

struct LookupTables {
    map<string, string> defaultTable = {{"CLA", "7800"}, {"CLE", "7400"}, {"CMA", "7200"}, {"CIR", "7080"},
        /*also adds labels later on*/   {"CIL", "7040"}, {"INC", "7020"}, {"SPA", "7010"}, {"SNA", "7008"},
                                        {"SZA", "7004"}, {"SZE", "7002"}, {"HLT", "7001"}, {"INP", "F800"},
                                        {"OUT", "F400"}, {"SKI", "F200"}, {"SKO", "F100"}, {"ION", "F080"},
                                        {"IOF", "F040"}, {"CME", "7100"}, {"ORG", ""}}; 
    string at(string input){ //for instructions that do NOT care about interrupt
        if(defaultTable.count(input)){
            return defaultTable.at(input); //I hate that map.at() just crashes if key doesnt exist
        }
        return "99999999"; //If string.find() can return obvious garbage data, so should map.at()
    }
    void emplace(string input1, string input2){ defaultTable.emplace(input1, input2); }
    bool count(string input){ return defaultTable.count(input); }


    map<string, vector<string>> interruptTable = {{"AND", {"0", "8"}}, {"ADD", {"1", "9"}}, {"LDA", {"2", "A"}},
       /*{"instruction", {I=0 case, I=1 case}}*/  {"STA", {"3", "B"}}, {"BUN", {"4", "C"}}, {"BSA", {"5", "D"}},
                                                  {"ISZ", {"6", "E"}}};

    string at(string input, bool isInterrupt){ //for instructions that DO care about interrupt
        if(interruptTable.count(input)){                                  //if "AND" key exists
            if(isInterrupt){ return interruptTable.at(input).at(1); }     //if interrupt, return "8"
            else {           return interruptTable.at(input).at(0); }     //if no interrupt, return "0"
        }
        return "99999999"; 
    }
};

struct Row{
    string fullLine = "";
    uint16_t LC = 0x000;
    string machineCode = "";
};

string fitTo4Chars(string input){ 
    while(input.size() < 4){ //fit to 4 chars
        input = "0" + input;
    }
    for(char &eachChar : input){ //capitalizes
        eachChar = toupper(eachChar);
    }
    return input;
}

string convertDecToHex(string input){
    stringstream temp;
    temp << hex << uint16_t(stoi(input)); //convert string to int, cut off extra data with uint16_t
    return temp.str();                    //stringstream automatically converts uint16_t to hex, same line
}

string fitTo3Chars(uint16_t input){
    stringstream HEX;
    HEX << hex << input;
    string temp = HEX.str(); //convert uint16_t to string
    while(temp.size() < 3){  //fit to 3 chars
        temp = "0" + temp;
    }
    for(char &eachChar : temp){ //capitalize
        eachChar = toupper(eachChar);
    }
    return temp;
}