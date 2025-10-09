#include "SIB1.h"
#include "asn_application.h"
#include "per_encoder.h"
#include "cellinfo_init.h"
#include <vector>
#include <cstring>
#include <cstdio>
#include <stdint.h>
#include <iostream>
using namespace std;

static int cpp_collector(const void* buffer, size_t size, void* app_key)
{
	vector<uint8_t>* output_vector = static_cast<vector<uint8_t>*>(app_key);
	if(!output_vector)
		return -1;
	const uint8_t* data = static_cast<const uint8_t*>(buffer);
	output_vector->insert(output_vector->end(), data, data + size);
	return 0;
}
static bool initialize_sib1(SIB1_t* sib1)
{
	CellAccessRelatedInfo_t* cell_info = initialize_cell_access_related_info();
	if(!cell_info) {
		cout << "Failed to initialize CellAccessRelatedInfo" << endl;
		return false;
	}
	memcpy(&sib1->cellAccessRelatedInfo, cell_info, sizeof(CellAccessRelatedInfo_t));
	free(cell_info);
	return true;
}
vector<uint8_t> perEncoder()
{
	vector<uint8_t> encoded_data;
	SIB1_t* sib1 = static_cast<SIB1_t*>(calloc(1, sizeof(SIB1_t)));
	if(!sib1) {
		cout << "Memory allocation failed for SIB1_t" << endl;
		return encoded_data;
	}
	if(!initialize_sib1(sib1)) {
		free(sib1);
		return encoded_data;
	}
	asn_enc_rval_t enc_rval = uper_encode(&asn_DEF_SIB1, sib1, cpp_collector, &encoded_data);

	if(enc_rval.encoded == -1) {
		cout << "Error: Encoding failed at " << (enc_rval.failed_type ? enc_rval.failed_type->name : "unknown") << endl;
	}
	else {
		cout << "Successfully encoded " << enc_rval.encoded << " bits (" << (enc_rval.encoded + 7) / 8 << " bytes)"
		     << endl;
	}
	ASN_STRUCT_FREE(asn_DEF_SIB1, sib1);
	return encoded_data;
}
