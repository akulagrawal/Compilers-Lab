#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define mp make_pair
#define MAX 1000006
#define mod 1000000007
#define pb push_back
#define INF 1e18
#define pii pair<int,int>
#define OFFSET 268435455

struct quad {
	string opcode;
	string op1;
	string op2;
	string res;
};

int isfull[MAX];
map<string, char> type;
map<string, int> mapmem;
map<string, int> funcArgs;
map<string, int> isArray;

int getmem(string s, char ch = 'i') {
	if(mapmem[s])
		return mapmem[s];
	for(int i=1;i<MAX;i+=4) {
		if(!isfull[i]) {
			mapmem[s] = i;
			isfull[i] = 1;
			type[s] = ch;
			return i;
		}
	}
	exit(1);
}

string hextoken(int x) {
	if (x % 16 < 10)
		return to_string(x % 16);
	string s;
	s.push_back('a' + x % 16 - 10);
	return s;
}

string to_hex(int y) {
	long long x = (long long)y;
	x+= OFFSET;
	string s;
	while(x) {
		s = hextoken(x % 16) + s;
		x/=16;
	}
	s = "0x" + s;
	return s;
}

int main(int argc, char **argv)
{
    freopen ("./Assembly.asm","w",stdout);
	// File pointer
	fstream fin;
	vector<quad> quadlist;
	quad temp;

	// Open an existing file
	fin.open("./IR.csv", ios::in);
	vector<string> row;
	string line, word;
	vector<string> v;
	v.push_back(".data 0x10000000\n.text\n.globl main\nmain: ");

	while (fin >> line) {
		row.clear();

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, ',')) {
			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}
		temp.opcode = row[0];
		temp.op1 = row[1];
		temp.op2 = row[2];
		temp.res = row[3];
		quadlist.push_back(temp);
		// cout << "Opcode: " << temp.opcode << "\n";
		// cout << "Op1   : " << temp.op1 << "\n";
		// cout << "Op1   : " << temp.op2 << "\n";
		// cout << "Res   : " << temp.res << "\n";
	}
	map<string, int> isLabel;
	int labelidx = 1;
	for(int i=0;i<quadlist.size();i++) {
		if((quadlist[i].opcode == "ifF") || (quadlist[i].opcode == "ifT")) {
			if(!isLabel[quadlist[i].res]) {
				isLabel[quadlist[i].res] = labelidx;
				labelidx++;
			}
		}
		if((quadlist[i].opcode == "jmp") || (quadlist[i].opcode =="ljmp")) {
			if(!isLabel[quadlist[i].res]) {
				isLabel[quadlist[i].res] = labelidx;
				labelidx++;
			}
		}
	}
	for(int i=0;i<quadlist.size();i++) {
		string idx = to_string(i);
		if(isLabel[idx])
			v.push_back("Label" + to_string(isLabel[idx]) + ":");
		temp = quadlist[i];
		int nsize = 3000;
		if(temp.opcode == "assign") {
			if(isdigit(temp.op2[0])) {
				int x = getmem(temp.res, temp.op1[0]);
				if(temp.op1 == "int"){
					v.push_back("li $t0, 0");
					v.push_back("sw $t0, " + to_hex(x) + "($0)");
				}
				else{
					v.push_back("li.s $f0, 0.0");
					v.push_back("s.s $f0, " + to_hex(x) + "($0)");
				}
			}
			else {
				for(int i=0;i<nsize;i++){
					int x = getmem(temp.res + "[" + to_string(i) + "]", temp.op1[0]);
				}
				isArray[temp.res] = 1;
				type[temp.res] = temp.op1[0];
			}
		}
		if(temp.opcode == "=") {
			
			if(temp.res[temp.res.size() - 1] == ']'){
				string sname, soffset;
				int l;
				for(l=0;l<temp.res.size();l++){
					if(temp.res[l] == '[')
						break;
					sname = sname + temp.res[l];
				}
				l++;
				while(l<temp.res.size()){
					if(temp.res[l] == ']')
						break;
					soffset = soffset + temp.res[l];
					l++;
				}
				v.push_back("li $t3, " + to_string(OFFSET + 1 + mapmem[temp.res + "[0]"]));
				v.push_back("lw $t4, " + to_hex(mapmem[soffset]) + "($0)");
				v.push_back("sll $t4, $t4, 2");
				v.push_back("add $t5, $t3, $t4");
				//v.push_back("lw $t6, 0($t5)");
				if(type[sname] == 'i'){
					if(isdigit(temp.op1[0]))
						v.push_back("li $t0, " + temp.op1);
					else
						v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
					v.push_back("sw $t0, 0($t5)");
				}
				else{
					if(isdigit(temp.op1[0]))
						v.push_back("li.s $f0, " + temp.op1);
					else
						v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
					v.push_back("s.s $f0, 0($t5)");
				}
			}
			else{
				int x = getmem(temp.res);
				if(type[temp.res] == 'i'){
					if(isdigit(temp.op1[0]))
						v.push_back("li $t0, " + temp.op1);
					else
						v.push_back("lw $t0, " + to_hex(getmem(temp.op1)) + "($0)");
					v.push_back("sw $t0, " + to_hex(x) + "($0)");
				}
				else{
					if(isdigit(temp.op1[0]))
						v.push_back("li.s $f0, " + temp.op1);
					else
						v.push_back("l.s $f0, " + to_hex(getmem(temp.op1,'f')) + "($0)");
					v.push_back("s.s $f0, " + to_hex(x) + "($0)");
				}
			}
		}
		if(temp.opcode == "+") {
			int x = getmem(temp.res);
			if(type[temp.res] == 'i'){
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("add $v0, $t0, $t1");
				v.push_back("sw $v0, " + to_hex(x) + "($0)");
			}
			else{
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("add.s $f3, $f0, $f1");
				v.push_back("s.s $f3, " + to_hex(x) + "($0)");
			}
		}
		if(temp.opcode == "-") {
			int x = getmem(temp.res);
			if(type[temp.res] == 'i'){
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("sub $v0, $t0, $t1");
				v.push_back("sw $v0, " + to_hex(x) + "($0)");
			}
			else{
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("sub.s $f3, $f0, $f1");
				v.push_back("s.s $f3, " + to_hex(x) + "($0)");
			}
		}
		if(temp.opcode == "*") {
			int x = getmem(temp.res);
			if(type[temp.res] == 'i'){
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("mult $t0, $t1");
				v.push_back("mflo $v0");
				v.push_back("sw $v0, " + to_hex(x) + "($0)");
			}
			else{
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("mul.s $f3, $f0, $f1");
				v.push_back("s.s $f3, " + to_hex(x) + "($0)");
			}
		}
		if(temp.opcode == "/") {
			int x = getmem(temp.res);
			if(type[temp.res] == 'i'){
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("div $t0, $t1");
				v.push_back("mflo $v0");
				v.push_back("sw $v0, " + to_hex(x) + "($0)");
			}
			else{
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("div.s $f3, $f0, $f1");
				v.push_back("s.s $f3, " + to_hex(x) + "($0)");
			}
		}
		if(temp.opcode == "ifF") {
			if(type[temp.op1] == 'i'){
				v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				v.push_back("beqz $t0, Label" + to_string(isLabel[quadlist[i].res]));
			}
			else{
				v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				v.push_back("li.s $f1, 0.0");
				v.push_back("c.eq.s $f0, $f1");
				v.push_back("bc1t Label" + to_string(isLabel[quadlist[i].res]));
			}
		}
		if(temp.opcode == "ifT") {
			if(type[temp.op1] == 'i'){
				v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				v.push_back("bnez $t0, Label" + to_string(isLabel[quadlist[i].res]));
			}
			else{
				v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				v.push_back("li.s $f1, 0.0");
				v.push_back("c.eq.s $f0, $f1");
				v.push_back("bc1f Label" + to_string(isLabel[quadlist[i].res]));
			}
		}
		if(temp.opcode == "<") {
			if(type[temp.op1] == 'i'){
				v.push_back("li $t2, 1");
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("blt $t0, $t1, Label" + to_string(labelidx));
				v.push_back("li $t2, 0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("sw $t2, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			else{
				v.push_back("li.s $f0, 1.0");
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("c.lt.s $f1, $f2");
				v.push_back("bc1t Label" + to_string(labelidx));
				v.push_back("li.s $f0, 0.0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("s.s $f0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			labelidx++;
		}
		if(temp.opcode == ">") {
			if(type[temp.op1] == 'i'){
				v.push_back("li $t2, 1");
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("bgt $t0, $t1, Label" + to_string(labelidx));
				v.push_back("li $t2, 0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("sw $t2, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			else{
				v.push_back("li.s $f0, 1.0");
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("c.lt.s $f2, $f1");
				v.push_back("bc1t Label" + to_string(labelidx));
				v.push_back("li.s $f0, 0.0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("s.s $f0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			labelidx++;
		}
		if(temp.opcode == "<=") {
			if(type[temp.op1] == 'i'){
				v.push_back("li $t2, 1");
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("ble $t0, $t1, Label" + to_string(labelidx));
				v.push_back("li $t2, 0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("sw $t2, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			else{
				v.push_back("li.s $f0, 1.0");
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("c.le.s $f1, $f2");
				v.push_back("bc1t Label" + to_string(labelidx));
				v.push_back("li.s $f0, 0.0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("s.s $f0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			labelidx++;
		}
		if(temp.opcode == ">=") {
			if(type[temp.op1] == 'i'){
				v.push_back("li $t2, 1");
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("bge $t0, $t1, Label" + to_string(labelidx));
				v.push_back("li $t2, 0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("sw $t2, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			else{
				v.push_back("li.s $f0, 1.0");
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("c.le.s $f2, $f1");
				v.push_back("bc1t Label" + to_string(labelidx));
				v.push_back("li.s $f0, 0.0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("s.s $f0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			labelidx++;
		}
		if(temp.opcode == "==") {
			if(type[temp.op1] == 'i'){
				v.push_back("li $t2, 1");
				if(isdigit(temp.op1[0]))
					v.push_back("li $t0, " + temp.op1);
				else
					v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li $t1, " + temp.op2);
				else
					v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("beq $t0, $t1, Label" + to_string(labelidx));
				v.push_back("li $t2, 0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("sw $t2, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			else{
				v.push_back("li.s $f0, 1.0");
				if(isdigit(temp.op1[0]))
					v.push_back("li.s $f0, " + temp.op1);
				else
					v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				if(isdigit(temp.op2[0]))
					v.push_back("li.s $f1, " + temp.op2);
				else
					v.push_back("l.s $f1, " + to_hex(mapmem[temp.op2]) + "($0)");
				v.push_back("c.eq.s $f1, $f2");
				v.push_back("bc1t Label" + to_string(labelidx));
				v.push_back("li.s $f0, 0.0");
				v.push_back("Label" + to_string(labelidx) + ":");
				v.push_back("s.s $f0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			labelidx++;
		}
		if(temp.opcode == "label") {
			v.push_back("Label" + to_string(labelidx) + ":");
			isLabel[temp.op1] = labelidx;
			funcArgs[temp.op1] = 
			labelidx++;
		}
		if(temp.opcode == "pop") {
			if(type[temp.res] == 'i'){
				v.push_back("lw $t0,($sp)");
				v.push_back("addi $sp, $sp, 4");
				v.push_back("sw $t0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
			else{
				v.push_back("l.s $f0,($sp)");
				v.push_back("addi $sp, $sp, 4");
				v.push_back("s.s $f0, " + to_hex(mapmem[temp.res]) + "($0)");
			}
		} //we can still access elements not on top
		if(temp.opcode == "push") {
			if(type[temp.op1] == 'i'){
				v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
				v.push_back("sub $sp, $sp, 4");
				v.push_back("sw $t0, ($sp)");
			}
			else{
				v.push_back("l.s $f0, " + to_hex(mapmem[temp.op1]) + "($0)");
				v.push_back("sub $sp, $sp, 4");
				v.push_back("s.s $f0, ($sp)");
			}
		}
		if(temp.opcode == "end") {
			v.push_back("jr $ra");
		}
		if(temp.opcode == "call") {
			v.push_back("jal Label" + to_string(isLabel[temp.op1]));
		}
		if((temp.opcode == "jmp") || (temp.opcode == "ljmp")) {
			v.push_back("j Label" + to_string(isLabel[quadlist[i].res]));
		}
		
	}
	//v.push_back("jr $ra");
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<endl;
	}

    return 0;
}
/* To display $t0
move $a0, $t0
li $v0, 1
syscall
*/
/* To display $f0
mov.s $f12, $f0
li $v0, 2
syscall
*/
