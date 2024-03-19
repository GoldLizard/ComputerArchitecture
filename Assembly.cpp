#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include "lookupTables.h"
using namespace std;

int main(){
    vector<Row*> allRows = {};
    LookupTables lookupTable;
    ifstream inFS;
    ofstream outCDM, outSYM;
    string fileNameInput, fileNameOutput, line, instruction, trash;
    int16_t LC = 0x000;

    cout << "Alan Golden" << endl;
    cout  << "Input full file name. (Ex: \"testFile1.asm\")" << endl << "File: ";
    cin >> fileNameInput;
    cout << endl;
    inFS.open(fileNameInput); //open file as inFS
    outCDM.open("program.cdm"); //compiled assembly
    outSYM.open("program.sym"); //symbols

    while(!inFS.eof()){ //1st pass code
        Row* currentRow = new Row;          //define new row
        getline(inFS, line);                //getLine to parse
        currentRow->fullLine = line;        //store line for 2nd pass
        stringstream ASMline(line);         //prepare to parse

        if(line.find("ORG") < line.size()){ //ORG case, only change LC
            ASMline >> trash >> hex >> LC;
        }
        else{ //every other case
            if(line.find(",") < line.size()){ //label case
                line.resize(line.find(","));       //extract label from line
                lookupTable.emplace(line, fitTo3Chars(LC)); //remember label reference for later
                outSYM << line << ": " << lookupTable.at(line) << endl;
            }
            currentRow->LC = LC;
            LC++;
        }
        allRows.push_back(currentRow);
    }

    for(int i = 0; i < allRows.size(); i++){ //2nd pass code, using allRows generated in 1st pass
        Row* currentRow = allRows.at(i);
        line = currentRow->fullLine;
        if(line.find("/") < line.size()){                           //get rid of comments by resizing each line        
            line.resize(line.find("/")-1);
        }
        
        stringstream ASMline(line);
        ASMline >> instruction;                                     //parse first instruction
        if(!(instruction.find("ORG") < instruction.size())              //while not ORG or END line
        && !(instruction.find("END") < instruction.size())){
            if(instruction.find(",") < instruction.size()){             //label case, if "," present
                ASMline >> instruction;                                 //trash the first instruction, continue parsing
            }
            if(instruction == "HEX"){                                   //HEX case, if "HEX" present
                ASMline >> instruction;                                 //remember next instruction as machine code
                currentRow->machineCode = fitTo4Chars(instruction);     
            }
            else if(instruction == "DEC"){                              //DEC case
                ASMline >> instruction;                                 //remember next instruction as machine code
                currentRow->machineCode = fitTo4Chars(convertDecToHex(instruction));
            }
            else if(lookupTable.count(instruction)){                    //normal instruction case, no operand
                currentRow->machineCode = lookupTable.at(instruction);  //get machine code from table
            }
            else{                                                       //I = 0 or I = 1 case, depends on operand
                bool isInterrupt = (line.find(" I") < line.size())  &&  !(line.find("  I") < line.size());
                currentRow->machineCode = lookupTable.at(instruction, isInterrupt); //2xxx
                ASMline >> hex >> instruction;                                      //get next instruction
                currentRow->machineCode += lookupTable.at(instruction);             //2xxx + x10B = 210B
            }
            if(currentRow->machineCode != ""){     //skip printing ORG and END lines
                outCDM << fitTo3Chars(currentRow->LC) << ": " << fitTo4Chars(currentRow->machineCode) << endl;
            }
        }
    }
    cout << "program.cdm and program.sym generated in same directory" << endl;
    system("Pause");
    return 0;
}