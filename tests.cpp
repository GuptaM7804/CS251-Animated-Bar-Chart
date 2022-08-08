#include <iostream>
#include "barchartanimate.h"
using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarChartDefaultConstructor() {
	BarChart b;
    if (b.getFrame() != "") {
    	cout << "testBarChartDefaultConstructor: getFrame failed" << endl;
    	return false;
    } else if (b.getSize() != 0) {
    	cout << "testBarChartDefaultConstructor: getSize failed" << endl;
    	return false;
    } else if (b.addBar("no", 50, "no") != false) {
        cout << "testBarChartDefaultConstructor: addBar failed" << endl;
    	return false;
    }
    cout << "testBarChartDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarChartParamConstructor() {
    BarChart b(4);
    if (b.getSize() != 0) {
    	cout << "testBarChartNumParamConstructor: getSizeWithoutAdd failed" << endl;
    	return false;
    }
    b.addBar("Chicago", 9234324, "US");
    b.addBar("New York", 9078725, "US");
    b.addBar("California", 9928984, "US");
    b.addBar("Delhi", 9328124, "India");
    if (b.getSize() != 4) {
    	cout << "testBarChartNumParamConstructor: getSizeAfterAdd failed" << endl;
    	return false;
    } else if (b.addBar("no", 50, "no") != false) {
        cout << "testBarChartNumParamConstructor: addBar failed" << endl;
    }
    BarChart a(b);
    if (a.getSize() != 4) {
    	cout << "testBarChartCopyParamConstructor: getSizeAdd failed" << endl;
    	return false;
    } else if (a.addBar("no", 50, "no") != false) {
        cout << "testBarChartNumParamConstructor: addBar failed" << endl;
    }
    for (int i = 0; i < a.getSize(); i++) {
        if (a[i].getName() != b[i].getName()) {
        	cout << "testBarChartCopyParamConstructor: CopyParamConstructor failed" << endl;
        	return false;
        } else if (a[i].getValue() != b[i].getValue()) {
        	cout << "testBarChartCopyParamConstructor: CopyParamConstructor failed" << endl;
        	return false;
        } else if (a[i].getCategory() != b[i].getCategory()) {
        	cout << "testBarChartCopyParamConstructor: CopyParamConstructor failed" << endl;
        	return false;
        }
    }
    stringstream agraph, bgraph, adump, bdump;
    map<string, string> colorMap;
    colorMap["US"] = RED;
    colorMap["India"] = BLUE;
    a.graph(agraph, colorMap, 4);
    b.graph(bgraph, colorMap, 4);
    a.dump(adump);
    b.dump(bdump);
    if (agraph.str() != bgraph.str()) {
        cout << "testBarChartCopyParamConstructor: GraphCopyConstructorTest failed" << endl;
        return false;
    } else if (adump.str() != bdump.str()) {
        cout << "testBarChartCopyParamConstructor: DumpCopyConstructorTest failed" << endl;
        return false;
    }
    cout << "testBarChartParamConstructor: all passed!" << endl;
    return true;
}

bool testBarChartCopyOperator() {
    BarChart b(4);
    if (b.getSize() != 0) {
    	cout << "testBarChartNumParamConstructor: getSizeWithoutAdd failed" << endl;
    	return false;
    }
    b.addBar("Chicago", 9234324, "US");
    b.addBar("New York", 9078725, "US");
    b.addBar("California", 9928984, "US");
    b.addBar("Delhi", 9328124, "India");
    if (b.getSize() != 4) {
    	cout << "testBarChartNumParamConstructor: getSizeAfterAdd failed" << endl;
    	return false;
    } else if (b.addBar("no", 50, "no") != false) {
        cout << "testBarChartNumParamConstructor: addBar failed" << endl;
    }
    BarChart c = b;
    if (c.getSize() != 4) {
    	cout << "testBarChartCopyParamConstructor: getSizeAdd failed" << endl;
    	return false;
    } else if (c.addBar("no", 50, "no") != false) {
        cout << "testBarChartNumParamConstructor: addBar failed" << endl;
    }
    for (int i = 0; i < c.getSize(); i++) {
        if (c[i].getName() != b[i].getName()) {
        	cout << "testBarChartCopyOperator: CopyOperator failed" << endl;
        	return false;
        } else if (c[i].getValue() != b[i].getValue()) {
        	cout << "testBarChartCopyOperator: CopyOperator failed" << endl;
        	return false;
        } else if (c[i].getCategory() != b[i].getCategory()) {
        	cout << "testBarChartCopyOperator: CopyOperator failed" << endl;
        	return false;
        }
    }
    stringstream bgraph, cgraph, bdump, cdump;
    map<string, string> colorMap;
    colorMap["US"] = RED;
    colorMap["India"] = BLUE;
    b.graph(bgraph, colorMap, 4);
    c.graph(cgraph, colorMap, 4);
    b.dump(bdump);
    c.dump(cdump);
    if (bgraph.str() != cgraph.str()) {
        cout << "testBarChartCopyOperator: GraphCopyOperatorTest failed" << endl;
        return false;
    } else if (bdump.str() != cdump.str()) {
        cout << "testBarChartCopyOperator: DumpCopyOperatorTest failed" << endl;
        return false;
    }
    cout << "testBarChartCopyOperator: all passed!" << endl;
    return true;
}

bool testBarChartSetFrame() {
    BarChart b;
    b.setFrame("1950");
    if (b.getFrame() != "1950") {
        cout << "testBarChartSetFrame: getFrame failed" << endl;
    	return false;
    }
    BarChart a(b);
    if (a.getFrame() != "1950") {
        cout << "testBarChartSetFrame: getFrameCopyConst failed" << endl;
    	return false;
    }
    BarChart c = b;
    if (c.getFrame() != "1950") {
        cout << "testBarChartSetFrame: getFrameCopyOp failed" << endl;
    	return false;
    }
    cout << "testBarChartSetFrame: all passed!" << endl;
    return true;
}

bool testBarChartComplexTest() {
    BarChart b(4);
    b.setFrame("1950");
    b.addBar("Chicago", 9234324, "US");
    b.addBar("New York", 9078725, "US");
    b.addBar("California", 9928984, "US");
    b.addBar("Delhi", 9328124, "India");
    BarChart a(b);
    BarChart c = b;
    for (int i = 0; i < b.getSize(); i++) {
        if (c[i].getName() != a[i].getName()) {
        	cout << "testBarChartComplexTest: NameComplexTest failed" << endl;
        	return false;
        } else if (c[i].getValue() != a[i].getValue()) {
        	cout << "testBarChartComplexTest: ValueComplexTest failed" << endl;
        	return false;
        } else if (c[i].getCategory() != a[i].getCategory()) {
        	cout << "testBarChartComplexTest: CategoryComplexTest failed" << endl;
        	return false;
        }
    }
    if (a.getFrame() != c.getFrame()) {
    	cout << "testBarChartComplexTest: FrameComplexTest failed" << endl;
    }
    stringstream agraph, cgraph, adump, cdump;
    map<string, string> colorMap;
    colorMap["US"] = RED;
    colorMap["India"] = BLUE;
    a.graph(agraph, colorMap, 4);
    c.graph(cgraph, colorMap, 4);
    a.dump(adump);
    c.dump(cdump);
    if (agraph.str() != cgraph.str()) {
        cout << "testBarChartComplexTest: GraphComplexTest failed" << endl;
        return false;
    } else if (adump.str() != cdump.str()) {
        cout << "testBarChartComplexTest: DumpComplexTest failed" << endl;
        return false;
    }
    cout << "testBarChartComplexTest: all passed!" << endl;
    return true;
}

bool testBarChartClear() {
    BarChart b(4);
    b.setFrame("1950");
    b.addBar("Chicago", 9234324, "US");
    b.addBar("New York", 9078725, "US");
    b.addBar("California", 9928984, "US");
    b.addBar("Delhi", 9328124, "India");
    BarChart a(b);
    BarChart c = b;
    b.clear();
    a.clear();
    c.clear();
    if (b.getFrame() != "") {
    	cout << "testBarChartClear: getFrame failed" << endl;
    	return false;
    } else if (b.getSize() != 0) {
    	cout << "testBarChartClear: getSize failed" << endl;
    	return false;
    } else if (b.addBar("no", 50, "no") != false) {
        cout << "testBarChartClear: addBar failed" << endl;
    	return false;
    } else if (a.getFrame() != "") {
    	cout << "testBarChartClear: getFrame failed" << endl;
    	return false;
    } else if (a.getSize() != 0) {
    	cout << "testBarChartClear: getSize failed" << endl;
    	return false;
    } else if (a.addBar("no", 50, "no") != false) {
        cout << "testBarChartClear: addBar failed" << endl;
    	return false;
    } else if (c.getFrame() != "") {
    	cout << "testBarChartClear: getFrame failed" << endl;
    	return false;
    } else if (c.getSize() != 0) {
    	cout << "testBarChartClear: getSize failed" << endl;
    	return false;
    } else if (c.addBar("no", 50, "no") != false) {
        cout << "testBarChartClear: addBar failed" << endl;
    	return false;
    }
    cout << "testBarChartClear: all passed!" << endl;
    return true;
}

bool testBarChartAnimateConstructor() {
    string title = "TestTitle";
    string xlabel = "TestXlabel";
    string source = "Manav";
    BarChartAnimate bca(title, xlabel, source);
    if (bca.getSize() != 0) {
    	cout << "testBarCharAnimateConstructor: getSize failed" << endl;
    	return false;
    }
    for (int i = 0; i < bca.getSize(); i++) {
        if (bca[i].getFrame() != "") {
        	cout << "testBarCharAnimateConstructor: getSize failed" << endl;
        	return false;
        } else if (bca[i].getSize() != 0) {
        	cout << "testBarChartDefaultConstructor: getSize failed" << endl;
        	return false;
        } else if (bca[i].addBar("no", 50, "no") != false) {
            cout << "testBarChartDefaultConstructor: addBar failed" << endl;
        	return false;
        }
    }
    cout << "testBarCharAnimateConstructor: all passed!" << endl;
    return true;
}

void createFile(ofstream &outFile) {
	outFile << "title: MINE" << endl;
	outFile << "xlabel: xx" << endl;
	outFile << "source: ME" << endl;
	outFile << endl;
	outFile << "4" << endl;
	outFile << "MINE1,Manav,no,500,India" << endl;
	outFile << "MINE1,Isabel,no,400,Spain" << endl;
	outFile << "MINE1,Will,no,300,Australia" << endl;
	outFile << "MINE1,Sajal,no,600,India" << endl;
	outFile << endl;
	outFile << "4" << endl;
	outFile << "MINE2,Manav,no,550,India" << endl;
	outFile << "MINE2,Isabel,no,450,Spain" << endl;
	outFile << "MINE2,Will,no,350,Australia" << endl;
	outFile << "MINE2,Sajal,no,650,India" << endl;
	outFile << endl;
	outFile << "4" << endl;
	outFile << "MINE3,Manav,no,450,India" << endl;
	outFile << "MINE3,Isabel,no,350,Spain" << endl;
	outFile << "MINE3,Will,no,400,Australia" << endl;
	outFile << "MINE3,Sajal,no,600,India" << endl;
	outFile << endl;
	outFile << "4" << endl;
	outFile << "MINE4,Manav,no,500,India" << endl;
	outFile << "MINE4,Isabel,no,550,Spain" << endl;
	outFile << "MINE4,Will,no,550,Australia" << endl;
	outFile << "MINE4,Sajal,no,400,India" << endl;
	outFile << endl;
	outFile << "4" << endl;
	outFile << "MINE5,Manav,no,640,India" << endl;
	outFile << "MINE5,Isabel,no,650,Spain" << endl;
	outFile << "MINE5,Will,no,600,Australia" << endl;
	outFile << "MINE5,Sajal,no,610,India" << endl;
}

bool testBarChartAnimateAddFrame() {
	string filename = "mine.txt";
	ofstream outFile(filename);
	createFile(outFile);
	ifstream inFile(filename);
    string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);
	BarChartAnimate bca(title, xlabel, source);
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
	BarChart b(4);
	b.addBar("Manav", 500, "India");
	b.addBar("Isabel", 400, "Spain");
	b.addBar("Will", 300, "Australia");
	b.addBar("Sajal", 600, "India");
	b.setFrame("MINE1");
	BarChart a(4);
	a.addBar("Manav", 640, "India");
	a.addBar("Isabel", 650, "Spain");
	a.addBar("Will", 600, "Australia");
	a.addBar("Sajal", 610, "India");
	a.setFrame("MINE5");
	stringstream ss, expected, ss2, expected2;
	bca[0].dump(ss);
	b.dump(expected);
	bca[4].dump(ss2);
	a.dump(expected2);
	if (ss.str() != expected.str()) {
	    cout << "testBarChartAnimateAddFrame: addFrame failed" << endl;
	    return false;
	} else if (ss2.str() != expected2.str()) {
	    cout << "testBarChartAnimateAddFrame: addFrame(IncreaseBarChartAnimateSize) failed" << endl;
	    return false;
	}
	cout << "testBarChartAnimateAddFrame: all passed!" << endl;
	return true;
}

int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
	testBarDefaultConstructor();
	testBarChartParamConstructor();
	testBarChartCopyOperator();
	testBarChartSetFrame();
	testBarChartComplexTest();
	testBarChartClear();
	testBarChartAnimateConstructor();
	testBarChartAnimateAddFrame();
    return 0;
}
