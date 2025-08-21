#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
		"KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
		"ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}
bool hasRightSyntax(string pollData) {
	
	//cout << pollData << endl;
	//cout << pollData.length() << endl;
	for (int x = 1; x+1 < pollData.length(); x++) {
		//cout << "through" << endl;
		if (isdigit(pollData.at(x)) && !isdigit(pollData.at(x - 1)) && !isdigit(pollData.at(x + 1))) {
			pollData.insert(x, "0"); // mmakes all vote numbers two digits long so that I can use % to check what type of character I should be looking for
		}
	}
	//cout << "done" << endl;
	//cout << pollData << endl;
	if (pollData.length() % 5 != 0 || pollData.length() == 0) { // checks if poll data snippets are not in groups of 5 (which they should be after adding a 0 in front of single digit vode codes)
		return false;
	}
	for (int x = 0; x+1 < pollData.length(); x++) {
		if (x % 5 == 0) {
			if (!isalpha(pollData.at(x))) { //checks if the party code is a letter in alphabet
				//cout << x << 'a' << endl;
				return false;
			}
		}else if ((x - 1) % 5 == 0) {
			if (!isdigit(pollData.at(x)) && !isdigit(pollData.at(x + 1))) { // checks if the vote digits are numbers
				//cout << x<<'d'<<endl;
				return false;
			}
		}else if ((x - 3) % 5 == 0) {//checks if the state code is a real state code
			string stateCode = "";
			stateCode += toupper(pollData.at(x));
			stateCode+= toupper(pollData.at(x + 1));
			//cout << stateCode << endl;
			
			if (!isValidUppercaseStateCode(stateCode)) {
				//cout << x<<'c'<<endl;
				return false;
			}
		}

	}
	return true;
}

int computeVotes(string pollData, char party, int& voteCount) {
	for (int x = 1; x+1 < pollData.length(); x++) {
		if (isdigit(pollData.at(x)) && !isdigit(pollData.at(x - 1)) && !isdigit(pollData.at(x + 1))) {
			pollData.insert(x, "0"); // mmakes all vote numbers two digits long so that I can use % to check what type of character I should be looking for
		}
	}
	if (!hasRightSyntax(pollData)) {
		//cout << "syntax" << endl;
		return 1;
	}
	for (int x = 0; x < pollData.length(); x++) {
		if ((x - 1) % 5 == 0) {
			string num = "";
			num += pollData.at(x);
			num += pollData.at(x + 1);
			if (stoi(num) == 0) {
				//cout << "0" << endl;
				return 2;
			}
		}
	}
	if (!isalpha(party)) {
		//cout << "party" << endl;
		return 3;
	}
	char currentParty = toupper(pollData.at(0));
	voteCount = 0; // sets vote count to zero if the data given will yield valid results
	for (int x = 0; x < pollData.length(); x++) {
		if (x % 5 == 0) {
			currentParty = toupper(pollData.at(x));
		}
		else if ((x - 1) % 5 == 0 && currentParty == toupper(party)) {
			string num = "";
			num += pollData.at(x);
			num += pollData.at(x + 1);
			voteCount += stoi(num);
			//cout << voteCount<<endl;
		}
	}
	return 0;
}
int main()
{
	int votes;
	assert(hasRightSyntax("R40TXD54CAr6Msd28nYL06UT"));//checks success
	assert(!hasRightSyntax(""));//checks empty string failure
	assert(!hasRightSyntax("R40TXD5CaAr6Msd28nYL06UT"));//checks poll data length failure
	assert(!hasRightSyntax("4R0MXD54CAr6Msd28nYL06UT"));//checks state code failure
	assert(!hasRightSyntax("R40TX154CAr6Msd28nYL06UT"));//checks party code failure
	assert(!hasRightSyntax("eawiuasdnkfjaweni232423wjkafnkwj")); //random string check
	votes = 25;
	assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'd', votes) == 0 && votes == 82); // successful case and ensures vote code gets set to zero before calculations
	votes = -999;
	assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'Q', votes) == 0 && votes == 0); // party code never matches
	votes = -999;// so we can detect whether computeVotes sets votes
	assert(computeVotes("R40TX3242", '%', votes) == 1 && votes == -999); // incorrect syntax
	votes = -999;// so we can detect whether computeVotes sets votes
	assert(computeVotes("R40TXD54CAr0Msd28nYL06UT", 'D', votes) == 2 && votes == -999); // 0 vote code failure
	votes = -999;// so we can detect whether computeVotes sets votes
	assert(computeVotes("R40TXD54CA", '%', votes) == 3 && votes == -999);
	cout << "All tests succeeded" << endl;
}