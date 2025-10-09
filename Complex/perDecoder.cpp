#include "SIB1.h"
#include "per_decoder.h"
#include "asn_application.h"
#include <vector>
#include <iomanip>
#include <ios>
#include <cstring>
#include <stdint.h>
#include <iostream>
using namespace std;

// Функция для печати PLMN информации (в MATLAB console)
void PrintPlmnInfo(const PLMN_IdentityInfo_t* plmn_info)
{ // принимает указатель на структуру
	if(!plmn_info)
		return;

	cout << "PLMN Identity Info:" << endl;

	// PLMN Identity List
	for(size_t i = 0; i < plmn_info->plmn_IdentityList.list.count; i++) {
		const PLMN_Identity_t* plmn = plmn_info->plmn_IdentityList.list.array[i]; // см. A_SET_OF.h

		// MCC
		if(plmn->mcc) {
			cout << "MCC:" << endl;
			for(size_t j = 0; j < plmn->mcc->list.count; j++) {
				long* digit = (long*)plmn->mcc->list.array[j];
				if(digit) {
					cout << *digit;
				}
				else {
					cout << "?";
				}
			}
			cout << endl;
		}

		// MNC
		cout << "MNC: " << endl;
		for(size_t j = 0; j < plmn->mnc.list.count; j++) {
			long* digit = (long*)plmn->mnc.list.array[j];
			if(digit) {
				cout << *digit;
			}
			else {
				cout << "?";
			}
		}
		cout << endl;
	}

	// Cell Identity
	cout << "Cell Identity (hex): " << endl;
	for(size_t i = 0; i < plmn_info->cellIdentity.size; i++) { // см.BIT_STRING.h
		cout << hex << uppercase << setw(2) << setfill('0')
		     << static_cast<unsigned int>(plmn_info->cellIdentity.buf[i]);
	}
	cout << endl;

	// cellReservedForOperatorUse
	cout << "Cell Reserved For Operator Use: " << endl;
	switch(plmn_info->cellReservedForOperatorUse) {
	case 0: // Или константа, соответствующая reserved
		cout << "Reserved" << endl;
		break;
	case 1: // Или константа, соответствующая notReserved
		cout << "Not Reserved" << endl;
		break;
	default:
		cout << "Unknown (" << plmn_info->cellReservedForOperatorUse << ")" << endl;
		break;
	}
}

void perDecoder(const vector<uint8_t>& InputData)
{
	SIB1_t* sib1 = NULL;
	asn_dec_rval_t rval;

	if(InputData.empty()) {
		cout << "Error: Input data is empty" << endl;
		return;
	}

	rval = uper_decode_complete(NULL, &asn_DEF_SIB1, (void**)&sib1, InputData.data(),
	                            InputData.size()); // см. per_decoder.h

	if(rval.code == RC_OK && sib1) { // декодирование успешно и sib1 не NULL
		cout << "=== Decoding successful ===" << endl;

		// Вывод информации о cellAccessRelatedInfo
		if(sib1->cellAccessRelatedInfo.plmn_IdentityInfoList.list.count > 0) {
			cout << "PLMN Identity Info List:" << endl;
			for(size_t i = 0; i < sib1->cellAccessRelatedInfo.plmn_IdentityInfoList.list.count; i++) {
				PrintPlmnInfo(sib1->cellAccessRelatedInfo.plmn_IdentityInfoList.list.array[i]); // вызов
			}
		}
		else {
			cout << "No PLMN Identity Info found" << endl;
		}
	}
	else {
		cout << "Decoding failed" << endl;
	}

	ASN_STRUCT_FREE(asn_DEF_SIB1, sib1);
}